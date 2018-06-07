#include <stdio.h>
#include <stdlib.h> 
#include <signal.h> // sigaction(), sigsuspend(), sig*()
#include <unistd.h> // alarm()
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int chk_file_exists(const char * filename){
    /* try to open file to read */
    FILE *file;
    if (file = fopen(filename, "r")){
        fclose(file);
        return 1;
    }
    return 0;
}

int main(int argc, char **argv) {
  int fd;
  char str[128];
  char myfifo[128] = "my_pipe";
  // if (!chk_file_exists(myfifo)) {
    // printf ("file does not exist\n");
    // if (mkfifo(myfifo, 0660) < 0) {
      // printf ("Error opening creating fifo\n");
      // return (-1);
    // }
  // }
  fd = open(myfifo, O_RDONLY);
  read(fd, str, 128);
  printf ("%s \n", str);
  close(fd);
  fd = open(myfifo, O_WRONLY);
  write(fd, str, strlen(str)+1);
  close(fd);
  return 0;
}