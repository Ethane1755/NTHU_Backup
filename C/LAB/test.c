#include <stdio.h>
#include <stdlib.h>

int* find(int n) {
    int* k = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        k[i] = n * i;
    }
    return k;
}

int main() {
    int* result = find(123);
    for (int i = 0; i < 4; i++) {
        printf("%d ", result[i]);
    }
    free(result);
    return 0;
}
