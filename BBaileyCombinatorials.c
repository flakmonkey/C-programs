/*
 ============================================================================
 Name        : BBaileyCombinatorials.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int check(int, int);
void err_msg();
int comb(int, int);
int fact(int);

int main(void) {
	int n;
	int r;
	int result;
	int notDone = 1;
	char buffer[BUFSIZ + 1];

FILE	*combFile;
	combFile = fopen("comb.txt", "w");

	printf("BBaileyCombinatorials.c v1");

	do {
		printf("\n\nEnter n: ");
		n = atoi(gets(buffer));

		printf("\nEnter r: ");
		r = atoi(gets(buffer));

		if (n >= 0 && r >= 0) {
			if (check(n, r)) {
				result = comb(n, r);
				printf("\nResult: %d", result);
				fprintf(combFile, "n: %d, r: %d\n", n, r);
				fprintf(combFile, "Result: %d\n", result);
			} else
				err_msg();
		} else
			notDone = 0;
	} while (notDone);

	fclose(combFile);
	printf("\nGoodbye.");

	getchar();

	return EXIT_SUCCESS;
}

int check(int n, int r) {
	if (r > n) {
		return 0;
	} else
		return 1;
}

void err_msg() {
	printf("\nInvalid parameters.");
}

int comb(int n, int r) {
	int result = fact(n) / (fact(r) * fact(n - r));
	return result;
}

int fact(int n) {
	if (n <= 1)
		return 1;
	else
		return n * fact(n - 1);
}
