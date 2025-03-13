#include <stdio.h>
#include <math.h>

int main() {
    double x, y;
    int z;
    scanf("%lf %lf %d", &x, &y, &z);

    double result = x * y;  

    double rounded = round(result * pow(10, z)) / pow(10, z);

    printf("%.*f\n", z, rounded);

    return 0;
}