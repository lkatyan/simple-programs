#include <iostream>
#include <thread>

void  vch(int num1, int num2) {
	int b=1;
	for (num1; num1<=num2; num1++) {
		for (int i=2; i<num1; i++) {
			if (num1%i==0)
				b=0;
			}
		if (b==1) {
			printf("%d  ", num1);
		}
		b=1;
	}
}

int main() {
	std::thread first(vch, 2, 5000);
	std::thread second(vch, 5000, 10000);

	first.join();
	second.join();

	std::cout<<std::endl;
	return 0;
}
