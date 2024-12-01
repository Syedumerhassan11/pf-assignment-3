#include <stdio.h>
#include <string.h>

struct Employee {
    int employeeCode;
    char employeeName[50];
    char dateOfJoining[11];
};

void add(struct Employee *e) {
    printf("\nEnter Employee Code: ");
    scanf("%d", &e->employeeCode);
    printf("Enter Employee Name: ");
    scanf("%s", e->employeeName);
    printf("Enter Date of Joining (yyyy/mm/dd): ");
    scanf("%s", e->dateOfJoining);
}

void display(const struct Employee *e) {
    printf("\nEmployee Code: %d", e->employeeCode);
    printf("\nEmployee Name: %s", e->employeeName);
    printf("\nDate of Joining: %s", e->dateOfJoining);
}

int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int month, int year) {
    if (month == 2) {
        return isLeapYear(year) ? 29 : 28;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    return 31;
}

int totalDays(int year, int month, int day) {
    int total = 0;
   int y=0;
   int m=1;
    for (; y < year; y++) {
        total += isLeapYear(y) ? 366 : 365;
    }
    for (; m < month; m++) {
        total += daysInMonth(m, year);
    }
    total += day;
    return total;
}

int hasTenureMoreThan3Years(const struct Employee *e,int y2,int m2,int d2) {
    char currentDate[11];
    int y1, m1, d1;
    sscanf(e->dateOfJoining, "%d/%d/%d", &y1, &m1, &d1);
    int total1 = totalDays(y1, m1, d1);
    int total2 = totalDays(y2, m2, d2);
    int difference = total2 - total1;
    return difference > 3 * 365;
}

int main(void) {
    struct Employee employees[4];
    int count = 0;
    int i=0;
    for (; i < 4; i++) {
        printf("\nAdding details for Employee %d", i + 1);
        add(&employees[i]);
    }
    char currentDate[11];
    int y2,m2,d2;
    printf("\nEmployees with tenure of more than 3 years:\n");
    printf("\nEnter Current Date (yyyy/mm/dd): ");
    scanf("%s", currentDate);
    sscanf(currentDate, "%d/%d/%d", &y2, &m2, &d2);
    for (; i < 4; i++) {
        if (hasTenureMoreThan3Years(&employees[i],y2,m2,d2)) {
            display(&employees[i]);
            count++;
        }
    }
    printf("\nTotal employees with tenure of more than 3 years: %d\n", count);
    return 0;
}

