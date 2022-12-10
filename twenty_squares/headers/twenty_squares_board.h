#ifndef TWENTY_SQUARES_BOARD_H
#define TWENTY_SQUARES_BOARD_H

#include "twenty_squares.h"

void print_board(const int number_of_turns, const int level, const int current_player_id, Player* players, Cell* all_cells);
void print_turn_line(const int number_of_turns);
void print_column0(const int line, const int level, const int current_player_id, Player* players);
void print_column1(const int line, const int current_player_id, Cell* all_cells);
void print_column2(const int line, const int current_player_id, Cell* all_cells);
void print_column3(const int line, const int current_player_id, Cell* all_cells);
void print_column4(const int line, const int level, const int current_player_id, Player* players);

#endif

