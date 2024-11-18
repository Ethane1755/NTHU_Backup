#include <stdio.h>

// function.c
#include "function.h"

void shift(char *start, char *end) {
    if (start == end) return; // 如果子字串長度為1，則無需改變

    char first_char = *start; // 暫存子字串的第一個字元
    char *ptr;

    // 將子字串中每個字元向左移一位
    for (ptr = start; ptr < end; ++ptr) {
        *ptr = *(ptr + 1);
    }

    // 最後一個位置設為原來的第一個字元
    *end = first_char;
}



int main(){
	char str[111];
	int n,l,r;
	scanf("%s",str);
	scanf("%d",&n);
	while(n--){
		scanf("%d%d",&l,&r);
		shift(&str[l-1], &str[r-1]);
	}
	printf("%s\n",str);
}