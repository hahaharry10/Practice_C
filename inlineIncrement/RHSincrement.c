#include "ways.h"

int RHSincrement(int arr[MAX]) {
    int i;

    i = 0;
    while( i < MAX ) {
        arr[i] = i++;
    }

    return 0;
}
