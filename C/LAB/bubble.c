#include <stdio.h>

void bubblesort (int *ap, int n) {
      int i, j, temp;
      for (i = 0; i < n-1; i++) {
            for (j = 0; j < n-1-i; j++) {
                  if (ap[j] > ap[j + 1]) {
                       temp = ap[j];
                       ap[j] = ap[j + 1];
                       ap[j + 1] = temp;
                  }
            }
      }
      for (int k = 0 ; k < n ; k++) {
        printf("%d ", ap[k]);
      };
}

int main() {
    int ap[] = {1,3,2,909,3,6,8,9,45,0};
    int n = sizeof(ap) / sizeof(ap[0]);
    bubblesort(ap, n);
    return 0;
}