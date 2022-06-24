// Реализация очереди через массив
// +замена местами первого и последнего элемента в созданной очереди

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
	Queue(int s) // Конструктор
	{
		maxSize = s;
		queArray = new int[maxSize];
		front = 0;
		rear = -1;
		nItems = 0;
	}
	void insert(int j) // Вставка элемента в конец очереди
	{ 
		if (!isFull()) {
			if (rear == maxSize - 1) // Циклический перенос
				rear = -1;
			queArray[++rear] = j;
			nItems++;
		} 
	}
	int remove() // Извлечение элемента в начале очереди
	{ 
		if (!isEmpty()) {
			if (front == maxSize) // Циклический перенос
				front = 0;
			int temp = queArray[front++];
			nItems--;
			return temp;
		}
	}
	int change(int p) // Замена элемента в начале очереди
	{
		int tem = queArray[front];
		queArray[front] = p;
		return tem;
	}
	void changeEnd(int r) // Замена элемента в конце очереди
	{ 
		queArray[rear] = r;
	}
	int peekFront() // Чтение элемента в начале очереди
	{
		return queArray[front];
	}
	int peekRear() // Чтение элемента в конце очереди
	{
		return queArray[rear];
	}
	bool isEmpty() // true, если очередь пуста
	{
		return (nItems == 0);
	}
	bool isFull() // true, если очередь заполнена
	{
		return (nItems == maxSize);
	}
	int size() // Количество элементов в очереди
	{
		return nItems;
	}
	void www(Queue y) //Меняются местами первый и последний элементы
	{
	int p = y.peekRear(); //Элемент с конца
	int a = y.change(p); //Замена с первым и возвращение первого
	y.changeEnd(a); //Замена последнего на первый
	}
};

int main(){
	Queue theQueue = Queue(101); // Очередь из 101 ячейки
	for (int i=-50; i<=50; i+=1) theQueue.insert(i); // Вставка элементов от -50 до 50
	theQueue.www(theQueue); //Меняются местами первый и последний элементы
	while (!theQueue.isEmpty()) // Извлечение и вывод
	{
		int n = theQueue.remove();
		cout<<n<<"	";
	}
	cout<<"";
	system ("pause");
	return 0;
}