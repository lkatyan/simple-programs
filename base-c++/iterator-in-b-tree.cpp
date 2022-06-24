// Реализация итератора в бинарном дереве

#include <iostream>
using namespace std;
class Tree {
private:
    class Node {
    public:
        Node* _left, * _right;
        string _data;
        Node(const string data, Node* left = nullptr, Node* right = nullptr) : _data(data), _left(left), _right(right) {}
    };
    class Iterator {
    public:
        Node* node;
        Iterator(Node* n = nullptr) :node(n) {}
        string& operator*() const { return node->_data; }
        string& operator->() const { return node->_data; }
        bool operator==(const Iterator& it) { return node == it.node; }
        bool operator!=(const Iterator& it) { return node != it.node; }
        Iterator left() { return Iterator(node->_left); }
        Iterator right() { return Iterator(node->_right); }
    };
    Node* root = nullptr;
    void print(Iterator it) {
        if (it == end())
            return;
        print(it.left());
        std::cout << *it << " ";
        print(it.right());
    }
public:
    Iterator begin() { return { root }; }
    Iterator end() { return Iterator(nullptr); } 
    void add(string x) {
        if (!root) {
            root = new Node(x);
            return;
        }
        Iterator iter = begin();
        Iterator iter_parent;
        while (iter != end()) {
            iter_parent = iter;
            if (x < *iter)
                iter = iter.left();
            else if (x == *iter)
                return;
            else iter = iter.right();
        }
        if (x > * iter_parent)
            iter_parent.node->_right = new Node(x);
        else
            iter_parent.node->_left = new Node(x);
    }
    void print() {
        print(begin()); cout << endl;
    }
    void push() {
        string t; cout << "vvedite - ";
        cin >> t; add(t);
    } 
    int veubor() {
        print();
        cout << "1:push string" << endl;
        int i; cin >> i;
        system("cls");
        return i;
    }
};

int main()
{
    Tree tree;
    tree.add("q");
    tree.add("d");
    tree.add("i");
    tree.add("a");
    tree.add("e");
    tree.add("w");
    tree.add("r");
    tree.add("n");
    tree.add("x");
    tree.add("u");
    while (true)
    {
        switch (tree.veubor())
        {
        case 1: tree.push(); break;
        default: "Введите верно!";
        }
        system("pause");
        system("cls");
    }
    return 0;
}
