// Отрисовка спирали конечным автоматом

#include <iostream>

using namespace std;
void spiral() {
	int const u = 15;
	int const m = 15;
	char mass[u][m];
	int x = 0, y = 0, n = 0, t=2;
	for (int i = 0; i < u; i++) {
		for (int j = 0; j < m; j++)
		{
			mass[i][j] = ' ';
		}
	}
		while (true) {
			mass[x][y] = '*';
			if (n == 0) {
				if (mass[x][y+t] == '*' || y + 1 == m) n++;
				else y++;
			}
			if (n == 1) {
				if (mass[x+t][y] == '*' || x + 1 == m) n++;
				else x++;
			}
			if (n == 2) {
				if (mass[x][y-t] == '*' || y - 1 == 0) n++;
				else y--;
			}
			if (n == 3) {
				if (mass[x-t][y] == '*') n = 0;
				else x--;
			}
			if ((mass[x - t][y] == '*') && (mass[x + t][y] == '*') && (mass[x][y - t] == '*') && (mass[x][y+t-1]=='*')) {
				break;
			}
		}
		for (int i = 0; i < u; i++) {
			for (int j = 0; j < m; j++)
				cout << mass[i][j];
			cout << endl;
		}

	}
int main() {
	spiral();
}