#include <stdio.h>
#include <string.h>
#define MAX_DIGITS 256 

void reverse(char* str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

void formatWithCommas(char* result) {
    int len = strlen(result);
    int count = 0;

    char formatted[MAX_DIGITS];
    int j = 0;

    for (int i = len - 1; i >= 0; i--) {
        count++;
        formatted[j++] = result[i];
        if (count % 3 == 0 && i != 0) {
            formatted[j++] = ','; 
        }
    }
    formatted[j] = '\0'; 
    reverse(formatted);
    printf("%s\n", formatted); 
}

int main(void) {
    char num1[MAX_DIGITS], num2[MAX_DIGITS];
    scanf("%s", num1);
    scanf("%s", num2);

    char num11[MAX_DIGITS], num21[MAX_DIGITS];
    int j = 0;
    for (int i = 0; num1[i]; i++) {
        if (num1[i] != ',') {
            num11[j++] = num1[i];
        }
    }
    num11[j] = '\0'; 

    j = 0; 
    for (int i = 0; num2[i]; i++) {
        if (num2[i] != ',') {
            num21[j++] = num2[i];
        }
    }
    num21[j] = '\0'; 

    char result[MAX_DIGITS];
    int carry = 0;
    int len1 = strlen(num11);
    int len2 = strlen(num21);
    int i = 0, k = 0;

    while (i < len1 || i < len2 || carry) {
        int digit1 = (i < len1) ? num11[len1 - 1 - i] - '0' : 0; 
        int digit2 = (i < len2) ? num21[len2 - 1 - i] - '0' : 0; 
        
        int sum = digit1 + digit2 + carry; 
        result[k++] = (sum % 10) + '0'; 
        carry = sum / 10; 
        i++;
    }

    result[k] = '\0'; 
    reverse(result); 

    formatWithCommas(result);

    return 0;
}