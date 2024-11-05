#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100
#define NAME_LENGTH 50
#define FILENAME "students.csv"

typedef struct {
    int id;
    char name[NAME_LENGTH];
} Student;

typedef struct {
    int id;
    long position;
} IndexEntry;

void writeRecords(FILE *dataFile) {
    fprintf(dataFile, "ID,Name\n"); 
    Student students[MAX_RECORDS] = {
        {1, "Aman"},
        {2, "Shrikar"},
        {3, "Ravi"},
        {4, "Harish"},
        {5, "Ramesh"}
    };

    for (int i = 0; i < 5; i++) {
        fprintf(dataFile, "%d,%s\n", students[i].id, students[i].name);
    }
}


void createIndex(FILE *dataFile, IndexEntry *index, int *indexSize) {
    fseek(dataFile, 0, SEEK_SET);
    char line[NAME_LENGTH + 10]; 
    *indexSize = 0;

    while (fgets(line, sizeof(line), dataFile)) {

        index[*indexSize].position = ftell(dataFile) - strlen(line);
        
        sscanf(line, "%d,", &index[*indexSize].id);
        (*indexSize)++;
    }
}

void searchRecord(FILE *dataFile, IndexEntry *index, int indexSize, int searchId) {
    for (int i = 0; i < indexSize; i++) {
        if (index[i].id == searchId) {
            char line[NAME_LENGTH + 10];
            fseek(dataFile, index[i].position, SEEK_SET);
            fgets(line, sizeof(line), dataFile);
            printf("Record Found: %s", line);
            return;
        }
    }
    printf("Record with ID %d not found.\n", searchId);
}

int main() {
    FILE *dataFile = fopen(FILENAME, "w+");
    if (dataFile == NULL) {
        perror("Unable to open file");
        return 1;
    }

    writeRecords(dataFile);

    IndexEntry index[MAX_RECORDS];
    int indexSize;
    createIndex(dataFile, index, &indexSize);

    int searchId;
    printf("Enter ID to search for: ");
    scanf("%d", &searchId);
    searchRecord(dataFile, index, indexSize, searchId);

    fclose(dataFile);
    return 0;
}