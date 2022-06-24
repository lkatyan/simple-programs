// Реализация вектора
// +чтение текста из файла, запись в вектор и частотный анализ слов 

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
using namespace std;

template <class T>
class Vector
{
private:
	T *arr;
	int size;
	int N;
	int left;
	int right;
public:
	Vector() {
		size = 1;
		N = -1;
		arr = new T[size];
		left = 0;
	}
	~Vector() {
		cout << "CRASH OF FILE" << endl;
		delete[] arr;
	}
	void push_back(T value)	{
			if (isFull()) {
				T* temp = arr;
				arr = new T[size *= 2];
				for (int i = 0; i <= N; i++)
					arr[i] = temp[i];
				delete[] temp;
			}
			arr[++N] = value;
	}
	void sortq(T* ar, int N) {
		int i = 0, j = N;
		T temp, p;
		p = ar[N >> 2];
		do {
			while (ar[i] < p) i++;
			while (ar[j] > p) j--;
			if (i <= j) {
				temp = ar[i]; ar[i] = ar[j]; ar[j] = temp;
				i++; j--;
			}
		} while (i <= j);
		if (j > 0) sortq(ar, j);
		if (N > i) sortq(ar + i, N - i);
	}

	void print() {
		cout << "--------" << endl;
		cout << "Вывод вектора: " << endl;
		cout << "--------" << endl;
		for (int i = 0; i < N + 1; i++)
			cout << arr[i] << endl;
	}
	void print_sort() {
		sortq(arr, N);
		cout << "--------" << endl;
		cout << "Вывод отсортированного вектора: " << endl;
		cout << "--------" << endl;
		for (int i = 0; i < N + 1; i++)
			cout << arr[i] << endl;
	}

	bool isFull() { return N == size - 1; }
	bool isEmpty() { return N == -1; }

	void load()	{
		string file = "11.txt";
		ifstream fin;//создание объекта класса ifstream
		fin.open(file);//открытие файла
		if (!fin.is_open())	{ //открыт ли файл
			cout << "ФАЙЛ НЕ ОТКРЫЛСЯ" << endl;;
		}
		else {
			cout << "ФАЙЛ ОТКРЫЛСЯ" << endl;
			T str;
			cout << "--------" << endl;
			cout << "Содержимое файла: " << endl;
			cout << "--------" << endl;
			while (!fin.eof()) { //достигнут ли конец файла
				str = "";
				getline(fin, str, ' '); //чтение из fin до ' ' и запись в str
				cout << str << endl;
				for (int i = 0; i < str.length(); i++)
					if (str[i] == ',' || str[i] == '?' || str[i] == '!' || str[i] == '.')
						str.erase(i); //удаление
				push_back(str); //добавление в вектор
			}
		}
		fin.close();
	}
	void show_table() {
		int count = 0;
		T* y; int r = -1, kolvo = 0;
		y = new T[100];
		cout << "--------" << endl;
		cout << "Частотный анализ: " << endl;
		cout << "--------" << endl;
		for (int i = 0; i < N + 1; i++)	{
			T word = arr[i];
			for (int j = 0; j < N + 1; j++)
				if (word == arr[j]) count++;
			if (count==1) cout << word << " " << count << endl;

			if (count > 1) { y[++r] = word; kolvo += 1; }

			count = 0;
		}
		for (int i = 0; i < kolvo; i++) {
			T word = y[i];
			for (int j = 0; j < N + 1; j++)
				if (word == arr[j]) count++;
			cout << word << " " << count << endl;
			i += count - 1;
			count = 0;
		}
	}
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Vector <string> v;
	v.load();
	v.print();
	v.print_sort();
	v.show_table();
	system("pause");
	return 0;
}
