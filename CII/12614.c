#include <stdio.h>

int main() {
    int N, M, cnt = 0;
    int games[1001], wallet[1001];

    scanf("%d %d", &N, &M);
    for(int i = 0; i < N; i++) {
        scanf("%d", &games[i]);
    }
    for(int i = 0; i < M; i++) {
        scanf("%d", &wallet[i]);
    }

    int j = 0; 
    for(int i = 0; i < N && j < M; i++) {
        if(wallet[j] >= games[i]) {
            cnt++; 
            j++;   
        }
    }

    printf("%d\n", cnt);
    return 0;
}
