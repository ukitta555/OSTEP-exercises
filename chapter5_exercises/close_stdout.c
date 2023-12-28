#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    // open("testfile.txt", O_CREAT|O_WRONLY|O_TRUNC);
    int file_descriptors[2];
    int pipe_status = pipe(file_descriptors);
    if (pipe_status == -1) {
        fprintf(stderr, "Can't create pipe!");
    } else {
        int rc1 = fork();
        if (rc1 < 0) {
            fprintf(stderr, "Couldn't fork!");
        } else if (rc1 == 0) {
            // child case
            // close(STDOUT_FILENO);
            printf("In child1\n");
            close(file_descriptors[0]);
            write(file_descriptors[1], "Hello world\n", 12);
            close(file_descriptors[1]);
        } else {
            // parent case
            int rc2 = fork();
            if (rc2 < 0) {
                fprintf(stderr, "Couldn't fork!");
            } else if (rc2 == 0) {
                // child case
                // close(STDOUT_FILENO);
                printf("In child2\n");
                char buf[100];
                close(file_descriptors[1]);
                read(file_descriptors[0], buf, 100);
                printf(buf);
                printf('\n');
                close(file_descriptors[0]);
            } else {
                printf("In parent\n");
            }
        }
    }
    return 0;
}