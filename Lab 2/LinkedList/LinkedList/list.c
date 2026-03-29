#include "list.h"
#include <stdlib.h>
#include <assert.h>

/*It is allowed to add your own helper functions. However, the already existing functiondeclarations (function heads) are not allowed to be changed.
 */

 /*
  Helper function to add.
  Allocate memory for a new node. If the allocation is successful, initialize data and pointer (pointer is initialized to NULL).
  The new node (or NULL) are returned.
 */
static struct node* createListNode(const Data data)
{
	assert(data != NULL); //Testar att det är något värde på data som skickas in

	struct node* temp = (struct node*)malloc(1 * sizeof(struct node));
	if (temp != NULL)
	{
		temp->data = data; //Lägger in data som skickas in i funktione
		temp->next = NULL; //Ser till att nya noods next är NULL

		return temp;
	}
	else
	{
		printf("Error: No memory");
		return NULL;
	}

}

List createEmptyList(void)
{
	return NULL;
}


/*Is the list empty?
  Return 1 if empty, 0 is not.*/
int isEmpty(const List list)
{
	if (list == NULL)
		return 1; 
	else return 0;
}

/*
 Add a node first in the list.
 Postcondition: The new data is first in the list (test with assert)
 */
void addFirst(List* list, const Data data)
{

	assert(data != NULL);
	List addfirst = createListNode(data);
	if (addfirst != NULL) //Testa om minet gick att få
	{
		if (*list == NULL) //Kollar om det finns någon lista, ej länka till första nood 
		{
			(*list) = addfirst;
		}
		else //länkar om nya nooden så head pekar på nya nood och nya nood pekar på den förra som låg först
		{
			addfirst->next = (*list);
			(*list) = addfirst;
		}
	}
	assert((*list) == addfirst); //Testa om nya data är först i listan 

	//Call createListNode to create the new node.
	//Don't forget to test that memory allocation was successful.
	//Remember that the list may be empty when a new node is added.
}

/*
 Add a node last in the list.
 Tip: When you find the right position you can use the function addFirst to insert the node.
 */
void addLast(List* list, const Data data)
{
	List addlast = createListNode(data);
	if (addlast != NULL) //testa om det gick att skapa minne
	{
		if (*list == NULL) //Om de fanns någon lista från början
		{
			(*list) = addlast;
		}
		else //Pekar om sisista nood till den nya sista noden

		{
			List step = (*list);

			while (step->next != NULL) //Stepar igenom listan för kolla efter vart de inte pekar någon stans
			{
				step = step->next;

			}
			step->next = addlast;

		}
	}

}

/*
 Remove the first node from the listTa bort forsta noden i listan.
 The node shoul be linked out of the list and its memory should be freed, the rest of the list should remain.
 Precondition: the list is not empty (test with assert).
 */

void removeFirst(List* list)
{
	assert(list != NULL); //Kollar om de finns någon lista

	List removefirst = (*list); //Skapar en nood så head inte tappar handtaget


	if ((removefirst->next) != NULL) //Kollar om det bara ett nood i listan eller flera. Sätt 
	{
		(*list) = removefirst->next;
	}
	else
	{
		(*list) = NULL;
	}
	free(removefirst);
	removefirst = NULL;





	//Don't forget to free the memory for the removed node.
	//Remember that the head of the list needs to be updated.
}

/*
 Remove the last node in the list.
 Precondition: The list is not empty (test with assert).
 */
void removeLast(List* list) // Lom de finns bara en länka till head? 
{

	assert(list != NULL); //Kollar om de finns någon lista

	if ((*list)->next == NULL) //En nod i listan, ta bort den
	{
		free(*list);
		*list = NULL;
	}
	else
	{
		List step = (*list), prev = (*list);

		while (step->next != NULL) {
			prev = step;
			step = step->next;
		}

		free(step);
		prev->next = NULL;
	}
}

//Don't forget to free the memory for the removed node.
//Remember to update the pointer in the new last node.


/*
 Remove data from list (first occurence).
 Return 1 if data is found, 0 if not found.
 Tip: when you find the correct node, you can use one of the above functions to remove the node.
 */
int removeElement(List* list, const Data data)
{
	List step = (*list), prev = NULL;

	if (step != NULL && step->data == data) //Om de är första data som skall ta bort i listan 
	{
		(*list) = step->next; 
		free(step); 
		return 1; 
	}

	while (step != NULL) //Går genom listan
	{
		if (step->data == data) //Hitta rätt data i listan
		{
			prev->next = step->next; //Peka om den inann de som skall ta bort till den efter 

			free(step);

			return 1;
		}
		else 
		{
			prev = step; //Släpande pekare
			step = step->next;
		}
	}
	return 0;

}


/*
 Is the data in the list?Finns data i listan?
 Return 1 if data is found, 0 if not found.
 Remember that the list may be empty.
*/
int search(const List list, const Data data)
{
	if (list == NULL) //Är listan tom från början
		return 0;

	List step = list;

	while (step != NULL) //Går igenom listan tillslutet 
	{
		if (step->data == data) //Hitta rätt data i listan går ut funktionen
		{

			return 1;
		}
		step = step->next;
	}
	return 0; //Gått till slutet utan att hitta värdet 
}

/*Return number of nodes in list.*/
int numberOfNodesInList(const List list)
{
	if (list == NULL) //Är listan tom från början
	{
		return 0;
	}

	List step = list;
	int count = 0;

	while (step != NULL) //Går igenom listan, var gång den går in plussa på count 
	{
		count += 1;
		step = step->next;
	}
	return count; //räknar antal nooder
}

/*
 Remove all nodes from the list.
 Don't forget to free the dynamic memory.
 Postcondition: The list is empty, *list is NULL (test with assert).
*/
void clearList(List* list)
{
	while ((*list) != NULL) //Går till slutat av listan och ta bort den baklängelse 
		removeLast(list);
	assert(*list == NULL);
	//All nodes must be de-allocated one by one. It is not enough to only free the list pointer.
}

/*
 Print the list.
 In the function call, stdout should be given as argument 2 (to print to the screen).
 Use fprintf to the the print out.
 This kind of print out function is more general since it can be used both to write to the console but also to external files.
*/
void printList(const List list, FILE* textfile)
{
	assert(textfile != NULL);

	List pprint = list;

	while (pprint != NULL) //går till slutet. 
	{

		fprintf(stdout, " \n%d", pprint->data);

		pprint = pprint->next;
	}

}

/*
 Return the first data in the list.
 Precondition: The list is not empty (tesst with assert).
*/
Data getFirstElement(const List list)
{
	assert(list != NULL);

	return list->data;


}

/*
 Return last data in the list
 Precondition: The list is not empty (test with assert).
*/
Data getLastElement(const List list)
{
	assert(list != NULL);
	List getlastelement = list;

	while (getlastelement->next != NULL) //Går igenom listan, går ut loop om hittar värde eller slutet 
	{

		getlastelement = getlastelement->next; //Stega så de kommer till slutat av listan 
	}

	return getlastelement->data; //Sista noods data

}

