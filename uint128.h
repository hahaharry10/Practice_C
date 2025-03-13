/*
* This is the header file for all the functions required to create and handle
* a 128 bit integer.
*/

#include <stdio.h>
#include <stdlib.h>

#define INCOMPATIBLE_PART_COUNT_ERROR 3

#define SYSTEM_BIG_ENDIAN 0
#define SYSTEM_LITTLE_ENDIAN 1

#define OVERFLOW_OPERATION 3

/* define how many unsigned long integers are needed to create 128 bit integer */
#define NUM_OF_PARTS 16/sizeof(unsigned long)

#define NUM_OF_BITS 128
#define SIZE_OF_DECIMAL_STRING 40

typedef struct {
	unsigned long* data;
	int byte_endianness;
} uint128_t;

int CREATE_UINT128(uint128_t **uint128);
int WRITE_TO_UINT128(uint128_t *uint128, unsigned long* parts, int numOfParts);
int UINT128_ADD_LONG(uint128_t *uint128, unsigned long value); /* Add long to 128-bit integer */
int UINT128_ADD_UINT128(uint128_t *u1, uint128_t *u2); /* Performs the equivalent of `u1 = u1 + u2` (u2 is left untouched) */
void PRINT_UINT128_AS_DECIMAL(uint128_t *uint128, char *dest); /* Output to the terminal as decimal number */
void FREE_UINT128(uint128_t *data); /* Free up the data */
