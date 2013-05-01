

int main(void) {
	int randomValue;
	int done = 0;
	int usersGuess;
	char buffer[1000 + 1];
	int numbOfGuesses = 0;
	
	puts("Higher / Lower v1.0"); 
	
	// compute a random number 
	srand(time(0));
	randomValue = rand() % 1000 + 1;
	
	// keep asking the user for a number, give them a higher or lower
	// hint, and exit when they guess the number
	do {
		printf("\nEnter a value: ");
		usersGuess = atoi(gets(buffer));
		
		numbOfGuesses++;
		
		if (usersGuess > randomValue)
			printf("\nLower");
		else if(usersGuess < randomValue)
			printf("\nHigher");
		else
			done = 1;

	} while(!done);
	
	printf("\nYou got it!");
	// Print out the number of guesses
	return 0;
}
	
	/*
	int count = 0;
	
	do {
		printf("Hello\n");
		count += 1;
	} while (count < 10);
	
	return EXIT_SUCCESS;
	*/
	
