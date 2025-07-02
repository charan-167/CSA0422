#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd;
    char buffer[100];

    // Creating a new file with read/write/execute permissions for the user
    fd = creat("sample.txt", S_IRWXU);
    if (fd == -1) {
        perror("creat");
        exit(1);
    } else {
        printf("File 'sample.txt' created successfully.\n");
        close(fd);
    }

    // Opening the file for writing (append mode)
    fd = open("sample.txt", O_WRONLY | O_APPEND);
    if (fd == -1) {
        perror("open (write)");
        exit(1);
    } else {
        printf("File 'sample.txt' opened for writing.\n");
    }

    // Writing data to the file
    if (write(fd, "Hello, World!\n", 14) == -1) {
        perror("write");
        close(fd);
        exit(1);
    }
    printf("Data written to 'sample.txt'.\n");
    close(fd);

    // Opening the file for reading
    fd = open("sample.txt", O_RDONLY);
    if (fd == -1) {
        perror("open (read)");
        exit(1);
    } else {
        printf("File 'sample.txt' opened for reading.\n");
    }

    // Reading data from the file
    int bytesRead = read(fd, buffer, sizeof(buffer) - 1); // leave space for null-terminator
    if (bytesRead == -1) {
        perror("read");
        close(fd);
        exit(1);
    } else {
        buffer[bytesRead] = '\0'; // null-terminate
        printf("Data read from 'sample.txt':\n%s", buffer);
    }
    close(fd);

    // Deleting the file
    if (remove("sample.txt") == -1) {
        perror("remove");
        exit(1);
    } else {
        printf("\nFile 'sample.txt' deleted.\n");
    }

    return 0;
}
