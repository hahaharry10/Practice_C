#include "uint128.h"
#include <stdint.h>
#include <stdio.h>

void ULtoBits( unsigned long x ) {
    unsigned long remainder, bit;
    int i;
    int* bits;

    bits = (int *) calloc(sizeof(unsigned long) * 8, sizeof(int));
    remainder = x;
    bit = (sizeof(unsigned long) * 8) - 1;
    while( 1 ) {
        /* printf("%lu << %lu & %lu = %lu & %lu = %lu\n", 0x1UL, bit, x, (0x1UL << bit), x, ((0x1UL << bit) | x)); */
        if( ((0x1UL << bit) | x) == x ) {
            bits[((sizeof(unsigned long) * 8) - 1) - bit] = 1;
        } else
            bits[((sizeof(unsigned long) * 8) - 1) - bit] = 0;
        bit--;

        if( bit == 0 ) {
            if( ((0x1UL << bit) | x) == x ) {
                bits[((sizeof(unsigned long) * 8) - 1) - bit] = 1;
            } else
                bits[((sizeof(unsigned long) * 8) - 1) - bit] = 0;
            break;
        }
    }

    for( i = 0; i < sizeof(unsigned long) * 8; i++ )
        printf("%i ", bits[i]);
    printf("\n");

    free(bits);
}

int main(int argc, char** argv) {
    /*  
    *  TODO:
    *       Test Creation of 128bit data struct.
    *       Test the freeing of memory.
    *       Test the print function.
    */
    uint128_t uint128;
    unsigned long parts[NUM_OF_PARTS], outputPart;
    int i;


    for( i = 0; i < NUM_OF_PARTS; i++ )
        parts[i] = 0UL - (i % 2);

    printf("%lu parts:\n", NUM_OF_PARTS);
    for( i = 0; i < NUM_OF_PARTS; i++ )
        printf("\tpart %i: %lu\t%lu\n", i, parts[i], parts[i] ^ 0UL);

    /* Test creation of 128 bit unsigned int */
    uint128 = CREATE_UINT128();


    printf("uint128 is created. Data given address: %p\n", (void *) uint128.data);
    for( i = 0; i < 128 / 8; i++ )
        printf("\tByte %i: %p\n", i, (void *) (uint128.data + i));

    printf("The bits of the parts (before uint128 conversion):\n");
    for( i = 0; i < NUM_OF_PARTS; i++ ) {
        printf("\tPart %i (%lu):\n\t", i, parts[i]);
        ULtoBits(parts[i]);
    }
    printf("\n\n");

    printf("Writing parts to uint128...\n");
    if( WRITE_TO_UINT128(uint128, parts, NUM_OF_PARTS) ) {
        printf("ERROR: Failed to write to UINT128.\n");
        return 1;
    }

    /* Iterate through uint128 and output each bit: */
    for( i = 0; i < NUM_OF_PARTS; i++ ) {
        /*
         * TODO:
         *      - Split the data address into unsigned long segments.
         *      - Output the bytes of each segment.
         */
        printf("Shifting %lu bytes, unsigned long created from adress %p\n", i * sizeof(unsigned long), (void *) (uint128.data + (i * sizeof(unsigned long))));
        outputPart = *((unsigned long *) uint128.data + (i * sizeof(unsigned long)));
        ULtoBits(outputPart);
        printf("\nNext Part...\n");
    }

    /*     PRINT_UINT128(uint128); */

    printf("Freeing Struct...\n");
    FREE_UINT128(uint128);
}

