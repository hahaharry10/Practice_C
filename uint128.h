/*
* This is the header file for all the functions required to create and handle
* a 128 bit integer.
*/

#include <stdio.h>
#include <stdlib.h>

#define INCOMPATIBLE_PART_COUNT_ERROR 3

#define SYSTEM_BIG_ENDIAN 0
#define SYSTEM_LITTLE_ENDIAN 1

/* define how many unsigned long integers are needed to create 128 bit integer */
#define NUM_OF_PARTS 16/sizeof(unsigned long)

#define NUM_OF_BITS 128
#define SIZE_OF_DECIMAL_STRING 40

typedef struct {
	unsigned long* data;
	int byte_endianness;
	int bit_endianness;
} uint128_t;

uint128_t CREATE_UINT128(void);
int WRITE_TO_UINT128(uint128_t uint128, unsigned long* parts, int numOfParts);
int ADD_TO_UINT128(uint128_t uint128, unsigned long value); /* Add long to 128-bit integer */
void PRINT_UINT128_AS_DECIMAL(uint128_t uint128); /* Output to the terminal as decimal number */
void FREE_UINT128(uint128_t data); /* Free up the data */
