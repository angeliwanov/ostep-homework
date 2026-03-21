#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sched.h>
#define NUM_SWITCHES 1000000

int main() 
{
    int p1fd[2];
    int p2fd[2];
    if ((pipe(p1fd)) != 0) {
        fprintf(stderr, "pipe");
    }
    if ((pipe(p2fd)) != 0) {
        fprintf(stderr, "pipe");
    }

    int ch1 = fork();

    if (ch1 < 0) {
        fprintf(stderr, "fork failed");
        exit(1);
    } else if (ch1 == 0) {
        close(p1fd[0]);
        close(p2fd[1]);
    } else {
        close(p1fd[1]);
        close(p2fd[0]);
    }
    
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);
    sched_setaffinity(0, sizeof(set), &set);

    struct timeval start;
    struct timeval end;

    gettimeofday(&start, NULL);

    for (int i = 0; i < NUM_SWITCHES; ++i) {
        if (ch1 < 0) {
            fprintf(stderr, "fork failed");
            exit(1);
        } else if (ch1 == 0) {
            write(p1fd[1], "", 1);            
            char buffer[1];
            read(p2fd[0], buffer, 1);
        } else {            
            char buffer[1];
            read(p1fd[0], buffer, 1);        
            write(p2fd[1], "", 1);
        }              
    }

    gettimeofday(&end, NULL);

    if (ch1 > 0) {
        long elapsed = (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);
        double switch_time = (double) elapsed / (NUM_SWITCHES * 2);
        printf("time per switch is around %f us\n", switch_time);
    }
    return 0;
}
