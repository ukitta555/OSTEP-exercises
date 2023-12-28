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
        fprintf(stderr, "Fork call failed!");
    } else if (rc == 0) {
        // child case
        char* args[3];
        args[0] = "/bin/ls";
        args[1] = "-la";
        args[2] = (char*)NULL;
        char* envp[2];
        envp[0] = "TIME_STYLE=full-iso";
        envp[1] = (char*)NULL;
        execvpe("/bin/ls", args, envp);
    } else {
        // parent case
        printf("Inside parent process!\n");
    }
}