// Реализация простых примеров по работе с потоками

#include <iostream>
#include <thread>
#include <cassert> // для assert();
#include <vector>
#include <algorithm>
#include <functional>

void do_something() {
	std::cout << "Hello World!\n";
}

void do_something_else() {
	std::cout << "\t\tHello World TOO!\n";
}

class background_task
{
public:
	void operator()() const
	{
		do_something();
		do_something_else();
	}
};

void do_something5(int& i) {
	std::cout << "\tHello World and birds!\n";
}
void func9(int i, std::string const& s)
{
	std::cout << i << "Hello World!\n";
}

struct func // есть ссылки на локальные переменные
{
	int& i;
	func(int& i_) : i(i_) {}
	void operator()()
	{
		for (unsigned j = 0; j < 3; ++j)
		{
			do_something5(i);
		}
	}
};

void five()
{
	int some_local_state = 0;
	func my_func(some_local_state);
	std::cout << "FIVE: ";
	std::thread my_thread5(my_func);
	// my_thread5.detach(); // отсоединяемся от потока и не ждем его завершения.
							// поток будет работать в фоновом режиме.
							// может привести к обращению к уничтоженной 
							// переменной do_something5(i).
	my_thread5.join();   // присоединяемся к потоку и ждем его завершения

}

void six() // поток завершается в любом случае (в т.ч. в случае ошибки)
{
	std::cout << "SIX: \t ";
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);
	try
	{
		do_something();
	}
	catch (...)
	{
		t.join();
		throw;
	}
	t.join();
}

class thread_guard { // Использование идиомы RAII для ожидания завершения потока 
	std::thread& t;
public:
	explicit thread_guard(std::thread& t_) : t(t_) {}
	~thread_guard()
	{
		if (t.joinable())
		{
			t.join();
		}
	}
	thread_guard(thread_guard const&) = delete;
	thread_guard& operator=(thread_guard const&) = delete;
};

void seven()
{
	std::cout << "SEVEN: \t ";
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);
	thread_guard g(t);
	do_something();
}

void nine(int some_param)
{
	char buffer[1024];
	sprintf_s(buffer, "&i", some_param);
	// std::thread t(func9, 9, buffer);
		// есть шансы, что выход из функции произойдет раньше, 
		// чем буфер будет преобразован к стринг в новом потоке
		// так как thread копирует переданные значения как есть
		// без преобразования к ожидаемому типу аргумента
	std::thread t(func9, 9, std::string(buffer));
	// преобразование к стринг до передачи потоку позволяет
	// избежать висячего указателя
	t.join();
}

void update_j(int i, int& j)
{
	j = i;
}
void ten(int i)
{
	int j = 0;
	//std::thread t(update_j, i, j);
		// функция ждет указатель на j, а thread передаст копию объекта j,
		// то есть j  не будет преобразован, 
		// решение=обернуть аргумент объектом ref
	std::thread t(update_j, i, std::ref(j));
	t.join();
	std::cout << j << "Hello World!\n";
}

class X
{
public: 
	void do_work(int i)
	{
		std::cout << i << "Hello!\n";
	}
};

class Big_object
{
public:
	int num = 0;
	Big_object() {}
	void prepare_data(int i) { num = i; }
	~Big_object() { std::cout << "12Bye\n"; }
};

void process_big_object(std::unique_ptr<Big_object> x)
{
	std::cout <<  x->num << "Hello ~~~ ";
}

std::thread t14_2() {	return std::thread(do_something_else); }
void f14(std::thread t14_1) { t14_1.join(); }
void func14()
{
	f14(std::thread(do_something));
	std::thread t14_3=t14_2();
	f14(std::move(t14_3));
}

class thread_guard2 { // Использование идиомы RAII для ожидания завершения потока 
	std::thread t;
public:
	explicit thread_guard2(std::thread t_) : t(std::move(t_)) 
	{
		if (!t.joinable())
			throw std::logic_error("No thread");
	}
	~thread_guard2()
	{
		t.join();
	}
	thread_guard2(thread_guard2 const&) = delete;
	thread_guard2& operator=(thread_guard2 const&) = delete;
};

void func15()
{
	int some_local_state = 0;
	func my_func2(some_local_state);
	thread_guard2 g((std::thread(my_func2)));
	do_something();
}

void func16()
{
	std::vector<std::thread> threads;
	for (int i = 0; i < 3; ++i)
	{
		threads.push_back(std::thread(do_something_else));
	}
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
}

int main()
{
	std::cout << "ONE: \t\t ";
	std::thread my_thread(do_something);
	my_thread.join();

	// объект-функция копируется в память потока
	// и оттуда вызывается
	std::cout << "TWO: \t\t ";
	background_task f;
	std::thread my_thread2(f);
	my_thread2.join();

	// передача временного объекта-функции.
	// нужны скобки чтобы компилятор не интерпретировал как объявление функции
	std::cout << "THREE_ONE: \t ";
	std::thread my_thread3_1((background_task()));
	my_thread3_1.join();
	std::cout << "THREE_TWO: \t ";
	std::thread my_thread3_2{ background_task() };
	my_thread3_2.join();

	// с помощью лямбда-выражений
	std::cout << "FOUR: \t\t ";
	std::thread my_thread4([] {
		do_something();
		do_something_else();
		});
	my_thread4.join();

	// 5 - в функции
	five();

	// ловим исключения
	six();

	// ждем завершения потока с помощью RAII - захват ресурса есть инициализация
	seven();

	// проверяем отсоединился ли поток
	std::cout << "EIGHT: \t\t ";
	std::thread t(do_something);
	t.detach();
	assert(!t.joinable()); // проверяет выражение, true-ничего не делает, 
						   // false-выводит сообщение об ошибке и завершает программу

	// преобразование передаваемого типа аргумента
	std::cout << "NINE: \t\t ";
	nine(9);

	// передача аргумента ссылкой
	std::cout << "TEN: \t\t ";
	ten(10);

	// в качестве функции передаем указатель на функцию-член, при условии, 
	// что в первом аргументе указатель на правильный объект
	std::cout << "11: \t\t ";
	X some_x;
	std::thread t11(&X::do_work, &some_x, 11);
	// вызывается some_x.do_work() в новом потоке, 
	// т.к. в качестве указателя на объект передан адрес some_x.
	// третий аргумент стал первым аргументом функции-члена и тд
	t11.join();

	// передача владения динамическим объектом потоку с помощью move()
	// -нужна, когда передаваемые аргументы нельзя копировать, только перемещать
	// в примере класс unique_ptr, на объект может указывать только один экземпляр класса, 
	// когда экзмепляр уничтожается, объект удаляется
	std::cout << "12: \t\t "; 
	std::unique_ptr<Big_object> object(new Big_object);
	object->prepare_data(12);
	std::thread t12(process_big_object, std::move(object));
	// владение объектом передается потоку, а затем функции
	t12.join();

	// передача владения потоком
	// (thread, как и unique_ptr, перемещаемый, а не копируемый) 
	std::cout << "13: \t\t ";
	std::thread t13_1(do_something);
	std::thread t13_2 = std::move(t13_1);   // явная передача владения 
	t13_1 = std::thread(do_something_else); // неявная передача владения от временного объекта thread к t13_1 
	std::thread t13_3;
	t13_3 = std::move(t13_2);
	t13_1.join(); t13_3.join(); // к t13_2 не присоединен поток, вызывать join было бы ошибкой

	// владение можно передать при возврате объекта thread из функции
	// аналогично можно передать владение внутрь функции
	std::cout << "14: \t\t ";
	func14();

	// передача владения потоком объекту thread_guard, модификация прошлого класса thread_guard
	std::cout << "15: \t\t ";
	func15();

	// хранение объектов thread в контейнере при условии, что класс контейнера поддерживает перемещение
	// 1) статически:
	std::cout << "16: \t\t ";
	func16();
	// 2) динамически:
	// можно задавать количество потоков с помощью thread::hardware_concurrency()
	// Она возвращает число потоков, которые могут работать параллельно

	// получение индентификатора потока. тип: thread::id.
	// 1) функцией-членом get_id()
	// 2) функцией this_thread::get_id()
	// идентификаторы хранятся упорядочено, так же в стандартной библиотеке есть класс hash<thread::id>
}
