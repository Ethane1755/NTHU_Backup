#include <stdio.h>

int is_leap(int year) {
    return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
}

int main() {
    int T, y;
    scanf("%d", &T);

    while (T--) {
        scanf("%d", &y);

        int target_leap = is_leap(y);
        int start_day = 0;           

        for (int i = 1000; i < y; i++) {
            start_day = (start_day + (is_leap(i) ? 366 : 365)) % 7;
        }

        int current_day = start_day;
        int next_year = y;

        while (1) {
            next_year++;
            current_day = (current_day + (is_leap(next_year - 1) ? 366 : 365)) % 7;
            if (current_day == start_day && is_leap(next_year) == target_leap) {
                printf("%d\n", next_year);
                break;
            }
        }
    }

    return 0;
}
