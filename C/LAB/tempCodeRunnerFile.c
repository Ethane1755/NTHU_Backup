#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100005

int colors[MAX_N];
int weights[MAX_N];
int distinct_colors[8]; // Since 1 ≤ Ci ≤ 7

void process_query(int m, int *max_distinct, int *max_weight) {
    int collected_colors[8] = {0}; // To track collected colors
    int total_weight = 0;
    int distinct_count = 0;

    for (int i = 1; i <= m; i++) {
        if (collected_colors[colors[i]] == 0) {
            collected_colors[colors[i]] = weights[i];
            distinct_count++;
            total_weight += weights[i];
        } else if (collected_colors[colors[i]] < weights[i]) {
            total_weight = total_weight - collected_colors[colors[i]] + weights[i];
            collected_colors[colors[i]] = weights[i];
        }
    }

    *max_distinct = distinct_count;
    *max_weight = total_weight;
}

int main() {
    int N, Q;
    scanf("%d %d", &N, &Q);

    for (int i = 1; i <= N; i++) {
        scanf("%d", &colors[i]);
    }

    for (int i = 1; i <= N; i++) {
        scanf("%d", &weights[i]);
    }

    while (Q--) {
        int m;
        scanf("%d", &m);

        int max_distinct = 0;
        int max_weight = 0;
        process_query(m, &max_distinct, &max_weight);

        printf("%d %d\n", max_distinct, max_weight);
    }

    return 0;
}