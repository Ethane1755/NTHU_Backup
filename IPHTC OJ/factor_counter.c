#include <stdio.h>
#include <math.h>

int arr[20000];

int find_factor(int a) {
    int cnt = 0;
    for (int i = 1; i <= sqrt(a); i++) {
        if (a % i == 0 && i != sqrt(a)) cnt += 2;
        else if (a % i == 0 && i == sqrt(a)) cnt += 1;
    }
    return cnt;
}

int main () {
    int T, l, r;
    int temp, ans;
    for (int i = 1; i <= 20000; i++) {
        arr[i-1] = find_factor(i);
    }
    scanf("%d", &T);
    while (T--) {
        temp = 0;
        scanf("%d %d", &l, &r);
        if (l == r) {
            printf("%d\n", l);
        } else {
            for (int j = l-1; j < r; j++) {
                //printf("%d %d %d\n", j+1, arr[j], temp);
                if (arr[j] > temp) {
                    temp = arr[j];
                    ans = j+1;
                }
            }
            printf("%d\n", ans);
        }
    }

    return 0;
}