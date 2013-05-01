#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
	float testScore;
	char buffer[BUFSIZ + 1];char
	menuSelection;
	int numbOfScores = 0;
	int set = 1;
	int done = 0;
	int noMoreScores = 0;
	float low = 100;
	float high = 0;
	float sum = 0;
	float sumSquares = 0;
	float standardDeviation;

	FILE *statsFile;

	statsFile = fopen("Statistics.dat", "w");

	printf("***** TEST SCORES STATISTICS v2.0 *****");

	do {
		printf("\n\n\n[C] Clear Stats");
		printf("\n[E] Enter Test Scores");
		printf("\n[D] Display Test Score Stats");
		printf("\n[Q] Quit");
		printf("\n\nType the letter of your selection and press <ENTER>\n\n>>");

		gets(buffer);
		menuSelection = buffer[0];

		switch (menuSelection) {
		case 'C':
			low = 100;
			high = 0;
			numbOfScores = 0;
			sum = 0;
			standardDeviation = 0;
			set++;
			break;
		case 'E':
			noMoreScores = 0;
			do {
				printf("\nEnter a test score: ");
				testScore = atof(gets(buffer));
				if (testScore) {
					if (testScore < low) {
						low = testScore;
					}

					if (testScore > high) {
						high = testScore;
					}

					sum += testScore;
					sumSquares += pow(testScore, 2);
					numbOfScores++;
				} else
					noMoreScores = 1;
			} while (!noMoreScores);
			break;
		case 'D':
			printf("\nSet #%d", set);
			printf("\nNumber of Test Scores = %d", numbOfScores);
			printf("\nLow Score = %.2f", low);
			printf("\nHigh Score = %.2f", high);
			printf("\nAverage Score =  %.2f", sum / numbOfScores);

			fprintf(statsFile, "\nSet #%d", set);
			fprintf(statsFile, "\nNumber of Test Scores = %d", numbOfScores);
			fprintf(statsFile, "\nLow Score = %.2f", low);
			fprintf(statsFile, "\nHigh Score = %.2f", high);
			fprintf(statsFile, "\nAverage Score =  %.2f", sum / numbOfScores);

			standardDeviation = sqrt(
					(sumSquares - (pow(sum, 2) / numbOfScores)) / numbOfScores);

			printf("\nStandard Deviation =  %.2f", standardDeviation);
			fprintf(statsFile, "\nStandard Deviation =  %.2f", standardDeviation);
			break;
		case 'Q':
			done = 1;
			break;
		default:
			printf("Try again.");
			break;
		}
	} while (!done);

	fclose(statsFile);

	// Print out the number of guesses
	return EXIT_SUCCESS;
}
