#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100
#define MAX_LENGTH 100

typedef struct {
    char key[MAX_LENGTH]; 
    long position;        
} Index;

Index indexTable[MAX_RECORDS]; 
int indexCount = 0;            

void createIndex(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    char line[MAX_LENGTH];
    long position;
    while ((position = ftell(fp)) != -1 && fgets(line, MAX_LENGTH, fp)) {
        
        char key[MAX_LENGTH];
        sscanf(line, "%s", key);

        strcpy(indexTable[indexCount].key, key);
        indexTable[indexCount].position = position;
        indexCount++;
    }

    fclose(fp);
    printf("Index created successfully with %d records.\n", indexCount);
}

void searchRecord(const char *filename, const char *key) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < indexCount; i++) {
        if (strcmp(indexTable[i].key, key) == 0) {
            fseek(fp, indexTable[i].position, SEEK_SET);
            char line[MAX_LENGTH];
            fgets(line, MAX_LENGTH, fp);
            printf("Record found: %s", line);
            fclose(fp);
            return;
        }
    }

    printf("Record with key '%s' not found.\n", key);
    fclose(fp);
}

void displayIndex() {
    printf("Index Table:\n");
    for (int i = 0; i < indexCount; i++) {
        printf("Key: %s, Position: %ld\n", indexTable[i].key, indexTable[i].position);
    }
}

int main() {
    const char *filename = "records.txt";

    int choice;
    char key[MAX_LENGTH];
    do {
        printf("\nFile Indexing System\n");
        printf("1. Create Index\n");
        printf("2. Search Record\n");
        printf("3. Display Index\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createIndex(filename);
                break;
            case 2:
                printf("Enter the key to search: ");
                scanf("%s", key);
                searchRecord(filename, key);
                break;
            case 3:
                displayIndex();
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 4);

    return 0;
}
