// Реализация двусвязного списка

#include <iostream>
using namespace std;

class Link
{
public: int dData; // Данные
		Link* next; // Следующий элемент в списке
		Link* previous; // Предыдущий элемент в списке
		Link(int d) // Конструктор
		{ dData = d; }
		void displayLink() // Вывод содержимого элемента
		{ cout<<dData<<" "; }
};

class DoublyLinkedList
{
private: Link* first; // Ссылка на первый элемент списка
		 Link* last; // Ссылка на последний элемент
public: DoublyLinkedList() // Конструктор
{
	first = NULL; // Список пока не содержит элементов
	last = NULL;
}
		bool isEmpty() // true, если список пуст
		{ return first == NULL; }
		void insertFirst(int dd) // Вставка элемента в начало списка
		{
			Link* newLink = new Link(dd);
			if (isEmpty()) last = newLink; // newLink <— last
			else first->previous = newLink; // newLink <— старое значение first
			newLink->next = first; // newLink —> старое значение first
			first = newLink; // first —> newLink
		}
		void insertLast(int dd) // элемент в конец списка
		{
			Link* newLink = new Link(dd);
			if (isEmpty()) first = newLink;
			else {
				last->next = newLink; // старое значение last —> newLink
				newLink->previous = last;} // старое значение last <— newLink
			last = newLink; // newLink <— last
		}
		Link* deleteFirst() // Удаление первого элемента
		{ // (предполагается, что список не пуст)
			Link* temp = first;
			if (first->next == NULL) // Если только один элемент
				last = NULL; // null <— last
			else first->next->previous = NULL; // null <— старое значение next
			first = first->next; // first —> старое значение next
			return temp;
		}
		Link* deleteLast() // Удаление последнего элемента
		{ // (предполагается, что список не пуст)
			Link* temp = last;
			if (first->next == NULL) // Если только один элемент
				first = NULL; // first —> null
			else last->previous->next = NULL; // старое значение previous —> null
			last = last->previous; // старое значение previous <— last
			return temp;
		}
		// Вставка dd в позицию после key
		bool insertAfter(int key, int dd)
		{ // (предполагается, что список не пуст)
			Link* current = first; // От начала списка
			while (current->dData != key) // Пока не будет найдено совпадение
			{
				current = current->next; // Переход к следующему элементу
				if (current == NULL) return false; // Ключ не найден
			}
			Link* newLink = new Link(dd); // Создание нового элемента
			if (current == last) // Для последнего элемента списка
			{
				newLink->next = NULL; // newLink —> null
				last = newLink; // newLink <— last
			}
			else // Не последний элемент
			{
				newLink->next = current->next; // newLink —> старое значение next
				// newLink <— старое значение next
				current->next->previous = newLink;
			}
			newLink->previous = current; // старое значение current <— newLink
			current->next = newLink; // старое значение current —> newLink
			return true; // Ключ найден, вставка выполнена
		}
		Link* deleteKey(int key) // Удаление элемента с заданным ключом
		{ // (предполагается, что список не пуст)
			Link* current = first; // От начала списка
			while (current->dData != key) // Пока не будет найдено совпадение
			{
				current = current->next; // Переход к следующему элементу
				if (current == NULL) return NULL; // Ключ не найден
			}
			if (current == first) // Ключ найден; это первый элемент?
				first = current->next; // first —> старое значение next
			else // Не первый элемент
			// старое значение previous —> старое значение next
				current->previous->next = current->next;
			if (current == last) // Последний элемент?
				last = current->previous; // старое значение previous <— last
			else // Не последний элемент
			// Старое значение previous <— старое значение next
				current->next->previous = current->previous;
			return current; // Возвращение удаленного элемента
		}
		void displayForward()
		{
			cout<<"List (first-->last): ";
			Link* current = first; // От начала списка
			while (current != NULL) // Перемещение до конца списка
			{ current->displayLink();// Вывод данных
			  current = current->next; // Переход к следующему элементу
			}
		}
		void displayBackward()
		{
			cout<<"List (last-->first): ";
			Link* current = last; // От начала списка
			while (current != NULL) // Перемещение до конца списка
			{	current->displayLink(); // Вывод данных
				current = current->previous; // Переход к след. элементу
			}
		}

};

int main()
{ // Создание нового списка
	DoublyLinkedList* theList = new DoublyLinkedList();
	for (int i = -50;i <= 50;i++)theList->insertLast(i);
	theList->insertFirst(22); // Вставка в начале
	theList->insertLast(11); // Вставка в конце
	theList->displayForward(); // Вывод в прямом направлении
	system("pause");
	return 0;
}