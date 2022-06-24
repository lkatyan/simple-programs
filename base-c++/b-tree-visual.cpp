// Программа составляет бинарное дерево, читая слова из файла, 
// и отрисовывает его псевдографикой в консоли

#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <windows.h>

using namespace std;
class Node {
public:
	string Data;
	Node* leftChild;
	Node* rightChild;
	Node(string N)
	{
		Data = N;
		leftChild = rightChild = 0;
	}
	void displayNode()
	{
		cout << " " << Data << " ";
	}
};
class Tree {
public:
	Node* root;             
	Tree() : root(0) {}         
	
	void insert(string d)
	{
		Node* newNode = new Node(d);          
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
		return true;
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
	
	void displayTree() {
		stack <Node*> globalStack;
		globalStack.push(root);      
		int nBlanks = 32;      
		bool isRowEmpty = false;      
		while (isRowEmpty == false) {
			stack <Node*> localStack;         
			isRowEmpty = true;
			for (int j = 0; j < nBlanks; j++)
				cout << ' ';
			while (globalStack.empty() == false) {
				Node* temp = globalStack.top();
				globalStack.pop();
				if (temp != NULL) {
					cout << temp->Data;
					localStack.push(temp->leftChild);
					localStack.push(temp->rightChild);
					if (temp->leftChild != NULL || temp->rightChild != NULL)
						isRowEmpty = false;
				}
				else {
					cout << "--";
				localStack.push(NULL);               
				localStack.push(NULL); }            
				for (int j = 0; j < nBlanks * 2 - 2; j++)
					cout << ' ';
			}            
			cout<<endl;            
			nBlanks /= 2;           
			while (localStack.empty() == false) {
				globalStack.push(localStack.top());
				localStack.pop();
			}
		}         
	}
	void push() {
	string t; cout << "vvedite - ";
	cin >> t; insert(t); 
	}
	void del() {
		string t; cout << "vvedite - ";
		cin >> t; delet(t);
	}
	int veubor() {
		cout << "1:display tree" << endl;
		cout << "2:push string" << endl;
		cout << "3:delete string" << endl;
		cout << "4: Exit" << endl;
		int i; cin >> i;
		system("cls");
		return i;
	}
};

int main()
{
	//setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Tree t;
	ifstream file;
	file.open("d:\\kk.txt");
	string s;
	for (file >> s; !file.eof(); file >> s){
		t.insert(s);
	s = "";
	}
	file.close();
	//t.print();
	t.displayTree();
	while (true)
	{
		switch (t.veubor())
		{
		case 1: t.displayTree(); break;
		case 2: t.push(); break;
		case 3: t.del(); break;
		case 4: return 0;
		default: "Введите верно!";
		}
		system("pause");
		system("cls");
	}
	//t.displayTree();
	t.deltree();
	system("pause");
	return 0;
}
