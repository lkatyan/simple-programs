// ���������� ����������� ������ ����� ��������

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

public: LinkList() // �����������
		{ first = NULL; } // ������ ���� �� �������� ���������

		Link* getFirst() // ��������� ������� ��������
		{ return first;	}

		void setFirst(Link* f) // ������������ ������ �������� first
		{ first = f; }

		bool isEmpty() // true, ���� ������ ����
		{ return first == NULL;	}

		void displayList()
		{
			Link* current = first; // �� ������ ������
			while (current != NULL) // ����������� �� ����� ������
			{
				current->displayLink(); // ����� �������� ��������
				current = current->next; // ������� � ���������� ��������
			}
		}
};

class ListIterator
{
private: Link* current; // ������� ������� ������
		 Link* previous; // ���������� ������� ������
		 LinkList* ourList; // ��������� ������

public: ListIterator(LinkList* list) // �����������
		{
			ourList = list;
			reset();
		}

		void reset() // ������� � 'first'
		{
			current = ourList->getFirst();
			previous = NULL;
		}
		bool atEnd() // true, ���� ������� �������� ��������� �������
		{ return (current->next == NULL); }

		void nextLink() // ������� � ���������� ��������
		{
			previous = current;
			current = current->next;
		}

		Link* getCurrent() // ��������� �������� ��������
		{ return current; }

		void insertAfter(int dd) // ������� ����� �������� ��������
		{
			Link* newLink = new Link(dd);
			if (ourList->isEmpty()) // ������ ������
			{
				ourList->setFirst(newLink);
				current = newLink;
			}
			else // ������ �� ����
			{
				newLink->next = current->next;
				current->next = newLink;
				nextLink(); // ������� � ������ ��������
			}
		}
		void insertBefore(int dd) // ������� ����� ������� ���������
		{
			Link* newLink = new Link(dd);
			if (previous == NULL)  // � ������ ������
			{					  // (��� ������ ������)
				newLink->next = ourList->getFirst();
				ourList->setFirst(newLink);
				reset();
			}
			else // �� � ������ ������
			{
				newLink->next = previous->next;
				previous->next = newLink;
				current = newLink;
			}
		}
		int deleteCurrent() // �������� �������� ��������
		{
			int value = current->dData;
			if (previous == NULL) // ���� � ������ ������
			{
				ourList->setFirst(current->next);
				reset();
			}
			else // �� � ������ ������
			{
				previous->next = current->next;
				if (atEnd()) reset();
				else current = current->next;
			}
			return value;
		}
};

int main() {
	LinkList* theList = new LinkList(); // �������� ������ 
	ListIterator* iter1 = new ListIterator(theList); // �������� ���������
	int value;
	iter1->insertAfter(20); // ������� ���������
	iter1->insertAfter(40);
	iter1->insertAfter(80);
	iter1->insertBefore(60);

	// ����� ������
	theList->displayList();
	system("pause");
	return 0;
}