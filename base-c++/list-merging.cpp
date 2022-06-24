// Реализация слияния списков: 
// Создание двух списков, сортировка, слияние в третий список, сортировка

#include <iostream>
using namespace std;
struct Link
{
	int data;
	Link* prev, * next;
	Link(int N)
	{
		data = N;
		next = prev = 0;
	}
	Link() { next = prev = 0; }
	void print() { cout << data << ' '; }
};
struct List
{
	Link* left, * right;
	List()
	{
		left = new Link;
		right = new Link;
		left->next = right;
		right->prev = left;
	}
	struct iterator
	{
		Link* i;
		iterator() : i(0) {} //конструктор по умолчанию; инициализация //нулевым указателем
		iterator(Link* lnk) : i(lnk) {} //инициализация адресом узла
		iterator& operator=(const iterator& it) { i = it.i; return *this; }
		//приравниваем значение другого итератора;
		int& operator*() { return i->data; }//разыменование итератора
		bool operator ==(const iterator& it) { return i == it.i; }
		bool operator !=(const iterator& it) { return i != it.i; }
		iterator& operator ++() { i = i->next; return *this; }//инкрементируем адрес, возвращаем итератор по ссылке
		iterator operator ++(int) { Link* lnk = i; i = i->next; return lnk; }
		iterator& operator --() { i = i->prev; return *this; }//декрементируем адрес, возвращаем итератор по ссылке
		iterator operator --(int) { Link* lnk = i; i = i->prev; return lnk; }
		Link* y() { return i; }
	};
	iterator begin() { return iterator(left->next); }
	iterator end() { return iterator(right); }
	void insertFirst(int N)
	{
		Link* newLink = new Link(N);
		newLink->next = left->next;
		left->next->prev = newLink;
		newLink->prev = left;
		left->next = newLink;
	}
	int removeFirst()
	{
		Link* del = left->next;
		int temp = del->data;
		left->next = del->next;
		del->next->prev = left;
		delete del;
		return temp;
	}
	void print()
	{
		for (Link* l = left->next; l != right; l = l->next)
			l->print();
		cout << endl;
	}
};
template <class iterator>
void insertion(iterator first, iterator last)
{
	iterator out = first, in, prev;
	int temp;
	while (++out != last)
	{
		temp = *out;
		in = prev = out;
		while (in != first && *--prev > temp) *in-- = *prev;
		*in = temp;
	}
}
template <class iterator>
void ww(iterator first, iterator last, List h) {
	last--;
	while (last != first) h.insertFirst(*last--);
	h.insertFirst(*last);
}
int main()
{
	setlocale(0, "");
	List l, l2, l3;
	for (int i = 0; i < 9; i++) l.insertFirst(rand() % 33);
	for (int i = 0; i < 9; i++) l2.insertFirst(rand() % 33);
	cout << "Список 1:" << endl;
	l.print();
	cout << "Список 2:" << endl;
	l2.print();

	insertion(l.begin(), l.end());
	cout << "Отсортированный 1:" << endl;
	l.print();
	insertion(l2.begin(), l2.end());
	cout << "Отсортированный 2:" << endl;
	l2.print();
	cout << "Слияние:" << endl;
	ww(l.begin(), l.end(), l3);
	ww(l2.begin(), l2.end(), l3);
	insertion(l3.begin(), l3.end());
	l3.print();
	system("pause");
	return 0;
}
