#include <stdio.h>
#include <string.h>

#define MAX_SIZE 500

char content[MAX_SIZE];
char input[MAX_SIZE];

int main()
{

    fgets(input, MAX_SIZE, stdin);

    int len = 0;
    int cursor = 0;
    for(int i = 0; input[i] != '\0'; i++) {
        if(input[i] == '/') {
            if(strncmp(&input[i], "/backspace", 10) == 0) {
                if (cursor > 0) {
                    for(int j = cursor - 1; j < len - 1; j++) {
                        content[j] = content[j+1];
                    }
                    len--;
                    cursor--;
                }
                i += 9;
            }
            else if(strncmp(&input[i], "/newline", 8) == 0) {
                if (len < MAX_SIZE - 1) {
                    for(int j = len; j > cursor; j--) {
                        content[j] = content[j-1];
                    }
                    content[cursor] = '\n';
                    cursor++;
                    len++;
                }
                i += 7;
            }
            else if(strncmp(&input[i], "/left", 5) == 0) {
                if (cursor > 0) {
                    cursor--;
                }
                i += 4;
            } 
            else if(strncmp(&input[i], "/right", 6) == 0) {
                if (cursor < len) {
                    cursor++;
                } 
                i += 5;
            } 
        } else if(len < MAX_SIZE - 1) {
            for(int j = len; j > cursor; j--) {
                content[j] = content[j-1];
            }
            content[cursor] = input[i];
            cursor++;
            len++;
        }
    }
    content[len] = '\0';
    printf("%s", content);

    return 0;
}