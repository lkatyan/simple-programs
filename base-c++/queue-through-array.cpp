// ���������� ������� ����� ������
// +������ ������� ������� � ���������� �������� � ��������� �������

#include<iostream>
#include<conio.h>
using namespace std;

class Queue
{
private: 
	int maxSize;
	int* queArray;
	int front, rear, nItems;
public: 
	Queue(int s) // �����������
	{
		maxSize = s;
		queArray = new int[maxSize];
		front = 0;
		rear = -1;
		nItems = 0;
	}
	void insert(int j) // ������� �������� � ����� �������
	{ 
		if (!isFull()) {
			if (rear == maxSize - 1) // ����������� �������
				rear = -1;
			queArray[++rear] = j;
			nItems++;
		} 
	}
	int remove() // ���������� �������� � ������ �������
	{ 
		if (!isEmpty()) {
			if (front == maxSize) // ����������� �������
				front = 0;
			int temp = queArray[front++];
			nItems--;
			return temp;
		}
	}
	int change(int p) // ������ �������� � ������ �������
	{
		int tem = queArray[front];
		queArray[front] = p;
		return tem;
	}
	void changeEnd(int r) // ������ �������� � ����� �������
	{ 
		queArray[rear] = r;
	}
	int peekFront() // ������ �������� � ������ �������
	{
		return queArray[front];
	}
	int peekRear() // ������ �������� � ����� �������
	{
		return queArray[rear];
	}
	bool isEmpty() // true, ���� ������� �����
	{
		return (nItems == 0);
	}
	bool isFull() // true, ���� ������� ���������
	{
		return (nItems == maxSize);
	}
	int size() // ���������� ��������� � �������
	{
		return nItems;
	}
	void www(Queue y) //�������� ������� ������ � ��������� ��������
	{
	int p = y.peekRear(); //������� � �����
	int a = y.change(p); //������ � ������ � ����������� �������
	y.changeEnd(a); //������ ���������� �� ������
	}
};

int main(){
	Queue theQueue = Queue(101); // ������� �� 101 ������
	for (int i=-50; i<=50; i+=1) theQueue.insert(i); // ������� ��������� �� -50 �� 50
	theQueue.www(theQueue); //�������� ������� ������ � ��������� ��������
	while (!theQueue.isEmpty()) // ���������� � �����
	{
		int n = theQueue.remove();
		cout<<n<<"	";
	}
	cout<<"";
	system ("pause");
	return 0;
}