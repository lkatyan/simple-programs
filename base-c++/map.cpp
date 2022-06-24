// Реализация словаря как бин.дерева пар ключ-значение

#include <iostream>
#include <string>
#include <windows.h>

using namespace std;
class Node {
public:
	string Data; string data2;
	Node* leftChild;
	Node* rightChild;
	Node(string N, string D)
	{
		Data = N; data2 = D;
		leftChild = rightChild = 0;
	}
	void displayNode()
	{
		cout << " " << Data << " ; " << data2 << endl;
	}
};
class Tree {
public:
	Node* root;
	Tree() : root(0) {}

	void insert(string d, string d2)
	{
		Node* newNode = new Node(d, d2);
		if (root == NULL)
			root = newNode;
		else
		{
			Node* current = root;
			Node* parent;
			while (true)
			{
				parent = current;
				if (d < current->Data)
				{
					current = current->leftChild;
					if (current == NULL)
					{
						parent->leftChild = newNode;
						return;
					}
				}
				else
				{
					current = current->rightChild;
					if (current == NULL)
					{
						parent->rightChild = newNode;
						return;
					}
				}
			}
		}
	}
	void find(string d) {
		Node* current = root;
		if (current == NULL)
			cout << "Словарь пуст" << endl;
		else
		{
			while (current->Data != d)
			{
				if (d < current->Data)
					current = current->leftChild;
				else
					current = current->rightChild;
				if (current == NULL)
					cout << "Ключ не найден" << endl;
			}
			cout << "Данные по ключу: " << current->data2 << endl;
		}
	}

	void recprint(Node* n)
	{
		if (!n)return;
		recprint(n->leftChild);
		n->displayNode();
		recprint(n->rightChild);
	}
	void print()
	{
		recprint(root);
		cout << endl;
	}
	bool delet(string key) {
		Node* current = root;
		Node* parent = root;
		bool isLeftChild = true;
		if (current == NULL)
			cout << "Словарь пуст" << endl;
		else
		{
			while (current->Data != key) {
				parent = current;
				if (key < current->Data) {
					isLeftChild = true;
					current = current->leftChild;
				}
				else {
					isLeftChild = false;
					current = current->rightChild;
				}
				if (current == NULL) return false;
			}

			if (current->leftChild == NULL && current->rightChild == NULL) {
				if (current == root) root = NULL;
				else if (isLeftChild) parent->leftChild = NULL;
				else parent->rightChild = NULL;
			}

			else if (current->rightChild == NULL) {
				if (current == root) root = current->leftChild;
				else if (isLeftChild) parent->leftChild = current->leftChild;
				else parent->rightChild = current->leftChild;
			}
			else if (current->leftChild == NULL) {
				if (current == root) root = current->rightChild;
				else if (isLeftChild) parent->leftChild = current->rightChild;
				else parent->rightChild = current->rightChild;
			}
			else {
				Node* successor = getSuccessor(current);
				if (current == root) root = successor;
				else if (isLeftChild) parent->leftChild = successor;
				else parent->rightChild = successor;
				successor->leftChild = current->leftChild;
			}
			delete current;
			cout << "Удалено!" << endl;
			return true;
		}
	}
	Node* getSuccessor(Node* delNode) {
		Node* successorParent = delNode;
		Node* successor = delNode;
		Node* current = delNode->rightChild;
		while (current != NULL) {
			successorParent = successor;
			successor = current;
			current = current->leftChild;
		}
		if (successor != delNode->rightChild) {
			successorParent->leftChild = successor->rightChild;
			successor->rightChild = delNode->rightChild;
		}
		return successor;
	}
	bool isEmpty() { return !root; }

	void dt(Node* root) {
		if (root != NULL) {
			dt(root->leftChild);
			dt(root->rightChild);
			delete(root);
			root = NULL;
		}
	}
	void deltree() { dt(root); }

	void push() {
		string t; string t2; 
		print();
		cout << "Введите ключ - ";
		cin >> t;
		cout << "Введите значение - ";
		cin >> t2; insert(t, t2);
	}
	void del() {
		string t; 
		print(); cout << "Введите ключ - ";
		cin >> t; delet(t); 
	}
	void f() {
		string t; print(); cout << "Введите ключ - ";
		cin >> t; find(t);
	}
	int veubor() {
		print();
		cout << "1:Добавить ключ,значение" << endl;
		cout << "2:Удалить ключ,значение" << endl;
		cout << "3:Найти значение по ключу" << endl;
		cout << "4: Выход" << endl;
		int i; cin >> i;
		system("cls");
		return i;
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Tree t;
	while (true)
	{
		switch (t.veubor())
		{
		case 1: t.push(); break;
		case 2: t.del(); break;
		case 3: t.f(); break;
		case 4: return 0;
		default: "Введите верно!";
		}
		system("pause");
		system("cls");
	}
	t.deltree();
	system("pause");
	return 0;
}

