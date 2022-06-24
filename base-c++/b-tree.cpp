// ���������� ��������� ������
// +������� ������� ������ � ����� ��������

#include <iostream>
#include <stack>
#include <vector>
using namespace std;
class Node {
public: int Data;                  // ������ 
		Node* leftChild;
		Node* rightChild; // ������ � ����� ������� ����   
		Node(int N)
		{
			Data = N;
			leftChild = rightChild = 0;
		}
	 void displayNode()            // ����� ����      
	{
		 cout << " " << Data << " ";
	 }
};
class Tree {
public:
	Node* root;             // first node of tree
	Tree() : root(0) {} // ����������� // ���� ��� �� ������ ����          
	int find(int d) {
		Node* current = root;                // ������ � ��������� ����      
		while (current->Data != d)         // ���� �� ������� ����������         
		{
			if (d < current->Data)          // ��������� ������?            
				current = current->leftChild;
			else                             // ��� �������?
				current = current->rightChild;
			if (current == NULL)             // ���� ������� ���,            
				return NULL;                 // ����� ���������� ��������         
		}
		return current->Data;                    // ������� ������      
	}
	void insert(int d)
	{
		Node* newNode = new Node(d);    // �������� ������ ����      
		//newNode->Data = d;           // ������� ������     
		if (root == NULL)                // �������� ���� �� ����������         
			root = newNode;
		else                          // �������� ���� �����         
		{
			Node* current = root;       // ������ � ��������� ����         
			Node* parent;
			while (true)                // (���������� ����� �� �����)            
			{
				parent = current;
				if (d < current->Data)  // ��������� ������?               
				{
					current = current->leftChild;
					if (current == NULL)  // ���� ��������� ����� �������,                  
					{                 // �������� �����                 
						parent->leftChild = newNode;
						return;
					}
				}
				else                    // ��� �������?               
				{
					current = current->rightChild;
					if (current == NULL)  // ���� ��������� ����� �������,                  
					{                 // �������� ������                  
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
	bool delet(int key) {  // �������� ����   
		Node* current = root;
		Node* parent = root;
		bool isLeftChild = true;
		while (current->Data != key) {       // ����� ����
			parent = current;
			if (key < current->Data) {        // ��������� ������?            
				isLeftChild = true;
				current = current->leftChild;
			}
			else {                           // ��� �������?            
				isLeftChild = false;
				current = current->rightChild;
			}
			if (current == NULL) return false;  // ����� ������� // ���� �� ������                                 
		}      // ��������� ���� ������

		if (current->leftChild == NULL && current->rightChild == NULL) { // ���� ���� �� ����� ��������, �� ������ ���������.
			if (current == root) root = NULL;                 // ���� ���� �������� ��������, ������ ���������            	                         
			else if (isLeftChild) parent->leftChild = NULL;   // ���� ������������� �� ��������
			else parent->rightChild = NULL;
		}

		else if (current->rightChild == NULL) { // ���� ��� ������� �������, ���� ���������� ����� ���������� 
			if (current == root) root = current->leftChild;
			else if (isLeftChild) parent->leftChild = current->leftChild;
			else parent->rightChild = current->leftChild;
		}
		else if (current->leftChild == NULL) { // ���� ��� ������ �������, ���� ���������� ������ ����������  
			if (current == root) root = current->rightChild;
			else if (isLeftChild) parent->leftChild = current->rightChild;
			else parent->rightChild = current->rightChild;
		}
		else { // ��� �������, ���� ���������� ����������
			Node* successor = getSuccessor(current); // ����� ��������� ��� ���������� ���� (current)   
			if (current == root) root = successor; // �������� current ����������� � �����������
			else if (isLeftChild) parent->leftChild = successor;
			else parent->rightChild = successor; // �������� ����������� � ����� �������� current   
			successor->leftChild = current->leftChild;        
		}
		delete current;
		return true;
	}
	// ����� ���������� ���� �� ��������� ��������� ����� delNode.   
	// ��� ����� �� ������� ��������� � ������� �������, � �����   
	// ����������� ������� ����� �������� ����� ����.   
	Node* getSuccessor(Node* delNode) {
		Node* successorParent = delNode;
		Node* successor = delNode;
		Node* current = delNode->rightChild;   // ������� � ������� �������     
		while (current != NULL) {              // ���� �������� ����� �������         
			successorParent = successor;
			successor = current;
			current = current->leftChild;      // ������� � ������ �������        
		}                                           // ���� �������� �� �������� ������ ��������, ������� ����� ����� ������     
		if (successor != delNode->rightChild) {
			successorParent->leftChild = successor->rightChild;
			successor->rightChild = delNode->rightChild;
		}
		return successor;
	}
	bool isEmpty() { return !root; }
	vector <int> k;
	void list_count(Node* root, int g)
	{
		if (root == NULL)
		{
			g = 0;
			k.push_back(g);
		}
		else {
			if ((root->leftChild == NULL) && (root->rightChild == NULL))
			{
				k.push_back(g);
				g = 0;
			}
			else
			{
				g++;
				list_count(root->leftChild, g);
				list_count(root->rightChild, g);
			}
		}
	}
	void kl() 
	{ 
		list_count(root, 1);		
		int maxg = k.front();
		for (int n:k) if (n > maxg) maxg = n;
		cout << maxg << endl; 
	}
	void dt(Node* root) {
		if (root != NULL) {
			dt(root->leftChild);
			dt(root->rightChild);
			delete(root);
			root = NULL;
		}
	}
	void deltree() { dt(root); }
};
int main()
	{
		setlocale(0, "");
		Tree t;
		for (int i = 0; i < 9; i++) {
			t.insert(rand() % 33); t.print();
		}
		t.print(); 
		t.delet(1); t.print(); 
		t.delet(8); t.print(); 
		t.delet(31); t.print();
		cout << "�������: ";
		t.kl();
		cout<<"����� ��-��: "<<t.find(27)<<endl;
		t.deltree();
		system("pause");
		return 0;
	}
