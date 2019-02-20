#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <math.h>

int range = 50000;
int myid = 0;
pipe(fd);
int fd[2];
int val = 0;


int func(int n) 
{
    pid_t childPID;

    
    if (n == 0)
    { 
        return 0;
    }
    childPID = fork(); 
    if (childPID == 0) {
        close(fd[1]);
        // read the data (blocking operation)
        read(fd[0], &val, sizeof(val));

        printf("Parent received value: %d\n", val);
        // close the read-descriptor
        close(fd[0]);
        exit(0);
    }
    if (childPID == 0) {
        myid = myid + 1;
        srand(getpid());
        int value = rand() % range;
        int flag = 0;
        if(value % 2 == 1){
            flag = flag + 1;
        }
        printf("myid is:%d child process pid is:%d  ppid is %d value is: %d \n", myid, getpid(), getppid(), value);
        n = n-1;
        func(n);
        close(fd[0]);
        write(fd[1], &flag, sizeof(flag)); 
        printf(" %d Child send value: %d\n", myid, flag);

        // close the write descriptor:
        close(fd[1]);

        exit(0);
    }
    else {
       wait(NULL);
    } 
    return 0;   
}


int main(int argc, char *argv[])
{   
    
    if(argc == 1){
        printf("Wrong usage, correct usage is <program-name> n(>0)");
        return 0;
    }
    else{
    int n = atoi(argv[1]);
    func(n); 
    return 0;
    }
}