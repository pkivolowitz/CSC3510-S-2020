#include <stdio.h>

int main() {
	int i = 0;
top:
	if (i >= 100) 
		goto bottom;
	int pflag = 0;

	if (i % 3 != 0) 
		goto test5;
	printf("Fizz");
	pflag = 1;

test5:
	if (i % 5 != 0)
		goto testNumber;
	printf("Buzz");
	pflag = 1;

testNumber:
	if (pflag != 0)
		goto pnl;
	printf("%d", i);

pnl:
	printf("\n");
	i = i + 1;
	goto top;
bottom:
	return 0;
}
