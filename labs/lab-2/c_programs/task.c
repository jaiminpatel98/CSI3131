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
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

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
  printf ("%s %s start ... \n", argv[0], argv[1]);
  sleep(10);
  printf ("%s %s end\n", argv[0], argv[1]);
  return(0);  // All is done.
}

