#include <stdio.h>
#include <string.h>

// Function to perform a cyclic shift on a substring
void cyclic_shift(char *substring, int k) {
    int n = strlen(substring);
    k = k % n;  // Only need to shift k % n times
    if (k == 0) return;  // No need to shift if k is a multiple of n

    // Temporary buffer to store the shifted substring
    char temp[n + 1];
    strncpy(temp, substring + n - k, k);  // Copy the last k characters
    temp[k] = '\0';  // Null-terminate the new substring

    // Shift the first part of the substring
    strncat(temp, substring, n - k);  // Append the first part

    // Copy the result back to the original substring
    strcpy(substring, temp);
}

int main() {
    char s[10001];  // String with a maximum length of 10,000
    int m;  // Number of queries
    
    // Read the input string
    scanf("%s", s);
    
    // Read the number of queries
    scanf("%d", &m);

    // Process each query
    while (m--) {
        int li, ri, ki;
        // Read the query parameters
        scanf("%d %d %d", &li, &ri, &ki);
        
        // Convert 1-based indices to 0-based
        li--; ri--;
        
        // Extract the substring
        char substring[ri - li + 2];  // +2 for null-terminator
        strncpy(substring, s + li, ri - li + 1);
        substring[ri - li + 1] = '\0';  // Null-terminate the substring
        
        // Perform the cyclic shift on the substring
        cyclic_shift(substring, ki);
        
        // Replace the original part of the string with the shifted substring
        strncpy(s + li, substring, ri - li + 1);
    }
    
    // Output the resulting string
    printf("%s\n", s);
    
    return 0;
}