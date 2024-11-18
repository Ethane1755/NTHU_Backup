#include <stdio.h>
#include <string.h>

int if_palindrome(char a[]) {
    int len;
    len = strlen(a);
    for (int i = 0 ; i < len; i++) {
        if (a[i] != a[len-i-1]) {
            //printf("%c %c", a[i], a[len-i-1]);
            return 0;
            break;
        }
    }
    return 1;
}

void pop(char a[]) {
    int tf;
    int key = 0;
    int len;

    len = strlen(a);
    tf = if_palindrome(a);
    printf("%d\n", tf);
    if(tf == 1) {
        printf("YES");
    } else {
        char b[1000];
        for (int i = 0 ; i < len; i++) {
            if (i != key) {
                if (i < key) {
                    b[i] = a[i];
                }
            } else {
                b[i] = a[i-1];
            }
            key++;
        }
        printf("%s", b);
        pop(b);
    }


}


int main() {
    int n, m;
    char a[1000];
    int k;


    //scanf("%d %d", &n, &m);
    scanf("%s", a);
    //printf("%d\n", if_palindrome(a));
    pop(a);

    return 0;
}