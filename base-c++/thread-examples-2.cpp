// Реализация простых примеров по работе с потоками

#include <iostream>
#include <list>
#include <mutex>
#include <algorithm>
#include <thread> 
#include <iterator>
#include <exception>
#include <memory>
#include <stack>
#include <map>
#include <shared_mutex>

// Bызов мьютекса в функциях взаимоисключается
class FirstListing {
private:
	std::list<int> some_list;
	std::mutex some_mutex;
public:
	void add_to_list(int new_value)
	{
		std::lock_guard<std::mutex> guard(some_mutex);
		some_list.push_back(new_value);
	}
	bool list_contains(int value_to_find)
	{
		std::lock_guard<std::mutex> guard(some_mutex);
		if (std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end()) { std::cout << value_to_find << " "; return true; }
		else return false;
	}
	void print() { copy(some_list.begin(), some_list.end(), std::ostream_iterator<int>(std::cout, " ")); }
};
void first() {
	std::cout << "FirstListing\n";
	FirstListing first;
	std::thread thread1(&FirstListing::add_to_list, &first, 1);
	std::thread thread2(&FirstListing::list_contains, &first, 1);
	thread1.join();
	thread2.join();
	first.print();
	std::cout << std::endl;
}

// Передача ссылки на неразрешeнные данные
class some_data
{
private:
	int a;
	std::string b;
public:
	void do_something() { std::cout << "222\n"; }
};
class data_wrapper
{
private:
	some_data data;
	std::mutex m;
public:
	template<typename Function>
	void process_data(Function func)
	{
		std::lock_guard<std::mutex> guard(m);
		func(data);
	}
};
some_data* unprotected;
void malicious_function(some_data& protected_data)
{
	unprotected = &protected_data;
}
data_wrapper x;
void second()
{
	std::cout << "SecondListing\n";
	x.process_data(malicious_function);
	unprotected->do_something();
}

// Безопасная обертка вокрут стека 
// 1) Удаляемый элемент записывается в переданное по ссылке место 
// 2) Используется shared_ptr который возвращает указатель на удаляемый элемент 
struct empty_stack : std::exception
{
	const char* what() const throw();
};
template<typename T>
class threadsafe_stack
{
private:
	std::stack<T> data;
	mutable std::mutex m;
public:
	threadsafe_stack() {}
	threadsafe_stack(const threadsafe_stack& other)
	{
		std::lock_guard<std::mutex> lock(other.m);
		data = other.data;
	}
	threadsafe_stack& operator=(const threadsafe_stack&) = delete;
	void push(T new_value)
	{
		std::lock_guard<std::mutex> lock(m);
		data.push(new_value);
	}
	std::shared_ptr<T> pop()
	{
		std::lock_guard<std::mutex> lock(m);
		if (data.empty()) throw empty_stack();
		std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
		data.pop();
		return res;
	}
	void pop(T value)
	{
		std::lock_guard<std::mutex> lock(m);
		if (data.empty()) throw empty_stack();
		value = data.top();
		data.pop();
	}
	bool empty() const
	{
		std::lock_guard<std::mutex> lock(m);
		return data.empty();
	}
};
void third()
{
	int result=0;
	threadsafe_stack<int> st;
	st.push(3);	st.push(3);	st.push(3);
	//std::shared_ptr<int> res = st.pop();
	//std::cout << *res << std::endl;
	//st.pop(result);
	//std::cout << *res << std::endl;
}

// Захват нескольких мьютексов, чтобы избежать взаимоблокировки 
class some_big_object
{
public: int datas;
};
void swap(some_big_object& lhs, some_big_object& rhs);
class X
{
private:
	some_big_object some_detail;
	std::mutex m;
public:
	X(some_big_object const& sd) :some_detail(sd) {}
	friend void swap(X& lhs, X& rhs)
	{
		if (&lhs == &rhs) return;
		std::lock(lhs.m, rhs.m); // Захватываем два мьютекса, затем создаем для них экземпляры lock_guard
		std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock);
		std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);
		swap(lhs.some_detail, rhs.some_detail);
	}
};

// Гибка блокировка с помощью std::unique_lock 
class some_big_object2
{
public: int data2;
};
void swap2(some_big_object2& lhs2, some_big_object2& rhs2);
class X2
{
private:
	some_big_object2 some_detail2;
	std::mutex m2;
public:
	X2(some_big_object2 const& sd2) :some_detail2(sd2) {}
	friend void swap2(X2& lhs2, X2& rhs2)
	{
		if (&lhs2 == &rhs2) return;
		std::unique_lock<std::mutex> lock_a2(lhs2.m2, std::defer_lock); // Мьютексы не 
		std::unique_lock<std::mutex> lock_b2(rhs2.m2, std::defer_lock); // захвачены
		std::lock(lock_a2, lock_b2); // Мьютексы захватываются
		swap2(lhs2.some_detail2, rhs2.some_detail2);
	}
};

// Поочередный захват мьютексов в операторе сравнения
class Y
{
private:
	int some_detail9;
	mutable std::mutex m9;
	int get_detail9() const
	{
		std::lock_guard<std::mutex> lock_a9(m9);
		return some_detail9;
	}
public:
	Y(int sd9) :some_detail9(sd9) {}
	friend bool operator==(Y const& lhs9, Y const& rhs9)
	{
		if (&lhs9 == &rhs9) return true;
		int const lhs_value9 = lhs9.get_detail9();
		int const rhs_value9 = rhs9.get_detail9();
		return lhs_value9 == rhs_value9;
	}
};

int main()
{
	first();
	second();
	third();
	return 0;
}