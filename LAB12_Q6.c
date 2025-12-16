#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int totalAttendance(int *gates, int n) {
if (n == 0)
return 0;
return gates[n - 1] + totalAttendance(gates, n - 1);
}


int main() {
int *gates = NULL;
int gateCount = 0, extra = 0, i;
int maxGate = 0;
FILE *fp;
time_t now;


printf("Enter number of entry gates: ");
scanf("%d", &gateCount);


gates = (int *)malloc(gateCount * sizeof(int));
if (gates == NULL) {
printf("Memory allocation failed!\n");
return 1;
}


for (i = 0; i < gateCount; i++) {
printf("Enter headcount at gate %d: ", i + 1);
scanf("%d", (gates + i));
if (*(gates + i) > *(gates + maxGate))
maxGate = i;
}


printf("Enter number of additional gates: ");
scanf("%d", &extra);


gates = (int *)realloc(gates, (gateCount + extra) * sizeof(int));


for (i = gateCount; i < gateCount + extra; i++) {
printf("Enter headcount at gate %d: ", i + 1);
scanf("%d", (gates + i));
if (*(gates + i) > *(gates + maxGate))
maxGate = i;
}


gateCount += extra;


fp = fopen("attendance.txt", "w");
now = time(NULL);


fprintf(fp, "Event Attendance Log\nTime: %s\n", ctime(&now));


for (i = 0; i < gateCount; i++) {
fprintf(fp, "Gate %d: %d attendees\n", i + 1, *(gates + i));
}


fprintf(fp, "\nTotal Attendance: %d\n", totalAttendance(gates, gateCount));
fprintf(fp, "Gate with Highest Attendance: Gate %d\n", maxGate + 1);


fclose(fp);
free(gates);


printf("Attendance data saved to attendance.txt\n");


return 0;
}
