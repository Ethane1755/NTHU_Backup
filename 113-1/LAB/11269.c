#include <stdio.h>
#include <string.h>

#define MAX_SIZE 500

char content[MAX_SIZE];
char input[MAX_SIZE];

int main() {
    fgets(input, MAX_SIZE, stdin); // Read the input sequence
    int cursor = 0;               // Cursor position in the content
    int len = 0;                  // Current length of the content

    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '/') { // Detect commands
            if (strncmp(&input[i], "/backspace", 10) == 0) {
                // Handle backspace
                if (cursor > 0) {
                    for (int j = cursor - 1; j < len - 1; j++) {
                        content[j] = content[j + 1];
                    }
                    len--;
                    cursor--;
                }
                i += 9; // Skip the command
            } else if (strncmp(&input[i], "/newline", 8) == 0) {
                // Handle newline
                if (len < MAX_SIZE - 1) {
                    for (int j = len; j > cursor; j--) {
                        content[j] = content[j - 1];
                    }
                    content[cursor] = '\n';
                    len++;
                    cursor++;
                }
                i += 7; // Skip the command
            } else if (strncmp(&input[i], "/left", 5) == 0) {
                // Handle left navigation
                if (cursor > 0) {
                    cursor--;
                }
                i += 4; // Skip the command
            } else if (strncmp(&input[i], "/right", 6) == 0) {
                // Handle right navigation
                if (cursor < len) {
                    cursor++;
                }
                i += 5; // Skip the command
            }
        } else if (len < MAX_SIZE - 1) {
            // Handle regular characters
            for (int j = len; j > cursor; j--) {
                content[j] = content[j - 1];
            }
            content[cursor] = input[i];
            cursor++;
            len++;
        }
    }

    content[len] = '\0'; // Null-terminate the content
    printf("%s", content);
    return 0;
}