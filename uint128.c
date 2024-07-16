#include "uint128.h"

uint128_t CREATE_UINT128(void) {
    uint128_t uint128;
    int n;
    uint128.data = ((unsigned long *) malloc(NUM_OF_PARTS * sizeof(unsigned long))) + ( (NUM_OF_PARTS - 1) * sizeof(unsigned int) );
    n = 1;
    uint128.byte_endianness = (int) *((char *) &n); /* BIG = 0, LITTLE = 1 */
    uint128.bit_endianness = (int) (0x01 >> 7);
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

    for( i = numOfParts-1; i >= 0; i-- ) {
        u128_part = (unsigned long *) uint128.data + i;
        *u128_part = (unsigned long) parts[i] ^ 0UL;
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

/* 
 * Convert the bits stored in the 128bit integer into an array of bits represented as strings. 
 * The Bits are stored in a bit string in big endian format on both the bit level and the byte level.
 */
void getBits(uint128_t uint128, char** bitString) {
    int i, j, p, count;
    char byte;

    count = 0;
    if( uint128.byte_endianness == SYSTEM_LITTLE_ENDIAN && uint128.bit_endianness == SYSTEM_LITTLE_ENDIAN ) { /* Copy bytes in reversed order in which they are stored in */
        for( p = 0; p < NUM_OF_PARTS; p++ ) {
            for( i = sizeof(unsigned long)-1; i >= 0; i-- )
                for( j = 0; j < 8; j++ ) {
                    byte = *( (char *) (uint128.data + p) + i );
                    _strcpy(bitString[count], ( (byte >> j) & 0x01 ? "1\0" : "0\0" ), 2);
                    count++;
                }
        }
    }
    else if( uint128.byte_endianness == SYSTEM_LITTLE_ENDIAN && uint128.bit_endianness == SYSTEM_BIG_ENDIAN ) { /* Copy bytes in reverse order and copy the bits in each byte in reverse order */
        for( p = 0; p < NUM_OF_PARTS; p++ ) {
            for( i = sizeof(unsigned long)-1; i >= 0; i-- )
                for( j = 7; j >= 0; j-- ) {
/*                     byte = *( (char *) uint128.data + i ); */
                    byte = *( (char *) (uint128.data + p) + i );
                    _strcpy(bitString[count], ( (byte >> j) & 0x01 ? "1\0" : "0\0" ), 2);
                    count++;
                }
        }
    }
    else if( uint128.byte_endianness == SYSTEM_BIG_ENDIAN && uint128.bit_endianness == SYSTEM_BIG_ENDIAN ) { /* Copy bytes in order they are stored in */
        for( p = 0; p < NUM_OF_PARTS; p++ ) {
            for( i = 0; i < sizeof(unsigned long); i++ )
                for( j = 7; j >= 0; j-- ) {
                    /* if((*uint128.data >> ( (i*sizeof(unsigned long)*8)+j )) & 0x01UL)
                    _strcpy(bitString[((i+1)*sizeof(unsigned long)*8)-j-1], "1\0", 2);
                else
                    _strcpy(bitString[((i+1)*sizeof(unsigned long)*8)-j-1], "0\0", 2); */
/*                     byte = *( (char *) uint128.data + i ); */
                    byte = *( (char *) (uint128.data + p) + i );
                    _strcpy(bitString[count], ( (byte >> j) & 0x01 ? "1\0" : "0\0" ), 2);
                    count++;
                }
        }
    }
    else { /* Copy Bytes in order that they are stored but reverse the order of each byte */
        for( p = 0; p < NUM_OF_PARTS; p++ ) {
            for( i = 0; i < sizeof(unsigned long); i++ ) {
                for( j = 0; j < 8; j++ ) {
/*                     byte = *( (char *) uint128.data + i ); */
                    byte = *( (char *) (uint128.data + p) + i );
                   _strcpy(bitString[count], ( (byte >> j) & 0x01 ? "1\0" : "0\0" ), 2);
                    count++;
                }
            }
        }
    }
}

void PRINT_UINT128_AS_DECIMAL(uint128_t uint128, char* dest) {
    int i, j, offset;
    char** binary;
    binary = (char **) calloc(NUM_OF_BITS, sizeof(char));

    for( i = 0; i < NUM_OF_BITS; i++ )
        binary[i] = (char *) malloc(SIZE_OF_DECIMAL_STRING);

    getBits(uint128, binary);

    for( i = 0; i < NUM_OF_BITS; i++ ) 
        for( j = i; j < NUM_OF_BITS-1; j++ )
            doubleDecimal(binary[i]);

    for( i = 1; i < NUM_OF_BITS; i++ )
        addDecimalBits(binary[0], binary[i]);

    for( i = 0; i < SIZE_OF_DECIMAL_STRING; i++ ) {
        dest[i] = binary[0][i];
        if( binary[0][i] == '\0' )
            break;
    }

    for( i = 0; i < NUM_OF_BITS; i++ )
        free(binary[i]);
    free(binary);
}

void FREE_UINT128(uint128_t data) {
    free(data.data - ( (NUM_OF_PARTS - 1) * sizeof(unsigned int) ));
}
