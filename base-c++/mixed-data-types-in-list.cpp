// Реализация контейнера, хранящего разные типы данных

#include <iostream>
#include <Windows.h>
#include <utility>
#include <string>
using namespace std;

class Dannue {
public:
	int Int;
	string String;
	bool Bool;
	float Float;
	struct pair<string, int> p;
	Dannue* next;
	void printN() {
		if (Int != NULL) cout << Int;
		if (String != "") cout << String;
		if (Bool == true || Bool == false) {
			if (Bool) cout << "true";
			if (!Bool) cout << "false";
		}
		if (Float != NULL) cout << Float;
		if (p.first != "" && p.second != NULL) cout << p.first << "---" << p.second;
		cout << endl;
	}
};

class Conteiner 
{
public:
	Dannue* first; 
	Dannue* last; 
	Conteiner() { 
		first = NULL; last = NULL;
	}
	bool isEmpty() { return (first == NULL); }
	void deleteFirst()
	{ 
		if (first->next == NULL)
			last = NULL;
		first = first->next;
	}
	void print()
	{
		Dannue* current = first;
		while (current != NULL) 
		{
			current->printN(); 
			current = current->next; 
		}
	}
	void push1() {
		int t; cout << "vvedite int - "; cin >> t;
		Dannue* node = new Dannue();
		if (isEmpty()) first = node;
		else last->next = node;
		last = node; node->Int = t;
	}
	void push2() {
		string t; cout << "vvedite string - "; cin >> t; 
		Dannue* node = new Dannue();
		if (isEmpty()) first = node;
		else last->next = node;
		last = node; node->String = t;
	}
	void push3() {
		bool t; cout << "vvedite bool - 0 or 1 "<<endl; cin >> t; 
		Dannue* node = new Dannue();
		if (isEmpty()) first = node;
		else last->next = node;
		last = node; 
		if (t == 1) node->Bool = true;
		else node->Bool = false;
	}	
	void push4() {
		float t; cout << "vvedite float - "; cin >> t; 
		Dannue* node = new Dannue();
		if (isEmpty()) first = node;
		else last->next = node;
		last = node; node->Float = t;
	}	
	void push5() {
		string t; int t2; cout << "push first - string - "; cin >> t; cout << "push second - int - "; cin >> t2;
		Dannue* node = new Dannue();
		if (isEmpty()) first = node;
		else last->next = node;
		last = node; node->p.first = t; node->p.second = t2;
	}
	int veubor() {
		cout << "Содержание контейнера:" << endl;
		print(); cout << endl;
		cout << "Добавить элемент" << endl;
		cout << "1:push int" << endl;
		cout << "2:push string" << endl;
		cout << "3:push bool" << endl;
		cout << "4:push float" << endl;
		cout << "5:push struct pair" << endl;
		cout << "Удалить элемент" << endl;
		cout << "6:delete first" << endl;
		int i; cin >> i;
		system("cls");
		return i;
	}
};
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Conteiner l;
	while (true)
	{
		switch (l.veubor())
		{
		case 1: l.push1(); break;
		case 2: l.push2(); break;
		case 3: l.push3(); break;
		case 4: l.push4(); break;
		case 5: l.push5(); break;
		case 6: l.deleteFirst(); break;
		default: "Введите верно!";
		}
		system("cls");
	}
	system("pause");
	return 0;
}
