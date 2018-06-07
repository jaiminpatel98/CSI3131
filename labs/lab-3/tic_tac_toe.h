
class tic_tac_toe {
  char game_state[3][3];
  char buffer[10];
  public:
  tic_tac_toe();
  char* convert2string();
  void set_game_state(char *state);
  void display_game_board();
  int make_move (int row, int col, char player);
  void get_player_move(char player);
  char game_result();
};