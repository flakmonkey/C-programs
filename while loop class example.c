#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int count = 0;
	
	do {
		printf("Hello\n");
		count += 1;
	} while (count < 10);
	
	return EXIT_SUCCESS;
}
	