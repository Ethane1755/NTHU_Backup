#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char s[100000+10];

int compare (const void *a, const void *b) {
    const char *str1 = *(char**)a;
    const char *str2 = *(char**)b;

    int len_a = strlen(str1);
    int len_b = strlen(str2);
    // 長度長的排前面
    if (len_a < len_b) return 1;
    else if (len_a > len_b) return -1; 
    else return strcmp(str1, str2);
    
}

int main () {
    int T;
    scanf("%d", &T);
    while (T--) {
        fgets(s, 100010, stdin);
        int len = strlen(s);
        s[len - 1] = '\0';
        int o = strcspn(s, "+-.@");
        if (s[o] == '+') {
            char *a = strtok(s, " + ");
            char *b = strtok(NULL, " + "); // 特別注意 strtok 會記得分到哪
            printf("%s%s", a, b);
        } else if (s[o] == '-') {
            char *a = strtok(s, " - ");
            char *b = strtok(NULL, " - "); 
            char *overlap = strstr(a, b);
            if (overlap) {
                int end = overlap - a;
                for (int i = 0; i < end; i++) printf("%c", a[i]);
                printf("%s\n", overlap + strlen(b));
            } else {
                printf("error\n");
            }
        }




    }
    return 0;
}