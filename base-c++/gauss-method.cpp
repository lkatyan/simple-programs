//������� ������� ���. ��������� ������� ������

#include <windows.h>
#include <iostream>
#include <time.h>
//#include <chrono>

using namespace std;

class Slau 
{
private:
	double *a1; //������ ��������� ������
	double *x; //������ ������
	int m, n; //������

public:
	void newmassiv(int y1, int y2) //������� ������ ��� �������
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
		cout << "�������:" << endl;
		for (int i = 0; i < m; i++) 
		{
			for (int j = 0; j < n; j++)
				cout << matrica[i][j] << "	";
			cout << endl;
		}
		system("pause");
		system("cls");
	}

	//V-������� ������ ������
	//W-������� ������ �������
	//maxi-������ ������������ �������� �� ������ � ������� �������
	void izmMestamiStroki(double** matrica, int v, int w)
	{
		int maxi = v;
		for (int i = v; i < m; i++) //������������ �� ������ ��������� ������ ������� ������
			if (matrica[i][w] != 0 && fabs(matrica[i][w]) > fabs(matrica[maxi][w]))
				maxi = i; //-�������� ������ ������
		double* temp = matrica[maxi];
		matrica[maxi] = matrica[v];
		matrica[v] = temp; //����� ������� ������
	}

	void PrymoiHod(double** matrica) //������ ��� ������ ������
	{ 
		int v = 0, w = 0;
		for (int t = 0; t < n - 1; t++) 
		{
			izmMestamiStroki(matrica, v, w);
			double vw = matrica[v][w]; //������� �������
			for (int j = w; j < n; j++) 
			{
				matrica[v][j] = matrica[v][j] / vw; //���� 1-�� ������ �� ������� �������
			}  

			for (int i = v + 1; i < m;i++) //��������� ������, ������� ����� �������
			{ 
				if (matrica[i][w] != 0) //-���� ������ ������� ������ �� �������-
				{         
					double ved = matrica[i][w];
					for (int j = w;j < n;j++) 
					{
						double k = matrica[v][j] * ved;  //������� ������� ������ �� ������ ������� ��������� ������ �
						matrica[i][j] = matrica[i][j] - k; //������� �� ��������� ������ ������� ������
					}
				}
			}
			w++;v++; //���������� ������ ������� ������ � ������� (�������� �� ���������)
		}
	}

	void ObratnuiHod(double** matrica) //�������� ���
	{ 
		for (int i = 0; i < m; i++) //���������� ��������� �������(��������� �����)
			a1[i] = matrica[i][n - 1];
		double sum = 0;
		for (int i = 0; i < m; i++)	x[i] = 0;
		for (int i = m - 1; i >= 0; i--)
		{
			x[i] = (a1[i] - sum); //�� ���������� ����� �������� ����� ��������� ����������� ������
			sum = 0;
			if (i > 0)
			{
				for (int j = m - 1; j >= i; j--) //����� ����������� ������
					sum = sum + x[j] * matrica[i - 1][j]; //��������� ������ �� ����������� � ������ ����
			}
		}
	}

	void printKorni() 
	{
		cout << "����� �������:" << endl;
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

	double** a2; //������ ��� �������
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
			a2[i][j] = ar[i][j]; //������ ����������� � ����������� �������� � ������������

	m1.vuvodmassiva(a2);
	time(&start);
	//auto begin = chrono::high_resolution_clock::now();
	m1.PrymoiHod(a2);
	m1.ObratnuiHod(a2);
	m1.printKorni();
	time(&end);
	double seconds = difftime(end, start);
	cout << "\n����� ������ ��������� : " << seconds << " ������/�/�" << endl;
	//auto end = chrono::high_resolution_clock::now();
	//cout<<"\n����� ������ ��������� : "<<chrono::duration_cast<chrono::nanoseconds>(end - begin).count()<<" ����������"<<endl;
	m1.deleteMassivu(a2);
}

void matr2()
{
	Slau m2;
	time_t start, end;

	double** a22; //������ ��� �������
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
			a22[i][j] = ar2[i][j]; //������ ����������� � ����������� �������� � ������������

	m2.vuvodmassiva(a22);
	time(&start);
	//auto begin = chrono::high_resolution_clock::now();
	m2.PrymoiHod(a22);
	m2.ObratnuiHod(a22);
	m2.printKorni();
	time(&end);
	double seconds = difftime(end, start);
	cout << "\n����� ������ ��������� : " << seconds << " ������/�/�" << endl;
	//auto end = chrono::high_resolution_clock::now();
	//cout<<"\n����� ������ ��������� : "<<chrono::duration_cast<chrono::nanoseconds>(end - begin).count()<<" ����������"<<endl;
	m2.deleteMassivu(a22);
}

int menu()
{
	cout << "1. ������� 4�4" << endl;
	cout << "2. ������� 5�5" << endl;
	int z;
	cin >> z;
	system("cls");
	return z;
}

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251); //������� �����������
	while (true)
	{
		switch (menu())
		{
		case 1: matr1(); break;
		case 2: matr2(); break;
		default: "������� �����!";
		}
		system("pause"); //�������� �������
		system("cls"); //��������� �������
	}
}