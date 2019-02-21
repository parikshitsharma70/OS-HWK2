#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){
	pid_t child_pid, retid;
	int status, even,odd,i,n,value;

	if (argc != 2){
	        fprintf(stderr, "Usage is %s <int> \n", argv[0]);
	        exit(1);
	}
	n = atoi(argv[1]);
	for (i = 0; i < n; i++){
       		if((child_pid = fork()) == -1){
			fprintf(stderr, "For failed . \n");
			exit(2);
    		}

    		else if(child_pid > 0){
			srand(child_pid);
			value=rand()%50000;
        		fprintf(stderr, "myid:%d pid:%d ppid: %d value: %d. \n",i+1,getpid(),getppid(),value);
			retid = wait(&status);	
			if(WIFEXITED(status)){
				if(WEXITSTATUS(status))
					odd+=1;
				else
					even+=1;
                	fprintf(stderr, "myid:%d recieves #odd: %d #even: %d \n", i+1,odd,even);
            		}
        		else{
            			fprintf(stderr, "Abnormal exit of child. \n");
        		}
       			
		}
			
    		else{
			if(value % 2==0)
				exit(1);
		
			else
				exit(0);
			
			
        		
        		
		}
	}
	return 0;
}
