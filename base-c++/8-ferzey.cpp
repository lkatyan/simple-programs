// Программа расстанавливает 8 "ферзей" в массиве таким образом, 
// чтобы они не стояли на пересечениях друг у друга
// горизонтально, вертикально и по диагонали

#include <iostream>
#include <ctime>

char mas[8][8];
int count; bool l;

bool diagproverka(int i, int j) {
	int u=i, w=j;
	while (u > 0 && w > 0) { 
		u--; w--;
		if (mas[u][w] == 42) return false; 
	}
	u = i; w = j;
	while (u < 7 && w > 0 ) {
		u++; w--;
		if (mas[u][w] == 42) return false;
	}
	u = i; w = j;
	while (u > 0 && w < 7) {
		u--; w++;
		if (mas[u][w] == 42) return false;
	}
	u = i; w = j;
	while ( u < 7 && w < 7) {
		u++; w++;
		if (mas[u][w] == 42) return false;
	}
	return true;
}

bool proverka(int x) {
	l=true;
	for (int j = 0; j < 8; j++) {
		if (mas[x][j] == 45) {
			for (int i = 0; i < 8; i++)
				if (mas[i][j] == 42) l = false;
			if ( l == true ) l = diagproverka(x, j);
			if ( l == true ) {
				mas[x][j] = 42;
				count++;
				return true; 
			}
		}
		l = true;
	}
	return false;
}

bool work() {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			mas[i][j] = 45;
	count = 1;
	srand(time(0));
	int x = rand() % 7 + 1;
	int y = rand() % 7 + 1;
	mas[x][y] = 42;
	int q = x;
	for (q = q + 1; q < 8; q++) {
		l = proverka(q);
	}
	q = x;
	for (q = q - 1; q >= 0; q--) {
		l = proverka(q);
	}
	return l;
}

int main()
{
	while (true) {
		l = work();
		if (l && count == 8) { 
			std::cout << "true\n"; 
			break;
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			std::cout << mas[i][j];
		}
		std::cout << std::endl;
	}
	return 0;
}

