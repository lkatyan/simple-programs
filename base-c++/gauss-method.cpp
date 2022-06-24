//Решение системы лин. уравнений методом Гаусса

#include <windows.h>
#include <iostream>
#include <time.h>
//#include <chrono>

using namespace std;

class Slau 
{
private:
	double *a1; //массив свободных членов
	double *x; //Массив корней
	int m, n; //Размер

public:
	void newmassiv(int y1, int y2) //Выделяю память под массивы
	{
		a1 = new double[y1];
		x = new double[y1];
		m = y1; n = y2;
	}

	void deleteMassivu(double** matrica)
	{
		delete[] matrica;
		delete[] a1;
		delete[] x;
	}

	void vuvodmassiva(double** matrica)
	{
		cout << "Матрица:" << endl;
		for (int i = 0; i < m; i++) 
		{
			for (int j = 0; j < n; j++)
				cout << matrica[i][j] << "	";
			cout << endl;
		}
		system("pause");
		system("cls");
	}

	//V-ведущий индекс строки
	//W-ведущий индекс столбца
	//maxi-индекс максималного элемента по модулю в ведущем столбце
	void izmMestamiStroki(double** matrica, int v, int w)
	{
		int maxi = v;
		for (int i = v; i < m; i++) //максимальный по модулю ненулевой первый элемент строки
			if (matrica[i][w] != 0 && fabs(matrica[i][w]) > fabs(matrica[maxi][w]))
				maxi = i; //-сохраняю индекс строки
		double* temp = matrica[maxi];
		matrica[maxi] = matrica[v];
		matrica[v] = temp; //Меняю местами строки
	}

	void PrymoiHod(double** matrica) //Прямой ход метода Гаусса
	{ 
		int v = 0, w = 0;
		for (int t = 0; t < n - 1; t++) 
		{
			izmMestamiStroki(matrica, v, w);
			double vw = matrica[v][w]; //Ведущий элемент
			for (int j = w; j < n; j++) 
			{
				matrica[v][j] = matrica[v][j] / vw; //Делю 1-ую строку на ведущий элемент
			}  

			for (int i = v + 1; i < m;i++) //Перебираю строки, которые после ведущей
			{ 
				if (matrica[i][w] != 0) //-Если первый элемент строки не нулевой-
				{         
					double ved = matrica[i][w];
					for (int j = w;j < n;j++) 
					{
						double k = matrica[v][j] * ved;  //Умножаю ведущую строку на первый элемент выбранной строки и
						matrica[i][j] = matrica[i][j] - k; //отнимаю из выбранной строки ведущую строку
					}
				}
			}
			w++;v++; //Увеличиваю индекс ведущих строки и столбца (двигаюсь по диагонали)
		}
	}

	void ObratnuiHod(double** matrica) //Обратный ход
	{ 
		for (int i = 0; i < m; i++) //записываем последний столбец(свободные члены)
			a1[i] = matrica[i][n - 1];
		double sum = 0;
		for (int i = 0; i < m; i++)	x[i] = 0;
		for (int i = m - 1; i >= 0; i--)
		{
			x[i] = (a1[i] - sum); //от свободного члена отнимаем сумму остальных посчитанных корней
			sum = 0;
			if (i > 0)
			{
				for (int j = m - 1; j >= i; j--) //сумма посчитанных корней
					sum = sum + x[j] * matrica[i - 1][j]; //найденный корень на коэффициент в строке выше
			}
		}
	}

	void printKorni() 
	{
		cout << "Корни матрицы:" << endl;
		for (int i = 0; i < m; i++)
			cout << "x" << i + 1 << "=" << x[i] << " " << endl;
		system("pause");
		system("cls");
	}
};

void matr1()
{
	Slau m1;
	time_t start, end;

	double** a2; //Массив под матрицу
	a2 = new double*[5];
	for (int i = 0;i < 5;i++)
		a2[i] = new double[4];
	m1.newmassiv(4, 5);

	double ar[4][5] = { {-5, 1, 4, 4, 28},
						{0, -5, -1, 1, -7},
						{-2, 2, 4, 2, 8},
						{2, -5, 2, -3, -45} };
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 5; j++)
			a2[i][j] = ar[i][j]; //Создаю статический и перекидываю элементы в динамический

	m1.vuvodmassiva(a2);
	time(&start);
	//auto begin = chrono::high_resolution_clock::now();
	m1.PrymoiHod(a2);
	m1.ObratnuiHod(a2);
	m1.printKorni();
	time(&end);
	double seconds = difftime(end, start);
	cout << "\nВремя работы программы : " << seconds << " секунд/а/ы" << endl;
	//auto end = chrono::high_resolution_clock::now();
	//cout<<"\nВремя работы программы : "<<chrono::duration_cast<chrono::nanoseconds>(end - begin).count()<<" наносекунд"<<endl;
	m1.deleteMassivu(a2);
}

void matr2()
{
	Slau m2;
	time_t start, end;

	double** a22; //Массив под матрицу
	a22 = new double*[6];
	for (int i = 0;i < 6;i++)
		a22[i] = new double[5];
	m2.newmassiv(5, 6);

	double ar2[5][6] = { {2, -1, 2, -2, -1, 10 },
						{4, -1, -2, 0, -5, -10 },
						{3, -1, -3, -3, 1, 1 },
						{3, 0, 4, -2, -4, 17 },
						{0, 1, -5, 3, -5, -26 } };
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 6; j++)
			a22[i][j] = ar2[i][j]; //Создаю статический и перекидываю элементы в динамический

	m2.vuvodmassiva(a22);
	time(&start);
	//auto begin = chrono::high_resolution_clock::now();
	m2.PrymoiHod(a22);
	m2.ObratnuiHod(a22);
	m2.printKorni();
	time(&end);
	double seconds = difftime(end, start);
	cout << "\nВремя работы программы : " << seconds << " секунд/а/ы" << endl;
	//auto end = chrono::high_resolution_clock::now();
	//cout<<"\nВремя работы программы : "<<chrono::duration_cast<chrono::nanoseconds>(end - begin).count()<<" наносекунд"<<endl;
	m2.deleteMassivu(a22);
}

int menu()
{
	cout << "1. Матрица 4х4" << endl;
	cout << "2. Матрица 5х5" << endl;
	int z;
	cin >> z;
	system("cls");
	return z;
}

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251); //Русская локализация
	while (true)
	{
		switch (menu())
		{
		case 1: matr1(); break;
		case 2: matr2(); break;
		default: "Введите верно!";
		}
		system("pause"); //задержка консоли
		system("cls"); //обнуление консоли
	}
}