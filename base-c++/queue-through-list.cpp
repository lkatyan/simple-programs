// ���������� ������� ����� 2-��������� ������
// +������ ������� ������� � ���������� �������� � ��������� �������

#include<iostream>
using namespace std;

class Link
{
public:
	int dData; // ������
	Link* next;
	Link(int d) // �����������
	{ dData = d; }
	void displayLink() { cout << dData << " "; } // ����� ����������� ��������
};

class FirstLastList
{
private:
	Link* first; // ������ �� ������ �������
	Link* last; // ������ �� ��������� �������
public:
	FirstLastList() { // �����������
		first = NULL; last = NULL; } // ������ ���� �� �������� ���������
	bool isEmpty() { return (first == NULL); } // true, ���� ������ ����
	void insertLast(int dd) // ������� �������� � ����� ������
	{
		Link* newLink = new Link(dd); // �������� ������ ��������
		if (isEmpty()) first = newLink;
		else last->next = newLink; // Next ������� �������� last --> newLink
		last = newLink;
	}
	int deleteFirst() // �������� ������� ��������
	{ // (��������������, ��� ������ �� ����)
		int temp = first->dData;
		if (first->next == NULL) // ���������� ������
			last = NULL; // null <-- last
		first = first->next; // first --> ������ �������� next
		return temp;
	}
	void displayList()
	{
		Link* current = first; // �� ������ ������
		while (current != NULL) // ���� �� ����� ������
		{
			current->displayLink(); // ����� ������
			current = current->next; // ������� � ���������� ��������
		}
		cout << "";
	}
	void ChangeF(int e)	{ first->dData = e; } // �������� ������
	void ChangeL(int s) { last->dData = s; } // �������� ���������
	int ReadLast() { return (last->dData); }
	int ReadFirst()	{ return (first->dData); }
};

class LinkQueue
{
private: FirstLastList theList;
public:
	LinkQueue() // �����������
	{ FirstLastList* theList = new FirstLastList(); } // �������� 2-���������� ������
	bool isEmpty() { return theList.isEmpty(); } // true, ���� ������� �����
	void insert(int j) { theList.insertLast(j); } // ������� �������� � ����� �������
	int remove() { return theList.deleteFirst(); } // �������� �������� � ������ �������
	void displayQueue()	{ theList.displayList(); }
	void ChangeFirst(int r)	{ theList.ChangeF(r); } // ������ �������� � ������ �������
	void ChangeLast(int d) { theList.ChangeL(d); } // ������ �������� � ����� �������
	int First() { return theList.ReadFirst(); } // ������ �������
	int Last() { return theList.ReadLast(); } // ������ ����������
	void www(LinkQueue q) //�������� ������� ������ � ��������� ��������
	{
		int c = q.First(); int v = q.Last();
		q.ChangeFirst(v); q.ChangeLast(c);
	}
};

int main() {
	LinkQueue theQueue = LinkQueue(); // �������
	for (int i = -50; i <= 50; i += 1) theQueue.insert(i); // ������� ��������� �� -50 �� 50
	theQueue.www(theQueue); //�������� ������� ������ � ��������� ��������
	theQueue.displayQueue(); //�����
	while (!theQueue.isEmpty())	{ theQueue.remove(); } // ��������
	cout << "";
	system("pause");
	return 0;
}
