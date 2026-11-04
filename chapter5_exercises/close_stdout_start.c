#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    // open("testfile.txt", O_CREAT|O_RDWR|O_TRUNC);
    int rc = fork();
    if (rc == 0) {
        close(STDOUT_FILENO);
        printf("In child\n");
    } else {
        int res = wait(NULL);
        printf("In parent %d\n", res);
    }
    return 0;
}