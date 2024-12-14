#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 50000
#define MAX_RESULT 1000

// Concatenate two strings
void handle_concat(char *a, char *b) {
    printf("%s%s\n", a, b);
}

// Remove first occurrence of b from a
void handle_remove(char *a, char *b) {
    char *pos = strstr(a, b);
    if (pos) {
        *pos = '\0';
        printf("%s%s\n", a, pos + strlen(b));
    } else {
        printf("error\n");
    }
}

// Format floating-point number
void handle_round(char *a, char *b) {
    char num_str[MAX_LEN];
    sprintf(num_str, "%s.%s", a, b); // Combine strings into a floating-point number
    double num = atof(num_str);
    printf("%.6f\n", num); // Print rounded to six decimal places
}

// Match substrings and sort
int compare_strings(const void *p1, const void *p2) {
    char *str1 = *(char **)p1;
    char *str2 = *(char **)p2;

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if (len1 != len2) {
        return len2 - len1; // Longer strings come first
    }
    return strcmp(str1, str2); // Lexicographical order for same length
}

void handle_match(char *a, char *b) {
    char *tokens[MAX_RESULT];
    int count = 0;

    // Copy b to prevent modifying original string
    char b_copy[MAX_LEN];
    strncpy(b_copy, b, MAX_LEN - 1);
    b_copy[MAX_LEN - 1] = '\0';

    // Tokenize b by '_'
    char *token = strtok(b_copy, "_");
    while (token) {
        if (strstr(token, a)) {
            tokens[count++] = strdup(token);
        }
        token = strtok(NULL, "_");
    }

    // Sort matched substrings
    qsort(tokens, count, sizeof(char *), compare_strings);

    // Print sorted result
    for (int i = 0; i < count; i++) {
        if (i > 0) printf(" ");
        printf("%s", tokens[i]);
        free(tokens[i]); // Free allocated memory
    }
    printf("\n");
}

int main() {
    int T;
    scanf("%d", &T);
    getchar(); // Clear newline

    for (int i = 0; i < T; i++) {
        char line[MAX_LEN];
        char a[MAX_LEN], b[MAX_LEN];
        fgets(line, MAX_LEN, stdin);

        if (strstr(line, " + ")) {
            sscanf(line, "%s + %s", a, b);
            handle_concat(a, b);
        } else if (strstr(line, " - ")) {
            sscanf(line, "%s - %s", a, b);
            handle_remove(a, b);
        } else if (strstr(line, " . ")) {
            sscanf(line, "%s . %s", a, b);
            handle_round(a, b);
        } else if (strstr(line, " @ ")) {
            sscanf(line, "%s @ %s", a, b);
            handle_match(a, b);
        }
    }

    return 0;
}