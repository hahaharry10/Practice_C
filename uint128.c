#include "uint128.h"
#include <stdio.h>

uint128_t CREATE_UINT128(void) {
    uint128_t uint128;
    uint128.data = ((unsigned long *) malloc(NUM_OF_PARTS * sizeof(unsigned long))) + ( (NUM_OF_PARTS - 1) * sizeof(unsigned int) );
    return uint128;
}

/* Writes to the uin128 in big endianne format:
 *      parts[0]: contains most significant bit.
 *      parts[numOfParts-1]: contains least significant bit.
 */
int WRITE_TO_UINT128(uint128_t uint128, unsigned long* parts, int numOfParts) {
    int i;
    unsigned long* u128_part;

    if( numOfParts != NUM_OF_PARTS )
        return INCOMPATIBLE_PART_COUNT_ERROR;

    /*
        * TODO:
        *       Iterate through each part and use bitwise OR to assign to uint128
    */
    for( i = numOfParts-1; i >= 0; i-- ) {
        u128_part = (unsigned long *) uint128.data + i;
/*         printf("parts[%i] ^ 0UL = %lu ^ %lu = %lu\n", i, parts[i], 0UL, parts[i] ^ 0UL); */
        *u128_part = (unsigned long) parts[i] ^ 0UL;
/*         printf("\t%lu\n", *u128_part); */
    }

    return EXIT_SUCCESS;
}

void PRINT_UINT128_AS_DECIMAL(uint128_t uint128) {
    /*
    * TODO:
    *   1) Get each bit of the uint128.
    *   2) Convert the binary to decimal.
    */
}

void FREE_UINT128(uint128_t data) {
    free(data.data - ( (NUM_OF_PARTS - 1) * sizeof(unsigned int) ));
}
