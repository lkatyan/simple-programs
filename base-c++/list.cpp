// Реализация списка, хранящего эл-ты в одной области памяти, связь эл-в через индексы

#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;

template <class T>
class Lis
{
private:
	T* arr;
	int size;
	int N;
	int left;
	int right;
public:
	Lis() {
		size = 1;
		N = -1;
		arr = new T[size];
		left = 0;
	}
	~Lis() {
		cout << "CRASH spisok" << endl;
		delete[] arr;
	}
	void push_back(T value) {
		if (isFull()) {
			T* temp = arr;
			arr = new T[size *= 2];
			for (int i = 0; i <= N; i++)
				arr[i] = temp[i];
			delete[] temp;
		}
		arr[++N] = value;
	}
	void delet(T value) {
			T* temp = arr;
			arr = new T[size];
			int k = 0;
			for (int i = 0; i <= N; i++)
				if (temp[i] == value && k == 0)
					k++;
				else arr[i] = temp[i];
			delete[] temp;
	}

	void print() {
		cout << "----------------" << endl;
		cout << "Вывод списка: " << endl;
		cout << "----------------" << endl;
		for (int i = 0; i < N + 1; i++)
			cout << arr[i] << endl;
		cout << "----------------" << endl;
	}

	bool isFull() { return N == size - 1; }
	bool isEmpty() { return N == -1; }

	void push() {
		print();
		string t; cout << "vvedite - ";
		cin >> t; push_back(t);
	}
	void del() {
		print();
		string t; cout << "vvedite - ";
		cin >> t; delet(t);
	}
	int veubor() {
		print();
		cout << endl << "1:push string" << endl;
		cout << "2:delete string" << endl;
		cout << "3: Exit" << endl;
		int i; cin >> i;
		system("cls");
		return i;
	}
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Lis <string> lis;
	while (true)
	{
		switch (lis.veubor())
		{
		case 1: lis.push(); break;
		case 2: lis.del(); break;
		case 3: return 0;
		default: "Введите верно!";
		}
		system("pause");
		system("cls");
	}

	system("pause");
	return 0;
};