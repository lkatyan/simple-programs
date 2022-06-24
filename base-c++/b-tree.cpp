// Реализация бинарного дерева
// +подсчет глубины дерева и поиск элемента

#include <iostream>
#include <stack>
#include <vector>
using namespace std;
class Node {
public: int Data;                  // Данные 
		Node* leftChild;
		Node* rightChild; // Правый и левый потомок узла   
		Node(int N)
		{
			Data = N;
			leftChild = rightChild = 0;
		}
	 void displayNode()            // Вывод узла      
	{
		 cout << " " << Data << " ";
	 }
};
class Tree {
public:
	Node* root;             // first node of tree
	Tree() : root(0) {} // Конструктор // Пока нет ни одного узла          
	int find(int d) {
		Node* current = root;                // Начать с корневого узла      
		while (current->Data != d)         // Пока не найдено совпадение         
		{
			if (d < current->Data)          // Двигаться налево?            
				current = current->leftChild;
			else                             // Или направо?
				current = current->rightChild;
			if (current == NULL)             // Если потомка нет,            
				return NULL;                 // поиск завершился неудачей         
		}
		return current->Data;                    // Элемент найден      
	}
	void insert(int d)
	{
		Node* newNode = new Node(d);    // Создание нового узла      
		//newNode->Data = d;           // Вставка данных     
		if (root == NULL)                // Корневой узел не существует         
			root = newNode;
		else                          // Корневой узел занят         
		{
			Node* current = root;       // Начать с корневого узла         
			Node* parent;
			while (true)                // (внутренний выход из цикла)            
			{
				parent = current;
				if (d < current->Data)  // Двигаться налево?               
				{
					current = current->leftChild;
					if (current == NULL)  // Если достигнут конец цепочки,                  
					{                 // вставить слева                 
						parent->leftChild = newNode;
						return;
					}
				}
				else                    // Или направо?               
				{
					current = current->rightChild;
					if (current == NULL)  // Если достигнут конец цепочки,                  
					{                 // вставить справа                  
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
	bool delet(int key) {  // Удаление узла   
		Node* current = root;
		Node* parent = root;
		bool isLeftChild = true;
		while (current->Data != key) {       // Поиск узла
			parent = current;
			if (key < current->Data) {        // Двигаться налево?            
				isLeftChild = true;
				current = current->leftChild;
			}
			else {                           // Или направо?            
				isLeftChild = false;
				current = current->rightChild;
			}
			if (current == NULL) return false;  // Конец цепочки // Узел не найден                                 
		}      // Удаляемый узел найден

		if (current->leftChild == NULL && current->rightChild == NULL) { // Если узел не имеет потомков, он просто удаляется.
			if (current == root) root = NULL;                 // Если узел является корневым, дерево очищается            	                         
			else if (isLeftChild) parent->leftChild = NULL;   // Узел отсоединяется от родителя
			else parent->rightChild = NULL;
		}

		else if (current->rightChild == NULL) { // Если нет правого потомка, узел заменяется левым поддеревом 
			if (current == root) root = current->leftChild;
			else if (isLeftChild) parent->leftChild = current->leftChild;
			else parent->rightChild = current->leftChild;
		}
		else if (current->leftChild == NULL) { // Если нет левого потомка, узел заменяется правым поддеревом  
			if (current == root) root = current->rightChild;
			else if (isLeftChild) parent->leftChild = current->rightChild;
			else parent->rightChild = current->rightChild;
		}
		else { // Два потомка, узел заменяется преемником
			Node* successor = getSuccessor(current); // Поиск преемника для удаляемого узла (current)   
			if (current == root) root = successor; // Родитель current связывается с посредником
			else if (isLeftChild) parent->leftChild = successor;
			else parent->rightChild = successor; // Преемник связывается с левым потомком current   
			successor->leftChild = current->leftChild;        
		}
		delete current;
		return true;
	}
	// Метод возвращает узел со следующим значением после delNode.   
	// Для этого он сначала переходит к правому потомку, а затем   
	// отслеживает цепочку левых потомков этого узла.   
	Node* getSuccessor(Node* delNode) {
		Node* successorParent = delNode;
		Node* successor = delNode;
		Node* current = delNode->rightChild;   // Переход к правому потомку     
		while (current != NULL) {              // Пока остаются левые потомки         
			successorParent = successor;
			successor = current;
			current = current->leftChild;      // Переход к левому потомку        
		}                                           // Если преемник не является правым потомком, создать связи между узлами     
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
		cout << "Глубина: ";
		t.kl();
		cout<<"Поиск эл-та: "<<t.find(27)<<endl;
		t.deltree();
		system("pause");
		return 0;
	}
