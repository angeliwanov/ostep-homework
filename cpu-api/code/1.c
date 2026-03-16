#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) 
{
    int x = 100;
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed");
        exit(1);
    } else if (rc == 0) {
        printf("child sees var x as %d\n", x);
    } else {        
        wait(NULL);
        printf("parent sees var x as %d\n", x);
    }
    return 0;
}
