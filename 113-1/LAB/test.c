#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000
#define MAX_COLOR 7

int main() {
    int N, Q;
    scanf("%d %d", &N, &Q);

    int colors[MAX_N + 1];
    int weights[MAX_N + 1];
    int max_distinct_colors[MAX_N + 1];
    int max_weight[MAX_N + 1];

    // Read colors and weights
    for (int i = 1; i <= N; i++) {
        scanf("%d", &colors[i]);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d", &weights[i]);
    }

    // Precompute results for all positions
    for (int i = 1; i <= N; i++) {
        int color_count[MAX_COLOR + 1] = {0}; // To count distinct colors
        int total_weight = 0;

        // Collect gems from multiples of i
        for (int j = i; j <= N; j += i) {
            int color = colors[j];
            if (color_count[color] == 0) { // New color found
                color_count[color] = weights[j];
                total_weight += weights[j];
            } else { // Existing color, add weight only if it's not already counted
                total_weight += weights[j]; // Add weight for existing color
            }
        }

        // Count distinct colors
        max_distinct_colors[i] = 0;
        for (int c = 1; c <= MAX_COLOR; c++) {
            if (color_count[c] > 0) {
                max_distinct_colors[i]++;
            }
        }
        
        max_weight[i] = total_weight;
    }

    // Answering queries
    for (int k = 0; k < Q; k++) {
        int m;
        scanf("%d", &m);
        printf("%d %d\n", max_distinct_colors[m], max_weight[m]);
    }

    return 0;
}
