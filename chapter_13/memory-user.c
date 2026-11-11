#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "usage: %s <megabytes> [seconds]\n", argv[0]);
        return 1;
    }

    long megabytes = atol(argv[1]);
    // no time limit given -> run until killed
    long seconds = argc == 3 ? atol(argv[2]) : -1;
    if (megabytes <= 0) {
        fprintf(stderr, "megabytes must be positive\n");
        return 1;
    }

    size_t size = (size_t) megabytes * 1024 * 1024;
    // volatile so the compiler can't optimize the writes away
    volatile char* array = malloc(size);
    if (array == NULL) {
        fprintf(stderr, "Couldn't allocate %ld MB!\n", megabytes);
        return 1;
    }

    // pid is handy for pmap in exercise 5
    printf("pid: %d, using %ld MB\n", getpid(), megabytes);

    time_t start = time(NULL);
    long passes = 0;
    while (seconds < 0 || time(NULL) - start < seconds) {
        for (size_t i = 0; i < size; i++) {
            array[i] = (char) i;
        }
        passes++;
    }

    printf("done, %ld passes over the array\n", passes);
    free((void*) array);
    return 0;
}
