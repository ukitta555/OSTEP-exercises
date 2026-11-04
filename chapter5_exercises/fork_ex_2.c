#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>


int main() {
    int fd = open("fork_ex_2.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        fprintf(stderr, "Open call failed!\n");
        exit(1);
    }

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork call failed!");
    } else if (rc == 0) {
        // child case
        char *msg = "Written by child process!\n";
        int written = write(fd, msg, strlen(msg));
        printf("Inside child process! fd = %d, write returned %d\n", fd, written);
    } else {
        // parent case
        char *msg = "Written by parent process!\n";
        int written = write(fd, msg, strlen(msg));
        printf("Inside parent process! fd = %d, write returned %d\n", fd, written);
    }
    close(fd);
}