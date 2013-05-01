/*
 ============================================================================
 Name        : BBaileyAddressBook.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "main.h"

int main(void) {
	char buf[BUFSIZ + 1];
	char* stringFromFile;
	int choice = 0;
	Contact* currentContact = NULL;

	//get input file path
	//load contacts from file
	int done = 0;
	while (!done) {
		printf("Enter contact list path: ");
		gets(buf);
		if (strcmp(buf, "\0")) { //get path from user, check if path is entered
			stringFromFile = readFileToString(buf);
			if (!stringFromFile) {
				printf("\nError opening file.\n");
			} else {
				currentContact = populateList(stringFromFile);
				done++;
			}
		} else
			done++;
	}

	printf(
			"Enter the # of the command you wish to execute, then press <RETURN>");

	while (choice != 9) {
		printMenu();

		if (currentContact)
			printContact(currentContact, 0);

		printf("\nEnter menu choice: ");

		choice = atoi(gets(buf));
		switch (choice) {
		case 1: // next contact
			if (currentContact) {
				if (currentContact->next)
					currentContact = currentContact->next;
				else {
					printf("\nNo more contacts.");
					getchar();
				}
			} else {
				printf("\nNo contacts in list.");
				getchar();
			}
			break;
		case 2: // previous contact
			if (currentContact) {
				if (currentContact->prev)
					currentContact = currentContact->prev;
				else {
					printf("\nNo previous contacts.");
					getchar();
				}
			} else {
				printf("\nNo contacts in list.");
				getchar();
			}
			break;
		case 3: // add after current contact
			currentContact = insertContact(currentContact, "");
			editContactInfo(currentContact);
			break;
		case 4: // delete current contact
			if (currentContact) {
				currentContact = deleteContact(currentContact);
			} else {
				printf("\nNo contacts in list.");
				getchar();
			}
			break;
		case 5: // edit current contact
			if (currentContact) {
				editContactInfo(currentContact);
			} else {
				printf("\nNo contacts in list.");
				getchar();
			}
			break;
		case 6: // sort contact list
			sortAddressBook();
			break;
		case 7: // find contact by last name
			if (currentContact) {
				Contact *foundContact;
				printf("\nSearch for (last name): ");
				if ((foundContact = findContact(gets(buf))))
					currentContact = foundContact;
				else
					printf("\nUnable to find contact.\n");
				getchar();
			} else {
				printf("\nNo contacts in list.");
				getchar();
			}
			break;
		case 8: // print contact list
			if (currentContact) {
				printAddressBook(currentContact);
				getchar();
			} else {
				printf("\nNo contacts in list.");
				getchar();
			}
			break;
		default: // exit program
			break;
		}
	}
	return EXIT_SUCCESS;
}

char* readFileToString(char* path) {
	FILE *fp;
	long fileSize;
	char* text;

	fp = fopen(path, "r");

	if (fp) {
		// Determine number of floats in the file
		fseek(fp, 0, SEEK_END); // Seek the end of the file
		fileSize = ftell(fp); // Ask for the file position marker position
		rewind(fp); // Rewind so that we can read in the text

		// Dynamically allocate enough space for the file and a null terminator
		text = malloc(fileSize + 1);
		fread(text, sizeof(char), fileSize, fp);
		text[fileSize] = '\0';
		fclose(fp);
	} else {
		return NULL;
	}
	return text;
}

Contact *editContactInfo(Contact *editContact) {
	char buf[BUFSIZ + 1];
	char *choice;

	while (choice[0] != 'Q') {

		printf("\nEditing information for:");
		printContact(editContact, 1);

		printf("\nEnter the character in parenthesis to select a field.");
		printf(
				"\n(F)irst Name, (L)ast Name, Email(1), Email(2), (N)otes, (Q)uit");
		printf("\n\nEnter a character: ");

		choice = gets(buf);

		switch (choice[0]) {
		case 'F':
			printf("\nEnter first name: ");
			strcpy(editContact->first, gets(buf));
			break;
		case 'L':
			printf("Enter last name: ");
			strcpy(editContact->last, gets(buf));
			break;
		case '1':
			printf("Enter email #1: ");
			strcpy(editContact->email1, gets(buf));
			break;
		case '2':
			printf("Enter email #2: ");
			strcpy(editContact->email2, gets(buf));
			break;
		case 'N':
			printf("Enter notes (or leave blank):");
			strcpy(editContact->notes, gets(buf));
			break;
		default:
			break;
		}
	}

	return editContact;
}

Contact *populateList(char* data) {
	char *chunk;
	char *delims = ",\n";
	int scheme;
	int lineCount = 0;
	int count = 0;
	Contact *curContact = NULL;

	//get scheme at top of file
	if ((chunk = strtok(data, "\n"))) {
		if ((scheme = validateScheme(chunk))) {
			if ((chunk = strtok(NULL, delims))) {
				lineCount = atoi(chunk);
			}
			while ((chunk = strtok(NULL, delims)) && count < lineCount) {
				curContact = insertContact(NULL, chunk);
				chunk = strtok(NULL, delims);
				strcpy(curContact->first, chunk);
				chunk = strtok(NULL, delims);
				strcpy(curContact->email1, chunk);
				chunk = strtok(NULL, delims);
				strcpy(curContact->email2, chunk);
				if (scheme == 2) {
					chunk = strtok(NULL, "\""); //notes are quoted
					strcpy(curContact->notes, chunk);
				}
				count++;
			}
		} else {
			printf("\nUnsupported scheme in specified data file.");
			return NULL;
		}
	} else
		return NULL;
	return curContact;
}

int validateScheme(char *scheme) {
	char *baseScheme = "LastName,FirstName,Email1,Email2";
	char notesScheme[256];
	strcpy(notesScheme, baseScheme);
	strcat(notesScheme, ",Notes");
	if (!strcmp(scheme, baseScheme))
		return 1; // no notes
	else if (!strcmp(scheme, notesScheme))
		return 2; // notes enabled
	else
		return 0;
}

int saveContactList(char *path) {
	Contact *cursor = top;
	int count = 0;
	FILE *fp = fopen(path, "w");

	if (fp == NULL)
		return 0;

	while(cursor) {
		count++;
		cursor = cursor->next;
	}

	cursor = top;

	fprintf(fp,"LastName,FirstName,Email1,Email2,Notes\n");
	fprintf(fp,"%d\n",count);

	while (cursor) {
		fprintf(fp, "%s,%s,%s,%s,%s\n", cursor->last, cursor->first,
				cursor->email1, cursor->email2, cursor->notes);
		cursor = cursor->next;
	}
	fclose(fp);
	return 1;
}

void printMenu() {
	printf(
			"\n1) Next Contact\n2) Previous Contact\n3) Add After Current Contact");
	printf(
			"\n4) Delete Current Contact\n5) Edit Current Contact\n6) Sort list by last name");
	printf("\n7) Seach by Last Name\n8) Print Contact List\n9) Exit Program\n");
}

void printContact(Contact* curContact, int printNotes) {
	if (curContact) {
		printf("\nFirst:\t%s", curContact->first);
		printf("\nLast:\t%s", curContact->last);
		printf("\nemail1:\t%s", curContact->email1);
		printf("\nemail2:\t%s", curContact->email2);
		if (printNotes)
			printf("\nnotes:\t%s", curContact->notes);
		printf("\n");
	} else
		printf("No contacts in list.");
}

void printAddressBook() {
	Contact* cursor = top;
	while (cursor) {
		printContact(cursor, 1);
		cursor = cursor->next;
	}
}
