/*
 * main.h
 *
 *  Created on: Nov 10, 2011
 *      Author: brett
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"

Contact* populateList(char* data);
Contact* editContactInfo(Contact* editContact);
char* readFileToString(char* path);
int validateScheme(char* scheme);
int saveContactList(char* path);
void printMenu();
void printContact(Contact* curContact, int printNotes);
void printAddressBook();

Contact* top;

#endif /* MAIN_H_ */
