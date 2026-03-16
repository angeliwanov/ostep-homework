#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int fd = open("./2.output", O_WRONLY|O_CREAT|O_TRUNC|O_APPEND, S_IRWXU );    
    int rc = fork();
    
    if (rc < 0) {
        fprintf(stderr, "fork failed");
    } else if (rc == 0) {
        char chld_buff[64];
        snprintf(chld_buff, sizeof(chld_buff), "Hello from child %d\n", getpid());        
        write(fd, chld_buff, strlen(chld_buff));
    } else {
        // wait(NULL);
        char prt_buff[64];
        snprintf(prt_buff, sizeof(prt_buff), "Hello from parent %d\n", getpid());
        write(fd, prt_buff, strlen(prt_buff));
    }

    //appended by both child and parent process
    char msg_buff[64];
    snprintf(msg_buff, sizeof(msg_buff), "Hello from %d\n", getpid());
    write(fd, msg_buff, strlen(msg_buff));
    
    close(fd);
    return 0;
}
