#include <stdio.h>
#include <ctype.h>  // for toupper, tolower

// Function to compute the shift between two characters
int compute_shift(char plain, char encrypted) {
    // Convert both characters to uppercase for comparison
    plain = toupper(plain);
    encrypted = toupper(encrypted);
    
    // Calculate the shift by considering the cyclic nature of the alphabet
    int shift = (encrypted - plain + 26) % 26;
    return shift;
}

// Function to encrypt a message using the shift array and case inversion
void encrypt_message(char* B, int shifts[5]) {
    for (int i = 0; i < 5; i++) {
        char base = isupper(B[i]) ? 'A' : 'a';  // Determine if the character is uppercase or lowercase
        char encrypted_char = ((B[i] - base + shifts[i]) % 26) + base;  // Apply the right shift

        // Invert case
        if (isupper(encrypted_char)) {
            encrypted_char = tolower(encrypted_char);
        } else {
            encrypted_char = toupper(encrypted_char);
        }

        // Print the encrypted character
        printf("%c", encrypted_char);
    }
    printf("\n");  // End the line
}

int main() {
    char A[6], A_prime[6], B[6];
    
    // Input the three lines: plaintext A, encrypted A', and plaintext B
    scanf("%s", A);
    scanf("%s", A_prime);
    scanf("%s", B);
    
    int shifts[5];
    
    // Calculate the shifts by comparing A and A'
    for (int i = 0; i < 5; i++) {
        shifts[i] = compute_shift(A[i], A_prime[i]);
    }
    
    // Encrypt the message B using the calculated shifts
    encrypt_message(B, shifts);
    
    return 0;
}