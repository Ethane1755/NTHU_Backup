#include <stdio.h>

void create_spiral(int n) {
    // Create an N x N grid filled with spaces (' ')
    char grid[n][n];
    
    // Initialize the grid with spaces
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            grid[i][j] = ' ';

    // Spiral movement directions: right -> down -> left -> up
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int dir = 0;  // Start by moving right
    int x = 0, y = 0;  // Starting position

    // Mark the starting position with '#'
    grid[0][0] = '#';

    // Keep track of the boundaries of the spiral
    int top_bound = 1, bottom_bound = n - 1;
    int left_bound = 0, right_bound = n - 1;

    // We already placed the first '#', now place the remaining (N*N - 1) symbols
    for (int step = 1; step < n * n; ++step) {
        // Get current direction
        int dx = directions[dir][0];
        int dy = directions[dir][1];

        // Calculate the next position
        int nx = x + dx;
        int ny = y + dy;

        // Check if the next position is within bounds
        if (dir == 0 && ny > right_bound) { // right -> down
            dir = 1;
            top_bound++;
        } else if (dir == 1 && nx > bottom_bound) { // down -> left
            dir = 2;
            right_bound--;
        } else if (dir == 2 && ny < left_bound) { // left -> up
            dir = 3;
            bottom_bound--;
        } else if (dir == 3 && nx < top_bound) { // up -> right
            dir = 0;
            left_bound++;
        }

        // Update direction and calculate the next position
        dx = directions[dir][0];
        dy = directions[dir][1];
        x += dx;
        y += dy;

        // Mark the grid position with '#'
        grid[x][y] = '#';
    }

    // Print the grid row by row
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%c", grid[i][j]);
        }
        printf("\n");  // Move to the next line after each row
    }
}

int main() {
    int t, n;

    // Read the number of test cases
    scanf("%d", &t);

    // Process each test case
    for (int i = 0; i < t; ++i) {
        // Read the size of the grid for the current test case
        scanf("%d", &n);

        // Generate and print the spiral for the given size
        create_spiral(n);
        
        // Print a newline between test case outputs, except after the last one
        if (i < t - 1) {
            printf("\n");
        }
    }

    return 0;
}