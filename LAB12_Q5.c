#include <stdio.h>
#include <stdlib.h>


int main() {
int *rentals = NULL;
int customers = 0, i;
int totalTime = 0, maxTime = 0;
int rate;
FILE *fp;


printf("Enter number of customers today: ");
scanf("%d", &customers);


rentals = (int *)malloc(customers * sizeof(int));
if (rentals == NULL) {
printf("Memory allocation failed!\n");
return 1;
}


printf("Enter rental rate per hour/day: ");
scanf("%d", &rate);


for (i = 0; i < customers; i++) {
printf("Enter rental duration for customer %d: ", i + 1);
scanf("%d", (rentals + i));


totalTime += *(rentals + i);
if (*(rentals + i) > maxTime)
maxTime = *(rentals + i);
}


fp = fopen("Rental_Invoices.txt", "w");
fprintf(fp, "Car Rental Invoices\n\n");


for (i = 0; i < customers; i++) {
fprintf(fp, "Customer %d | Duration: %d | Cost: %d\n",
i + 1, *(rentals + i), (*(rentals + i) * rate));
}


fprintf(fp, "\nTotal Rental Time: %d\n", totalTime);
fprintf(fp, "Highest Rental Duration: %d\n", maxTime);


fclose(fp);
free(rentals);


printf("Rental invoices saved to Rental_Invoices.txt\n");


return 0;
}
