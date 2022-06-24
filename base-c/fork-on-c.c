#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void vch();

int main() {
	pid_t pid;
	int rv=13;
	switch (pid=fork()) {
		case -1:
			perror("fork");
			exit(1);
		case 0:
			vch(10000,15000);
			exit(rv);
		default:
			vch(15000,20000);
			wait(&rv);
	}
	printf("\n");
	return 0;
}

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
