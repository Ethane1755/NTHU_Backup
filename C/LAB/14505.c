#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 10010 // 單個字符串的最大長度

// 計算字符串的偏好層級
int calculatePreferenceLevel(const char *s, int m, int k, int x, int y) {
    int len = strlen(s);
    if (len < m) return 0; // 若字符串長度不足 m，偏好層級為 0

    // 計算 k^(m-1) % y
    long long km1 = 1;
    for (int i = 0; i < m - 1; i++) {
        km1 = (km1 * k) % y;
    }

    // 計算首個子字符串的值
    long long sum = 0;
    for (int i = 0; i < m; i++) {
        sum = (sum * k + (s[i] - 'a' + 1)) % y;
    }
    int preferenceLevel = (sum == x);

    // 滑動窗口計算剩餘子字符串的值
    for (int i = m; i < len; i++) {
        sum = (sum - ((s[i - m] - 'a' + 1) * km1) % y + y) % y; // 移除舊字符
        sum = (sum * k + (s[i] - 'a' + 1)) % y;                // 添加新字符
        if (sum == x) preferenceLevel++;
    }

    return preferenceLevel;
}

// 使用穩定排序對字符串進行排序（冒泡排序）
void bubbleSort(char puzzles[][MAX_LEN], int *preferenceLevels, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (preferenceLevels[j] < preferenceLevels[j + 1]) {
                // 交換偏好層級
                int temp = preferenceLevels[j];
                preferenceLevels[j] = preferenceLevels[j + 1];
                preferenceLevels[j + 1] = temp;

                // 交換字符串
                char tempStr[MAX_LEN];
                strcpy(tempStr, puzzles[j]);
                strcpy(puzzles[j], puzzles[j + 1]);
                strcpy(puzzles[j + 1], tempStr);
            }
        }
    }
}

int main() {
    int n, m, k, x, y;
    scanf("%d %d %d %d %d", &n, &m, &k, &x, &y);

    char puzzles[n][MAX_LEN]; // 儲存所有字符串
    int preferenceLevels[n];  // 儲存每個字符串的偏好層級

    // 輸入字符串並計算偏好層級
    for (int i = 0; i < n; i++) {
        scanf("%s", puzzles[i]);
        preferenceLevels[i] = calculatePreferenceLevel(puzzles[i], m, k, x, y);
    }

    // 排序字符串
    bubbleSort(puzzles, preferenceLevels, n);

    // 輸出排序結果
    for (int i = 0; i < n; i++) {
        printf("%s\n", puzzles[i]);
    }

    return 0;
}