// Реализация двусвязного списка через итератор

#include<iostream>
using namespace std;
class Link
{
public: int dData;
		Link* next;
		Link* last;
		Link(int dd) { dData = dd; }

		void displayLink() { cout << dData << " ";	}
};

class LinkList
{
private: Link* first;

public: LinkList() // Конструктор
		{ first = NULL; } // Список пока не содержит элементов

		Link* getFirst() // Получение первого элемента
		{ return first;	}

		void setFirst(Link* f) // Присваивание нового значения first
		{ first = f; }

		bool isEmpty() // true, если список пуст
		{ return first == NULL;	}

		void displayList()
		{
			Link* current = first; // От начала списка
			while (current != NULL) // Перемещение до конца списка
			{
				current->displayLink(); // Вывод текущего элемента
				current = current->next; // Переход к следующему элементу
			}
		}
};

class ListIterator
{
private: Link* current; // Текущий элемент списка
		 Link* previous; // Предыдущий элемент списка
		 LinkList* ourList; // Связанный список

public: ListIterator(LinkList* list) // Конструктор
		{
			ourList = list;
			reset();
		}

		void reset() // Возврат к 'first'
		{
			current = ourList->getFirst();
			previous = NULL;
		}
		bool atEnd() // true, если текущим является последний элемент
		{ return (current->next == NULL); }

		void nextLink() // Переход к следующему элементу
		{
			previous = current;
			current = current->next;
		}

		Link* getCurrent() // Получение текущего элемента
		{ return current; }

		void insertAfter(int dd) // Вставка после текущего элемента
		{
			Link* newLink = new Link(dd);
			if (ourList->isEmpty()) // Пустой список
			{
				ourList->setFirst(newLink);
				current = newLink;
			}
			else // Список не пуст
			{
				newLink->next = current->next;
				current->next = newLink;
				nextLink(); // Переход к новому элементу
			}
		}
		void insertBefore(int dd) // Вставка перед текущим элементом
		{
			Link* newLink = new Link(dd);
			if (previous == NULL)  // В начале списка
			{					  // (или пустой список)
				newLink->next = ourList->getFirst();
				ourList->setFirst(newLink);
				reset();
			}
			else // Не в начале списка
			{
				newLink->next = previous->next;
				previous->next = newLink;
				current = newLink;
			}
		}
		int deleteCurrent() // Удаление текущего элемента
		{
			int value = current->dData;
			if (previous == NULL) // Если в начале списка
			{
				ourList->setFirst(current->next);
				reset();
			}
			else // Не в начале списка
			{
				previous->next = current->next;
				if (atEnd()) reset();
				else current = current->next;
			}
			return value;
		}
};

int main() {
	LinkList* theList = new LinkList(); // Создание списка 
	ListIterator* iter1 = new ListIterator(theList); // Создание итератора
	int value;
	iter1->insertAfter(20); // Вставка элементов
	iter1->insertAfter(40);
	iter1->insertAfter(80);
	iter1->insertBefore(60);

	// Вывод списка
	theList->displayList();
	system("pause");
	return 0;
}