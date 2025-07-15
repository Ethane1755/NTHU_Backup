#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000000  
#define ALPHABET_SIZE 26 

int main() {
    char s[MAX_LEN + 1]; 
    int Q;               
    char map[ALPHABET_SIZE]; 

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        map[i] = 'a' + i;
    }
    scanf("%s", s);
    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
        char A, B;
        scanf(" %c %c", &A, &B); 

        for (int j = 0; j < ALPHABET_SIZE; j++) {
            if (map[j] == A) {
                map[j] = B;
            }
        }
    }
    for (int i = 0; s[i] != '\0'; i++) {
        s[i] = map[s[i] - 'a']; 
    }
    printf("%s\n", s);
    return 0;
}