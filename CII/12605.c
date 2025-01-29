#include <stdio.h>

int main() {
    int L, N;
    scanf("%d %d", &L, &N);
    char table[27];
    char original[200001];
    for (int i = 0; i < 26; i++) {
        table[i] = i + 'a';
    }
    scanf("%s", original);
    for (int i = 0; i < N; i++) {
        char char_a, char_b;
        scanf(" %c %c", &char_a, &char_b);
        for (int j = 0; j < 26; j++) {
            if (table[j] == char_a) {
                table[j] = char_b;
            } else if (table[j] == char_b) {
                table[j] = char_a;
            }
        }
    }
    for (int i = 0; i <= L; i++) {
        original[i] = table[original[i] - 'a'];
    }
    printf("%s\n", original);
    
    return 0;
}