#include <stdio.h>
#include <limits.h>

int main() {
    int N;
    scanf("%d", &N);  

    int x, min_pos = INT_MAX, max_pos = INT_MIN;

    for (int i = 0; i < N + 1; i++) {
        scanf("%d", &x);  
        if (x < min_pos) min_pos = x;  
        if (x > max_pos) max_pos = x;  
    }

    long long result = 2 * (max_pos - min_pos);  
    printf("%lld\n", result);  
    return 0;
}