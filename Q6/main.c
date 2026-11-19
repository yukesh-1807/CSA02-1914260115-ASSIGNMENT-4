
#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 5

struct Date
{
    int day, month, year;
};

struct Packaged
{
    int batchNo;
    struct Date expiry;
};

struct Cooked
{
    int preparationTime;
};

struct Combo
{
    int componentCount;
    int componentIds[3];
};

union ItemDetails
{
    struct Packaged packaged;
    struct Cooked cooked;
    struct Combo combo;
};

struct Item
{
    int id;
    char name[30];
    int type;
    int stock;
    float price;
    float revenue;
    union ItemDetails details;
};

void displayItems(struct Item items[], int n)
{
    int i;

    printf("\n--- CANTEEN INVENTORY ---\n");

    for (i = 0; i < n; i++)
    {
        printf("ID: %d | Name: %s | Stock: %d | Price: Rs.%.2f\n",
               items[i].id, items[i].name,
               items[i].stock, items[i].price);
    }
}

void sellItem(struct Item items[], int n, int id, int quantity)
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (items[i].id == id)
        {
            if (quantity <= 0)
            {
                printf("Invalid quantity!\n");
                return;
            }

            if (items[i].stock < quantity)
            {
                printf("Insufficient stock for %s!\n",
                       items[i].name);
                return;
            }

            items[i].stock -= quantity;
            items[i].revenue += items[i].price * quantity;

            printf("Sale successful: %s x %d = Rs.%.2f\n",
                   items[i].name, quantity,
                   items[i].price * quantity);
            return;
        }
    }

    printf("Item not found!\n");
}

void checkExpiry(struct Item items[], int n)
{
    int i;

    printf("\n--- EXPIRY CHECK ---\n");

    for (i = 0; i < n; i++)
    {
        if (items[i].type == 1)
        {
            if (items[i].details.packaged.expiry.month == 11 &&
                items[i].details.packaged.expiry.year == 2026 &&
                items[i].details.packaged.expiry.day <= 21)
            {
                printf("Warning: %s is expiring within 2 days!\n",
                       items[i].name);
            }
        }
    }
}

void sortByRevenue(struct Item items[], int n)
{
    int i, j;
    struct Item temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (items[j].revenue < items[j + 1].revenue)
            {
                temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }
}

void displayRevenue(struct Item items[], int n)
{
    int i;

    sortByRevenue(items, n);

    printf("\n--- REVENUE SUMMARY (HIGH TO LOW) ---\n");

    for (i = 0; i < n; i++)
    {
        printf("%s : Rs.%.2f\n",
               items[i].name, items[i].revenue);
    }
}

int main(void)
{
    struct Item items[MAX_ITEMS] =
    {
        {1, "Milk", 1, 10, 20.0, 0,
            {.packaged = {101, {20, 11, 2026}}}},

        {2, "Sandwich", 2, 8, 40.0, 0,
            {.cooked = {15}}},

        {3, "Juice", 1, 12, 30.0, 0,
            {.packaged = {102, {25, 11, 2026}}}},

        {4, "Combo Meal", 3, 5, 80.0, 0,
            {.combo = {2, {2, 3}}}},

        {5, "Water", 1, 20, 10.0, 0,
            {.packaged = {103, {30, 11, 2026}}}}
    };

    printf("COLLEGE CANTEEN INVENTORY AND BILLING\n");

    displayItems(items, MAX_ITEMS);

    printf("\n--- NORMAL SALES ---\n");
    sellItem(items, MAX_ITEMS, 1, 2);
    sellItem(items, MAX_ITEMS, 2, 3);
    sellItem(items, MAX_ITEMS, 4, 1);

    printf("\n--- INSUFFICIENT STOCK TEST ---\n");
    sellItem(items, MAX_ITEMS, 2, 20);

    checkExpiry(items, MAX_ITEMS);

    displayRevenue(items, MAX_ITEMS);

    printf("\nProgram completed successfully.\n");

    return 0;
}
