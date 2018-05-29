/*------------------------------------------------------------
File: stn.c   (CSI3131 Assignment 1)

Student Name:

Student Number:

Description:  This program creates the station processes
     (A, B, C, and D) and then acts as a Ethernet/802.3 hub.
-------------------------------------------------------------*/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

char ID;
char *cfg_fname;
pthread_t rcv_thread_id;

/* Prototypes */
void* readMsg(void *args);

/*-------------------------------------------------------------
Function: main
Parameters:
    int ac - number of arguments on the command line
    char **av - array of pointers to the arguments
Description:
    Creates the stations using createStation() and threads using
    using createHubThreads().  createHubThreads() cancels
    (terminates) the threads after 30 seconds.
-------------------------------------------------------------*/


int main(int argc, char **argv)
{
  int pid1, pid2, pid3;
  int cnt = 0;
  int status;

  pid1 = fork();
  if (pid1 < 0) fprintf(stderr, "Fork Failed");
  else if (pid1 == 0) { // child
    // printf("in child 1, pid: %d %d %d\n", pid1, pid2, pid3);
    sleep(1);
    execlp ("./task", "task", "1");
  }
  else {
    pid2 = fork();
    if (pid2 < 0) fprintf(stderr, "Fork Failed");
    if (pid2 == 0) { // child
      // printf("in child 2, pid: %d %d %d\n", pid1, pid2, pid3);
      sleep(2);
      execlp ("./task", "task", "2");
    }
    else {
      pid3 = fork();
      if (pid3 < 0) fprintf(stderr, "Fork Failed");
      if (pid3 == 0) {  // child
        // printf("in child 3, pid: %d %d %d\n", pid1, pid2, pid3);
        sleep(3);
        execlp ("./task", "task", "3");
      }
      else {
        // printf("in parent inside pid: %d %d %d\n", pid1, pid2, pid3);
        execlp ("./task", "task", "4");
        wait(&status);
        wait(&status);
        wait(&status);
      }
    }
  }

  return(0);  // All is done.
}               

