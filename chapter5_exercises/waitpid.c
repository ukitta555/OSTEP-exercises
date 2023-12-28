#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

int main() {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork failed!");
    } else if (rc == 0) {
        // child case
        printf("Child reporting!\n"); 
    } else {
        // parent case
        int child_pid = waitpid(-1, NULL, 0);
        printf("Parent reporting! Return value of wait: %d\n", child_pid);
    }
    return 0;
}