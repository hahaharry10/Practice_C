#include <stdio.h>
#include <time.h>
#include "ways.h"

void check(int arr[MAX]) {
    int failed, i;
    failed = 0;
    for( i = 0; i < MAX; i++ ) {
        if( arr[i] != i ) {
            fprintf(stderr, "\tERROR: arr[%i] = %i\n", i, arr[i]);
            failed++;
        }
        arr[i] = 0; /* Re-assign element to 0. */
    }
    if( !failed )
        fprintf(stdout, "\tPASSED: arr[i] = i\n");
    else
        fprintf(stdout, "\tFAILED: %i index-value pairs do not match.\n", failed);

}

int main(void) {
    int i, arr[MAX];
    clock_t startTime, endTime;
    for( i = 0; i < MAX; i++ )
        arr[i] = 0;

    /* Test Standard Way */
    startTime = clock();
    correctWay(arr);
    endTime = clock();
    fprintf(stdout, "The Correct Way:\n");
    check(arr);
    fprintf(stdout, "Time: %lu\n", (unsigned long) endTime - startTime);

    fprintf(stdout, "\n");

    /* Test Standard Way */
    startTime = clock();
    LHSincrement(arr);
    endTime = clock();
    fprintf(stdout, "arr[var++] = var:\n");
    check(arr);
    fprintf(stdout, "Time: %lu\n", (unsigned long) endTime - startTime);

    fprintf(stdout, "\n");

    /* Test Incorrect Way */
    startTime = clock();
    RHSincrement(arr);
    endTime = clock();
    fprintf(stdout, "arr[var] = var++:\n");
    check(arr);
    fprintf(stdout, "Time: %lu\n", (unsigned long) endTime - startTime);

    fprintf(stdout, "\n");

    return 0;
}
