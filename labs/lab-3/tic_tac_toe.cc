#include <stdio.h>
#include <string.h>
#include "tic_tac_toe.h"

  
  tic_tac_toe::tic_tac_toe(){
     for(int i=0; i<3; i++) {
        for (int j=0; j<3; j++){
           game_state[i][j] = '-';
        }
     }
  }
  char* tic_tac_toe::convert2string(){
    memcpy (buffer, game_state, 9);
    buffer[10] = '\0';  // terminate the string
     return (char*) buffer;
  }
  void tic_tac_toe::set_game_state(char *state){
    memcpy (game_state, state, 9);
  }
  void tic_tac_toe::display_game_board(){
    printf ("  1  2  3 \n");
     for(int i=0; i<3; i++) {
       printf ("%c ", 'A' + i);
        for (int j=0; j<3; j++){
           printf ("%c ", game_state[i][j]);
        }
        printf ("\n");
     }
  }
  int tic_tac_toe::make_move (int row, int col, char player){
     int result = 0; // bad move
     if (row >= 0 && row <3 && col>= 0 && col < 3){
        if (game_state[row][col] == '-'){
           game_state[row][col] = player; 
           result = 1; // good move
        }
     }
     return result;
  }
  void tic_tac_toe::get_player_move(char player){
    char buffer[16];
    char *move = buffer;
    int done;

    do {
      printf ("Player %c enter your move: ", player);
      move = gets(move);
      while (move[0] < 'A' || move[0] > 'C' || move[1] < '1' || move[1] > '3') {
        printf ("Illegal move, moves must be row,col (e.g. B2), your move: ");
        move = gets(move);
      }
      done = make_move(move[0] - 'A', move[1] - '1', player);
      if (!done) printf ("Illigal move!\n");
    } while (!done);
  }
  char tic_tac_toe::game_result(){
    // return 'X' if X won, 'O' if O won, 'd' if draw, '-' if not done
     int row1[] = {0,1,2,0,0,0,0,0};
     int row2[] = {0,1,2,1,1,1,1,1};
     int row3[] = {0,1,2,2,2,2,2,2};
     int col1[] = {0,0,0,0,1,2,0,2};
     int col2[] = {1,1,1,0,1,2,1,1};
     int col3[] = {2,2,2,0,1,2,2,0};
     
     for (int i=0; i<8; i++){
        if ( game_state[row1[i]][col1[i]] == game_state[row2[i]][col2[i]] && 
             game_state[row2[i]][col2[i]] == game_state[row3[i]][col3[i]] ){
           return game_state[row1[i]][col1[i]];
        }
     }
     // check if the game actually ended
     for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
           if (game_state[i][j] == '-'){ return '-'; }
        }
     }
     // must be a draw
     return 'd';
  }
