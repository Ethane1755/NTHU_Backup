#include <stdio.h> 
#define MAX_SIZE 1000005 
long long a[MAX_SIZE], b[MAX_SIZE];

int main(){
    int t, n;
    scanf("%d %d ", &t, &n);
    for(int i=1; i <= n; i++){
        char c;
        scanf("%c", &c);
        a[i] = c - 'a';
        b[i] = a[i] - a[i-1];
    }
    
    for (int i=0, l, r, m; i < t; i++){
        scanf("%d %d %d", &l, &r, &m);
        b[l] += m;
        b[r+1] -= m;
    }
    for (int i = 1; i <= n; i++){
        a[i] = a[i - 1] + b[i];   
        printf("%c", (char)('a' + (a[i] % 26 + 26) % 26));
    }
    printf("\n");

    return 0;
}