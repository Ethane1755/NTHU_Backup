#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, m;
    
    // Read the size of the sequence and the number of requests
    scanf("%d %d", &n, &m);

    int *number = malloc(n * sizeof(int));
    int *position = malloc(n * sizeof(int));
    int *output = malloc(n * sizeof(int));
    
    // Initialize the number array with values from 1 to n
    for (int i = 0; i < n; i++) {
        number[i] = i + 1;  // Fill the array with 1 to n
        position[i] = i;    // Initial positions
    }

    // Process each request
    for (int i = 0; i < m; i++) {
        int c;
        scanf("%d", &c);
        int pos = position[c - 1];  // Get the current position of the element c
        
        // If c is not at the front
        if (pos > 0) {
            // Move c to the front
            int temp = number[pos]; // Store the value at pos
            // Shift elements from pos to 0
            for (int j = pos; j > 0; j--) {
                number[j] = number[j - 1]; // Shift elements
                position[number[j] - 1] = j; // Update positions
            }
            number[0] = temp; // Place c at the front
            position[c - 1] = 0; // Update position of c
        }
    }

    // Output the final arrangement
    for (int i = 0; i < n; i++) {
        printf("%d\n", number[i]);
    }

    // Free allocated memory
    free(number);
    free(position);
    free(output);

    return 0;
}