/*  
*  Name:       Parikshit Sharma 
*  Login:      SP_19_CPS536_12
*  Purpose:    Create chain of processes and generate random int in each child process, and return to the 
*              parent process as exit code
*  Bug report: The counter is not working since the increment function is being executed in a parent 
*              different process in the chain everytime.
*              Hence, the address space of each process is different and we need to utilize shared memory
*              using mutex and locks.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//Declare global variables

pid_t child_pid, wpid;
int status = 0;
int odd = 0, even = 0;
int range = 50000;
int id;
int x, n;

//Recursive function to fork processes in chain
int function(int n){
    
    //Break if n == 0
    if(n>0){
        
        //If fork is successful
        if ((child_pid = fork()) == 0) {
            
            //Increment MyID counter
            id = id + 1;
            
            //Generate random value
            srand(getpid());
            int value = rand() % range;
            
            fprintf(stderr, "MyID : %d, Child Process PID : %d , ppid :  %d, Random Value : %d \n", id, getpid(), getppid(), value);     
            
            //Function callback here 
            function(n-1);
            
            //If value is even
            if(value % 2 == 0){
                exit(0);
            }

            //If value is odd
            else{
                exit(1);
            }
        }
        //If fork failed
        else if((child_pid = fork()) == -1){
            fprintf(stderr, "Fork failed");
            exit(2);
        } 
    }
        
    //Wait for child processes to quit
    while ((wpid = wait(&status)) > 0) {
        if(WIFEXITED(status)){
            wpid = wait(&status);
            x = WEXITSTATUS(status);
            if(x == 0 && id > 0){
                even = even + 1; 
                fprintf(stderr, "PID %d received - EVEN #even : %d #odd : %d \n", id, even, odd);
            }
            else if( x == 1 && id > 0){
                odd = odd + 1;
                fprintf(stderr, "PID %d received - ODD  #even : %d #odd : %d \n", id, even, odd);
            }
            else if(id == 0){
                printf("Final results : #even : %d, #odd : %d \n", even, odd);
            }
        }
        else{
            fprintf(stderr, "Child exited abnormally");
        }
    }
}


//Function to check correct usage and invoke recursive function first time
int main(int argc, char * argv[]){
    
    //Invalid usage error handling
    if (argc != 2) {
      fprintf(stderr, "Usage is %s <int> \n", argv[0]);
      exit(1);
    }
    
    //Number of processes to be created
    n = atoi(argv[1]);

    //Invoke function for the first time.
    function(n);
}