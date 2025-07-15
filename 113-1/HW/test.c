#include <stdio.h>
#include <string.h>

// Function to check if a string is a palindrome
int is_palindrome(char a[]) {
    int len = strlen(a);
    for (int i = 0; i < len / 2; i++) {
        if (a[i] != a[len - i - 1]) {
            return 0;  // Not a palindrome
        }
    }
    return 1;  // Is a palindrome
}

// Function to remove character at a specified index
void remove_char(char str[], int index) {
    int len = strlen(str);
    for (int i = index; i < len - 1; i++) {
        str[i] = str[i + 1];
    }
    str[len - 1] = '\0';  // Null-terminate the string
}

// Recursive function to check if we can make the string a palindrome by removing up to 'removals_left' characters
int make_palindrome(char a[], int removals_left) {
    if (is_palindrome(a)) {
        return 1;  // Palindrome achieved
    }
    if (removals_left == 0) {
        return 0;  // No more removals allowed
    }

    int len = strlen(a);
    for (int i = 0; i < len; i++) {
        char temp[1000];
        strcpy(temp, a);  // Copy original string
        remove_char(temp, i);  // Remove character at index i

        if (make_palindrome(temp, removals_left - 1)) {
            return 1;  // Found a palindrome by removing characters
        }
    }

    return 0;  // Not possible to make it a palindrome with given removals
}

int main() {
    char a[1000];
    int max_removals, k;

    // Input the string and maximum removals allowed
    scanf("%d %d", &k,  &max_removals);
    scanf("%s", a);


    // Check if it's possible to make the string a palindrome
    if (make_palindrome(a, max_removals)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}