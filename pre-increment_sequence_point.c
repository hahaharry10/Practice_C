/*
 * Investigate whether the pre-increment operator introduces a
 * sequence point.
 *
 * I read online that in C and C++, the pre-increment operator
 * introduces a sequence point. However the standard (C89, C99,
 * C11, C20) shows otherwise. Running on my Mac terminal this
 * code seems to be consistant accross compilers, however on
 * my Linux virtual machine it is undefined and the execution
 * is different with clang than it is with gcc.
 *
 * This means that the behaviour is truly undefined.
 *
 * NOTE: This ONLY tests C behaviour. There is no conclusion
 * in regards to C++.
 *
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
        x[i] = ++i;
        a[++j] = j;
    }

    for( i = 0; i < ARRAY_SIZE+1; i++ ) {
        fprintf(stdout, "arr[%i] = %i\t%i\n", i, x[i], a[i]);
    }

    return 0;
}
