#include <stdio.h>
#include <stdint.h>

int main() {
    float f; 
    while (scanf("%f", &f) == 1) {
        uint32_t bits = *(uint32_t*)&f;
        for (int i =  31; i >= 1; i--) {
            printf("%d", (bits >> i) & 1);
        }
        printf("\n");
    }
    return 0;
}