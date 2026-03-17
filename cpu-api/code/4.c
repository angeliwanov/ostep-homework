#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argv, char* argc[]) {
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed");
    } else if (rc == 0) {
        char* my_args[1];
        my_args[0] = strdup("/bin/ls");
        my_args[1] = NULL;        
        execvp(my_args[0], my_args);
    } else {
        wait(NULL);
    }

    return 0;
}
