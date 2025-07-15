#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _cat {
    char name[50];
    int occupation;
    int age;
}cat;

int compare (const void *a, const void *b) {
    cat A = *(cat *)a;
    cat B = *(cat *)b;

    if (A.occupation == B.occupation) {
        if (A.age > B.age) {
            if (A.occupation == 5) {
                return 1;
            } else {
                return -1;
            }
        } else if (A.age < B.age){
            if (A.occupation == 5) {
                return -1;
            } else {
                return 1;
            }
        } else if (A.age == B.age) {
            return strcmp(A.name, B.name);
        }
    } return (A.occupation < B.occupation) ? -1 : 1;
}

int main () {
    int n, m;
    cat cats[10000+10];
    while(~scanf("%d %d", &n, &m)) {
        for (int i = 0; i < n; i++) {
            char temp[50];
            scanf("%s %s %d", cats[i].name, temp, &cats[i].age);
            if (temp[0] == 'e') {
                cats[i].occupation = 1;
            } else if (temp[0] == 'n') {
                cats[i].occupation = 2;
            } else if (temp[0] == 'k') {
                cats[i].occupation = 3;
            }  else if (temp[0] == 'w') {
                cats[i].occupation = 4;
            }  else if (temp[0] == 'a') {
                cats[i].occupation = 5;
            }  else if (temp[0] == 'm') {
                cats[i].occupation = 6;
            }  else if (temp[0] == 'd') {
                cats[i].occupation = 7;
            }  else if (temp[0] == 'l') {
                cats[i].occupation = 8;
            } 
        }

        qsort (cats, n, sizeof(cat), compare);
        for (int i = 0; i < m && i < n; i++) {
            printf("%s\n", cats[i].name);
        }    
    }
    return 0;
}