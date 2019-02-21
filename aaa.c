#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <math.h>

pid_t child_pid, wpid;
int status = 0;
int id;
int odd = 0;
int even = 0;
int range = 50000;
int count = 0;
static int glob_var = 0;

int func(int n){
    glob_var = mmap(NULL, sizeof glob_var, PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if(n>0){
        if ((child_pid = fork()) == 0) {
            srand(getpid());
            int value = rand() % range;
            printf("pid : %d , ppid :  %d, val : %d \n", getpid(), getppid(), value);     
            func(n-1);
            // printf("value : %d \n", value);
            if(value % 2 == 0){
                exit(5);
            }
            else{
                exit(6);
            }
            }
        }
        
    while ((wpid = wait(&status)) > 0) {
        int y = glob_var;
        // y = y + 1;
        int x = WEXITSTATUS(status);
        printf("x : %d \n", y);
        if(x == 5){
            even = even + 1; 
            printf("EVEN myid %d received #even : %d #odd : %d \n", getpid(), even, odd);
        }
        else{
            odd = odd + 1;
            printf("ODD myid %d received #even : %d #odd : %d \n", getpid(), even, odd);
        }
    }
}

int main(){
    int odd = 0;
    int even = 0;
    func(10);
}