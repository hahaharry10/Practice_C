/*
 * Investigate whether the pre-increment operator introduces a
 * sequence point.
 */


#include <stdio.h>

#define ARRAY_SIZE 10

int main(void) {
    int x[ARRAY_SIZE+1], a[ARRAY_SIZE+1], i, j;

    for( i = 0; i < ARRAY_SIZE+1; i++ ) {
        x[i] = -1;
        a[i] = -1;
    }

    x[ARRAY_SIZE] = -1;
    i = 0;
    j = 0;
    while( i < ARRAY_SIZE || j < ARRAY_SIZE ) {
        x[i] = i++;
        a[j++] = j;
    }

    for( i = 0; i < ARRAY_SIZE+1; i++ ) {
        fprintf(stdout, "arr[%i] = %i\t%i\n", i, x[i], a[i]);
    }

    return 0;
}
