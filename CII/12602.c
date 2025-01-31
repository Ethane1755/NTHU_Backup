#include <stdio.h>

long long length[51];

void init_length() {
    length[1] = 3;
    for (int i = 2; i <= 50; i++) {
        length[i] = 2 * length[i - 1] + 3;
    }
}

char find(int k, long long a) {
    if (k == 1) {
        return "OuQ"[a];  
    }

    long long prevL = length[k - 1];

    if (a == 0) return 'O';
    if (a == prevL + 1) return 'u';
    if (a == 2 * prevL + 2) return 'Q';

    if (a <= prevL) {
        return find(k - 1, a - 1);  
    } else {
        return find(k - 1, a - prevL - 2); 
    }
}

int main() {
    init_length();
    int k, l, r;
    while (scanf("%d %d %d", &k, &l, &r) != EOF) {
        for (int i = l; i <= r; i++) {
            printf("%c", find(k, i));
        }
        printf("\n");
    }

    return 0;
}