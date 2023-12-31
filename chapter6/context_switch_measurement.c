#define _GNU_SOURCE
#include <time.h>
#include <unistd.h>
#include <sched.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//copy paste from stack overflow for debugging
void print_affinity() {
    cpu_set_t mask;
    long nproc, i;

    if (sched_getaffinity(0, sizeof(cpu_set_t), &mask) == -1) {
        perror("sched_getaffinity");
        assert(false);
    }
    nproc = sysconf(_SC_NPROCESSORS_ONLN);
    printf("sched_getaffinity = ");
    for (i = 0; i < nproc; i++) {
        printf("%d ", CPU_ISSET(i, &mask));
    }
    printf("\n");
}


int main() {
    struct timespec ts1;
    struct timespec ts2;
    int file_descriptors_first_pipe[2];
    int file_descriptors_second_pipe[2];
    // optimistically assuming that pipes are created correctly;
    int first_pipe = pipe(file_descriptors_first_pipe);
    int second_pipe = pipe(file_descriptors_second_pipe);

    cpu_set_t mask;
    CPU_SET(7, &mask);
    // int rc = sched_setaffinity(0, sizeof(cpu_set_t), &mask);    
    // printf("%d \n", rc);

    int child_pid = fork();

    cpu_set_t mask2;
    CPU_ZERO(&mask2); // for some reason, initial mask is created with some processors already set...
    CPU_SET(7, &mask2);
    int rc = sched_setaffinity(0, sizeof(cpu_set_t), &mask2);
    printf("%d \n", rc);
    print_affinity();

    if (child_pid < 0) {
        printf("Couldn't fork()!");
        exit(child_pid);
    } else if (child_pid == 0) {
        char buf[12];
        printf("child executes on CPU %d \n", sched_getcpu());
        unsigned long long total_ctx_swtch_nanoseconds = 0; 
        for (int i = 0; i < 1e4; i++) {
            write(file_descriptors_first_pipe[1], "Hello world\n", 12);
            clock_gettime(CLOCK_REALTIME, &ts1);
            read(file_descriptors_second_pipe[0], buf, 12);
            clock_gettime(CLOCK_REALTIME, &ts2);
            unsigned long long context_switch_nanoseconds = ts2.tv_nsec - ts1.tv_nsec;
            // printf("%d\n", context_switch_nanoseconds);
            total_ctx_swtch_nanoseconds += context_switch_nanoseconds;            
            // printf("%d\n", total_ctx_swtch_nanoseconds);
        }
        printf("Nanoseconds spent on average for context switch: %15.12lf", (double)total_ctx_swtch_nanoseconds / 1e4);
    } else {
        char buf[12];
        printf("parent executes on CPU %d \n", sched_getcpu());   
        for (int i = 0; i < 1e4; i++) {
            read(file_descriptors_first_pipe[0], buf, 12);
            write(file_descriptors_second_pipe[1], "Hello world\n", 12);
        }
    }
}