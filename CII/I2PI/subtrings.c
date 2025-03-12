#include <stdio.h>
#include <string.h>

int count_exquisite_substrings(const char *s) {
    int n = strlen(s);
    int dp[n][n];  // DP table to store whether s[i, j] is a palindrome
    int count = 0;

    // Initialize the DP table
    memset(dp, 0, sizeof(dp));

    // Single character substrings are trivially palindromes (but we don't count them)
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }

    // Check for two character substrings
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = 1;
            count++;  // Found a palindromic substring of length 2
        }
    }

    // Check for substrings of length >= 3
    for (int length = 3; length <= n; length++) {
        for (int i = 0; i <= n - length; i++) {
            int j = i + length - 1;
            if (s[i] == s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = 1;
                count++;  // Found a palindromic substring of length >= 3
            }
        }
    }

    return count;
}

int main() {
    char s[2001];  // The string can have a maximum length of 2000 characters
    
    // Read input until EOF
    while (fgets(s, sizeof(s), stdin)) {
        s[strcspn(s, "\n")] = 0;  // Remove the trailing newline
        printf("%d\n", count_exquisite_substrings(s));
    }

    return 0;
}