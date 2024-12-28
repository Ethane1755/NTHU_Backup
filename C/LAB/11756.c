#include <stdio.h>
#include <stdlib.h>
#include "function.h"

unsigned** new_2d_array(unsigned n,unsigned m) {
    unsigned ** arr = (unsigned**) malloc (sizeof(unsigned *) * n);
    arr[0] = (unsigned*) malloc (sizeof(unsigned) * n * m);

    for (unsigned i = 0; i < n; i++) {
        arr[i] = arr[0] + i * m;
    }
    return arr;
}

void delete_2d_array(unsigned **arr) {
    free(arr[0]);
    free(arr);
}

