#include "dstring.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>


DString dstring_initialize(const char* str)
{
	assert(str != NULL);
	int lenght = strlen(str) + 1;

	char* string = (char*)malloc(lenght * sizeof(char));
	if (string != NULL)
	{
		return strcpy(string, str);

	}
	else
	{
		printf("Error allocating memory!");
		return NULL;
	}

	// Precondition: str is not NULL - test with assert

   /* Tip:
	  - Allocate (e.g., with malloc) enough memory to fit str. Don't forget that there must be room for '\0' as well.
		Don't forget to test so that the allocation is successfull before you start working with the memory.
	  - It is allowed to use build-in string functions (e.g., strcpy())
	  - Remember to use assert()
	*/

	// Postcondition: The return value contains the same string as str - does not need to be testet.

	 // Replace this row. It is only there now so that the program can compile.
}

int dstring_concatenate(DString* destination, DString source)
{
	assert(*destination != NULL);
	assert(source != NULL);

	int legngt1 = strlen(*destination);
	int legnt2 = strlen(source);

	char* temp = (char*)realloc(*destination, (legngt1 + legnt2 + 1) * sizeof(char));

	if (temp == NULL)
	{
		
		return 0;
	}

	else
	{
		*destination = temp;

		strcat(*destination, source);
		
		return 1;
	}


	// Precondition: destination is not NULL
	// Precondition: *destination is not NULL
	// Precondition: source is not NULL
	// Preconditions should be testet with asserts

	/* Tip:
	   - Note that *destination already is a dynamically allocated string.
	   - Note that you will need to allocate more memory to fit the longer string. The memory that *destination points to needs to be extended (realloc), how large should the "new" memory be?
		 Don't forget that '\0' must fit in the string.
		 When allocating dynamic memory, you must always test so that the allocation is successfull before you start working with the memory.
	   - It is allowed to use built-in string functions (such as strcat()).
	*/

	// Postcondition: *destination contains the old string combined with source - does not need to be testet.
	//return -1; // Replace thiw row. Right now it's only there for the program to compile. What should be returned?
}

void dstring_truncate(DString* destination, unsigned int truncatedLength)
{
	assert(*destination != NULL);
	assert(truncatedLength >= 0);

	if (truncatedLength < strlen(*destination))
	{
		(*destination)[truncatedLength] = '\0';

		
		char* temp = (char*)realloc(*destination, (truncatedLength + 1) * sizeof(char));
		if (temp != NULL)
		{

			*destination = temp;
			temp = NULL;

		}
		else
		{
			printf("Error allocating memory!");
			free(temp);
		}
		
	}

}


// Precondition: destination is not NULL, *destination is not NULL
// the length (truncateLength) may not be negative
// Preconditions should be testet with asserts

/* Tip:
   - Use realloc to free the redundant memory.
	 (have a look at what realloc does)
   - Don't forget '\0'.
   - What happens if truncateLength is longer than the string?
*/

// Postcondition: *destination is not longer than  'truncatedLength' - does not need to be testet.


void dstring_print(DString str, FILE* textfile)
{
	assert(textfile != NULL);
	assert(str != NULL);

	fputs(str, textfile);


	// Precondition: textfile is not NULL - must be testet before you try to work with the file.
	/* Note that the file pointer is already connected to the file before the functions is called.*/

	/* Don't close the file (file pointer), the file should work as normal after the function call */
}

void dstring_delete(DString* stringToDelete)
{
	
	assert(*stringToDelete != NULL);

	free(*stringToDelete);
	*stringToDelete = NULL;

	// Precondition: stringToDelete is not NULL

	// Postcondition: *stringToDelete are NULL and the memory is freed. - does not need to be testet.
}