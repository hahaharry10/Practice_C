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

void _strcpy( char* pointer, char* string, int strlen) {
    int i;
    for( i = 0; i < strlen; i++ )
        pointer[i] = string[i];
}

/* Take in a C-String representing the decimal number, and double the value */
void doubleDecimal(char* number) {
    int i, nullPosition;

    for( i = 0; i < SIZE_OF_DECIMAL_STRING; i++ ) {
        if( number[i] == '\0' ) {
            nullPosition = i;
            break;
        }
    }

    /* Double all the digits */
    for( i = nullPosition-1; i >= 0; i-- )
        *(number+i) = ((number[i] - '0') * 2) + '0';

    /* if digit i has overflow, increment digit i-1 */
    for( i = 0; i <= nullPosition; i++ ) {
        while( number[i] > '9' && i != 0 ) {
            number[i-1]++;
            number[i] -= 10;
        }
        if( number[i] > '9' && i == 0 ) {
            /* Shift all the numbers down one and append MSB */ 
            for( i = nullPosition; i >= 0; i-- )
                number[i+1] = number[i];

            /* Find the new MSB */
            number[0] = '0';
            while( number[1] > '9' ) {
                number[1] -= 10;
                number[0]++;
            }
        }
    }
}

void addDecimalBits(char* bit1, char* bit2) {
    int i, j, lenL, lenS;
    char *larger, *smaller;

    /* Find the length of both bits and assign appropriate variables */
    for( i = 0; i < SIZE_OF_DECIMAL_STRING; i++ ) {
        if( bit1[i] == '\0' ) {
            larger = bit2;
            smaller = bit1;
            lenS = i+1;
            for( j = i; i < SIZE_OF_DECIMAL_STRING; j++ ) {
                if( bit2[j] == '\0' ) {
                    lenL = j+1;
                    break;
                }
            }
            break;
        }
        else if( bit2[i] == '\0' ) {
            larger = bit1;
            smaller = bit2;
            lenS = i+1;
            for( j = i; j < SIZE_OF_DECIMAL_STRING; j++ ) {
                if( bit1[j] == '\0' ) {
                    lenL = j+1;
                    break;
                }
            }
            break;
        }
    }

    /* Pad smaller number with zeros */
    for( i = lenS-1; i >= 0; i-- )
        smaller[i+(lenL-lenS)] = smaller[i];
    for( i = 0; i < lenL-lenS; i++ )
        smaller[i] = '0';

    /* Add both the bits together */ 
    for( i = lenL-2; i >= 0; i-- ) {
        bit1[i] = larger[i] + smaller[i] - '0';
        if( bit1[i] > '9' && i != 0 ) {
            bit1[i] -= 10;
            bit1[i-1]++;
        }
    }
    if( bit1[0] > '9' ) {
        for( i = lenL-1; i >= 0; i-- )
            bit1[i+1] = bit1[i];
        bit1[1] -= 10;
        bit1[0] = '1';
    }
}

void PRINT_UINT128_AS_DECIMAL(uint128_t uint128) {
    int i, j;
    char** binary;
    binary = (char **) calloc(NUM_OF_BITS, sizeof(char));
    for( i = 0; i < NUM_OF_BITS; i++ ) {
        binary[i] = (char *) malloc(SIZE_OF_DECIMAL_STRING);
        if( (*uint128.data >> i) & 0x01UL )
            _strcpy(binary[i], "1\0", 2);
        else
            _strcpy(binary[i], "0\0", 2);
    }

    for( i = 0; i < NUM_OF_BITS; i++ ) 
        for( j = i; j < NUM_OF_BITS-1; j++ )
            doubleDecimal(binary[i]);

    for( i = 1; i < NUM_OF_BITS; i++ )
        addDecimalBits(binary[0], binary[i]);

    printf("%s", binary[0]);

    for( i = 0; i < NUM_OF_BITS; i++ )
        free(binary[i]);
    free(binary);
}

void FREE_UINT128(uint128_t data) {
    free(data.data - ( (NUM_OF_PARTS - 1) * sizeof(unsigned int) ));
}
