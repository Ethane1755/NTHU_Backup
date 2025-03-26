#include <stdio.h>

int main () {
    int n, m, temp;
    int a1[200001] = {0}, a2[200001] = {0}, printed[200001] = {0};  
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d", &temp);
        a1[temp - 1] = 1;
        a2[i] = temp;
    }

    for (int i = m - 1; i >= 0; i--) {
        if (!printed[a2[i] - 1]) {  
            printf("%d\n", a2[i]);
            printed[a2[i] - 1] = 1;  
        }
    }

    for (int i = 0; i < n; i++) {
        if (a1[i] == 0) {
            printf("%d\n", i + 1);
        }
    }
    
    return 0;
}