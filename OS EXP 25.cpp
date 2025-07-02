#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>   // for close()

int main() {
    int fd = open("foo.txt", O_RDWR | O_CREAT, 0644); // read/write with user rw, group/others r
    printf("fd = %d\n", fd);

    if (fd == -1) {
        printf("Error Number: %d\n", errno);
        perror("Program");
    } else {
        printf("File opened (or created) successfully.\n");
        close(fd); // always close the file descriptor
    }

    return 0;
}
