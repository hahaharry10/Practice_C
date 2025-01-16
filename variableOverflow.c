#include <stdio.h>
#include <stdlib.h>

/* I was wondering if overflow just causes wrapping, or if it affects the proceeding memory address. */
int main(void) {
    unsigned char char2, char1;

    char1 = 0x0-1;
    char2 = 0x0;
    fprintf(stdout, "Created 2 chars with addresses (and stored values):\n\tchar 1: %p (%i)\n\tchar 2: %p (%i)", (void *) &char1, char1, (void *) &char2, char2);

    fprintf(stdout, "Incrementing char 1 by 1...\n");
    char1++;
    fprintf(stdout, "\n\tchar 1: %p (%i)\n\tchar 2: %p (%i)\n", (void *) &char1, char1, (void *) &char2, char2);
}
