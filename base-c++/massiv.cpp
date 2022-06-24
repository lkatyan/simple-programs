// Разбиение исходного массива на три новых массива с общей суммой эл-в не больше 
// трети от общей суммы элементов исходного массива 

#include <iostream>

int* m(int a[], int* b) {
	int n = 5, sum = 0, prsum = 0, k=0;
	for (int i = 0; i < n; i++) sum += a[i];
	if (sum % 3 != 0) { std::cout << "not work\n"; return b; }
	for (int i = 0; i < n; i++) {
		prsum += a[i];
		if (prsum == sum / 3) {
			b[k] = i;
			k++;
			prsum = 0;
		}
		else if (prsum > sum / 3) {
			std::cout << "not work\n"; return b;
		}
	}
	//for (int i = 0; i < 3; i++) std::cout<< b[i]<<std::endl;
	return b;
}
int main() {
	int* b = new int[3]{ 0,0,0 }; int n = 5;
	int a[5] = { 5, 3, 7, 1, 8 };
	for (int i = 0; i < n; i++) {
		std::cout << a[i];
	}
	std::cout << std::endl<<std::endl;
	b = m(a, b);
	int* a1 = new int[5] { 0,0,0,0,0 };
	int* a2 = new int[5]{ 0,0,0,0,0 };
	int* a3 = new int[5]{ 0,0,0,0,0 };
	for (int i = 0; i <= b[0]; i++) {
		a1[i] = a[i];
	}
	int pri = 0;
	for (int i = b[0]+1; i <= b[1]; i++) {
		a2[pri] = a[i];
		pri++;
	}
	pri = 0;
	for (int i = b[1]+1; i <= b[2]; i++) {
		a3[pri] = a[i];
		pri++;
	}
	for (int i = 0; i < n; i++) {
		std::cout << a1[i];
	}
	std::cout << std::endl;
	for (int i = 0; i < n; i++) {
		std::cout << a2[i];
	}
	std::cout << std::endl;
	for (int i = 0; i < n; i++) {
		std::cout << a3[i];
	}
	std::cout << std::endl;
}