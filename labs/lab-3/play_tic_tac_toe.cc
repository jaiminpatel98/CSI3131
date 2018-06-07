
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

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
  tic_tac_toe *game = new tic_tac_toe();
  char players[2] = {'X', 'O'};
  int turn = 0;
  char player;
  
  do {
    game->display_game_board();
    player = players[turn & 1];
    game->get_player_move(player);
    game->display_game_board();
    turn++;
  } while ((player = game->game_result()) == '-');
  printf ("Game finished, result: %c \n", player);
  return (0);
}
