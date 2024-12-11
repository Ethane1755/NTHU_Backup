#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define BASE 37

// Function to calculate occurrences of a pattern S in string str using rolling hash
int countOccurrences(char *str, char *pattern) {
    int len_str = strlen(str);
    int len_pat = strlen(pattern);

    if (len_pat > len_str) return 0;

    long long hash_pat = 0, hash_window = 0, base_power = 1;

    // Precompute hash for pattern and the first window
    for (int i = 0; i < len_pat; i++) {
        hash_pat = (hash_pat * BASE + (pattern[i] - 'a' + 1)) % MOD;
        hash_window = (hash_window * BASE + (str[i] - 'a' + 1)) % MOD;
        if (i < len_pat - 1) base_power = (base_power * BASE) % MOD;
    }

    int count = 0;

    // Slide the window over the string
    for (int i = 0; i <= len_str - len_pat; i++) {
        if (hash_window == hash_pat) {
            // Verify match to avoid hash collision
            if (strncmp(&str[i], pattern, len_pat) == 0) {
                count++;
            }
        }
        // Slide the window: remove the first character and add the next
        if (i < len_str - len_pat) {
            hash_window = (hash_window - (str[i] - 'a' + 1) * base_power % MOD + MOD) % MOD;
            hash_window = (hash_window * BASE + (str[i + len_pat] - 'a' + 1)) % MOD;
        }
    }

    return count;
}

// Bubble sort puzzles based on preference levels (stable sort)
void bubbleSort(char puzzles[][10001], int *preference, int n) {
    char temp[10001];
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (preference[j] < preference[j + 1]) {
                // Swap preference levels
                int temp_pref = preference[j];
                preference[j] = preference[j + 1];
                preference[j + 1] = temp_pref;

                // Swap strings
                strcpy(temp, puzzles[j]);
                strcpy(puzzles[j], puzzles[j + 1]);
                strcpy(puzzles[j + 1], temp);
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    char puzzles[n][10001];
    int preference[n];

    for (int i = 0; i < n; i++) {
        scanf("%s", puzzles[i]);
    }

    char pattern[10001];
    scanf("%s", pattern);

    // Calculate preference levels for each puzzle
    for (int i = 0; i < n; i++) {
        preference[i] = countOccurrences(puzzles[i], pattern);
        printf("%d ", preference[i]);
    }

    // Sort puzzles based on preference levels
    bubbleSort(puzzles, preference, n);

    // Output the sorted puzzles
    for (int i = 0; i < n; i++) {
        printf("%s\n", puzzles[i]);
    }

    return 0;
}
