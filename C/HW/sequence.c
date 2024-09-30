#include <stdio.h>

void Exchange(int seq[], int n, int x) {
    int pos, temp;
    for (pos = 0; pos < n; pos++) {
        if (seq[pos] == x) break;
    }
    
    temp = seq[pos];
    
    for (int i = pos; i > 0; i--) {
        seq[i] = seq[i-1];
    }
    
    seq[0] = temp;
}

int main(void) {
    int a, b, c;
    
    scanf("%d %d", &a, &b);

    int number[a];
    int dict[a];

    for (int i = 0; i < a; i++) {
        number[i] = i + 1;
    }

    for (int i = 0; i < a; i++) {
        dict[i] = number[i];
    }

    for (int i = 0; i < b ; i++) {
        scanf("%d", &c);
        Exchange(number, a, c);
        for (int i = 0; i < a; i++) {
            //printf("%d", number[i]); //
        }
        //printf("\n");
    }
    
    for (int i = 0; i < a; i++) {
        printf("%d\n", number[i]); //
    }
    //printf("\n");

    return 0;
}