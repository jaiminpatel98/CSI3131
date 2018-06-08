
#include <stdio.h>
#include <stdlib.h> 
#include <signal.h> // sigaction(), sigsuspend(), sig*()
#include <unistd.h> // alarm()
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "tic_tac_toe.h"
#include "my_pipe"

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
  
  tic_tac_toe *game = new tic_tac_toe();
  char* state = game->convert2string();
  game->set_game_state(state);
  int turn = 0;
  int pipe[2];
  my_pipe(pipe);

  do {
    if (turn%2 == 0) {
      int file;
      if(turn == 0) {
        game->display_game_board();
        game->get_player_move();
        game->display_game_board();
        turn++;
        state = game->convert2string();
        file = open(my_pipe, O_WRONLY);
        write(file, state, strlen(state)+1);
        close(file);
      } else {
        file = open(my_pipe, O_RDONLY);
        read(file, state, strlen(state)+1);
        close();
        game->set_game_state(state);
        game->display_game_board();
        game->get_player_move();
        game->display_game_board();
        turn++;
        state = game->convert2string();
        file = open(my_pipe, O_WRONLY);
        write(file, state, strlen(state)+1);
        close(file);
      }
    } else {
      file = open(my_pipe, O_RDONLY);
      read(file, state, strlen(state)+1);
      close(file);
      game->set_game_state(state);
      game->display_game_board();
      game->get_player_move();
      game->display_game_board();
      turn++;
      state = game->convert2string();
      file = open(my_pipe, O_WRONLY);
      write(file, state, strlen(state)+1);
      close(file);
    }
  } while ((player = game->game_result()) == '-');
  printf ("Game finished, result: %c \n", player);
  return (0);
}
