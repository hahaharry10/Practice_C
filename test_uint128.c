#include "uint128.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void _strcpy( char* pointer, char* string, int strlen) {
    int i;
    for( i = 0; i < strlen; i++ )
        pointer[i] = string[i];
}

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

int checkStringsAreIdentical(char* str1, char* str2) {
    int i;

    for( i = 0; i < SIZE_OF_DECIMAL_STRING; i++ ) {
        if( str1[i] != str2[i] )
            return 0;
        else if( str1[i] == '\0' || str2[i] == '\0' )
            return 1;
    }

    return 1;
}

void testDiffEndianness(uint128_t uint128, char** expectedOutput, char* decimalOutput) {
    int i;

    uint128.byte_endianness = SYSTEM_LITTLE_ENDIAN;
    printf("\tByte=LITTLE\n");
    printf("\t\tExpected Output:\t%s\n", expectedOutput[0]);
    PRINT_UINT128_AS_DECIMAL(uint128, decimalOutput);
    printf("\t\tActual Output:  \t%s\n", decimalOutput);
    if( !checkStringsAreIdentical(expectedOutput[0], decimalOutput) )
        printf("\033[0;31mFAILED\033[0m\n");

    uint128.byte_endianness = SYSTEM_BIG_ENDIAN;
    printf("\tByte=BIG\n");
    printf("\t\tExpected Output:\t%s\n", expectedOutput[1]);
    PRINT_UINT128_AS_DECIMAL(uint128, decimalOutput);
    printf("\t\tActual Output:  \t%s\n", decimalOutput);
    if( !checkStringsAreIdentical(expectedOutput[1], decimalOutput) )
        printf("\033[0;31mFAILED\033[0m\n");
    printf("\n\n");
}

void testUint128DecimalOutput(void) {
    int i, j, numOfTests, numOfSubTests;
    uint128_t uint128;
    char* decimalOutput;
    char*** expectedOutput;
    unsigned long **parts;

    numOfTests = 5;
    numOfSubTests = 2;

    decimalOutput = (char *) malloc(SIZE_OF_DECIMAL_STRING);
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
     *      sub Test:   Byte Endianness:
     *          1           LITTLE      
     *          2            BIG        
     * Tests:
     *      Test Num:   Input:
     *          0           All 1's
     *          1           All 0's
     *          2           01010101 Repeated.
     *          3           0x00101101 (0x2D (45)) in (char *) M+16-1
     *          4           0x00101101 (0x2D (45)) in M+0)
     */
    for( i = 0; i < numOfSubTests; i++ ) {
        _strcpy(expectedOutput[0][i], "340282366920938463463374607431768211455\0", 40);
        _strcpy(expectedOutput[1][i], "0\0", 2);
    }
    _strcpy(expectedOutput[2][0], "113427455640312821154458202477256070485\0", 40);
    _strcpy(expectedOutput[2][1], "113427455640312821154458202477256070485\0", 40);

    _strcpy(expectedOutput[3][0], "59815259810321214280671317712615505920\0", 39);
    _strcpy(expectedOutput[3][1], "45\0", 3);

    _strcpy(expectedOutput[4][0], "45\0", 3);
    _strcpy(expectedOutput[4][1], "59815259810321214280671317712615505920\0", 39);

    uint128 = CREATE_UINT128();

    /* Iterate through tests: */
    for( i = 0; i < numOfTests; i++ ) {
        WRITE_TO_UINT128(uint128, parts[i], NUM_OF_PARTS);
        printf("Test %i:\n", i);
        testDiffEndianness(uint128, expectedOutput[i], decimalOutput);
        printf("\n");
    }

    for( i = 0; i < numOfTests; i++ ) {
        for( j = 0; j < numOfSubTests; j++ )
            free(expectedOutput[i][j]);
        free(expectedOutput[i]);
        free(parts[i]);
    }
    free(decimalOutput);    decimalOutput = NULL;
    free(expectedOutput);   expectedOutput = NULL;
    free(parts);            parts = NULL;
    FREE_UINT128(uint128);
}

void testAddition(void) {
    int i, j, numOfTests, numOfSubTests;
    uint128_t uint128;
    char* decimalOutput;
    char*** expectedOutput;
    unsigned long *parts;

    numOfTests = 5;
    numOfSubTests = 4;

    decimalOutput = (char *) malloc(SIZE_OF_DECIMAL_STRING);
    expectedOutput = (char ***) calloc(numOfTests, sizeof(char **));
    parts = (unsigned long *) calloc(NUM_OF_PARTS, sizeof(unsigned long));
    for( i = 0; i < numOfTests; i++ ) {
        expectedOutput[i] = (char **) malloc(SIZE_OF_DECIMAL_STRING);
        for( j = 0; j < numOfSubTests; j++ )
            expectedOutput[i][j] = (char *) malloc(SIZE_OF_DECIMAL_STRING);
    }

    uint128 = CREATE_UINT128();

    /*
     * TODO:
     *      - Non-Edge cases are presumed to be correct as it involves native addition.
     *      - Test overflow for each part.
     *      - Test recursive overflow (overflows that cause overflows in other parts).
     *      - Test complete overflow (overflow in most significant part).
     */
    parts[0] = 0x0UL;
    parts[1] = 0x01UL;
    WRITE_TO_UINT128(uint128, parts, 2);
    for( i = 0; i < 0x0UL-1; i++ ) {
        for( j = 0; j < 2; j++ ) {
            UINT128_ADD_LONG(&uint128, parts[j]);
        }
    }

    PRINT_UINT128_AS_DECIMAL(uint128, decimalOutput);
    printf("Final Number: %s\n", decimalOutput);

    for( i = 0; i < numOfTests; i++ ) {
        for( j = 0; j < numOfSubTests; j++ )
            free(expectedOutput[i][j]);
        free(expectedOutput[i]);
    }
    free(expectedOutput);
    free(decimalOutput);
    free(parts);

}

void printHeader(char* title) {
    int i, titleLen, lineLen;
    lineLen = 102;
    titleLen = 0;
    printf("\x1b[36m/");
    for( i = 0; i < lineLen; i++ ) {
        printf("*");
        if( title[i] == '\0' && titleLen == 0 ) titleLen = i;
    }
    printf("/\n");
    printf("/*");
    for( i = 0; i < (lineLen/2)-(titleLen/2)-1; i++ )
        printf(" ");
    printf("%s", title);
    for( i = 0; i < (lineLen/2)-(titleLen-(titleLen/2))-1; i++ )
        printf(" ");
    printf("*/\n");
    printf("/");
    for( i = 0; i < lineLen; i++ )
        printf("*");
    printf("/\033[0m\n");
}

int main(int argc, char** argv) {
    uint128_t uint128;
    unsigned long parts[NUM_OF_PARTS], outputPart;
    int i;

    for( i = 0; i < NUM_OF_PARTS; i++ )
        parts[i] = (unsigned long) (i*2) + 1;

    /* Test creation of 128 bit unsigned int */
    uint128 = CREATE_UINT128();

    printf("Uint128 created with:\n");
    printf("\tbyte endianness: %s\n", ( uint128.byte_endianness ? "LITTLE" : "BIG" ));
    printf("\tbit  endianness: %s\n", ( uint128.bit_endianness ? "LITTLE" : "BIG" ));
    printf("\n");
    printf("uint128 is created. Data given address: %p\n", (void *) uint128.data);
    for( i = 0; i < 128 / 8; i++ )
        printf("\tByte %i: %p\n", i, (void *) ((char *) uint128.data + i));

    printHeader("TESTING UINT128 PRINT METHOD\0");
    testUint128DecimalOutput();

    /*printHeader("TESTING UINT128 ADDITION\0");*/
    /*testAddition();*/

    printf("Freeing Struct...\n");
    FREE_UINT128(uint128);
}
