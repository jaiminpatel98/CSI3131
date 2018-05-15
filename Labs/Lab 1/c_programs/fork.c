#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main() {
    pid_t pid;
    
    printf("fork \n");
    /* fork a child process */
    for (int i = 0; i <= 4; i++) {
        pid = fork();
        if (pid < 0) {
            /* error occured */
	    fprintf(stderr, "Fork Failed");
	    return 1;
	} else if (pid == 0) {
	    /* child process */
	    execlp("/bin/ls", "ls", NULL);
	} else {
	    /* parent process */
	    /* parent will wait for the child to complete */
	    wait(NULL);
	    printf("Child Complete");
	}
	sleep(1);
    }
    return 0;
}
