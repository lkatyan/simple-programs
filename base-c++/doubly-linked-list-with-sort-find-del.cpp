// Реализация 2-стороннего списка с итератором
// +сортировка вставками, удаление дубликатов и поиск полным перебором

#include <iostream>
using namespace std;
struct Link
{
	int data;
	Link *prev, *next;
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
	Link *left, *right;
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
	void removedub(iterator p)
	{
		Link *left2 = p.y();
		while (left2 != right->prev) {
			Link* del = left2->next;
			left2->next = del->next;
			del->next->prev = left2;
			delete del;
		}
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
iterator unique(iterator first, iterator last)
{
	iterator prev = first, next = ++first;
	while (next != last) if (*prev++ != *next++)*first++ = *next;
	return --first;
}
template <class iterator>
int find(iterator first, iterator last) {
	int num = 0;
	while (first != last) {
		num += 1;
		if (*first == 4) return num;
		first++;
	}
	return 0;
}
template <class iterator>
iterator maxAl(iterator first, iterator last) {
	iterator max = first;
	while (first != last) { if (*first > *max) max = first;  first++; }
	return max;
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
	List l, l2;
	for (int i = 0; i < 9; i++) l.insertFirst(i); //l.insertFirst(-67); //l.insertFirst(-23);
	for (int i = 0; i < 9; i++) l.insertFirst(i); l.insertFirst(-17); //l.insertFirst(-45);
	cout << "Список:" << endl;
	l.print();
	cout << "Переместить во второй список все элементы, находящиеся после элемента с максимальным значением:" << endl;
	ww(maxAl(l.begin(), l.end()), l.end(), l2);
	l2.print();
	insertion(l.begin(), l.end());
	cout << "Отсортированный:" << endl;
	l.print();
	l.removedub(unique(l.begin(), l.end()));
	cout << "Удаление дубликатов:" << endl;
	l.print();
	int w = find(l.begin(), l.end());
	if (w == 0) cout << "Эл-т не найден" << endl;
	else cout << "Порядковый номер элемента 4: " << w << endl;
	system("pause");
	return 0;
}
