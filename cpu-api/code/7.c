#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed");
    } else if (rc == 0) {
        close(STDOUT_FILENO);
        printf("child\n");
    } else {
        wait(NULL);
    }
    return 0;
}
