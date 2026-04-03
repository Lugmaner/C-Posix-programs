#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int mysystem(const char *command) {
    if(!command){return EXIT_FAILURE;}
    pid_t pid = fork();
    if(pid < 0){
        perror("fork");
        return EXIT_FAILURE;
    }
    if(pid == 0){
        if(execl("/bin/sh", "sh", "-c", command, (char *)NULL) == -1){
            perror("execl");
            _exit(127);
        }
    }
    else{
        int status = 0;
        if(waitpid(pid,&status,0) == -1){
            perror("waitpid");
            return EXIT_FAILURE;
        }
        if(WIFEXITED(status)){
            return WEXITSTATUS(status);
        }
        
    }
    return EXIT_FAILURE;
}


int main(int argc, char **argv) {
    if (argc != 2) return 2;
    int rc = mysystem(argv[1]);
    printf("%d\n", rc);
    return 0;
}