#include <stdio.h>
#include <string.h>
#include <assert.h>

void find(int n, int k, char c1[2001], char c2[2001]) {
    unsigned long long len[60];
    len[0] = strlen(c1);
    len[1] = strlen(c2);

    for (int i = 2; i <= n; i++) {
        len[i] = len[i-2] + len[i-1];
    }

    while (n > 1) {
        if (k < len[n-2]) {
            n -= 2;
        } else {
            k -= len[n-2];
            n -= 1;
        }
    }

    if (n == 0) {
        printf("%c\n", c1[k]);
    } else {
        printf("%c\n", c2[k]);
    }
}

// 測試函式
void test() {
    char F0[2001] = "abc", F1[2001] = "def";
    char result;

    // 測試 1: F0 的第 0 個字元
    {
        int n = 0, k = 0;
        result = F0[k];
        printf("Expected: %c, ", result);
        find(n, k, F0, F1);
    }

    // 測試 2: F1 的第 0 個字元
    {
        int n = 1, k = 0;
        result = F1[k];
        printf("Expected: %c, ", result);
        find(n, k, F0, F1);
    }

    // 測試 3: F2 的第 5 個字元
    {
        int n = 2, k = 5;
        char F2[2001];
        sprintf(F2, "%s%s", F0, F1); // 生成 F2 = "abcdef"
        result = F2[k];
        printf("Expected: %c, ", result);
        find(n, k, F0, F1);
    }

    // 測試 4: F3 的第 8 個字元
    {
        int n = 3, k = 8;
        char F2[2001], F3[4001];
        sprintf(F2, "%s%s", F0, F1); // F2 = "abcdef"
        sprintf(F3, "%s%s", F1, F2); // F3 = "defabcdef"
        result = F3[k];
        printf("Expected: %c, ", result);
        find(n, k, F0, F1);
    }

    // 測試 5: F4 的第 7 個字元
    {
        int n = 4, k = 7;
        char F2[2001], F3[4001], F4[6001];
        sprintf(F2, "%s%s", F0, F1); // F2 = "abcdef"
        sprintf(F3, "%s%s", F1, F2); // F3 = "defabcdef"
        sprintf(F4, "%s%s", F2, F3); // F4 = "abcdefdefabcdef"
        result = F4[k];
        printf("Expected: %c, ", result);
        find(n, k, F0, F1);
    }

    // 更多測試 (可擴展)
    {
        // 測試極限條件
        int n = 59, k = 0;
        printf("Testing extreme case with n = %d and k = %d\n", n, k);
        find(n, k, F0, F1);
    }
}

int main() {
    test(); // 執行測試
    return 0;
}