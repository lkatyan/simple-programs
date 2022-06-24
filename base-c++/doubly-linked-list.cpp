// ���������� ����������� ������

#include <iostream>
using namespace std;

class Link
{
public: int dData; // ������
		Link* next; // ��������� ������� � ������
		Link* previous; // ���������� ������� � ������
		Link(int d) // �����������
		{ dData = d; }
		void displayLink() // ����� ����������� ��������
		{ cout<<dData<<" "; }
};

class DoublyLinkedList
{
private: Link* first; // ������ �� ������ ������� ������
		 Link* last; // ������ �� ��������� �������
public: DoublyLinkedList() // �����������
{
	first = NULL; // ������ ���� �� �������� ���������
	last = NULL;
}
		bool isEmpty() // true, ���� ������ ����
		{ return first == NULL; }
		void insertFirst(int dd) // ������� �������� � ������ ������
		{
			Link* newLink = new Link(dd);
			if (isEmpty()) last = newLink; // newLink <� last
			else first->previous = newLink; // newLink <� ������ �������� first
			newLink->next = first; // newLink �> ������ �������� first
			first = newLink; // first �> newLink
		}
		void insertLast(int dd) // ������� � ����� ������
		{
			Link* newLink = new Link(dd);
			if (isEmpty()) first = newLink;
			else {
				last->next = newLink; // ������ �������� last �> newLink
				newLink->previous = last;} // ������ �������� last <� newLink
			last = newLink; // newLink <� last
		}
		Link* deleteFirst() // �������� ������� ��������
		{ // (��������������, ��� ������ �� ����)
			Link* temp = first;
			if (first->next == NULL) // ���� ������ ���� �������
				last = NULL; // null <� last
			else first->next->previous = NULL; // null <� ������ �������� next
			first = first->next; // first �> ������ �������� next
			return temp;
		}
		Link* deleteLast() // �������� ���������� ��������
		{ // (��������������, ��� ������ �� ����)
			Link* temp = last;
			if (first->next == NULL) // ���� ������ ���� �������
				first = NULL; // first �> null
			else last->previous->next = NULL; // ������ �������� previous �> null
			last = last->previous; // ������ �������� previous <� last
			return temp;
		}
		// ������� dd � ������� ����� key
		bool insertAfter(int key, int dd)
		{ // (��������������, ��� ������ �� ����)
			Link* current = first; // �� ������ ������
			while (current->dData != key) // ���� �� ����� ������� ����������
			{
				current = current->next; // ������� � ���������� ��������
				if (current == NULL) return false; // ���� �� ������
			}
			Link* newLink = new Link(dd); // �������� ������ ��������
			if (current == last) // ��� ���������� �������� ������
			{
				newLink->next = NULL; // newLink �> null
				last = newLink; // newLink <� last
			}
			else // �� ��������� �������
			{
				newLink->next = current->next; // newLink �> ������ �������� next
				// newLink <� ������ �������� next
				current->next->previous = newLink;
			}
			newLink->previous = current; // ������ �������� current <� newLink
			current->next = newLink; // ������ �������� current �> newLink
			return true; // ���� ������, ������� ���������
		}
		Link* deleteKey(int key) // �������� �������� � �������� ������
		{ // (��������������, ��� ������ �� ����)
			Link* current = first; // �� ������ ������
			while (current->dData != key) // ���� �� ����� ������� ����������
			{
				current = current->next; // ������� � ���������� ��������
				if (current == NULL) return NULL; // ���� �� ������
			}
			if (current == first) // ���� ������; ��� ������ �������?
				first = current->next; // first �> ������ �������� next
			else // �� ������ �������
			// ������ �������� previous �> ������ �������� next
				current->previous->next = current->next;
			if (current == last) // ��������� �������?
				last = current->previous; // ������ �������� previous <� last
			else // �� ��������� �������
			// ������ �������� previous <� ������ �������� next
				current->next->previous = current->previous;
			return current; // ����������� ���������� ��������
		}
		void displayForward()
		{
			cout<<"List (first-->last): ";
			Link* current = first; // �� ������ ������
			while (current != NULL) // ����������� �� ����� ������
			{ current->displayLink();// ����� ������
			  current = current->next; // ������� � ���������� ��������
			}
		}
		void displayBackward()
		{
			cout<<"List (last-->first): ";
			Link* current = last; // �� ������ ������
			while (current != NULL) // ����������� �� ����� ������
			{	current->displayLink(); // ����� ������
				current = current->previous; // ������� � ����. ��������
			}
		}

};

int main()
{ // �������� ������ ������
	DoublyLinkedList* theList = new DoublyLinkedList();
	for (int i = -50;i <= 50;i++)theList->insertLast(i);
	theList->insertFirst(22); // ������� � ������
	theList->insertLast(11); // ������� � �����
	theList->displayForward(); // ����� � ������ �����������
	system("pause");
	return 0;
}