
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
  char* my_pipe = "my_pipe";
  mkfifo (my_pipe, 0666);

  if (argc != 2) {
    printf ("Usage: sig_tic_tac_toe [X|O] \n");
    return (-1);
  }
  player = argv[1][0];
  if (player != 'X' && player != 'O') {
    printf ("Usage: player names must be either X or Y");
    return (-2);
  }
  
  char* my_fifo = "my_pipe";
  tic_tac_toe *game = new tic_tac_toe();
  char* state = game->convert2string();
  game->set_game_state(state);
  int turn = 0;
  int file;
  mkfifo(my_fifo, 0666);

  if (player == 'O') {
    turn = 1;
  }

  do {
    if (turn & 1) {
      file = open(my_fifo, O_RDONLY);
      read(file, state, strlen(state) + 1);
      close(file);
      game->set_game_state(state);
      game->display_game_board();
      turn++;
    } else {
      file = open(my_fifo, O_WRONLY);
      game->get_player_move(player);
      state = game->convert2string();
      write(file, state, strlen(state) + 1);
      close(file);
      game->display_game_board();
      turn++;
    }
  } while ((player = game->game_result()) == '-');
  printf ("Game finished, result: %c \n", player);
  return (0);
}
