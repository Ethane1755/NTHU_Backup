#include <stdio.h>

int main(void){  
    int a, b, c, d = 0;

    scanf("%d.%d %d.%d", &a, &b, &c, &d);

    int n1 = a*c;
    int n2 = b*d + a*d*100 + b*c*100;
    int n = n1*10000+n2;

    printf("%d.%.4d\n",n/10000,n2%10000); 

    return 0;
}