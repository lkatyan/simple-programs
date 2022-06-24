//Решение системы лин. уравнений методом LU-разложения 

#include <windows.h>
#include <iostream>
#include <time.h>
#include <vector>
using namespace std;

int m=4, n=5; //Размер
vector < vector <double> > a2(m, vector <double>(n));
vector < vector <double> > aa1(m, vector <double>(n));
vector < double > a1(m, 0); //под свободные члены
vector < double > x(m, 0); //под корни
vector < double > y(m, 0);  	

void vuvodmassiva(vector<vector<double>>& e, int q) {
	if (q == 0) cout << "---------------- Исходная матрица: ----------------" << endl << endl;
	if (q == 1) cout << endl << "---------------- Матрица L: -----------------------" << endl << endl;
	if (q == 2) cout << endl << "---------------- Матрица U: -----------------------" << endl << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) cout << e[i][j] << "	";
		cout << endl;
	}
}

void reshenie1() { //Прямой ход метода Гаусса
	int v = 0, w = 0; double koef;
	for (int i = 0; i < m; i++) //записываю последний столбец(свободные члены)
		a1[i] = a2[i][n - 1];
	for (int t = 0; t < n - 1; t++) {
		double vw = a2[v][w]; //Ведущий элемент
		for (int i = v + 1; i < m;i++) { //Перебираю строки, которые после ведущей
			if (a2[i][w] != 0) {         //-Если первый элемент строки не нулевой-
				double ved = a2[i][w];
				koef = ved / vw; //сохраняю коэффициент для матрицы L
				for (int j = w;j < n;j++) {
					double k = (a2[v][j] * ved)/vw ;  //Умножаю ведущую строку на первый элемент выбранной строки, делю на вед.эл-т
					a2[i][j] = a2[i][j] - k; //отнимаю из выбранной строки ведущую строку
						
				}
				aa1[i][w] = koef;
			}
		}
		w++;v++; //Увеличиваю индекс ведущих строки и столбца (двигаюсь по диагонали)
	}
}
	//L=aa1   //U=a2   //свободные члены=a1
void reshenie12() {
	double sum = 0;
	for (int i = 0 ; i <= m - 1; i++) //нахожу вектор y по формуле Ly=свободные члены
	{
		y[i] = (a1[i] - sum);
		sum = 0;
		if (i < m-1)
			for (int j = 0; j <= i; j++)
				sum = sum + y[j] * aa1[i + 1][j];
	}
	/*cout << endl << "---------------- Корни матрицы: -------------------" << endl << endl;
	for (int i = 0; i < m; i++)
		cout << "y" << i + 1 << "=" << y[i] << " " << endl;*/
	sum = 0;
	for (int i = m - 1; i >= 0; i--) //нахожу корни по формуле Ux=y
	{
		x[i] = (y[i] - sum) / a2[i][i];
		sum = 0;
		if (i > 0)
			for (int j = m - 1; j >= i; j--)
				sum = sum + x[j] * a2[i - 1][j];
	}
}

void printcorni() {
	cout << endl << "---------------- Корни матрицы: -------------------" << endl << endl;
	for (int i = 0; i < m; i++)
		cout << "x" << i + 1 << "=" << x[i] << " " << endl;
}



void matr1() {
	time_t start, end;
	a2 = { {8, -5, 4, 4, -161},
		   {-5, -1, 3, -7, 82},
		   {4, 3, -6, 8, -53},
		   {4, -7, 8, -3, -100} };
	aa1 = { {1, 0, 0, 0, 0},
			{0, 1, 0, 0, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 0, 1, 0} };
	vuvodmassiva(a2, 0);
	time(&start);
	reshenie1();
	reshenie12();
	vuvodmassiva(aa1, 1);
	vuvodmassiva(a2, 2);
	printcorni();
	time(&end);
	double seconds = difftime(end, start);
	cout << "\n------ Время работы программы : " << seconds << " секунд/а/ы ------" << endl << endl;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << " LU-разложение (Матрица 4х4)." << endl;
	matr1();
	system("pause");
	return 0;
}
