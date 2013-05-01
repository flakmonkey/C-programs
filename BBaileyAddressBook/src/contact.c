/*
 * contact.c
 *
 *  Created on: Nov 10, 2011
 *      Author: brett
 */

#include "contact.h"

Contact* createContact(char* last) {
	Contact* newContact;
	if ((newContact = (Contact *) malloc(sizeof(Contact))) == NULL) // not enough memory
		return NULL;
	strcpy(newContact->last, last);
	newContact->prev = NULL;
	newContact->next = NULL;
	return newContact;
}

Contact* insertContact(Contact* prevContact, char* last) {
	Contact* newContact = createContact(last);

	if (prevContact) {
		newContact->prev = prevContact;
		newContact->next = prevContact->next;
		prevContact->next = newContact;
		if (newContact->next) /* Verify there is a next node� */
			newContact->next->prev = newContact;

	} else /* insert node at top of list */
	{
		newContact->prev = NULL; /* for clarity */
		newContact->next = top;
		if (top)
			top->prev = newContact;
		top = newContact;
	}

	return newContact;
}

Contact* deleteContact(Contact* delContact) {
	Contact* ptReturn;

	if (delContact == NULL)
		return NULL; /* safety check */

	if (delContact == top) { /* delete top node */
		if (delContact->next) { /* not the only node in list */
			ptReturn = delContact->next;
			top = ptReturn;
			ptReturn->prev = NULL;
		} else { /* only node in list */
			ptReturn = NULL;
			top = NULL;
		}
	} else { /* not deleting top node */
		if (delContact->next) {/* not the last node in the list */
			ptReturn = delContact->next;
			ptReturn->prev = delContact->prev;
			delContact->prev->next = ptReturn;
		} else {/* deleting last node in list */
			ptReturn = delContact->prev;
			ptReturn->next = NULL;
		}
	}
	free(delContact);
	return (ptReturn);
}

Contact *findContact(char *last) {
	Contact *cursor = top;
	do {
		if (!strcmp(cursor->last, last))
			return cursor;
		else
			cursor = cursor->next;
	} while (cursor);
	return NULL;
}

/* To move a node to the start of the list, set ptPrevAfter to NULL */
void moveContact(Contact *moveContact, Contact* after) {

	/* safety checks */
	if (moveContact == NULL)
		return; /* No node to move */

	if (moveContact == after)
		return; /* Trying to move nowhere */

	if (moveContact == top) {
		if (moveContact->next == NULL)
			return; /* Only one node in list */

		if (after == NULL)
			return; /* Trying to move top node to top */
	}

	if (moveContact->prev)
		moveContact->prev->next = moveContact->next; /* Not moving top */
	else
		top = moveContact->next; /* Moving top node */

	if (moveContact->next)
		moveContact->next->prev = moveContact->prev; /* Not moving end node */

	if (after) /* not moving node to top */
	{
		if (after->next) /* Moving to the end of list ? */
			after->next->prev = moveContact;
		moveContact->next = after->next;
		after->next = moveContact;
		moveContact->prev = after;
	} else /* moving node to top */
	{
		top->prev = moveContact;
		moveContact->next = top;
		moveContact->prev = NULL;
		top = moveContact;
	}
} /* MoveNode */

void sortAddressBook() {
	Contact* min = top;
	Contact* cursor;
	Contact* swapWithMe;
	Contact* temp;

	if (top == NULL)
		return;
	else if (top->next == NULL) //zero or one contact in the list -- i.e. already sorted
		return;
	else {
		do {
			swapWithMe = min;
			cursor = min->next;
			while (cursor) {
				if (strcmp(min->last, cursor->last) > 1) {
					min = cursor;
				}
				cursor = cursor->next;
			}
			temp = min;
			moveContact(min, swapWithMe);
			moveContact(swapWithMe, temp);
			min = min->next;
		} while (min->next);
	}
}
