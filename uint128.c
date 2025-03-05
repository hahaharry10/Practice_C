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

static void _strcpy( char* pointer, char* string, int strlen) {
    int i;
    for( i = 0; i < strlen; i++ )
        pointer[i] = string[i];
}

/* Take in a C-String representing the decimal number, and double the value */
static void doubleDecimal(char* number) {
    int i, nullPosition;
    enum BOOL {FALSE, TRUE};
    enum BOOL carry;

    carry = FALSE;
    i = 0;
    while( number[i] != '\0' ) {
        number[i] = ((number[i] - '0') * 2) + '0';

        if( carry ) {
            number[i]++;
            carry = FALSE;
        }

        if( number[i] > '9' ) {
            number[i] -= 10;
            carry = TRUE;
        }
        i++;
    }

    /* If first digit is overflow */
    if( carry ) {
        number[i] = '1';
        number[i+1] = '\0';
    }
    
}

/*
 * BUG: RUN program and debug function
 *
 * NOTE: doubleDecimal() seems correct. May be wrong. But am fairly sure the bug is in addDecimalBits()
 */
static void addDecimalBits(char* bit1, char* bit2) {
    enum BOOL {FALSE, TRUE};
    enum BOOL carry;

    /*
     * TODO: THIS...
     */
    for( i = 0; i < SIZE_OF_DECIMAL_STRING; i++ ) {
        if( bit1[i] == '\0' ) {
            /* Copy remaining digits of bit2 into bit1 */
            for( j = i; j < SIZE_OF_DECIMAL_STRING; j++ ) {
                if( bit2[j] == '\0' )
                    break;

                bit1[j] = bit2[j];
                
                if( carry ) {
                    bit1[j]++;
                    carry = FALSE;
                }

                if( bit1[j] > '9' ) {
                    bit1[j] -= 10;
                    carry = TRUE;
                }

            }
            if( carry ) {
                bit1[j] = '1';
                bit1[j+1] = '\0';
            }
            return;
        }
        else if( bit2[i] == '\0' ) {
            for( j = 1; j < SIZE_OF_DECIMAL_STRING; j++ ) {
                if( !carry ) /* if carry stops */
                    break;

                bit1[j]++;
                carry = FALSE;

                if( bit1[j] > '9' ) {
                    bit1[j] -= 10;
                    carry = TRUE;
                }
            }
            if( carry ) {
                bit1[j] = '1';
                bit1[j+1] = '\0';
            }
            return;
        }
        else {
            bit1[i] += bit2[i] - '0';

            if( carry ) {
                bit1[i]++;
                carry = FALSE;
            }

            if( bit1[i] > '9' ) {
                bit1[i] -= 10;
                carry = TRUE;
            }
        }
    }
}

/* 
 * Convert the bits stored in the 128bit integer into an array of bits represented as strings. 
 * The Bits are stored in a bit string in big endian format.
 */
static void getBits(uint128_t uint128, char** bitString) {
    int B, b, p, count; /* [B]yte, [b]it, [p]art, count */
    char byte;
    char strByte[2] = "0\0";

    count = 0;
    if( uint128.byte_endianness == SYSTEM_LITTLE_ENDIAN ) {
        for( p = 0; p < NUM_OF_PARTS; p++ ) {
            /* Little Endian: LSB is first */
            for( B = sizeof(unsigned long)-1; B >= 0; B-- ) {
                for( b = 7; b >= 0; b-- ) {
                    byte = *( (char *) (uint128.data + p) + B );
                    strByte[0] = '0' + ( (byte >> b) & 0x01 );
                    _strcpy(bitString[count], strByte, 2);
                    count++;
                }
            }
        }
    } else {
        for( p = 0; p < NUM_OF_PARTS; p++ ) {
            /* Big Endian: MSB is first */
            for( B = 0; B < sizeof(unsigned long); B++ ) {
                for( b = 7; b >= 0; b-- ) {
                    byte = *( (char *) (uint128.data + p) + B );
                    strByte[0] = '0' + ( (byte >> b) & 0x01 );
                    _strcpy(bitString[count], strByte, 2);
                    count++;
                }
            }
        }

    }
}

static void reverse_string(char *str, int len) {
    int i;
    char temp;
    for( i = 0; i < len/2; i++ ) {
        temp = str[i];
        str[i] = str[len-i-1];
        str[len-i-1] = temp;
    }
}

void PRINT_UINT128_AS_DECIMAL(uint128_t uint128, char* dest) {
    int i, j, offset;
    char** binary;
    binary = (char **) calloc(NUM_OF_BITS, sizeof(char*));

    for( i = 0; i < NUM_OF_BITS; i++ )
        binary[i] = (char *) malloc(SIZE_OF_DECIMAL_STRING);

    getBits(uint128, binary);

    for( i = 0; i < NUM_OF_BITS; i++ ) {
        if( binary[i][0] != '1' )
            continue;
        for( j = i; j < NUM_OF_BITS-1; j++ )
            doubleDecimal(binary[i]);
    }

    fprintf(stderr, "BINARY:\n");
    for( i = 0; i < NUM_OF_BITS; i++ ) {
        fprintf(stderr, "\t%i: %s\n", i, binary[i]);
    }

    for( i = 1; i < NUM_OF_BITS; i++ ) {
        addDecimalBits(binary[0], binary[i]);
        for( j = 0; j < NUM_OF_BITS; j++ )
            fprintf(stderr, "\t%s\n", binary[j]);
        fprintf(stderr, "\n\n");
    }

    for( i = 0; i < SIZE_OF_DECIMAL_STRING; i++ ) {
        dest[i] = binary[0][i];
        if( dest[i] == '\0' )
            break;
    }

    reverse_string(dest, i);

    for( i = 0; i < NUM_OF_BITS; i++ )
        free(binary[i]);
    free(binary);
}

void FREE_UINT128(uint128_t data) {
    free(data.data - ( (NUM_OF_PARTS - 1) * sizeof(unsigned int) ));
}

int UINT128_ADD_LONG( uint128_t* uint128, unsigned long value ) {
    if( uint128->data == NULL ) {
        return 1;
    }

    if( (uint128->data[0] += value) < value ) {
        int i;
        for( i = 1; i < NUM_OF_PARTS; i++ ) {
            if( (++uint128->data[i]) != 0 )
                break;
        }
    }

    return 0;
}

/* Performs the equivalent of `u1 = u1 + u2` (u2 is left untouched) */
int UINT128_ADD_UINT128( uint128_t* u1, uint128_t* u2 ) {
    if( u1->data == NULL || u2->data == NULL ) {
        return 1;
    } else {
        int i, j;

        for( i = 0; i < NUM_OF_PARTS; i++ ) {
            if( (u1->data[i] += u2->data[i]) < u2->data[i] ) {
                for( j = i+1; j < NUM_OF_PARTS; j++ ) {
                    if( (++u1->data[j]) != 0 )
                        break;
                }
            }
        }
        
        return 0;
    }
}
