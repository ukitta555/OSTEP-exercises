#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>


int main() {
    int x = 100;
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork call failed!");
    } else if (rc == 0) {
        printf("Inside child process! %d\n", x);
        x = 123;
        printf("Inside child process! %d\n", x);
        // child case
    } else {
        // parent case
        printf("Inside parent process! %d\n", x);
        x = 321;
        printf("Inside parent process! %d\n", x);
    }
}