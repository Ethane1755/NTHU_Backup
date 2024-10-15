#include <stdio.h>

int main(void) {

    int num, cnt; 
    int arr[100][100];  // Assuming a maximum size of 100x100 for the array
    scanf("%d", &num);

    for (int i = 0; i < num; i++) {
        scanf("%d", &cnt);  // Read the size of the grid
        
        // Initialize the array to 0 for this test case
        for (int j = 0; j < cnt; j++) {
            for (int k = 0; k < cnt; k++) {
                arr[j][k] = 0;
            }
        }

        // Fill every 4th row with 1s
        for (int l = 0; l < cnt; l += 4) {
            for (int k = 0; k < cnt; k++) {
                arr[l][k] = 1;  // Set all elements of row l to 1
            }
        }

        // Print the array
        for (int j = 0; j < cnt; j++) {
            for (int k = 0; k < cnt; k++) {
                printf("%d", arr[j][k]);
            }
            printf("\n");  // Move to the next line after each row
        }
        printf("\n");  // Separate test cases with a blank line
    }

    return 0;
}