#include "set.h"
#include <assert.h>

/*
 Here it is important to re-use code you have already written for the
 linked list. Re-using don't mean to copy the code or writing the code
 again, you re-use code by calling the function with the functionality you
 want to re-use.
*/

/* This function is complete*/
Set initializeSet(void)
{
	return createEmptyList();
}

/* Postcondition: 'element' is in the set (tip, use isInSet() to verify). */
void addToSet(Set* set, const Data element)
{

	if (0 == isInSet(*set, element))
		addFirst(set, element);
	assert(isInSet(*set, element) == 1);

	//Remember to not at elements that are already in the set.
}

/* Postcondition: 'element is no longer in the set (tip: use isInSet() to verify).*/
void removeFromSet(Set* set, const Data element)
{
	if (isInSet(*set, element) == 1)
	removeElement(set, element); 
	assert(isInSet(*set, element) == 0);
}


int isInSet(const Set set, const Data element)
{
	return search(set, element);


}

/* Use for testing */
void printSet(const Set set, FILE* textfile)
{
	printList(set, textfile);

}


