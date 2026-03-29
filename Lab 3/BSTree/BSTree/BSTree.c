#include "BSTree.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>


/*
 It is allowed to add you own helper functions. However, the existing functions may not be changed.
 Static helper functions are used by other functions in the tree (program), they should not be part
 of the interface (the used does not need to now about these).
*/

/*Stöd funktion som fyller i en array med alla värden i trädet */
static void fillarray(const BSTree tree, int* array, int* number);

static void fillarray(const BSTree tree, int* array, int* number)  //Funktion som fyller i array med alla värden från trädet
{

	if (tree != NULL)
	{
		array[(*number)] = tree->data;
		(*number)++;
		fillarray(tree->left, array, number);
		fillarray(tree->right, array, number);
	}

}

/*
 Create a tree node with the given data by allocating memory, don't forget to test and initialize
 struct members.
*/
static struct treeNode* createNode(int data)
{

	struct treeNode* temp = (struct treeNode*)malloc(1 * sizeof(struct treeNode));
	if (temp != NULL)
	{
		temp->data = data; //Lägger in data som skickas in i funktione
		temp->left = NULL; //Ser till att nya noods next är NULL
		temp->right = NULL; //Ser till att nya noods next är NULL

		return temp;
	}
	else
	{
		printf("Error: No memory");

		return NULL;
	}

}

/* Return a dynamically allocated array containing the data in the tree sorted */

static int* writeSortedToArray(const BSTree tree)
{
	assert(tree != NULL);
	int nodesintree = numberOfNodes(tree);
	int number = 0;
	int* array = (int*)malloc(nodesintree * sizeof(int)); //Skapa en array för lagra värden i
	if (array != NULL)
	{
		fillarray(tree, array, &number);
	}
	else
	{
		printf("NO memory for write sortet to array ");
		return NULL;
	}

	/* Create a dynamic array with the correct size.

	   Write data sorted (smallest to larges) from the tree to the aray.
	   - perhaps you might need a helper function here */

	return array; //Replace with correct return value
}

/* Build a sorted, balanced tree from the array */
static void buildTreeSortedFromArray(BSTree* tree, const int arr[], int size)
{
	/* Build recursively from the middle.
	   The middle element creates root in sub-tree.
	   Left sub-array builds left sub-tree.
	   Right sub-array builds right sub-tree.
	*/
	if (size <= 0)
	{
		return;
	}


	int mid = size / 2; //Mitten av array, ex 100/2 =50 

	insertSorted(tree, arr[mid]);
	buildTreeSortedFromArray(tree, arr, mid); //Skickar in då 50
	if (size - mid - 1 > 0) //array får inte bli mindre än 0
	{
		buildTreeSortedFromArray(tree, (arr + mid + 1), (size - mid - 1)); //Flytta array start så den börjar på index 51, då finns de bara 49 tall kvar från 100
	}




}

/* Implementation of the tree - the functions in the interface */

/* Create an empty tree - this function is completed. */
BSTree emptyTree(void)
{
	return NULL;
}

int isEmpty(const BSTree tree)
{
	if (tree == NULL)
		return 1;

	return 0; //Replace with correct return value
}

/* Post-condition: data is in the tree, sorted correctly */
void insertSorted(BSTree* tree, int data)
{
	struct treeNode* addleaf = createNode(data);

	if (addleaf != NULL)
	{
		if (*tree == NULL)  // Om trädet är tomt, sätt roten till den nya noden
		{
			(*tree) = addleaf;
		}
		else
		{

			struct treeNode* current = *tree;
			struct treeNode* parent = NULL; //Släpande pekare

			while (current != NULL) // Gå igenom trädet tills en lämplig plats hittas, current är NULL=slutat av trädet
			{
				parent = current;


				if (data == current->data) // Kontrollera om värdet redan finns i trädet, om ja gå ut funktionen
				{
					free(addleaf); //Frigör minnet som ej används
					return;
				}
				else if (data < current->data) // Gå till vänster om värdet är mindre än nuvarande nod
				{
					current = current->left;
				}
				else // Gå till höger om värdet är större än nuvarande nod
				{
					current = current->right;
				}
			}

			if (data < parent->data) //Släpande pekare som tar reda på vilken håll de de nya data skall sätta ditt.
			{
				parent->left = addleaf;
			}
			else
			{
				parent->right = addleaf;
			}
		}
	}
	assert(1 == find(*tree, data));
}

/* Remember that the tree may be empty here.
   You decide how duplicats are handled.
   Post-condition can be verifyed using find()
 */

 /*
   When calling: use stdio as second parameter to print to the conole/screen
   It is enought that you implement the LR-orders
  */
void printPreorder(const BSTree tree, FILE* textfile)
{

	if (tree != NULL)
	{
		fprintf(textfile, "%d\n", tree->data);
		printPreorder(tree->left, textfile);
		printPreorder(tree->right, textfile);
	}

}

void printInorder(const BSTree tree, FILE* textfile)
{
	if (tree != NULL)
	{
		printInorder(tree->left, textfile);
		fprintf(textfile, "%d\n", tree->data);
		printInorder(tree->right, textfile);
	}

}

void printPostorder(const BSTree tree, FILE* textfile)
{
	if (tree != NULL)
	{
		printPostorder(tree->left, textfile);
		printPostorder(tree->right, textfile);
		fprintf(textfile, "%d\n", tree->data);
	}

}

int find(const BSTree tree, int data)
{
	if (tree == NULL)
	{
		return 0;
	}
	struct treeNode* search = tree;
	struct treeNode* parent = NULL; //Släpande pekare

	while (search != NULL)
	{
		if (search->data == data) // Data finns i trädet 
		{
			return 1;
		}

		if (data < search->data) //Om värdet är mindre än i trädet, gå till vänster
		{
			search = search->left;
		}

		else //Annars går man till högre om data är högre 
		{
			search = search->right;
		}
	}

	return 0; //Om inget värde hittades i trädet 
}

void removeElement(BSTree* tree, int data)
{
	if (*tree == NULL)
	{
		return; // Tomt träd
	}

	struct treeNode* current = *tree;
	struct treeNode* parent = NULL;

	while (current != NULL)
	{
		if (data == current->data)
		{
			if (current->left == NULL && current->right == NULL) //Inget barn
			{

				if (parent == NULL) //Fanns bara ett värde i trädet 
				{

					free(*tree);
					*tree = NULL;
				}
				else if (parent->left == current) //Lövet satt på vänstra grenen
				{
					free(current);
					parent->left = NULL;
				}
				else //Lövet sitter på högra grenen
				{
					free(current);
					parent->right = NULL;
				}
			}
			else if (current->left == NULL || current->right == NULL) //Finns det bara ett barn
			{

				struct treeNode* child; //Skapa för länka farfar direkt till barnbarnet

				if (current->left != NULL) //Vilken sidan som är tomt, vilket värdet barnbarnet skall ha
				{
					child = current->left;
				}
				else
				{
					child = current->right;
				}
				if (parent == NULL) //Första värdet i trädet som skall bort
				{

					free(*tree);
					*tree = child;
				}
				else if (parent->left == current) //Om farfar vänstra gren pekar på de som skall bort
				{
					free(current);
					parent->left = child;
				}
				else
				{
					free(current);
					parent->right = child;
				}
			}
			else //Två barn 
			{

				struct treeNode* successor = current->right;
				struct treeNode* successorParent = current;

				while (successor->left != NULL) //Hitta minsta värdet på det högra gren av de som skall bort
				{
					successorParent = successor;
					successor = successor->left;
				}

				current->data = successor->data;


				if (successorParent == current)
					successorParent->right = successor->right;
				else
					successorParent->left = successor->right;

				free(successor);
			}


			return;
		}
		else if (data < current->data) //bestämma vilket håll man skall gå i trädet
		{
			parent = current;
			current = current->left;
		}
		else
		{
			parent = current;
			current = current->right;
		}
	}
}
/* No data should/can be removed from an empty tree.
 Three cases: Leaf (no children), One child (left or right), Two children

 Don't forget to free the dynamic memory for the removed node.
 */

int numberOfNodes(const BSTree tree)
{

	if (tree == NULL)
	{
		return 0;

	}

	return (1 + numberOfNodes(tree->left) + numberOfNodes(tree->right));

}

int depth(const BSTree tree)
{
	if (tree == NULL)
	{
		return 0;
	}

	int maxtoleft = depth(tree->left);
	int maxtoright = depth(tree->right);

	if (maxtoleft > maxtoright)
		return 1 + maxtoleft;
	else
		return 1 + maxtoright;

}

int minDepth(const BSTree tree)
{
	return ceil(log2(numberOfNodes(tree) + 1));

}

/*
 Postcondition:
	- tree has the same number of nodes as previously
	- the depth of the tree is the same as mindepth of the tree.
 */
void balanceTree(BSTree* tree)
{
	if (*tree == NULL)
	{
		return;
	}


	int* arr = writeSortedToArray(*tree);
	if (arr != NULL)
	{
		int nrofood = numberOfNodes(*tree);
		freeTree(tree);
		buildTreeSortedFromArray(tree, arr, nrofood);
		free(arr);

		/* Suggested algorithm:
		   - write the tree sorted to a dynamic array (writeSortedToArray)
		   - empty tree (freeTree)
		   - build tree recursively from array (buildTreeSortedFromArray)
		   - free memory for the dynamic array
		 */
		assert(nrofood == numberOfNodes(*tree));
		assert(minDepth(*tree) == depth(*tree));
	}
}

/*Postcondition: the tree is empty*/
void freeTree(BSTree* tree)
{

	if (*tree == NULL)
	{
		return;
	}

	freeTree(&(*tree)->right);
	freeTree(&(*tree)->left);

	free(*tree);
	*tree = NULL;


	assert(isEmpty(*tree) == 1);
}