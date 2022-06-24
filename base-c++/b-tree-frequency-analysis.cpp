// Программа читает текстовый файл, строит бинарное дерево слов (в ячейке хранится 
// слово и кол-во его повторений в тексте) и выводит 10 слов
// с наивысшей частотой встречаемости. 

#include <fstream>
#include <iostream>
#include <string>
#include <cctype> //needed for ispunct()
#include <map>
#include <iterator>
using namespace std;
class Node {
public:
	string Data;
	int k;
	Node* leftChild;
	Node* rightChild;
	Node(string N)
	{
		Data = N;
		k = 1;
		leftChild = rightChild = 0;
	}
	Node(int N, string L)
	{
		Data = L;
		k = N;
		leftChild = rightChild = 0;
	}
	void displayNode()
	{
		cout << Data << " (" << k << ") ";
	}
};
class Tree {
public:
	Node* root;
	Tree() : root(0) {}
	bool find(string d) {
		Node* current = root;
		while (current->Data != d)
		{
			if (d < current->Data)
				current = current->leftChild;
			else
				current = current->rightChild;
			if (current == NULL)
				return true;
		}
		current->k++;
		return false;
	}
	void insert(string d)
	{
		Node* newNode = new Node(d);
		if (root == NULL)
			root = newNode;
		else
		{
			if (find(d))
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

map <int, string> q;
void l(Node* r)
{
	if (!r) return;
	l(r->leftChild);
	q.insert(pair <int,string> (r->k, r->Data));
	l(r->rightChild);
}
void printdeque() {
	int i = 0;
	for (auto it = q.rbegin(); it != q.rend(); ++it)
	{
		if (i <= 10) {
			cout << it->second << " " << it->first << endl;
			i++;
		}
	}
}
void ll() { l(root); printdeque(); }
};

int main()
{

	setlocale(0, "");
	Tree t;
	ifstream file;
	//ofstream f;
	//f.open("d:\\p.txt");
	file.open("d:\\pp.txt");
	string s;
	for (file >> s; !file.eof(); file >> s)
	{
		s.erase(remove_if(s.begin(),
			s.end(),
			[](unsigned char c) { return ispunct(c); }),
			s.end());
		string digits("0123456789");
		size_t index;
		while ((index = s.find_first_of(digits)) != string::npos)
			s.erase(index, 1);
		t.insert(s);
		//f << s << endl;
		s = "";
	}
	//f.close();
	file.close();
	t.print();
	t.ll();
	t.deltree();
	system("pause");
	return 0;
}