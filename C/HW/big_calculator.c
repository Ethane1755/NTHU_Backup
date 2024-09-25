#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(void){
    char num1[256], num2[256];
    int i;
    scanf("%s",num1);
    scanf("%s",num2);
    //printf("%s",num1);
    char num11[256], num21[256];
    int j = 0;
    for(i=0;i<256;i++){
        if (num1[i] != ','){
            num11[j++] = num1[i];
        }
    }
    num11[j] = '\0';

    int k = 0;
    int l = 0;
    for(k=0;k<256;k++){
        if (num2[k] != ','){
            num21[l++] = num1[k];
        }
    }
    num21[l] = '\0';

    char result[256];
    i = 0;
    for(;i<256;i++){
        result[i] = (int)num11[i] + (int)num21[i];
        printf("%c\n",result[i]);
    }

    result[i] = '\n';





    return 0;
}