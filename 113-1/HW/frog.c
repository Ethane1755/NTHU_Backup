#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

int N, S, T;
int h[16], c[16];
int max_energy = 0, max_jumps = 0;
int jumped[16];

int energy_cost(int i, int j) {
    return abs(i - j) * abs(h[i] - h[j]);
}

void dfs(int current, int energy, int jumps) {
    if (current == T) {
        if (energy > max_energy || (energy == max_energy && jumps > max_jumps)) {
            max_energy = energy;
            max_jumps = jumps;
        }
        return;
    }

    for (int i = 1; i <= N; i++) {
        if (!jumped[i]) {
            if (i == current - 1 || i == current + 1 || c[i] == c[current]) {
                jumped[i] = 1;
                dfs(i, energy + energy_cost(current, i), jumps + 1);
                jumped[i] = 0; 
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &N, &S, &T);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &h[i]);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d", &c[i]);
    }

    jumped[S] = 1;

    dfs(S, 0, 0);

    printf("%d %d\n", max_energy, max_jumps);
    
    return 0;
}