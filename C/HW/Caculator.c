#include <stdio.h>

int main(void){
    float a, b = 0.0;
    char x;
    
    scanf("%f %c %f",&a,&x,&b);

    if (x == '+'){
        printf("%1.3f\n",a+b);
    }
    if (x == '-'){
        printf("%1.3f\n",a-b);
    }
    if (x == '*'){
        printf("%1.3f\n",a*b);
    }
    if (x == '/'){
        printf("%1.3f\n",a/b);
    }

    return 0;
}