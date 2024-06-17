#include "uint128.h"
#include <stdio.h>

uint128_t CREATE_UINT128(void) {
    uint128_t uint128;
    uint128.data = ((unsigned long *) malloc(NUM_OF_PARTS * sizeof(unsigned long))) + ( (NUM_OF_PARTS - 1) * sizeof(unsigned int) );
    return uint128;
}

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
        u128_part = (unsigned long *) uint128.data - (i * sizeof(unsigned long));
        printf("parts[%i] ^ 0UL = %lu ^ %lu = %lu\n", i, parts[i], 0UL, parts[i] ^ 0UL);
        *u128_part = (unsigned long) parts[i] ^ 0UL;
        printf("\t%lu\n", *u128_part);
    }

    for( i = 0; i < NUM_OF_PARTS; i++ )
        printf("Part %lu: %lu\n", NUM_OF_PARTS-i-1, *(uint128.data - ((NUM_OF_PARTS-i-1) * sizeof(unsigned long))));

    return EXIT_SUCCESS;
}

void PRINT_UINT128(uint128_t uint128) {
    /*
        * TODO:
        *       Convert integer into bits.
        *       Print the uint128 value to the terminal.
    */
    char bits[129];
    int i, j;
    unsigned long ref;
    unsigned long temp;

    for( i = NUM_OF_PARTS-1; i >= 0; i-- ) {
        ref = *uint128.data >> (i * sizeof(unsigned long));
        for( j = 0; j < 8; j++ ) {
            printf("i=%i j=%i\t%lu\tref = %lu\n", i, j, (ref >> j) % 2, ref);
        }
        printf("\n");
    }
    bits[128] = '\0';

    for( i = 0; i < 128; i++ )
        printf("%c ", bits[i]);
    printf("\n");

    printf("Outputted Bits:\n\t%s\n", bits);
}

void FREE_UINT128(uint128_t data) {
    free(data.data - ( (NUM_OF_PARTS - 1) * sizeof(unsigned int) ));
}
