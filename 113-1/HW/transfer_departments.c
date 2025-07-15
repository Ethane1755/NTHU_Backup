#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, M, T;
    scanf("%d %d %d", &N, &M, &T);
    
    int *departments = (int *)malloc((N + 1) * sizeof(int));

    for (int i = 1; i <= N; i++) {
        scanf("%d", &departments[i]);
    }

    for (int i = 0; i < T; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        int temp = departments[x];
        departments[x] = departments[y];
        departments[y] = temp;
    }

    int Q;
    scanf("%d", &Q);

    int *result = (int *)malloc(N * sizeof(int));
    int count = 0;

    for (int i = 1; i <= N; i++) {
        if (departments[i] == Q) {
            result[count++] = i;
        }
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (result[i] > result[j]) {
                int temp = result[i];
                result[i] = result[j];
                result[j] = temp;
            }
        }
    }

    for (int i = 0; i < count; i++) {
        printf("%d", result[i]);
        if (i < count - 1) {
            printf(" ");
        }
    }
    printf("\n");

    free(departments);
    free(result);

    return 0;
}