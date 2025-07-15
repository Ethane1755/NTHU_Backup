#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int flag = 0;

int sort (const void *a, const void *b) {
    const char *sa = *(const char **)a;
    const char *sb = *(const char **)b;
    if (strstr(sa, sb)) return 1;   // sa 包含 sb，sa 應排後面
    if (strstr(sb, sa)) return -1;  // sb 包含 sa，sa 應排前面
    flag = 1;
    return strcmp(sa, sb);          // 否則字典序
}

int n;
char name[1001][1001];
char *ptr[1001];

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        scanf("%s", name[i]);
        ptr[i] = name[i];
    }

    qsort(ptr, n, sizeof(char*), sort);
    if (flag) {
        printf("NO\n");
        return 0;
    } else {
        printf("YES\n");
    }

    for (int i = 0; i < n; i++) {
        printf("%s\n", ptr[i]);
    }
    return 0;
}