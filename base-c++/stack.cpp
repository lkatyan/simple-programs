#include <iostream>
	using namespace std;
	struct Link
	{
		int data;
		Link* next;
		Link(int n)
		{
			data = n;
			next = 0;
		}
		void print()
		{
			cout << data << endl;
		}
	};
	struct Stack
	{
		Link* top;
		Stack()
		{
			top = 0;
		}
		void push(int n)
		{
			Link* newLink = new Link(n);
			newLink->next = top;
			top = newLink;
		}
		int pop()
		{
			int temp = top->data;
			Link* del = top;
			top = top->next;
			delete del;
			return temp;
		}
		void print()
		{
			for (Link* l = top; l; l = l->next) l->print();
			cout << endl;
		}
	};
	using namespace std;
	int main()
	{
		Stack s1, s2;
		for (int i = 0; i < 10; i++) s1.push(i);
		s1.print();
		for (int i = 0; i < 5; i++) s2.push(s1.pop());
		s1.print();
		s2.print();
		system("pause");
		return 0;
	}
