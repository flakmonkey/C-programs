/*
 ============================================================================
 Name        : BBaileyHTMLImageEstimator.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

long estimateImageContent(char *html, int *pNumberOfImages);
int textFileToString(char *textFileString, char *path);
void stringLower(char *string);
int dimInPixels(char *cursor);
void printOutput(char *path, int images, long pixels);

int main(void) {
	char path[BUFSIZ + 1];
	char html[80000];
	int numberOfImages;
	long totalPixels;
	int done = 0;

	printf("BBaileyHTMLImageEditor v0.1\n");

	do {
		//initialize variables
		html[0] = '\0';
		numberOfImages = 0;
		totalPixels = 0;

		//if valid path is given, calculate # of images and pixel area
		if (textFileToString(html, path)) {
			totalPixels = estimateImageContent(html, &numberOfImages);
			printOutput(path, numberOfImages, totalPixels);
			//if blank path is given end the program
		} else if (path[0] = '\0')
			done++;
		//if path is not blank or valid prompt for re-entry
		else
			printf("Invalid path.");
	} while (!done);
	return EXIT_SUCCESS;
}

long estimateImageContent(char *html, int *pNumberOfImages) {
	char *cursor = html;
	int numPixels = 0;

	*pNumberOfImages = 0;

	stringLower(html);

	//check if there is a background tag
	if (strstr(cursor, "background") != NULL) {
		*pNumberOfImages += 1;
	}

	//count img tags in hmtl and total pixel values
	while ((cursor = strstr(cursor, "<img")) != NULL) {
		cursor++;
		numPixels += dimInPixels(cursor);
		*pNumberOfImages += 1;
	}
	return numPixels;
}

//generic function to get get a string from a text file
int textFileToString(char *textFileString, char *path) {
	printf("\nEnter file path: ");
	FILE *textFile = fopen(gets(path), "r");

	if (textFile) {
		char line[1000];
		while (fgets(line, 1000, textFile)) {
			strcat(textFileString, line);
		}
	} else {
		return 0;
	}
	return 1;
}

void stringLower(char *string) {
	int i;
	for (i = 0; string[i] != '\0'; i++) {
		string[i] = (char) tolower(string[i]);
	}
}

int dimInPixels(char *cursor) {
	int x, y = 0;
	char *tempCursor = cursor;
	//look for width and height

	if ((tempCursor = strstr(tempCursor, "width")) != NULL) {
		while (!isdigit(*tempCursor)) {
			tempCursor++;
		}
		x = atoi(tempCursor);
	}
	tempCursor = cursor;
	if ((tempCursor = strstr(tempCursor, "height")) != NULL) {
		while (!isdigit(*tempCursor)) {
			tempCursor++;
		}
		y = atoi(tempCursor);
	}
	return x * y;
}

void printOutput(char *path, int images, long pixels) {
	printf("\nFile path: %s/%s", getcwd(NULL, 0), path);
	printf("\nNumber of images: %d", images);
	printf("\nTotal screen area in square pixels: %ld\n", pixels);
}
