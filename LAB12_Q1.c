#include <stdio.h>
#include <stdlib.h>

int main() {
    int *steps = NULL;
    int hours = 0, newHours = 0;
    int i, threshold;
    int totalSteps = 0, maxSteps = 0, aboveThreshold = 0;
    FILE *fp;

    printf("Enter initial number of hours: ");
    scanf("%d", &hours);

    
    steps = (int *)malloc(hours * sizeof(int));
    if (steps == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

   
    for (i = 0; i < hours; i++) {
        printf("Enter steps for hour %d: ", i + 1);
        scanf("%d", (steps + i)); 
    }

   
    printf("Enter number of additional hours to add: ");
    scanf("%d", &newHours);

    steps = (int *)realloc(steps, (hours + newHours) * sizeof(int));
    if (steps == NULL) {
        printf("Memory reallocation failed!\n");
        return 1;
    }

    for (i = hours; i < hours + newHours; i++) {
        printf("Enter steps for hour %d: ", i + 1);
        scanf("%d", (steps + i));
    }

    hours += newHours;

    printf("Enter step threshold: ");
    scanf("%d", &threshold);

    
    for (i = 0; i < hours; i++) {
        totalSteps += *(steps + i);
        if (*(steps + i) > maxSteps)
            maxSteps = *(steps + i);
        if (*(steps + i) > threshold)
            aboveThreshold++;
    }

    
    fp = fopen("fitness_tracker.txt", "w");
    if (fp == NULL) {
        printf("File could not be opened!\n");
        free(steps);
        return 1;
    }

    fprintf(fp, "Hourly Step Data:\n");
    for (i = 0; i < hours; i++) {
        fprintf(fp, "Hour %d: %d steps\n", i + 1, *(steps + i));
    }
    fprintf(fp, "\nTotal Steps: %d\n", totalSteps);
    fprintf(fp, "Maximum Steps in an Hour: %d\n", maxSteps);
    fprintf(fp, "Hours Above Threshold (%d): %d\n", threshold, aboveThreshold);

    fclose(fp);

    printf("\nAnalysis Complete! Data saved to fitness_tracker.txt\n");

    free(steps);
    return 0;
}
