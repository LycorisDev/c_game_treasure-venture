#ifndef TWENTY_SQUARES_MOVEMENT_H
#define TWENTY_SQUARES_MOVEMENT_H

#include "twenty_squares.h"

int set_number_of_moveable_stones_and_every_can_stone_move(Player* current_player, const int level, const int dice);
int can_this_classic_stone_move(const Stone* stone, Player* current_player, const int dice);
int can_this_ds_stone_move(Stone* stone, Player* current_player, const int dice);
int move_stone(const int level, int number_of_cells_forward, Stone* chosen_stone, Cell*** target_cell, Player* current_player, Player* other_player);

#endif

