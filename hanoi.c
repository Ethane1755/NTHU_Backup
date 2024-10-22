#include <stdio.h>

void bad_fibonacci(int a, int b, int c, int d, int n) {
    // Arrays to store the computed values for f(n) and g(n)
    long long f_values[n + 1];
    long long g_values[n + 1];
    
    // Base cases for f(n)
    f_values[0] = 1;  // Assume f(0) = 1 (can be adjusted based on the problem definition)
    f_values[1] = a;  // f(1) = a
    
    // Base cases for g(n)
    g_values[0] = 1;  // Assume g(0) = 1 (can be adjusted based on the problem definition)
    g_values[1] = c;  // g(1) = c
    
    // Fill the f_values array
    for (int i = 2; i <= n; i++) {
        if (i % 3 == 0){
            f_values[i] = f_values[i - 1] + g_values[f_values[i / 3 % 3]];
        }
        else {
            f_values[i] = f_values[i - 1] + g_values[i - 2];
        }
        //return f_values;
    }

    for (int i = 2; i <= n; i++) {
        if (i % 5 == 0){
            g_values[i] = g_values[i - 1] + f_values[g_values[i / 5 % 5]];
        }
        else {
            g_values[i] = g_values[i - 1] + f_values[i - 2];
        }
        //return g_values;
    }


    
    // Output the results for f(n) and g(n)
    printf("%lld %lld\n", f_values[n], g_values[n]);
}

int main() {
    int a, b, c, d, n;
    
    // Read input values
    scanf("%d %d %d %d %d", &a, &b, &c, &d, &n);
    
    // Calculate and print the results
    bad_fibonacci(a, b, c, d, n);
    
    return 0;
}