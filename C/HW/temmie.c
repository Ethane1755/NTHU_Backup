#include <stdio.h>

int main() {
    char C;
    char ID[11]; // Since ID has 10 digits, we need space for '\0'
    
    // Input the college code and student ID
    scanf("%c %s", &C, ID);

    // Determine Degree
    if (C <= 'L') {
        printf("Bachelor\n");
    } else {
        printf("Master\n");
    }

    // Determine Class
    int class_digit = ID[7] - '0'; // Third digit from the end is ID[7]
    char class_letter = 'A' + (class_digit - 1);
    printf("%c\n", class_letter);

    // Determine Enrollment Year
    int enrollment_year = (ID[0] - '0') * 100 + (ID[1] - '0') * 10 + (ID[2] - '0');
    printf("%d\n", enrollment_year);

    // Determine Seat Number
    int seat_number = (ID[8] - '0') * 10 + (ID[9] - '0');
    printf("%d\n", seat_number);

    return 0;
}
