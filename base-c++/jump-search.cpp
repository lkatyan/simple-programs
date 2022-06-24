// Реализация поиска прыжками (jumpSearch)

#include <iostream>

int jumpsearch(int a[], int n, int num) {
	if (num < a[0]) return -1;
	int i = 0;
	while (i + 2 <= n) {
		if (num == a[i]) return i;
		if (num < a[i]) {
			for (i = i - 2; i < i + 2; i++)
				if (num == a[i]) return i;
			return -1;
		}
		i = i + 2;
	}
	return -1;
}

int main()
{
	int a[7] = { 1, 2, 3, 4, 5, 6, 7 };
	int i = jumpsearch(a, 7, 4);
	std::cout << i << std::endl;
	return 0;
}