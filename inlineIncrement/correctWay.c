#include "ways.h"

int standardWay(int arr[MAX]) {
    int i;

    i = 0;
    while( i < MAX ) {
        arr[i] = i;
        i++;
    }

    return 0;
}
