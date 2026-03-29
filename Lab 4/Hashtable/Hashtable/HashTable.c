#define _CRT_SECURE_NO_WARNINGS // Needed in Visual Studio for some functions
#include "HashTable.h"
#include "Bucket.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


/*
 This function takes a key and returnes a hash-index (i.e. an index in the
 array/hashtable)
 */
static int hash(Key key, int tablesize) //Skapar Nyckel för hastabel
{
	return key % tablesize;

}

/*
 Searches according to the principle of linear probing.
 The number of collisions are returned via the pointer col in the parameter list
*/
static int linearProbe(const HashTable* htable, Key key, unsigned int* col) //Kollar om det är krockar 
{

	int hashIndex = hash(key, htable->size); //Start index i arrayen att kolal 

	for (int i = 0; i < htable->size; i++) 
	{
		
		if (htable->table[(hashIndex + i) % htable->size].key == UNUSED || htable->table[(hashIndex + i) % htable->size].key == key)
/* if, håller sig inom arrayen för hasindex startar sedan plusar ett, när samma värde som size blir storleken index noll i array, 
		Om de hittar tom plats eller om nyckel hittas så retuneras index platsen*/ 
		{
			return (hashIndex + i) % htable->size;


		}
		(*col)++; //Ha koll på antal krockar 
	}
	return -1; //Inget värde hittas 
}

/*Allocate memory for the hashtable*/

HashTable createHashTable(unsigned int size)
{
	HashTable* htable = (HashTable*)calloc(1, sizeof(HashTable)); 

	if (htable != NULL)
	{
		htable->size = size; //Storleken på hela arrayen
		htable->table = (struct Bucket*)calloc(size, sizeof(struct Bucket));//Skapa minne för buckets

		if (htable->table != NULL)
		{

			return *htable;
		}
		else
		{
			free(htable); //Gick inte att skapa buckets 
			printf("Memory error for bucket");
		}
	}
	else
	{
		printf("Memory error for hashtablet");

	}
	HashTable errorhtable = { 0, NULL }; //Skickar tillbaka ett tom
	return errorhtable;

}

/*
 Return number of collisions (calculated in linearProbe
 Postcondition: there is an element for key in the table (use loopup to verify)
*/

unsigned int insertElement(HashTable* htable, const Key key, const Value value)
{


	int hashIndex = hash(key, htable->size);
	int collisions = 0;

	int index = linearProbe(htable, key, &collisions);

	if (index != -1) // OM linearProbe Hittade tom plats (-1) -> Hittade ingen plats 
	{
		htable->table[index].key = key;
		htable->table[index].value = value;

	}
	assert(lookup(htable, key) != NULL);
	return collisions; // Retunera antal krockar som linearprob hittade
}

/*Postcondition: no element with key is in the table (use loopup to verify)*/

void deleteElement(HashTable* htable, const Key key)
{
	
	if (lookup(htable, key) == NULL) //Kollar om värdet finns 
	{
		return;
	}

	int collisions = 0;
	int index = linearProbe(htable, key, &collisions);

	if (index != -1)
	{
		htable->table[index].key = UNUSED; //NOllställer 

		struct Bucket* deletedValues = calloc(htable->size, sizeof(struct Bucket)); //Skapa en array för spara för sotering

		int deletedCount = 0;

		for (int y = index + 1; htable->table[(y) % htable->size].key != UNUSED; y++)  //Börja från plats efter och kör tills tomplats
		{
			deletedValues[deletedCount].key = htable->table[y % htable->size].key; //Spara ner nyckeln / värdet
			deletedValues[deletedCount].value = htable->table[y % htable->size].value; 
			deletedCount++;

			htable->table[y % htable->size].key = UNUSED; //Ta bort värdet
		}

		for (int j = 0; j < deletedCount; j++)
		{
			if (deletedValues[j].key != UNUSED) //Kör tills de inte blir en tomplats 
			{
				insertElement(htable, deletedValues[j].key, deletedValues[j].value); //Sätter tillbaka alla värderna i array
			}
		}

		free(deletedValues);

		assert(lookup(htable, key) == NULL);
		return;
	}
}

const Value* lookup(const HashTable* htable, const Key key)
{
	int hashIndex = hash(key, htable->size);
	int collisions = 0;

	for (int i = 0; i < htable->size; i++)
	{
		int currentIndex = (hashIndex + i) % htable->size;

		if (htable->table[currentIndex].key == key) //Hittat nyckel värdet
		{
			return &(htable->table[currentIndex].value);
		}
		else
			collisions += 1;

		if (collisions == htable->size)
		{
			return NULL; // Max antal krockar
		}
	}

	return NULL; // // Indikerar att elementet inte hittades
}

/*Postcondition: hashtable have size 0*/
void freeHashTable(HashTable* htable)
{

	free(htable->table); //Ta bort arrayen

	htable->table = NULL; //Säkerställer att allt är NULL
	htable->size = UNUSED;
	assert(UNUSED == getSize(htable));
}


unsigned int getSize(const HashTable* htable)
{

	return htable->size;
}

void printHashTable(const HashTable* htable)
{

	// Tip: use printPerson() in Person.h to print a persons' information
	if (htable == NULL || htable->table == NULL)
	{
		printf("No list to print\n");
		return;
	}

	printf("Hashtable Contents:\n");

	for (int i = 0; i < htable->size; i++)
	{
		if (htable->table[i].key != UNUSED) //Skriver bara ut på platser där de finns uppgifter 
		{
			printPerson(&htable->table[i].value, htable->table[i].key);
			printf("\n");
		}

	}
}