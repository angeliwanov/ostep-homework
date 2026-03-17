#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main() {
    int rc = fork();    

    if (rc < 0) {
        fprintf(stderr, "fork failed: %s\n", strerror(errno));
    } else if (rc == 0) {
        int pid_wait = wait(NULL);
        printf("child wait %d\n", pid_wait);
        printf("child finished %d\n", (int) getpid());
    } else {
        int pid_wait = wait(NULL);   
        printf("parent:  %d\n", pid_wait);
    }

    return 0;
}
