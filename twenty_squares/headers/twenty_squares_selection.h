#ifndef TWENTY_SQUARES_SELECTION_H
#define TWENTY_SQUARES_SELECTION_H

#include "twenty_squares.h"

Stone* select_stone(char* input, Player* current_player);
int select_number_of_cells_forward(const Player* current_player, const Stone* chosen_stone);
void select_use_ability(char* input, const Player* current_player, const int ability, const int ds_decision, Cell*** target_cell);
int select_number_of_stones_for_water(const int max_number, const Player* current_player);
int select_player_for_water(const Player* current_player);

#endif

