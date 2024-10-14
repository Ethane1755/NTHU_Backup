#include <stdio.h>
#include <string.h>

int main() {
	int n, m, ans = 0;
	scanf("%d", &n);
	char A[10005], B[10005];
	int cnt[26];
	for (int i = 0; i < n; i++) {
		scanf("%s %s", A, B);
		m = strlen(A);
		for (int j = 0; j < 26; j++)
			cnt[j] = 0;
		for (int j = 0; j < m; j++)
			cnt[A[j] - 'a']++;
		for (int j = 0; j < m; j++)
			cnt[B[j] - 'a']--;
		int flag = 1;
		for (int j = 0; j < 26; j++)
			if (cnt[j] != 0)
				flag = 0;
		ans += flag;
	}
	printf("%d\n", ans);
}
