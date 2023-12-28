#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

void print_goodbye(int sig){
    printf("Goodbye!\n");
}

int main(int argc, char* argv[]) {
    int x = 100;
    // close(STDOUT_FILENO);
    // open("testfile.txt", O_CREAT|O_WRONLY|O_TRUNC);
    signal(SIGCHLD, print_goodbye);
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Couldn't fork!");
    } else if (rc == 0) {
        // child case
        x = 123;
        printf("In child, value of x: %d \n", x);
        printf("Hello!\n");
        kill(0, SIGCHLD);
    } else {
        // parent case
        x = 321;
        printf("In parent, value of x: %d \n", x);
    }
    return 0;
}