#include <stdio.h>

int main() {
	for (int i = 0; i < 100; i++) {
		int pflag = 0;
		if (i % 3 == 0) {
			printf("Fizz");
			pflag = 1;
		}
		if (i % 5 == 0) {
			printf("Buzz");
			pflag = 1;
		}
		if (pflag == 0) {
			printf("%d", i);
		}
		printf("\n");
	}
	return 0;
}
