#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TITLE_LEN 100
#define ID_LEN 30


typedef struct {
    char bookTitle[TITLE_LEN];
    char memberID[ID_LEN];
    time_t checkoutTime;
    int returnDueDays;
    time_t dueDate;
} Checkout;

int main() {
    Checkout *logs = NULL;
    int count = 0, extra = 0;
    int i;
    FILE *fp;

    printf("Enter number of book checkouts today: ");
    scanf("%d", &count);
    getchar();

    
    logs = (Checkout *)malloc(count * sizeof(Checkout));
    if (logs == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

   
    for (i = 0; i < count; i++) {
        printf("\nCheckout %d Book Title: ", i + 1);
        fgets(logs[i].bookTitle, TITLE_LEN, stdin);
        logs[i].bookTitle[strcspn(logs[i].bookTitle, "\n")] = '\0';

        printf("Member ID: ");
        fgets(logs[i].memberID, ID_LEN, stdin);
        logs[i].memberID[strcspn(logs[i].memberID, "\n")] = '\0';

        printf("Return due days: ");
        scanf("%d", &logs[i].returnDueDays);
        getchar();

        logs[i].checkoutTime = time(NULL);
        logs[i].dueDate = logs[i].checkoutTime + (logs[i].returnDueDays * 24 * 60 * 60);
    }

    
    printf("\nEnter number of additional checkouts: ");
    scanf("%d", &extra);
    getchar();

    logs = (Checkout *)realloc(logs, (count + extra) * sizeof(Checkout));
    if (logs == NULL) {
        printf("Memory reallocation failed!\n");
        return 1;
    }

    for (i = count; i < count + extra; i++) {
        printf("\nCheckout %d Book Title: ", i + 1);
        fgets(logs[i].bookTitle, TITLE_LEN, stdin);
        logs[i].bookTitle[strcspn(logs[i].bookTitle, "\n")] = '\0';

        printf("Member ID: ");
        fgets(logs[i].memberID, ID_LEN, stdin);
        logs[i].memberID[strcspn(logs[i].memberID, "\n")] = '\0';

        printf("Return due days: ");
        scanf("%d", &logs[i].returnDueDays);
        getchar();

        logs[i].checkoutTime = time(NULL);
        logs[i].dueDate = logs[i].checkoutTime + (logs[i].returnDueDays * 24 * 60 * 60);
    }

    count += extra;

   
    fp = fopen("library_checkouts.csv", "a");
    if (fp == NULL) {
        printf("Could not open file!\n");
        free(logs);
        return 1;
    }

    for (i = 0; i < count; i++) {
        fprintf(fp, "%s,%s,%ld,%d,%ld\n",
                logs[i].bookTitle,
                logs[i].memberID,
                logs[i].checkoutTime,
                logs[i].returnDueDays,
                logs[i].dueDate);
    }

    fclose(fp);
    free(logs);

    printf("\nCheckout logs appended successfully to library_checkouts.csv\n");

    return 0;
}
