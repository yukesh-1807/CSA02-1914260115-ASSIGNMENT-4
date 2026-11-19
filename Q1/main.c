
#include <stdio.h>
#include <string.h>

#define MAX 100

struct Date {
    int day, month, year;
};

struct BloodPressure {
    int systolic;
    int diastolic;
};

struct Patient {
    char name[50];
    int age;
    char phone[16];
    struct BloodPressure bp;
    struct Date visitDate;
};

void addPatient(struct Patient *p, const char name[],
                int age, const char phone[],
                int systolic, int diastolic,
                struct Date date)
{
    if (p == NULL)
        return;

    snprintf(p->name, sizeof(p->name), "%s", name);
    p->age = age;
    snprintf(p->phone, sizeof(p->phone), "%s", phone);
    p->bp.systolic = systolic;
    p->bp.diastolic = diastolic;
    p->visitDate = date;
}

void displayPatient(const struct Patient *p)
{
    printf("\nName: %s\n", p->name);
    printf("Age: %d\n", p->age);
    printf("Phone: %s\n", p->phone);
    printf("Blood Pressure: %d/%d\n",
           p->bp.systolic, p->bp.diastolic);
    printf("Visit Date: %02d/%02d/%04d\n",
           p->visitDate.day,
           p->visitDate.month,
           p->visitDate.year);
}

int main(void)
{
    struct Patient patients[MAX];
    int count = 0;

    struct Date d = {19, 11, 2026};

    if (count < MAX) {
        addPatient(&patients[count], "Arun",
                   25, "9876543210", 120, 80, d);
        count++;
    }

    if (count < MAX) {
        addPatient(&patients[count], "Kumar",
                   30, "9123456780", 130, 85, d);
        count++;
    }

    printf("Patient Register\n");

    for (int i = 0; i < count; i++)
        displayPatient(&patients[i]);

    return 0;
}
