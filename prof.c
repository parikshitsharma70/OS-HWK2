#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){
    pid_t child_pid, retid;
    int status, exitval;

    if (argc != 2){
        fprintf(stderr, "Usage is %s <int> \n", argv[0]);
        exit(1);
    }
    exitval = atoi(argv[1]);

    if((child_pid = fork()) == -1){
        fprintf(stderr, "For failed . \n");
        exit(2);
    }
    else if(child_pid > 0){
        fprintf(stderr, "Parent to wait. \n");
        retid = wait(&status);
        fprintf(stderr, "Status from child id %d. \n", retid);
        if(WIFEXITED(status)){
                fprintf(stderr, "Child exited normally with exit status %d \n", WEXITSTATUS(status));
            }
        else{
            fprintf(stderr, "Abnormal exit of child. \n");
        }
        }
    else{
        fprintf(stderr, "Child %d to sleep \n", getpid());
        sleep(3);
        exit(exitval);
    }
    return 0;
}