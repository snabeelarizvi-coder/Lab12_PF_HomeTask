#include <stdio.h>
#include <stdlib.h>

int main() {
    float *temps = NULL;
    int count = 0, extra = 0;
    int i, alertCount = 0;
    float highest, lowest, alertThreshold;
    FILE *fp;

    printf("Enter number of temperature readings: ");
    scanf("%d", &count);

    
    temps = (float *)malloc(count * sizeof(float));
    if (temps == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    
    for (i = 0; i < count; i++) {
        printf("Enter temperature reading %d: ", i + 1);
        scanf("%f", (temps + i)); 
    }

    
    printf("Enter number of additional readings: ");
    scanf("%d", &extra);

    temps = (float *)realloc(temps, (count + extra) * sizeof(float));
    if (temps == NULL) {
        printf("Memory reallocation failed!\n");
        return 1;
    }

    for (i = count; i < count + extra; i++) {
        printf("Enter temperature reading %d: ", i + 1);
        scanf("%f", (temps + i));
    }

    count += extra;

    printf("Enter alert temperature threshold: ");
    scanf("%f", &alertThreshold);

    
    highest = lowest = *temps;

    
    for (i = 0; i < count; i++) {
        if (*(temps + i) > highest)
            highest = *(temps + i);
        if (*(temps + i) < lowest)
            lowest = *(temps + i);
        if (*(temps + i) > alertThreshold)
            alertCount++;
    }

    
    fp = fopen("temperature_summary.txt", "w");
    if (fp == NULL) {
        printf("Could not open file!\n");
        free(temps);
        return 1;
    }

    fprintf(fp, "Temperature Monitoring Summary\n\n");
    for (i = 0; i < count; i++) {
        fprintf(fp, "Reading %d: %.2f°C\n", i + 1, *(temps + i));
    }
    fprintf(fp, "\nHighest Temperature: %.2f°C\n", highest);
    fprintf(fp, "Lowest Temperature: %.2f°C\n", lowest);
    fprintf(fp, "Readings Above Alert Threshold (%.2f°C): %d\n",
            alertThreshold, alertCount);

    fclose(fp);
    free(temps);

    printf("\nTemperature analysis completed. Report saved to temperature_summary.txt\n");

    return 0;
}
