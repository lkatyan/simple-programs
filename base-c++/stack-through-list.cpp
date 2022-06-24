// Реализация стека через список
// +создание второго стека с положительными элементами первого стека

#include <iostream>
#include <conio.h>
using namespace std;
struct Link {
	int data;
	Link* next;
	Link* first;
	Link(int n) {
		data = n;
		next = 0;
	}
	int List() {
		first = 0;
	}
};
struct List {
	Link* first;
	int q;
	void push(int v) {
		Link *newLink = new Link(v);
		newLink->next = first;
		first = newLink;
	}
	void pop() {
		Link* temp = first;
		first = first->next;
		delete temp;
	}
	int peek() {
		Link* temp = first;
		int t = temp->data;
		return t;
	}
	void print() {
		Link* l = first;
		cout << l->data << " ";
		for (Link* l = first; l->first > l->next; l = l->next) {
			cout << l->next->data << " ";
		}
	}
	void reset(List* y, int q) {
		for (int i = 0; i < q; i++)
			y->pop();
	}
	int ttt(List* r, List* r2) { //Вставка во 2-ой стек положительных эл-в 1-ого
		for (int i = -50; i <= 50; i++) {
			int w = r->peek();
			if (w > 0) {
				r2->push(w);
				q += 1;
			}
			r->pop();
		}
		return q;
	}
	void vstavka(List* p) {
		for (int i = -50; i <= 50; i++) {
			p->push(i);
		}
	}
};

int main() {
	List *stk = new List;
	List *stk2 = new List;
	stk->vstavka(stk);
	stk->print();
	int q=stk->ttt(stk, stk2); //Вставка во 2-ой стек положительных эл-в 1-ого
	cout << endl << "New stack: " << endl;
	stk2->print();
	stk2->reset(stk2, q);
	system("pause");
	return 0;
}