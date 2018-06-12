
#include <stdio.h>
#include <stdlib.h> 
#include <signal.h> // sigaction(), sigsuspend(), sig*()
#include <unistd.h> // alarm()
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "tic_tac_toe.h"


/* Usage example
 * 
 * First, compile and run this program:
 *     $ gcc np_tic_tac_toe.c -o np_tic_tac_toe
 *     if not already created, create a named pipe (FIFO)
 *     $ mkfifo my_pipe 
 *
 *     In two separe shells run:
 *     $ ./np_tic_tac_toe X 
 *     $ ./np_tic_tac_toe O 
 * 
 *
 */
 
 
int main(int argc, char **argv) {
  char player;
  
  if (argc != 2) {
    printf ("Usage: sig_tic_tac_toe [X|O] \n");
    return (-1);
  }
  player = argv[1][0];
  if (player != 'X' && player != 'O') {
    printf ("Usage: player names must be either X or Y");
    return (-2);
  }

  int file;
  char str[128];
  char my_fifo[128] = "my_pipe";
  tic_tac_toe *game = new tic_tac_toe();
  char* state;
  int turn = 0;

  if (player == 'O') {
    turn = 0;
  }

  do {
    if (turn & 1) {
      file = open(my_fifo, O_RDONLY);
      read(file, str, 128);
      close(file);
      game->set_game_state(str);
      game->display_game_board();
      turn++;  
    } else {
      game->get_player_move(player);
      state = game->convert2string();
      file = open(my_fifo, O_WRONLY);
      write(file, state, strlen(state) + 1);
      close(file);
      game->display_game_board();
      turn++;
    }
  } while ((game->game_result()) == '-');
  printf ("Game finished, result: %c \n", player);
  return (0);

}
