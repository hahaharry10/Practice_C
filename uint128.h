/*
* This is the header file for all the functions required to create and handle
* a 128 bit integer.
*/

#include <stdio.h>
#include <stdlib.h>

#define INCOMPATIBLE_PART_COUNT_ERROR 3

/* define how many unsigned long integers are needed to create 128 bit integer */
#define NUM_OF_PARTS 16/sizeof(unsigned long)

typedef struct {
		unsigned long* data;
} uint128_t;

uint128_t CREATE_UINT128(void);
int WRITE_TO_UINT128(uint128_t uint128, unsigned long* parts, int numOfParts);
int ADD_TO_UINT128(uint128_t uint128, unsigned long value); /* Add long to 128-bit integer */
void PRINT_UINT128(uint128_t uint128); /* Output unsigned integer to the terminal */
void FREE_UINT128(uint128_t data); /* Free up the data */
