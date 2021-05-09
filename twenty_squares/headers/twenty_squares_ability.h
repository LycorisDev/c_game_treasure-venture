#ifndef TWENTY_SQUARES_ABILITY_H
#define TWENTY_SQUARES_ABILITY_H

#include "twenty_squares.h"

int set_ability(const int level, Cell*** target_cell, const Player* players, const Player* current_player);
void describe_ability(const int ability, const int dice);
int ds_stones_handle_ability(const Stone* chosen_stone, const int ability, const int level, const Player* current_player, const Player* other_player);
void execute_ability_fire(const int level, Player* players, Player* current_player, Cell* all_cells);
void execute_ability_water(const int dice, const int level, Player* players, Player* current_player, Cell* all_cells);
void remove_stone_from_board(Cell* all_cells, const int ability, const int level, Player* targeted_player, Player* current_player);

#endif

