// Конечный автомат поиска в тексте эл.адресов, номеров и почтовых индексов, 
// встречающихся не менее 2 раз

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;
struct Node {
	string key;
	int val;
	Node* left, * right, * parent;
	Node(string k = "", int v = 1)
	{
		key = k;
		left = right = parent = 0;
		val = v;
	}
};
struct Map
{
	Node* root;
	Map()
	{
		root = nullptr;
	}

	void insert(string key) {
		Node* newNode = new Node(key);

		if (!root) {
			root = newNode;
			return;
		}

		Node* current = root;
		Node* parent;
		while (true)
		{
			parent = current;

			if (key < current->key)
			{
				if (parent->key == key) {
					parent->left = newNode;
					return;
				}
				current = current->left;
				if (!current) {
					parent->left = newNode;
					return;
				}
			}

			else
			{
				if (parent->key == key) {
					parent->val++;
					break;
				}

				current = current->right;
				if (!current)
				{
					parent->right = newNode;
					return;
				}
			}
		}
	}

	void inOrder(Node* node) {
		if (!node) return;
		inOrder(node->left);
		if (node->val > 1)
			cout << '|' << node->key << '|' << '\t' << "Кол-во повторений:" << node->val << endl;
		inOrder(node->right);
	}

	void print() {
		inOrder(root);
	}
};
enum States
{
	States_Start,
	States_Email_Dog,
	States_Email_Dot,
	States_Phonenumber_Countrycode,
	States_Postcode,
};
int main()
{
	ifstream file("D://Text.txt");
	string str;

	bool flag_email;
	bool flag_phonenumber;
	bool flag_postcode;

	Map map_email;
	Map map_phonenumber;
	Map map_postcode;

	while (file >> str)
	{
		States state = States_Start;
		flag_email = true;
		flag_phonenumber = true;
		flag_postcode = true;

		for (int i = 0; i < str.size() - 1; i++)
		{
			if (!isalpha(str[i]) && !isdigit(str[i]) && str[i] != '_' && str[i] != '-' &&
				str[i] != '@' && str[i] != '.') flag_email = false;

			if (!isdigit(str[i]) && str[0] != '+') flag_phonenumber = false;

			if (!isdigit(str[i])) flag_postcode = false;

			switch (state)
			{
			case States_Start:
				if (str[i] == '@' && flag_email)
					state = States_Email_Dog;

				if (str[0] == '+' && str.size() == 12)
					state = States_Phonenumber_Countrycode;

				if (str.size() == 6)
					state = States_Postcode;
				break;

			case States_Email_Dog:
				if (str[i] == '.' && flag_email)
					state = States_Email_Dot;
				break;

			case States_Email_Dot:
				if (i == str.size() - 2 && flag_email)
					map_email.insert(str);
				break;

			case States_Phonenumber_Countrycode:
				if (i == str.size() - 2 && flag_phonenumber)
					map_phonenumber.insert(str);
				break;

			case States_Postcode:
				if (i == str.size() - 2 && flag_postcode)
					map_postcode.insert(str);
				break;
			}
		}
	}
	setlocale(0, "");
	cout << "Emails:" << endl;
	map_email.print();
	cout << endl;
	cout << "Телефонные номера:" << endl;
	map_phonenumber.print();
	cout << endl;
	cout << "Почтовые индексы:" << endl;
	map_postcode.print();
	cout << endl;
	system("pause");
	return 0;
}
