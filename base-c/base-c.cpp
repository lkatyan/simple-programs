#include<stdio.h>
#include <stdlib.h>  // для rand
#include <iostream> // для setlocale
#include <math.h>
#include <conio.h> // для getch
#include <string.h>

void functionExampleOne() {
	double x, y, z, s, a, b;
	x = 0,01; 
	y = 0,07;
	z = 0,05;
	a = pow(fabs(cos(x) - cos(y)), (1 + 2 * pow(sin(y), 2)));
	b = 1 + z + pow(z, 2) / 2 + pow(z, 3) / 3 + pow(z, 4) / 4;
	s = a * b;
	printf("Результат вычисления формулы: %lf \n", s);
}

void functionExampleTwo() {
	double x, y, f, s=1;
	int k = rand() % 3 + 1;
	x = 0,7;
	y = 0,1;
	switch (k) {
		case 1: f = sinh(x); break;
		case 2: f = pow(x, 2); break;
		case 3: f = exp(x); break;
		default: printf("\nНе выбрана функция\n");
	}
	if (x < y) {
		printf("\nНет результата\n");
	}
	else {
		if (x > y) s = pow(fabs(f - y), 1 / 3.0) + tan(f);
		if (y < x) s = pow((y - f), 3) + cos(f);
		if (y = x) s = pow((y + f), 2) + pow(x, 3);
		printf("\nРезультат подсчета функции: %lf \n", s);
	}
}

void functionExampleThree() {
	double a=1, b=2, s, y, x, h, p;
	int n=5;
	h = 0.1;
	x = a;
	printf("\nРезультат вычислений: \n");
	do
	{
		p = s = 1;
		for (int i = 1; i <= 2 * n; i++)
		{
			p = -p * (x * x) / (2 * i * (2 * i - 1));
			s = s + p;
		}
		y = cos(x);
		printf("%lf \t", x);
		printf("%lf \t", y);
		printf("%lf \n", s);
		x += h;
	} while (x <= b);
}

void functionExampleFour() {
	const int m = 100;
	int a[m], k=5, i, c;
	printf("\nСортировка пузырьком: \n");
	for (i = 0; i < k; i++)
	{
		a[i] = rand() % 10 + 1;
		printf("%d ", a[i]);
	}
	for (int i = 0; i < k - 1; i++)
		for (int j = i + 1; j < k; j++)
			if (a[i] > a[j])
			{
				c = a[i];
				a[i] = a[j];
				a[j] = c;
			}
	printf("  -->  ");
	for (i = 0; i < k; i++) {
		printf("%d ", a[i]);
	}
}

void functionExampleFive() {
	int** a2;
	int k = 0, s = 0, q = 0, n = 4, m = 5;
	a2 = new int* [n];
	printf("\n\nПроверка двумерного массива на наличие особых элементов\n");
	for (int i = 0; i < n; i++)
		a2[i] = new int[m];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j) {
			a2[i][j] = rand() % 10 + 1;
		}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			printf("%d ", a2[i][j]);
		printf("\n");
	}
	for (int j = 0; j < m; j++) {
		for (int i = 0; i < n; i++)
			s += a2[i][j];
		for (int i = 0; i < n; i++)
			if (a2[i][j] > s - a2[i][j])
				k += 1;
		s = 0;
	}
	printf("Кол-во особых эл-в: %d", k);
	for (int i = 0; i < n; i++)
		delete[]a2[i];
	delete[]a2;
	a2 = NULL;
}

void functionExampleSix() {
	int k;
	char str[100] = "ghyyjgggcvtttcvbuuuuf";
	printf("\n\nВывод цепочек с четным кол-вом повторяющихся символов в строке: \n");
	//gets_s(str);
	for (int i = 0; str[i] != '\0'; i++) {
		k = i;
		if (str[i] == str[i + 1]) {
			do {
				i++;
			} while (str[i] == str[i + 1]);
		}
		if (abs(k - i) % 2) {
			for (int j = k; j <= i; j++)
				printf("%c", str[j]);
			printf("\n");
		}
	}
}

#define _CRT_SECURE_NO_WARNINGS
struct vvv {
	int hours, hours2, minutes, minutes2, time;
	char nomer[100];
	char tipavtobusa[100];
	char punktnaznacheniy[100];
} w[9999];
void functionExampleSeven() {
	int n=1; // Кол-во рейсов
	for (int i = 0; i < n; i++)
	{
		char s[] = "135";
		strcpy_s(w[i].nomer, s);
		char s2[] = "Bus";
		strcpy_s(w[i].tipavtobusa, s2);
		char s3[] = "Selo";
		strcpy_s(w[i].punktnaznacheniy, s3);
		w[i].hours = 10; 
		w[i].minutes = 35;
		w[i].hours2 = 13; 
		w[i].minutes2 = 40;
		w[i].time = w[i].hours2 * 60 + w[i].minutes2;
	}
	int p = 13; int m = 50; // Нужное время прибытия
	char z[20] = "Selo"; // Нужный пункт назначения
	int time = p * 60 + m;
	printf("\nВыбор нужного маршрута исходя из запроса человека (пункт- %s, время- %d:%d)", z, p, m);
	for (int i = 0; i < n; i++)
	{
		if ((time >= w[i].time) && (strcmp(z, w[i].punktnaznacheniy) == 0))
		{
			printf("\nНомер автобуса: %s", w[i].nomer);
			printf("\nТип автобуса: %s", w[i].tipavtobusa);
			printf("\nВремя отправления %d:%d", w[i].hours, w[i].minutes);
			printf("\nВремя прибытия %d:%d", w[i].hours2, w[i].minutes2);
			printf("\nПункт назначения: %s", w[i].punktnaznacheniy);
		}
	}
}

typedef double(*uf)(double, double, int&);
void tabl(double, double, double, double, uf);
double y(double, double, int&);
double s(double, double, int&);
void tabl(double a, double b, double h, double eps, uf fun) {
	int k;
	double sum;
	for (double x = a; x < b + h / 2; x += h) {
		sum = fun(x, eps, k);
		printf("%lf\t%lf\t%lf\n", x, sum, k);
	}
}
double y(double x, double eps, int& k) {
	return pow(9, x);
}
double s(double x, double eps, int& k) {
	double a, c, sum;
	sum = a = c = 1;
	k = 1;
	while (fabs(c) > eps) {
		c = log(9) * x / k;
		a *= c;
		sum += a;
		k++;
	}
	return sum;
}
void functionExampleEight() {
	printf("\n\nРезультат вычисления: \n");
	printf("x\t\ty(x)\t\tk\n");
	tabl(-3, 3, 1, pow(10, -4), y);
	printf("\n");
	printf("x\t\ts(x)\t\tk\n");
	tabl(-3, 3, 1, pow(10, -4), s);
}

int quickSearchOne(int value, int values[], int left, int right) {
	if (left > right)return -1;
	int middle = (left + right) / 2;
	if (value == values[middle])
		return middle+1;
	if (value > values[middle])
		return quickSearchOne(value, values, middle + 1, right);
	else
		return quickSearchOne(value, values, left, middle - 1);
}
int quickSearchTwo(int value, int values[], int n, int low) {
	int middle = (low + n) / 2;
	if (value == values[middle])
		return middle + 1;
	if (values[middle] == low || values[middle] == n)
		return -1;
	if (value > values[middle])
		quickSearchTwo(value, values, n, middle);
	else
		quickSearchTwo(value, values, 0, middle);
}
void functionExampleNine() {
	printf("\n\nТри реализации быстрого поиска ");
	const int m = 100;
	int a[m], k = 10;
	int low = 0, high = k-1, middle;	
	printf("\nМассив: ");
	for (int i = 0; i < k; i++)
	{
		a[i] = rand() % 10 + 1;
		printf("%d ", a[i]);
	}
	int c = a[rand() % 10 + 1];
	printf("\nПоиск эл-та: %d", c);

	printf("\nПервая с рекурсией: %d", quickSearchOne(c, a, low, high));
	printf("\nВторая с рекурсией: %d", quickSearchTwo(c, a, k, low));

	while (low <= high) {
		middle = (low + high) / 2;
		if (c < a[middle])
			high = middle - 1;
		else if (c > a[middle])
			low = middle + 1;
		else {
			printf("\nТретья без рекурсии: %d\n", middle + 1);
			break;
		}
	}
}

#define _CRT_SECURE_NO_WARNINGS
FILE* fl;
FILE* ft;
struct vvvv {
	char fio[300];
	int kolvo_chasov;
	int tarif;
}rab[9999];
char name[47];
int nst = 0; //Число введённых структур
int menu(); //Меню
void nnf(); //Ввести имя файла
void newf(); //Новый файл
void spisok();
void opf(); //open file
void resc(); //Вывод результата на экран
void resf(); //Ввывод результата в файл
void qsort();
void vuborom();
void perebor();
int interh();
int functionExampleTen() {
	while (true) {
		switch (menu()) {
		case 1: nnf(); break;
		case 2: newf(); break;
		case 3: spisok(); break;
		case 4: opf(); break;
		case 5: resc(); break;
		case 6: resf(); break;
		case 7: qsort(); break;
		case 8: vuborom(); break;
		case 9: perebor(); break;
		case 10: interh(); break;
		case 11: return 0;
		default: "Viberite pravilno!";
		}
		puts("Press any key to continue");
		_getch();
		system("cls");
	}
}
int menu() {
	printf("Выберите:\n");
	printf("1. Ввести имя файла.\n");
	printf("2. Новый файл.\n");
	printf("3. Ввести список.\n");
	printf("4. Открыть файл.\n");
	printf("5. Вывести результат в консоль.\n");
	printf("6. Вывести результат в файл.\n");
	printf("7. Быстрая сортировка.\n");
	printf("8. Сортировка выбором.\n");
	printf("9. Поиск полным перебором.\n");
	printf("10. Интерполяционный поиск\n");
	printf("11. Выход.\n");
	int i;
	scanf_s("%d", &i);
	return i;
}
void nnf() {
	printf("Vvedite file name:\n");
	scanf_s("%s", &name);
}
void newf() {
	if ((fl = fopen(name, "wb")) == NULL) {
		printf("Oshibka pri sozdanii\n");
		exit(1);
	}
	printf("Ok\n");
	fclose(fl);
}
void spisok() {
	if ((fl = fopen(name, "rb+")) == NULL) {
		printf("Oshibka pri sozdanii\n");
		_getch();
		exit(1);
	}
	printf("Vvedite kolvo sotrudnikov:\n");
	scanf("%d", &nst);
	for (int i = 0; i < nst; i++) {
		printf("Vvedite FIO: ");
		scanf_s("%s", &rab[i].fio);
		printf("Vvedite kolvo prorabotannuh chasov: ");
		scanf_s("%d", &rab[i].kolvo_chasov);
		printf("Vvedite tarif: ");
		scanf_s("%d", &rab[i].tarif);
		fwrite(&rab[i], sizeof(vvvv), 1, fl);//1)буфер-указатель на информацию, записываемую в файл
	}										//2)Длина каждого элемента в байтах
	fclose(fl);								//3)объем-сколько элементов будет прочитано или записано
}											//4)файловый указатель на ранее открытый поток
void opf() {
	if ((fl = fopen(name, "rb")) == NULL) {
		printf("Oshibka pri sozdanii\n");
		_getch();
		exit(1);
	}
	nst = 0;
	vvvv std;
	while (true) {
		int nwrt = fread(&std, sizeof(vvvv), 1, fl);
		if (nwrt != 1)
			break;
		rab[nst] = std;
		printf("Sotrudnik: %s \n\tkol-vo chasov: %d \n\ttarif: %d \n", rab[nst].fio, rab[nst].kolvo_chasov, rab[nst].tarif);
		nst += 1;
		_getch();
	}
	fclose(fl);
}
void resc() {
	double zarplata;
	for (int i = 0; i < nst; i++) {
		if (rab[i].kolvo_chasov > 144)
			zarplata = ((rab[i].kolvo_chasov - 144) * 2 * rab[i].tarif + 144 * rab[i].tarif) * 0.88;
		else
			zarplata = (rab[i].kolvo_chasov * rab[i].tarif) * 0.88;
		printf("Zarplata %s:\n\t%lf\n", rab[i].fio, zarplata);
	}
	_getch();
}
void resf() {
	char namet[40];
	printf("Vvedite imya faila:\n");
	scanf("%s", &namet);
	if ((ft = fopen(namet, "w")) == NULL) {
		printf("Oshibka pri sozdanii\n");
		_getch();
		exit(1);
	}
	double z;
	char f[80], zp[80];
	for (int i = 0; i < nst; i++) {
		if (rab[i].kolvo_chasov > 144)
			z = ((rab[i].kolvo_chasov - 144) * 2 * rab[i].tarif + 144 * rab[i].tarif) * 0.88;
		else
			z = (rab[i].kolvo_chasov * rab[i].tarif) * 0.88;
		char zpl[100];
		sprintf(zpl, "%f", z); //вывод производится в массив zpl
		strcpy(f, rab[i].fio); //копирует строку rab[i].fio в f
		strcat(f, ": "); //добавляет строку ": " к переменной f
		fputs(f, ft); //записывает содержимое f в ft
		strcpy(zp, zpl);
		strcat(zp, "\n");
		fputs(zp, ft);
	}
	fclose(ft);
}
void qsort()
{
	struct
	{
		int l;
		int r;
	} stack[20];

	int i, j, left, right, x, s = 0;
	vvvv t;
	stack[s].l = 0; stack[s].r = nst - 1;
	while (s != -1)
	{
		left = stack[s].l; right = stack[s].r;
		s--;
		while (left < right)
		{
			i = left; j = right; x = rab[(left + right) / 2].kolvo_chasov;
			while (i <= j)
			{
				while (rab[i].kolvo_chasov < x) i++;
				while (rab[j].kolvo_chasov > x) j--;
				if (i <= j) {
					t = rab[i]; rab[i] = rab[j]; rab[j] = t;
					i++; j--;
				}
			}
			if ((j - left) < (right - i))
			{
				if (i < right) { s++; stack[s].l = i; stack[s].r = right; }
				right = j;
			}
			else {
				if (left < j) { s++; stack[s].l = left; stack[s].r = j; }
				left = i;
			}
		}
	}
	for (int i = 0; i < nst; i++)
		printf("%s %d %d\n", rab[i].fio, rab[i].kolvo_chasov, rab[i].tarif);
	_getch();
}
void vuborom() {
	int imin, i, j, t;
	for (i = 0; i < nst - 1; i++)
	{
		imin = i;
		for (j = i + 1; j < nst; j++)
			if (rab[imin].kolvo_chasov > rab[j].kolvo_chasov) imin = j;
		if (imin != i)
		{
			t = rab[imin].kolvo_chasov;
			rab[imin].kolvo_chasov = rab[i].kolvo_chasov;
			rab[i].kolvo_chasov = t;
		}
	}
	for (int i = 0; i < nst; i++)
		printf("%s %d %d\n", rab[i].fio, rab[i].kolvo_chasov, rab[i].tarif);
	_getch();
}
void perebor()
{
	for (int i = 0; i < nst; i++)
		if (rab[i].kolvo_chasov == 156)
		{
			printf("156 chasov y rabotnika %s \n", rab[i].fio);
			break;
		}
	_getch();
}
int interh()
{
	int low, high, mid;
	low = 0;
	high = nst - 1;
	while (rab[low].kolvo_chasov < 156 && rab[high].kolvo_chasov >= 156)
	{
		mid = low + ((156 - rab[low].kolvo_chasov) * (high - low)) / (rab[high].kolvo_chasov - rab[low].kolvo_chasov);
		if (rab[mid].kolvo_chasov < 156)
			low = mid + 1;
		else if (rab[mid].kolvo_chasov > 156)
			high = mid - 1;
		else
			return printf("156 chasov y rabotnika %s \n", rab[mid].fio);
	}
	if (rab[low].kolvo_chasov == 156)
		return printf("156 chasov y rabotnika %s \n", rab[low].fio);
	else
		return -1;
	_getch();
}

int main() {
	setlocale(LC_ALL, "Rus");
	functionExampleOne();
	functionExampleTwo();
	functionExampleThree();
	functionExampleFour();
	functionExampleFive();
	functionExampleSix();
	functionExampleSeven();
	functionExampleEight();
	functionExampleNine();
	functionExampleTen();
	_getch();
}