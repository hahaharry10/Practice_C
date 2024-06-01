#include <stdlib.h>
#include <stdio.h>

/*
	* NOTE: This bug is a discussion about memeory allocation within a C program.
	*
	* In C the array variable is stored as a pointer to the start of the array. Arrays 
	* are then retrieved relative to the pointer (so if you want the third element in
	* the array then u start at the head, and move 2 addresses down, hence arr[2]).
	* Square brackets are compiled and operated using pointer arithmatic such that
	*				arr[i]
	* is read and executed as:
	*				*(arr+i)
	*
	* Furthermore C does not contain memory boundries so if i was to execute `arr[i]`
	* where `i` is greater than the length of the array then i would be accessing a
	* memory address outside of the array (one of the reasons why C is not memory safe).
	*
	* Lets say I want to use a for loop to assign all elements in the array to value 0,
	* but in the for loop `i` is iterated from 0 to `x+1` (inclusive). Then all the
	* values in the array is assigned to 0 (when i=0 up to i='x-1', then the neighbouring 
	* address of the array (the address of variable `i`) is also assigned to 0 (creating 
	* an infinite loop).
	*
	* In this code, `i` is stored in the array `arr+(length+1)`, therefore to create the
	* infinite loop the condition of the for loop must be `< length+2`, but I don't know
	* what is stored in address `arr+length`. For my compiler there is a one memory space
	* gap, but on other compilers the gap may be larger, or there may be no gap at all. 
	* Either way this vulnerability remains consistent across all C compilers.
	*
	* This bug is just an example to show how C needs to be written in a memory safe way.
	* The same logic creating this infinite loop is the same reason why C needs to be
	* written in a memory safe way. If not, hackers could modify data in memory you
	* don't want them to have access to.
	*/

#define ARRAY_LENGTH 10

int main( int argc, char** argv ) {
	// Initialise array then iterator:
	int arr[ARRAY_LENGTH], i;


	printf("Creating array of length %i and assigning the following values:\n", ARRAY_LENGTH);
	for( i = 0; i < 10; i++ ) {
		arr[i] = i;
		printf("\tarr[%i] = %i\n", i, i);
	}
	printf("\n");

	printf("Lets test different element retrievals:\n");
	printf("\tarr[0]: %i\n", arr[0]); // Output: 0
	printf("\t0[arr]: %i\n", 0[arr]); // Output: 0
	
	// The infinite loop bug:
	for( i = 0; i < ARRAY_LENGTH+2; i++ ) {
		arr[i] = 0;
		printf("\ti = %i : arr[i] = %i\n", i, arr[i]);
	}


	return EXIT_SUCCESS;
}
