/* 
 * This project is to discuss memory access variations on big and little endianne systems.
 *
 * My system is bi-endian. But in default compilation it is little endian. This means the
 * least significant bit is stored first - that is, if a variable is stored in address, M,
 * the least significant bit is stored in address M+0.
 *
 * Explanation of below code:
 * The below code stores a 4byte (32bit) integer, and assigns it so that each byte contains
 * a different value. Then I access the memory byte-by-byte outputting the value (the
 * casting to a void pointer is so that the data is outputted in hexadecimal).
 *
 * Results:
 * Using default compilation on my system I get the following:
 * ```
 * &x = 0x16b2e6f78
 * 0x16b2e6f78     x[0] = 0x33
 * 0x16b2e6f79     x[1] = 0x77
 * 0x16b2e6f7a     x[2] = 0xaa
 * 0x16b2e6f7b     x[3] = 0xff
 * ```
 * This shows that the data is stored first is the least significant byte, 0x33.
 *
 * Now if I was to compile for a big endian system using we get:
 * ```
 * &x = 0x7fc51dd4                                                                 
 * 0x7fc51dd4       x[0] = 0xff                                                    
 * 0x7fc51dd5       x[1] = 0xaa                                                    
 * 0x7fc51dd6       x[2] = 0x77                                                    
 * 0x7fc51dd7       x[3] = 0x33 
 * ```
 *
 * NOTE: Compiling on big endian systems is a pain, so I used an online emulator found at
 *      https://s-macke.github.io/jor1k/demos/main.html?user=FeiYnkwfsw&cpu=asm&n=1&relayURL=wss%3A%2F%2Frelay.widgetry.org%2F
 *
 * As we can see, a big endian system and a little endian system are indexed differently. If
 * you were to use natural datatypes without individual byte addressing then there should be
 * no issue in compatibility with different endianness, but if you are operating on the byte
 * level like below then your code will not inherently be bi-endian compatible.
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint8_t getByte(char *arr, int index) {
    return arr[index];
}

int main(void) {
    uint32_t x, i;

    x = 0xFFAA7733;
    fprintf(stdout, "&x = %p\n", (void *) &x);
    for( i = 0; i < sizeof(x); i++ ) {
        fprintf(
            stdout,
            "%p\tx[%i] = %p\n",
            (void *) ((char *) &x + i),
            i,
            (void *) (uint64_t) getByte((char *) &x, i)
        );
    }
    return 0;
}
