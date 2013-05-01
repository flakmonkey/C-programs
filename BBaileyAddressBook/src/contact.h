/*
 * contact.h
 *
 *  Created on: Nov 10, 2011
 *      Author: brett
 */

#ifndef CONTACT_H_
#define CONTACT_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct contact Contact;
struct contact {
	char last[80];
	char first[80];
	char email1[128];
	char email2[128];
	char notes[1024];
	Contact* prev;
	Contact* next;
};

void sortAddressBook();
void moveContact(Contact* moveContact, Contact* after);
Contact* createContact(char* last);
Contact* insertContact(Contact* prevContact, char* last);
Contact* deleteContact(Contact* delContact);
Contact* findContact(char* last);


extern Contact* top;

#endif /* CONTACT_H_ */
