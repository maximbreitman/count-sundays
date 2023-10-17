#include <stdio.h>
#include <stdlib.h>

int CALENDAR[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30,31, 30, 31 };

const int HOLIDAY[] = {
    // March
    23,
    // June
    10,
    // September
    30,
    // December
    31
};

int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

const int ZELLER_TRANSLATION[] = {6, 7, 1, 2, 3, 4, 5};

// Zeller's congruence
int day_of_week(int day, int month, int year) {
    if (month < 3) { month += 12; year--; }
    int k = year % 100;
    int j = year / 100;
    return (day + (13 * (month + 1)) / 5 + k + k / 4 + j / 4 + (5 * j)) % 7;
}

static inline void check(int condition, char message[], int object) {
    if (!condition) { printf("%s: %d\n\n", message, object); exit(1); }
}

int main() {
    int day, month, year;

    printf("Awaiting for Date [Day Month Year]:\n");
    scanf("%d %d %d", &day, &month, &year);

    check(year > 1582, "Year must be in range of (1582; +Infinity)", year);
    check(month > 0 & month < 13, "Month must be in range of [1; 12]", month);

    month--;

    if (is_leap_year(year)) { CALENDAR[1] = 29; }

    check(day > 0 & day <= CALENDAR[month], "In this year (not leap?) there is no such day in selected month", day);

    month = (month / 3) * 3 + 1;
    int count = CALENDAR[month - 1] + CALENDAR[month] + HOLIDAY[month / 3];

    day = day_of_week(1, month, year);

    count = (count - (7 - ZELLER_TRANSLATION[day]) - 1) / 7 + 1;

    printf("Quantity of Sundays: %d\n", count);

    // system("pause");

    return 0;
}