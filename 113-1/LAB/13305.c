#include <stdio.h>


int horizontal(char a[1000][1000], int n, int m, int k) {
    int temp = 0; 
    int max = 0;  
    for (int i = 0; i < n; i++) {
        temp = 0; 
        for (int j = 0; j < m; j++) {
            if (a[i][j] == k) {
                temp++; 
                if (temp > max) {
                    max = temp; 
                }
            } else {
                temp = 0; 
            }
        }
    }
    return max;
}

int vertical(char a[1000][1000], int n, int m, int k) {
    int temp = 0; 
    int max = 0;  
    for (int j = 0; j < m; j++) {
        temp = 0; 
        for (int i = 0; i < n; i++) {
            if (a[i][j] == k) {
                temp++; 
                if (temp > max) {
                    max = temp; 
                }
            } else {
                temp = 0; 
            }
        }
    }
    return max;
}

int primary_diagonal(char a[1000][1000], int n, int m, char k) {
    int temp = 0, max = 0;

    // Iterate over all diagonals starting from each row in the first column
    for (int i = 0; i < n; i++) {
        int x = i, y = 0; // Start from row `i`, column `0`
        temp = 0;
        while (x < n && y < m) {
            if (a[x][y] == k) {
                temp++;
                if (temp > max) max = temp;
            } else {
                temp = 0;
            }
            x++;
            y++;
        }
    }

    // Iterate over all diagonals starting from each column in the first row
    for (int j = 1; j < m; j++) {
        int x = 0, y = j; // Start from row `0`, column `j`
        temp = 0;
        while (x < n && y < m) {
            if (a[x][y] == k) {
                temp++;
                if (temp > max) max = temp;
            } else {
                temp = 0;
            }
            x++;
            y++;
        }
    }

    return max;
}

int secondary_diagonal(char a[1000][1000], int n, int m, char k) {
    int temp = 0, max = 0;

    // Iterate over all diagonals starting from each row in the last column
    for (int i = 0; i < n; i++) {
        int x = i, y = m - 1; // Start from row `i`, last column
        temp = 0;
        while (x < n && y >= 0) {
            if (a[x][y] == k) {
                temp++;
                if (temp > max) max = temp;
            } else {
                temp = 0;
            }
            x++;
            y--;
        }
    }

    // Iterate over all diagonals starting from each column in the first row
    for (int j = m - 2; j >= 0; j--) {
        int x = 0, y = j; // Start from row `0`, column `j`
        temp = 0;
        while (x < n && y >= 0) {
            if (a[x][y] == k) {
                temp++;
                if (temp > max) max = temp;
            } else {
                temp = 0;
            }
            x++;
            y--;
        }
    }

    return max;
}


int main() {  
    int t;
    char a[1000][1000];


    scanf("%d", &t);
    for (int i = 0 ; i < t ; i++) {
        int n1, n2, n3, n4 = 0;
        int n, m = 0;
        scanf("%d%d", &n, &m);
        for (int j = 0 ; j < n ; j++) {
            for (int k = 0 ; k < m ; k++) {
                scanf(" %c", &a[j][k]);
            }
        }
        n1 = horizontal(a, n, m, 'o');
        n2 = vertical(a, n, m, 'o');
        n3 = primary_diagonal(a, n, m, 'o');
        n4 = secondary_diagonal(a, n, m, 'o');
        int ans1 = (n1 > n2 ? (n1 > n3 ? (n1 > n4 ? n1 : n4) : (n3 > n4 ? n3 : n4)) : (n2 > n3 ? (n2 > n4 ? n2 : n4) : (n3 > n4 ? n3 : n4)));

        n1 = horizontal(a, n, m, '#');
        n2 = vertical(a, n, m, '#');
        n3 = primary_diagonal(a, n, m, '#');
        n4 = secondary_diagonal(a, n, m, '#');
        int ans2 = (n1 > n2 ? (n1 > n3 ? (n1 > n4 ? n1 : n4) : (n3 > n4 ? n3 : n4)) : (n2 > n3 ? (n2 > n4 ? n2 : n4) : (n3 > n4 ? n3 : n4)));
        printf("%d %d\n", ans1, ans2);
    }
    return 0;
}