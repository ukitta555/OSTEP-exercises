#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <asm-generic/fcntl.h>
// #include <linux/time.h>

int main() {
    long long iterations = 1e5;
    struct timespec ts1;
    struct timespec ts2;
    unsigned long long total_syscall_nanoseconds = 0;
    char buf[100];
    int fd = open("./test.txt", O_RDONLY);
    for (int i = 0; i < iterations; i++) {

        clock_gettime(CLOCK_REALTIME, &ts1);
        read(fd, buf, 0);
        clock_gettime(CLOCK_REALTIME, &ts2);

        // printf("%d, %d\n", ts1.tv_sec, ts1.tv_nsec / 1000);
        // printf("%d, %d\n", ts2.tv_sec, ts2.tv_nsec / 1000);
        // printf("%d\n", ts1.tv_nsec / 1000);
        // printf("%d\n", ts2.tv_nsec / 1000);
        // printf("Syscall took %d \n", (ts1.tv_nsec / (long)1000) - (ts2.tv_nsec / (long)1000));
        long syscall_took_nanoseconds =  ts2.tv_nsec - ts1.tv_nsec;
        total_syscall_nanoseconds += syscall_took_nanoseconds;
        printf("Total nanoseconds so far: %d \n", total_syscall_nanoseconds);
    }
    printf("%d %d \n", total_syscall_nanoseconds, iterations);
    printf("Syscall on average takes %15.10lf nanoseconds", (double)total_syscall_nanoseconds / iterations);
    return 0;   
}