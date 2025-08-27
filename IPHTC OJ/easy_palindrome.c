#include <stdio.h>

int a, b;
double ans;

int main () {
    scanf("%d.%d", &a, &b);

    ans = (a / 100 % 10 + a % 10) + (a / 10 % 10) * 2 * 10 + (a / 100 % 10 + a % 10) * 100;
    //printf("%.3lf", ans);
    ans = ans + (b / 100 % 10 + b % 10) * 0.1 + (b / 10 % 10) * 2 * 0.01 + (b / 100 % 10 + b % 10) * 0.001;
    
    printf("%.3lf", ans);
    return 0;
}