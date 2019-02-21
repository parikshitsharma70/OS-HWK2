#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (void) {
    int i, n;
    pid_t childpid;
    
    n = 4;
    for (i = 1; i < n; i++){
        if (childpid = fork()){
            break;
        }
    fprintf(stderr, "My pid = %d Parent pid = %d\n", getpid(), getppid());
    }
    return(0);

}
