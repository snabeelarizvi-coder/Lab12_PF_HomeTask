#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NAME_LEN 50
#define ROLL_LEN 20


typedef struct {
    char studentName[NAME_LEN];
    char rollNumber[ROLL_LEN];
    int seatNumber;
} Seat;


int isAlphanumericRecursive(const char *str, int index) {
    if (str[index] == '\0')
        return 1;  

    if (!isalnum(str[index]))
        return 0;  

    return isAlphanumericRecursive(str, index + 1);
}

int main() {
    Seat *seats = NULL;
    int count = 0, extra = 0;
    int i;
    FILE *fp;

    printf("Enter number of students: ");
    scanf("%d", &count);
    getchar();

    
    seats = (Seat *)malloc(count * sizeof(Seat));
    if (seats == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

  
    for (i = 0; i < count; i++) {
        printf("\nStudent %d Name: ", i + 1);
        fgets(seats[i].studentName, NAME_LEN, stdin);
        seats[i].studentName[strcspn(seats[i].studentName, "\n")] = '\0';

        do {
            printf("Roll Number (alphanumeric only): ");
            fgets(seats[i].rollNumber, ROLL_LEN, stdin);
            seats[i].rollNumber[strcspn(seats[i].rollNumber, "\n")] = '\0';

            if (!isAlphanumericRecursive(seats[i].rollNumber, 0))
                printf("Invalid roll number. Try again.\n");

        } while (!isAlphanumericRecursive(seats[i].rollNumber, 0));

        seats[i].seatNumber = i + 1;  
    }

    
    printf("\nEnter number of additional students: ");
    scanf("%d", &extra);
    getchar();

    seats = (Seat *)realloc(seats, (count + extra) * sizeof(Seat));
    if (seats == NULL) {
        printf("Memory reallocation failed!\n");
        return 1;
    }

    for (i = count; i < count + extra; i++) {
        printf("\nStudent %d Name: ", i + 1);
        fgets(seats[i].studentName, NAME_LEN, stdin);
        seats[i].studentName[strcspn(seats[i].studentName, "\n")] = '\0';

        do {
            printf("Roll Number (alphanumeric only): ");
            fgets(seats[i].rollNumber, ROLL_LEN, stdin);
            seats[i].rollNumber[strcspn(seats[i].rollNumber, "\n")] = '\0';

            if (!isAlphanumericRecursive(seats[i].rollNumber, 0))
                printf("Invalid roll number. Try again.\n");

        } while (!isAlphanumericRecursive(seats[i].rollNumber, 0));

        seats[i].seatNumber = i + 1;
    }

    count += extra;

 
    fp = fopen("seating.txt", "w");
    if (fp == NULL) {
        printf("Could not open file!\n");
        free(seats);
        return 1;
    }

    fprintf(fp, "Exam Seating Plan\n\n");
    for (i = 0; i < count; i++) {
        fprintf(fp, "Seat %d | Name: %s | Roll No: %s\n",
                seats[i].seatNumber,
                seats[i].studentName,
                seats[i].rollNumber);
    }

    fclose(fp);
    free(seats);

    printf("\nSeating plan saved successfully to seating.txt\n");

    return 0;
}
