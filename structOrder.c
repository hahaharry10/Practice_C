#include <stdio.h>

/*
 * Here we have two structs, containing the same members but in a different
 * order. As initially explored in structPadding.c, alignment can affect the
 * padding within a struct and leave empty memory space between members.
 *
 * The below code demonstrates how the order of the structure can be optmised
 * so that less memory is used (as shown by the 4-byte difference in size
 * between `badOrder` and `goodOrder`), and even how the padding can be filled
 * with more members so that the struct can contain more date without changing
 * size (as shown by `optOrder` using all 12 bytes of data whereas goodOrder
 * only uses 10 bytes of its 12 byte size).
 */

typedef struct {
    char c1;
    int i1;
    char c2;
    int i2;
} badOrder;

typedef struct {
    int i1;
    int i2;
    char c1;
    char c2;
} goodOrder;

typedef struct {
    int i1;
    int i2;
    char c1;
    char c2;
    short s1;
} optOrder;

int main(void)  {
    badOrder b;
    goodOrder g;
    optOrder o;

    fprintf(stdout, "Addresses:\n");
    fprintf(stdout, "\tbadOrder:\n");
    fprintf(stdout, "\t\tc1: %p\n", (void *) &b.c1);
    fprintf(stdout, "\t\ti1: %p\n", (void *) &b.i1);
    fprintf(stdout, "\t\tc2: %p\n", (void *) &b.c2);
    fprintf(stdout, "\t\ti2: %p\n", (void *) &b.i2);
    fprintf(stdout, "\t\tSize: %lu\n", sizeof(b));

    fprintf(stdout, "\tgoodOrder:\n");
    fprintf(stdout, "\t\ti1: %p\n", (void *) &g.i1);
    fprintf(stdout, "\t\ti2: %p\n", (void *) &g.i2);
    fprintf(stdout, "\t\tc1: %p\n", (void *) &g.c1);
    fprintf(stdout, "\t\tc2: %p\n", (void *) &g.c2);
    fprintf(stdout, "\t\tSize: %lu\n", sizeof(g));

    fprintf(stdout, "\toptOrder:\n");
    fprintf(stdout, "\t\ti1: %p\n", (void *) &o.i1);
    fprintf(stdout, "\t\ti2: %p\n", (void *) &o.i2);
    fprintf(stdout, "\t\tc1: %p\n", (void *) &o.c1);
    fprintf(stdout, "\t\tc2: %p\n", (void *) &o.c2);
    fprintf(stdout, "\t\ts1: %p\n", (void *) &o.s1);
    fprintf(stdout, "\t\tSize: %lu\n", sizeof(o));

    return 0;
}
