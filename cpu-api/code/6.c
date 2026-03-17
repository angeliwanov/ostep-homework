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
        pid_t pid_wait = wait(NULL);
        printf("child wait %d\n", pid_wait);
        printf("child finished %d\n", (int) getpid());
    } else {
        pid_t pid_wait = waitpid(rc, NULL, 0);   
        printf("parent:  %d\n", pid_wait);
    }

    return 0;
}
