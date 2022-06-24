// Реализация очереди через 2-сторонний список
// +замена местами первого и последнего элемента в созданной очереди

#include<iostream>
using namespace std;

class Link
{
public:
	int dData; // Данные
	Link* next;
	Link(int d) // Конструктор
	{ dData = d; }
	void displayLink() { cout << dData << " "; } // Вывод содержимого элемента
};

class FirstLastList
{
private:
	Link* first; // Ссылка на первый элемент
	Link* last; // Ссылка на последний элемент
public:
	FirstLastList() { // Конструктор
		first = NULL; last = NULL; } // Список пока не содержит элементов
	bool isEmpty() { return (first == NULL); } // true, если список пуст
	void insertLast(int dd) // Вставка элемента в конец списка
	{
		Link* newLink = new Link(dd); // Создание нового элемента
		if (isEmpty()) first = newLink;
		else last->next = newLink; // Next старого значения last --> newLink
		last = newLink;
	}
	int deleteFirst() // Удаление первого элемента
	{ // (предполагается, что список не пуст)
		int temp = first->dData;
		if (first->next == NULL) // Сохранение ссылки
			last = NULL; // null <-- last
		first = first->next; // first --> старое значение next
		return temp;
	}
	void displayList()
	{
		Link* current = first; // От начала списка
		while (current != NULL) // Пока не конец списка
		{
			current->displayLink(); // Вывод данных
			current = current->next; // Переход к следующему элементу
		}
		cout << "";
	}
	void ChangeF(int e)	{ first->dData = e; } // Изменить первый
	void ChangeL(int s) { last->dData = s; } // Изменить последний
	int ReadLast() { return (last->dData); }
	int ReadFirst()	{ return (first->dData); }
};

class LinkQueue
{
private: FirstLastList theList;
public:
	LinkQueue() // Конструктор
	{ FirstLastList* theList = new FirstLastList(); } // Создание 2-стороннего списка
	bool isEmpty() { return theList.isEmpty(); } // true, если очередь пуста
	void insert(int j) { theList.insertLast(j); } // Вставка элемента в конец очереди
	int remove() { return theList.deleteFirst(); } // Удаление элемента в начале очереди
	void displayQueue()	{ theList.displayList(); }
	void ChangeFirst(int r)	{ theList.ChangeF(r); } // Замена элемента в начале очереди
	void ChangeLast(int d) { theList.ChangeL(d); } // Замена элемента в конце очереди
	int First() { return theList.ReadFirst(); } // Чтение первого
	int Last() { return theList.ReadLast(); } // Чтение последнего
	void www(LinkQueue q) //Меняются местами первый и последний элементы
	{
		int c = q.First(); int v = q.Last();
		q.ChangeFirst(v); q.ChangeLast(c);
	}
};

int main() {
	LinkQueue theQueue = LinkQueue(); // Очередь
	for (int i = -50; i <= 50; i += 1) theQueue.insert(i); // Вставка элементов от -50 до 50
	theQueue.www(theQueue); //Меняются местами первый и последний элементы
	theQueue.displayQueue(); //Вывод
	while (!theQueue.isEmpty())	{ theQueue.remove(); } // Удаление
	cout << "";
	system("pause");
	return 0;
}
