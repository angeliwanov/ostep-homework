#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 10
#define NUM_SYSCAL 1000000

int main() {
    struct timeval start;
    struct timeval end;

    int fd = open("./empty.txt", O_RDONLY, S_IREAD);
    char buffer[BUF_SIZE];

    gettimeofday(&start, NULL);
    
    for (int i = 0; i < NUM_SYSCAL; ++i) {
        read(fd, buffer, BUF_SIZE);
        lseek(fd, 0, SEEK_SET);
    }

    gettimeofday(&end, NULL);
    long elapsed = (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);
    double syscal_time = (double) elapsed / NUM_SYSCAL;
    printf("time per syscal is %f us\n", syscal_time);
    
    return 0;
}
