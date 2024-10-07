#include <stdio.h>
#include <string.h>

int main() {
    char line[1000];
    while (fgets(line, sizeof(line), stdin)) {
        int i = 0;
        while (line[i] == ';') {
            line[i] = ' ';
            i++;
        }
        printf("%s", line);
        int len = strlen(line);
        if (line[len - 1] == '\n') len--;  
        if (strncmp(line, "#include", 8) == 0 || line[len - 1] == '{' || (strspn(line, " ;") == len - 1 && line[len - 1] == '}')) {
            continue;
        }
        if (line[len - 1] != '}') printf(";\n");
    }
    return 0;
}