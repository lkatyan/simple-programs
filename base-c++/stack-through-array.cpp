// Реализация стека через массив
// +создание второго стека с положительными элементами первого стека

#include <iostream>
#include <conio.h>
using namespace std;
struct Stack {
	int *a, top, n, w, t;
	Stack(int size) {
		n = size;
		a = new int[size];
		top = -1;
	}
	bool isFull() {
		return top == n - 1;
	}
	bool isEmpty() {
		return top == -1;
	}
	void push(int v) {
		if (!isFull())
			a[++top] = v;
	}
	void pop() {
		if (!isEmpty())
			top--;
	}
	int peek() {
		if (!isEmpty())
			w = a[top];
		return w;
	}
	void print() {
		while (top != -1) cout << a[top--] << endl;
		cout << endl;
	}
	void reset() {
		while (top != -1) top--;
	}
};

int main() {
	int n = 100, a[100], top = -1, t;
	Stack s1(100);
	Stack s2(100);
	for (int i = -50;i < n;i++) {
		s1.push(i);
	}
	//s1.print();
	for (int i = -50;i < n;i++) {
		t = s1.peek();
		s1.pop();
		if (t > 0) s2.push(t);
	}
	s2.print();
	s1.reset();
	s2.reset();

	system("pause");
	return 0;
}