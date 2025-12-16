#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 50
#define LOW_STOCK_LIMIT 10


typedef struct {
    char medicineName[NAME_LEN];
    int quantityAvailable;
    float unitPrice;
} Medicine;

int main() {
    Medicine *inventory = NULL;
    int count = 0;
    int choice, i, index;
    float totalValue = 0.0f;
    FILE *fp;

    while (1) {
        printf("\n--- Medication Inventory Manager ---\n");
        printf("1. Add Medicine\n");
        printf("2. Remove Medicine\n");
        printf("3. View Inventory\n");
        printf("4. Exit and Save\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
           
            inventory = (Medicine *)realloc(inventory, (count + 1) * sizeof(Medicine));
            if (inventory == NULL) {
                printf("Memory allocation failed!\n");
                return 1;
            }

            printf("Enter medicine name: ");
            fgets(inventory[count].medicineName, NAME_LEN, stdin);
            inventory[count].medicineName[strcspn(inventory[count].medicineName, "\n")] = '\0';

            printf("Enter quantity available: ");
            scanf("%d", &inventory[count].quantityAvailable);

            printf("Enter unit price: ");
            scanf("%f", &inventory[count].unitPrice);
            getchar();

            count++;
            printf("Medicine added successfully.\n");
        }
        else if (choice == 2) {
            
            if (count == 0) {
                printf("Inventory is empty.\n");
                continue;
            }

            printf("Enter index of medicine to remove (1 to %d): ", count);
            scanf("%d", &index);

            if (index < 1 || index > count) {
                printf("Invalid index.\n");
                continue;
            }

            for (i = index - 1; i < count - 1; i++) {
                inventory[i] = inventory[i + 1];
            }

            count--;
            inventory = (Medicine *)realloc(inventory, count * sizeof(Medicine));
            printf("Medicine removed successfully.\n");
        }
        else if (choice == 3) {
            
            if (count == 0) {
                printf("Inventory is empty.\n");
                continue;
            }

            printf("\nCurrent Inventory:\n");
            for (i = 0; i < count; i++) {
                printf("%d. %s | Qty: %d | Price: %.2f",
                       i + 1,
                       inventory[i].medicineName,
                       inventory[i].quantityAvailable,
                       inventory[i].unitPrice);

                if (inventory[i].quantityAvailable < LOW_STOCK_LIMIT)
                    printf("  **LOW STOCK**");
                printf("\n");
            }
        }
        else if (choice == 4) {
           
            fp = fopen("medicine_inventory.txt", "w");
            if (fp == NULL) {
                printf("Could not open file!\n");
                free(inventory);
                return 1;
            }

            fprintf(fp, "Medication Inventory Report\n\n");
            totalValue = 0.0f;

            for (i = 0; i < count; i++) {
                float value = inventory[i].quantityAvailable * inventory[i].unitPrice;
                totalValue += value;

                fprintf(fp, "%s | Qty: %d | Price: %.2f | Value: %.2f",
                        inventory[i].medicineName,
                        inventory[i].quantityAvailable,
                        inventory[i].unitPrice,
                        value);

                if (inventory[i].quantityAvailable < LOW_STOCK_LIMIT)
                    fprintf(fp, " | LOW STOCK");
                fprintf(fp, "\n");
            }

            fprintf(fp, "\nTotal Inventory Value: %.2f\n", totalValue);
            fclose(fp);

            free(inventory);
            printf("Inventory saved to medicine_inventory.txt\n");
            break;
        }
        else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
