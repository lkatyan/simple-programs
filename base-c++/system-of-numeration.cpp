// Перевод числа в разные системы счисления

#include "stdafx.h"
#include<iostream>
#include<string>
#include <windows.h>
using namespace std;

void sys(int b, int n) {

	string res = "";

	for (int i = 0; n > 0; i++) {

		if (n == b) {
			res = "10" + res;
			break;
		}

		else {
			if (n % b > 9) {
				res = char('A' + (n%b) - 10) + res;
			}
			else {
				res = char((n%b) + '0') + res;
			}
		}

		n /= b;
	}
	cout << res<<endl;
}
int pow(int n, int s)
{
	int res = 1;
	for (size_t i = 0; i != s; ++i)
		res *= n;
	return res;
}
int translate(int ns, int n)
{
	int result = 0;
	for (int i = 0; n >= pow(10, i); ++i)
	{
		result += n % pow(10, i+1) / pow(10, i) * pow(ns, i);
	}
	return result;
}

int v() {
	system("cls");
	return 1;
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (true) {
		switch (v()) {
		case 1:
			int a,b,r;
			cout << "Введите число: ";
			cin >> a;
			cout << "Систему счисления, из которой переводить: ";
			cin >> r;
			cout << "Систему счисления, в которую переводить: ";
			cin >> b;
			sys(b, translate(r, a));
			break;
		default:
			break;
		}
		system("pause");
		system("cls");
	}

	return 0;
}

