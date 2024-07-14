#include "uint128.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void testDiffEndianness(uint128_t uint128, char** expectedOutput) {
    /*
     * TODO:
     *  Test the output for all endian combinations.
     */

    uint128.byte_endianness = SYSTEM_LITTLE_ENDIAN;
    uint128.bit_endianness = SYSTEM_LITTLE_ENDIAN;
    printf("\tByte=LITTLE, Bit=LITTLE\n");
    printf("\t\tExpected Output:\n\t\t\t%s\n", expectedOutput[0]);
    printf("\t\tActual Output:\n\t\t\t");
    PRINT_UINT128_AS_DECIMAL(uint128);
    printf("\n\n");

    uint128.bit_endianness = SYSTEM_BIG_ENDIAN;
    printf("\tByte=LITTLE, Bit=BIG\n");
    printf("\t\tExpected Output:\n\t\t\t%s\n", expectedOutput[1]);
    printf("\t\tActual Output:\n\t\t\t");
    PRINT_UINT128_AS_DECIMAL(uint128);
    printf("\n\n");

    uint128.byte_endianness = SYSTEM_BIG_ENDIAN;
    uint128.bit_endianness = SYSTEM_LITTLE_ENDIAN;
    printf("\tByte=BIG, Bit=LITTLE\n");
    printf("\t\tExpected Output:\n\t\t\t%s\n", expectedOutput[2]);
    printf("\t\tActual Output:\n\t\t\t");
    PRINT_UINT128_AS_DECIMAL(uint128);
    printf("\n\n");

    uint128.bit_endianness = SYSTEM_BIG_ENDIAN;
    printf("\tByte=BIG, Bit=BIG\n");
    printf("\t\tExpected Output:\n\t\t\t%s\n", expectedOutput[3]);
    printf("\t\tActual Output:\n\t\t\t");
    PRINT_UINT128_AS_DECIMAL(uint128);
    printf("\n\n");
}

void testUint128DecimalOutput(void) {
    uint8_t i, j, numOfTests, numOfSubTests;
    uint128_t uint128;
    char*** expectedOutput;
    unsigned long **parts;

    numOfTests = 5;
    numOfSubTests = 4;

    /*
     * TODO:
     *  Change the expected output to be a 3D array, where each element is an array of charStrings that show the expected output of the values for the endianness.
     */
    expectedOutput = (char ***) calloc(numOfTests, sizeof(char **));
    parts = (unsigned long **) calloc(numOfTests, sizeof(unsigned long *));
    for( i = 0; i < numOfTests; i++ ) {
        expectedOutput[i] = (char **) malloc(SIZE_OF_DECIMAL_STRING);
        for( j = 0; j < numOfSubTests; j++ )
            expectedOutput[i][j] = (char *) malloc(SIZE_OF_DECIMAL_STRING);
        parts[i] = (unsigned long *) calloc(NUM_OF_PARTS, sizeof(unsigned long));
    }
    for( i = 0; i < NUM_OF_PARTS; i++ ) {
        parts[0][i] = 0x0UL - 1;
        parts[1][i] = 0x0UL;
        for( j = 0; j < sizeof(unsigned long); j++ )
            *((char *) (parts[2] + i) + j) = 0x55;
        if( i == NUM_OF_PARTS-1 ) parts[3][i] = 0x2DUL;
        else parts[3][i] = 0UL;
        if( i == 0 ) parts[4][i] = 0x2DUL;
        else parts[4][i] = 0UL;
    }
    /* Order of Tests:
     *      sub Test:   Byte Endianness:    Bit Endianness:
     *          1           LITTLE              LITTLE
     *          2           LITTLE               BIG
     *          3            BIG                LITTLE
     *          4            BIG                 BIG
     */
    for( i = 0; i < numOfSubTests; i++ ) {
        strcpy(expectedOutput[0][i], "340282366920938463463374607431768211455\0");
        strcpy(expectedOutput[1][i], "0\0");
    }
    strcpy(expectedOutput[2][0], "226854911280625642308916404954512140970\0");
    strcpy(expectedOutput[2][1], "113427455640312821154458202477256070485\0");
    strcpy(expectedOutput[2][2], "226854911280625642308916404954512140970\0");
    strcpy(expectedOutput[2][3], "113427455640312821154458202477256070485\0");

    strcpy(expectedOutput[3][0], "180\0");
    strcpy(expectedOutput[3][1], "45\0");
    strcpy(expectedOutput[3][2], "12970366926827028480\0");
    strcpy(expectedOutput[3][3], "3242591731706757120\0");

    strcpy(expectedOutput[4][0], "3320413933267719290880\0");
    strcpy(expectedOutput[4][1], "830103483316929822720\0");
    strcpy(expectedOutput[4][2], "239261039241284857122685270850462023680\0");
    strcpy(expectedOutput[4][3], "59815259810321214280671317712615505920\0");

    uint128 = CREATE_UINT128();

    /* Iterate through tests: */
    for( i = 0; i < numOfTests; i++ ) {
        WRITE_TO_UINT128(uint128, parts[i], NUM_OF_PARTS);
        printf("Test %i:\n", i);
        testDiffEndianness(uint128, expectedOutput[i]);
        printf("\n");
    }
    FREE_UINT128(uint128);
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

    printf("This API uses the following endianness:\n\t");

    for( i = 0; i < NUM_OF_PARTS; i++ )
        parts[i] = (unsigned long) (i*2) + 1;

    printf("%lu parts:\n", NUM_OF_PARTS);
    for( i = 0; i < NUM_OF_PARTS; i++ )
        printf("\tpart %i: %lu\t%lu\n", i, parts[i], parts[i] ^ 0UL);

    /* Test creation of 128 bit unsigned int */
    uint128 = CREATE_UINT128();

    printf("Uint128 created with:\n");
    printf("\tbyte endianness: %s\n", ( uint128.byte_endianness ? "LITTLE" : "BIG" ));
    printf("\tbit  endianness: %s\n", ( uint128.bit_endianness ? "LITTLE" : "BIG" ));

    printf("uint128 is created. Data given address: %p\n", (void *) uint128.data);
    for( i = 0; i < 128 / 8; i++ )
        printf("\tByte %i: %p\n", i, (void *) ((char *) uint128.data + i));

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

    testUint128DecimalOutput();

    /* Iterate through uint128 and output each bit: */
    for( i = 0; i < NUM_OF_PARTS; i++ ) {
        /*
         * TODO:
         *      - Split the data address into unsigned long segments.
         *      - Output the bytes of each segment.
         */
        printf("Shifting %lu bytes, unsigned long created from adress %p\n", i * sizeof(unsigned long),  (void *) ((char *) uint128.data + (i * sizeof(unsigned long))));
        outputPart = *((unsigned long *) (uint128.data + i));
        ULtoBits(outputPart);
        printf("\nNext Part...\n");
    }

    /*     PRINT_UINT128(uint128); */

    printf("Freeing Struct...\n");
    FREE_UINT128(uint128);
}

