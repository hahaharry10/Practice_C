/*
* NOTE: `__attribute__` documentation:
*		https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes
*
* Attribute is a keyword used to define attributes of functions for optimisation.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_OF_CLOCK_TESTS 100000

/*
* const:
*	- Tells the compiler that the functions output is deterministic based on the parameters.
*	- If the parameter inputs are equal, the output will be the same.
*	- Suitable for deterministic functions that does not rely on the state outside of the
*		function, such as mathematical functions.
*	- Not suitable for functions that rely on the state of objects outside of the function.
*		for example:
*			~ Reading from a file (the contents of the file may vary).
*			~ Reading memory addresses (the addresses may be the same but the contents can vary).
*			~ Functions that depend on randomisation.
*
*	The keyword optimises through assuming that if the parameters are the same the output is the
*	same and therefore the function does not need to be run if the otuput is already calculated.
*/
__attribute__((const))
int const_square(int x, int pow) {
	int val = x;
	for( int i = 0; i < pow; i++ )
		val *= x;

	return val;
}

int nonConst_square(int x, int pow) {
	int val = x;
	for( int i = 0; i < pow; i++ )
		val *= x;

	return val;
}

int main(int argc, char** argv) {
	// Test optimisation of const:
	int output;
	int x = 2, pow = 10;
	clock_t constStart = clock();
	for( int i = 0; i < NUM_OF_CLOCK_TESTS; i++ )
		output = const_square(x, pow);
	clock_t constEnd = clock();

	clock_t nonConstStart = clock();
	for( int i = 0; i < NUM_OF_CLOCK_TESTS; i++ )
		output = nonConst_square(x, pow);
	clock_t nonConstEnd = clock();

	double constTime = (double) (constEnd-constStart)/CLOCKS_PER_SEC;
	double nonConstTime = (double) (nonConstEnd-nonConstStart)/CLOCKS_PER_SEC;
	printf("Testing `const` optimisation:\n\tWith const: %fs\tWithout const: %fs\tOutput: %i\n", constTime, nonConstTime, output);

	return EXIT_SUCCESS;
}
