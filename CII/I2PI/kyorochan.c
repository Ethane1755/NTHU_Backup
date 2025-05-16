#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TABLE_SIZE 1000005
#define MAX_PRIME_SIZE 200005
#define MAX_N 3000005

long long table[MAX_TABLE_SIZE];
long long prime[MAX_PRIME_SIZE];
int prime_id = 1;

void generate_primes() {
    bool* is_prime = (bool*)malloc(MAX_N * sizeof(bool));
    for (int i = 0; i < MAX_N; i++) {
        is_prime[i] = true;
    }
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i < MAX_N; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j < MAX_N; j += i) {
                is_prime[j] = false;
            }
        }
    }

    int count = 0;
    prime[count++] = 1;
    for (int i = 2; i < MAX_N && count < MAX_PRIME_SIZE; i++) {
        if (is_prime[i]) {
            prime[count++] = i;
        }
    }

    free(is_prime);
}

int binary_search(long long target) {
    int left = 0;
    int right = MAX_TABLE_SIZE - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (table[mid] > target) {
            right = mid - 1;
        } else if (table[mid] < target) {
            left = mid + 1;
        } else {
            return mid;
        }
    }
    return left;
}

int main() {
    generate_primes();

    int T;
    scanf("%d", &T);

    // Precompute table[i] = i * (i + 1) / 2
    for (long long i = 0; i < MAX_TABLE_SIZE; i++) {
        table[i] = i * (i + 1) / 2;
    }

    while (T--) {
        prime_id = 1;
        int n;
        long long m, k;
        scanf("%d %lld %lld", &n, &m, &k);

        if (m > table[n]) {
            printf("-1\n");
            continue;
        }

        int* answer = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            answer[i] = 1;
        }

        int lb = binary_search(m);
        int difference = table[lb] - m;
        int lb2_minus = binary_search(difference) - 1;
        int difference2 = difference - table[lb2_minus];

        for (int i = 0; i < lb; i++) {
            answer[i] = k;
        }

        prime_id++;
        for (int i = 1; i <= lb2_minus; i++) {
            answer[lb - i] = 2 * k;
        }

        for (int i = 1; i <= difference2; i++) {
            answer[lb - lb2_minus - i] = k * prime[prime_id++];
        }

        for (int i = 0; i < n; i++) {
            printf("%d", answer[i]);
            if (i != n - 1) {
                printf(" ");
            } else {
                printf("\n");
            }
        }

        free(answer);
    }

    return 0;
}