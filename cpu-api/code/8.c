#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#define BUF_SIZE 64

int main(int argc, char* argv[]) {
    int pfd[2];
    if (pipe(pfd) == -1){        
        exit(1);
    };

    int rc_w = fork();
    
    if (rc_w < 0) {
        fprintf(stderr, "fork write child failed");
    } else if (rc_w == 0) { 
        close(pfd[0]); /* close read end */
        if ((write(pfd[1], "message\n", strlen("message\n")) == -1)){
            exit(1);
        };
        close(pfd[1]); /* close write */
        exit(0);
    } 
    
    int rc_r = fork();
        
    if (rc_r < 0) {
        fprintf(stderr, "fork read child failed");
    } else if (rc_r == 0) {                       
        close(pfd[1]); /* close write */
        char buf[BUF_SIZE];
        ssize_t bytes_read;
        if ((bytes_read = read(pfd[0], buf, BUF_SIZE)) == -1) {
            exit(1);
        };
        write(STDOUT_FILENO, buf, bytes_read);
        close(pfd[0]); /* close read */        
        exit(0);
    }
     
    close(pfd[0]); /* close read */
    close(pfd[1]); /* close write */
    waitpid(rc_w, NULL, 0);
    waitpid(rc_r, NULL, 0);

    return 0;
}
