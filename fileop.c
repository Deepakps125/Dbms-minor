#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
void create_file(const char *filename) {
    int fd = creat(filename, 0644);
    if (fd == -1) {
        perror("Error creating file");
    } else {
        printf("File created successfully\n");
        close(fd);
    }
}
void open_file(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
    } else {
        printf("File opened successfully\n");
        close(fd);
    }
}
void read_file(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
    } else {
        char buffer[1024];
        ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
        if (bytes_read == -1) {
            perror("Error reading from file");
        } else {
            printf("Read %zd bytes: %s\n", bytes_read, buffer);
        }
        close(fd);
    }
}

void write_file(const char *filename) {
    int fd = open(filename, O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
    } else {
        char text[1024];
        printf("Enter text to write to file: ");
        fgets(text, sizeof(text), stdin);
        ssize_t bytes_written = write(fd, text, strlen(text));
        if (bytes_written == -1) {
            perror("Error writing to file");
        } else {
            printf("Wrote %zd bytes to file\n", bytes_written);
        }
        close(fd);
    }
}
void delete_file(const char *filename) {
    if (unlink(filename) == -1) {
        perror("Error deleting file");
    } else {
        printf("File deleted successfully\n");
    }
}

int main() {
    char filename[1024];

    printf("Enter filename: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;

    int choice;
    while (1) {
        printf("Enter your choice:\n");
        printf("1. Create a file\n");
        printf("2. Open a file\n");
        printf("3. Read from file\n");
        printf("4. Write to file\n");
        printf("5. Delete file\n");
        printf("6. Quit\n");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                create_file(filename);
                break;
            case 2:
                open_file(filename);
                break;
            case 3:
                read_file(filename);
                break;
            case 4:
                write_file(filename);
                break;
            case 5:
                delete_file(filename);
                break;
            case 6:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}