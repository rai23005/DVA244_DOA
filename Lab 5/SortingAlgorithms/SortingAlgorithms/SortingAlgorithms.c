#define _CRT_SECURE_NO_WARNINGS
#include "SortingAlgorithms.h"
#include "Statistics.h"
#include "Array.h"
#include <assert.h>
#include <string.h>

int placepivotright(ElementType* arrayToSort, int size, Statistics* statistics);

int isImplemented(SortingAlgorithm algorithm)
{
	switch (algorithm)
	{
	case BUBBLE_SORT:
		//      case INSERTION_SORT:
	case SELECTION_SORT:
		     case QUICK_SORT:
		//      case MERGE_SORT:
		return 1;
	default:
		return 0;
	}
}

/*Number of swaps in one and the same algorithm can be different depending
 on the implementation. Sometimes the data is already in the rigth place,
 then you can choose to test it and not make a swap (which gives an extra
 comparison), or you can choose to make a swap anyway (with oneself)
 without testing (which gives an extra swap). If you follow the algorithms
 we have worked through in class exactly, you will make a swap even when
 the element is in the correct position.
 When analysing the generated data (result.txt) you need to have this in
 mind.*/

 /******************************************************************************************/
 /*Here you will implement your algorithms*/



static void bubbleSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{


	int bytte = 1; // Gå ut loppen om vi inte gör bytten, 1=de är sant

	for (int i = 0; lessThan(i, (size - 1), statistics) && bytte; i++) //För antal tal som ev behövers byttas
	{
		bytte = 0; // Koll om vi har gjort bytte eller ej


		for (int j = 0; lessThan(j, (size - 1 - i), statistics); j++) // Jämför med talet 
		{

			if (greaterThan(arrayToSort[j], arrayToSort[j + 1], statistics)) // Flytta större tal till höger
			{

				swapElements(&arrayToSort[j], &arrayToSort[j + 1], statistics);

				bytte = 1; // Vi gör byte, stannar kvar i (i) lopen 
			}
		}

	}

	/*
	int bytte = 1; // Gå ut loppen om vi inte gör bytten, 1=de är sant

for (int i = 0; i < size - 1 && bytte; i++) // För antal tal som eventuellt behöver bytas
{
	bytte = 0; // Koll om vi har gjort bytte eller ej

	for (int j = 0; j < size - 1 - i; j++) // Jämför med talet
	{
		if (arrayToSort[j] > arrayToSort[j + 1]) // Flytta större tal till höger
		{
			int temp = arrayToSort[j];
			arrayToSort[j] = arrayToSort[j+1];
			arrayToSort[j+1] = temp;
			bytte = 1; // Vi gör byte, stannar kvar i (i) lopen
		}

		void swapElements(ElementType* element1, ElementType* element2, Statistics* statistics)
{
	assert(element1 != NULL && element2 != NULL);

	ElementType temp = *element1;
	*element1 = *element2;
	*element2 = temp;

	}
}*/




}

static void insertionSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{
}

static void selectionSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{

	
	for (int i = 0; lessThan(i, size - 1, statistics); i++)
	{
		int minstadata = arrayToSort[i];
		int minstaindex = i;

		for (int j = i; lessThan(j, size, statistics); j++)
		{
			 //True if element1 > element2
			if (greaterThan(minstadata, arrayToSort[j], statistics))
			{
				minstadata = arrayToSort[j];
				minstaindex = j;
			}
		}

		//Swaps element 1 and element 2, with statistics.
		swapElements(&arrayToSort[i], &arrayToSort[minstaindex], statistics);
		
	}


	/*
	for (int i = 0; i < size - 1; i++) //Antal gånger man måste sortera
	{
		int minstadata = arrayToSort[i];
		int minstaindex = i;

		for (int j = i; j < size; j++) //Gå igenom leken
		{
			if (minstadata > arrayToSort[j]) //KOlla vilket värde som är minst
			{
				minstadata = arrayToSort[j];
				minstaindex = j;
			}
		}
		//Bytter plats så minsta värdet blir utsorterad
		int temp = arrayToSort[i];
		arrayToSort[i] = minstadata;
		arrayToSort[minstaindex] = temp;

	}
	*/


}

static void mergeSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{
}


int placepivotright(ElementType* arrayToSort, int size, Statistics* statistics)  //hjälp funktion för quicsort skall fungera
{
	int pivot = arrayToSort[size - 1];
	int i = -1; // Index för mindre element

	
	for (int j = 0; lessThan(j, size-1, statistics); j++) {
		if (arrayToSort[j] <= pivot) {
			i++;
			swapElements(&arrayToSort[i], &arrayToSort[j], statistics); //Flytta alla värden mindre än pivot mot vänster
		}
	}

	// Sätter pivot längst till höger om "vänstra delen"
	swapElements(&arrayToSort[i + 1], &arrayToSort[size - 1], statistics);

	return (i + 1); // Returnera var pivots ligger plats
}

static void quickSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{

	
	if (lessThanOrEqualTo(size, 1, statistics))
	{
		return;  // Arrayen är redan sorterad om storleken är 1 eller mindre
	}

	int pi = placepivotright(arrayToSort, size, statistics);

	// Kalla på quickSort för vänstra och högra delen av arrayen
	quickSort(arrayToSort, pi, statistics);
	quickSort(arrayToSort + pi + 1, size - pi - 1, statistics);
}
/******************************************************************************************/


char* getAlgorithmName(SortingAlgorithm algorithm)
{
	/*Isn't the string we allocated local in the function?
	  No, not in this case. String constants is a special case in C.*/
	switch (algorithm)
	{
	case BUBBLE_SORT:    return "  Bubble sort ";
	case SELECTION_SORT: return "Selection sort";
	case INSERTION_SORT: return "Insertion sort";
	case MERGE_SORT:     return "  Merge sort  ";
	case QUICK_SORT:     return "  Quick sort  ";
	default: assert(0 && "Invalid algorithm!"); return "";
	}
}

//Sorts 'arrayToSort' with 'algorithmToUse'. Statistics for all swaps and comparisons will go into *statistics
static void sortArray(ElementType* arrayToSort, unsigned int size, SortingAlgorithm algorithmToUse, Statistics* statistics)
{
	if (statistics != NULL)
		resetStatistics(statistics);

	switch (algorithmToUse)
	{
	case BUBBLE_SORT:     bubbleSort(arrayToSort, size, statistics); break;
	case SELECTION_SORT: selectionSort(arrayToSort, size, statistics); break;
	case INSERTION_SORT: insertionSort(arrayToSort, size, statistics); break;
	case MERGE_SORT:     mergeSort(arrayToSort, size, statistics); break;
	case QUICK_SORT:     quickSort(arrayToSort, size, statistics); break;
	default:
		assert(0 && "Invalid algorithm!");
	}
}

//Prepares arrays for sorting by allocating memory for them and initializing them.
static void prepareArrays(SortingArray sortingArray[], SortingAlgorithm algorithm, const ElementType* arrays[], const unsigned int sizes[])
{
	assert(isImplemented(algorithm));

	int i;
	int totalArraySize;

	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		totalArraySize = sizeof(ElementType) * sizes[i];
		sortingArray[i].arrayToSort = malloc(totalArraySize);
		memcpy(sortingArray[i].arrayToSort, arrays[i], totalArraySize);

		sortingArray[i].algorithm = algorithm;
		sortingArray[i].arraySize = sizes[i];
		resetStatistics(&sortingArray[i].statistics);
	}
}

static void sortArrays(SortingArray toBeSorted[])
{
	int i;
	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		SortingArray* current = &toBeSorted[i];
		sortArray(current->arrayToSort, current->arraySize, current->algorithm, &current->statistics);

		if (!isSorted(current->arrayToSort, current->arraySize))
		{
			printf("Error! Algorithm %s has not sorted correctly!\n", getAlgorithmName(current->algorithm));
			printf("The result is: \n");
			printArray(current->arrayToSort, current->arraySize, stdout);
			assert(0); // Aktiveras alltid
		}
	}
}

void printResult(SortingArray sortedArrays[], FILE* file)
{
	assert(file != NULL);

	int i;
	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		fprintf(file, "%4u element: ", sortedArrays[i].arraySize);
		printStatistics(&sortedArrays[i].statistics, file);
		fprintf(file, "\n");
	}
	fprintf(file, "\n");
}

void sortAndPrint(SortingArray sortingArray[], SortingAlgorithm algorithm, const ElementType* arrays[], unsigned int sizes[], FILE* file)
{
	assert(file != NULL);

	prepareArrays(sortingArray, algorithm, arrays, sizes);
	sortArrays(sortingArray);
	printResult(sortingArray, file);
}

void freeArray(SortingArray sortingArray[])
{
	int i;
	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		if (sortingArray[i].arrayToSort != NULL)
			free(sortingArray[i].arrayToSort);
		sortingArray[i].arrayToSort = NULL;
		sortingArray[i].arraySize = 0;
		resetStatistics(&sortingArray[i].statistics);
	}
}

