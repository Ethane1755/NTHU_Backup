#include <stdio.h>
#include <string.h>

int count_occurrences(char A[10], char B[10]) {
    int count = 0;
    int lenA = strlen(A);
    int lenB = strlen(B);

    for (int i = 0; i <= lenB - lenA; i++) {
        int match = 1; 
        for (int j = 0; j < lenA; j++) {
            if (B[i + j] != A[j]) { 
                match = 0;
                break;
            }
        }
        if (match) { 
            count++;
        }
    }

    return count;
}

int main() {
    char f[10], k[10];
    int N;
    int max = 0;
    scanf("%s", f);
    scanf("%d", &N);
    while(N--) {
        scanf("%s", k);
        if(count_occurrences(f, k) > max) max = count_occurrences(f, k);
    }
    printf("%d", max);

    return 0;
}