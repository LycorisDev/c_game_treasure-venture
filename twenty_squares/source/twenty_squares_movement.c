#include "../headers/twenty_squares_movement.h"
#include "../../headers/rng.h"

int set_number_of_moveable_stones_and_every_can_stone_move(Player* current_player, const int level, const int dice)
{
	int i, number_of_moveable_stones = 0;
	for (i = 0; i < 7; ++i)
	{
		if (level <= 2 && can_this_classic_stone_move(&(current_player->stoneset[i]), current_player, dice))
		{
			current_player->stoneset[i].can_stone_move = 1;
			++number_of_moveable_stones;
		}
		else if (level > 2 && can_this_ds_stone_move(&(current_player->stoneset[i]), current_player, dice))
		{
			current_player->stoneset[i].can_stone_move = 1;
			++number_of_moveable_stones;
		}
		else
			current_player->stoneset[i].can_stone_move = 0;
	}
	return number_of_moveable_stones;
}

int can_this_classic_stone_move(const Stone* stone, Player* current_player, const int dice)
{
	int i;
	Cell** target_cell;

	/* target_cell is a double pointer because current_player is a double pointer */

	if (stone->coordinate == 1 || stone->coordinate == -1)
		return 0;

	if (stone->coordinate == 0)
	{
		target_cell = &current_player->racetrack[dice - 1];
	}
	else
	{
		for (i = 0; i < 14; ++i)
		{
			if (stone->coordinate == current_player->racetrack[i]->coordinate)
			{
				if (i + dice >= 14)
					return 1;

				target_cell = &current_player->racetrack[i + dice];
				break;
			}
		}
	}

	if ((*target_cell)->stone_in_cell == NULL)
		return 1;
	else if ((*target_cell)->ability == ABILITY_EARTH)
		return 0;
	else if ((*target_cell)->stone_in_cell->player_id == current_player->id)
		return 0; /* ally */
	else
		return 1; /* enemy */
}

int can_this_ds_stone_move(Stone* stone, Player* current_player, const int dice)
{
	int i, j = 0;
	int can_this_stone_move = 0, is_wrath_on_no_killing_road = 0;
	int coordinate_of_closest_enemy = 0;
	Cell** target_cells_1 = NULL;
	Cell** target_cells_2 = NULL;
	Cell** target_cells_3 = NULL;
	Cell** target_cells_4 = NULL;

	/* target_cells are double pointers because current_player is a double pointer + they are not an array because I suck */

	if (stone->coordinate == 1 || stone->coordinate == -1)
		return can_this_stone_move;

	stone->possible_movements[0] = 0;
	stone->possible_movements[1] = 0;
	stone->possible_movements[2] = 0;
	stone->possible_movements[3] = 0;

	if (stone->coordinate == 0)
	{
		if (dice >= 1)
			target_cells_1 = &current_player->racetrack[0];
		if (dice >= 2)
			target_cells_2 = &current_player->racetrack[1];
		if (dice >= 3)
			target_cells_3 = &current_player->racetrack[2];
		if (dice == 4)
			target_cells_4 = &current_player->racetrack[3];
	}
	else
	{
		for (i = 0; i < 14; ++i)
		{
			if (stone->coordinate == current_player->racetrack[i]->coordinate)
			{
				if (dice >= 1)
				{
					if (i + 1 >= 14)
					{
						/* We break after an out of bounds coordinate is found, because we don't need more than one */
						target_cells_1 = &current_player->racetrack[14];
						break;
					}
					else
						target_cells_1 = &current_player->racetrack[i + 1];
				}
				if (dice >= 2)
				{
					if (i + 2 >= 14)
					{
						target_cells_2 = &current_player->racetrack[14];
						break;
					}
					else
						target_cells_2 = &current_player->racetrack[i + 2];
				}
				if (dice >= 3)
				{
					if (i + 3 >= 14)
					{
						target_cells_3 = &current_player->racetrack[14];
						break;
					}
					else
						target_cells_3 = &current_player->racetrack[i + 3];
				}
				if (dice == 4)
				{
					if (i + 4 >= 14)
					{
						target_cells_4 = &current_player->racetrack[14];
						break;
					}
					else
						target_cells_4 = &current_player->racetrack[i + 4];
				}
				break;
			}
		}
	}

	if (stone->id == ID_STONE_WRATH)
	{
		/* If Wrath is on the "no killing" road, we don't care for enemies. */
		if (stone->coordinate == current_player->racetrack[INDEX_1_ON_3_NO_KILLING_ROAD]->coordinate 
		|| stone->coordinate == current_player->racetrack[INDEX_2_ON_3_NO_KILLING_ROAD]->coordinate 
		|| stone->coordinate == current_player->racetrack[INDEX_3_ON_3_NO_KILLING_ROAD]->coordinate)
			is_wrath_on_no_killing_road = 1;

		/* Wrath is not on "no killing" road */
		if (!is_wrath_on_no_killing_road)
		{
			/* We first get the index of Wrath's position.
			If it's before the common road, we start checking for an enemy from the beginning of the common road.
			If it's after this beginning, we start to check from the first cell after Wrath's position. */
			for (i = 0; i < 14; ++i)
			{
				if (stone->coordinate == 0 || stone->coordinate == current_player->racetrack[i]->coordinate)
				{
					for (i = stone->coordinate == 0 || ++i <= INDEX_1_ON_8_COMMON_ROAD ? INDEX_1_ON_8_COMMON_ROAD : i; i <= INDEX_8_ON_8_COMMON_ROAD; ++i)
					{
						if (current_player->racetrack[i]->stone_in_cell != NULL && current_player->racetrack[i]->stone_in_cell->player_id != current_player->id)
						{
							coordinate_of_closest_enemy = current_player->racetrack[i]->coordinate;
							break;
						}
					}
					break;
				}
			}
		}

		/* Wrath is on no killing road OR there is no enemy on the common road in front of Wrath: 
		It goes to the closest empty cell (this closest "cell" may be out of bounds). */
		if (is_wrath_on_no_killing_road || !coordinate_of_closest_enemy)
		{
			if ((*target_cells_1)->coordinate == 1)
			{
				/* This cell is out of bounds */
				stone->possible_movements[0] = 1;
				return 1;
			}
			else if ((*target_cells_1)->stone_in_cell == NULL)
			{
				/* The closest cell is empty */
				stone->possible_movements[0] = 1;
				return 1;
			}

			/* The closest cell is neither out of bounds nor empty, so we check the next one, and so on */
			if (target_cells_2 != NULL)
			{
				if ((*target_cells_2)->coordinate == 1)
				{
					stone->possible_movements[0] = 2;
					return 1;
				}
				else if ((*target_cells_2)->stone_in_cell == NULL)
				{
					stone->possible_movements[0] = 2;
					return 1;
				}

				if (target_cells_3 != NULL)
				{
					if ((*target_cells_3)->coordinate == 1)
					{
						stone->possible_movements[0] = 3;
						return 1;
					}
					else if ((*target_cells_3)->stone_in_cell == NULL)
					{
						stone->possible_movements[0] = 3;
						return 1;
					}

					if (target_cells_4 != NULL)
					{
						if ((*target_cells_4)->coordinate == 1)
						{
							stone->possible_movements[0] = 4;
							return 1;
						}
						else if ((*target_cells_4)->stone_in_cell == NULL)
						{
							stone->possible_movements[0] = 4;
							return 1;
						}
					}
				}
			}
		}
		else /* Wrath is not on "no killing" road and there's an enemy in front of it */
		{
			/* Wrath tries to get as close to the enemy as possible, until it can kill it, ignoring the presence of allies on its path (= killing them if needs be). */
			/* Disclaimer: Earth protects stones from Wrath. */
			if ((*target_cells_1)->coordinate == coordinate_of_closest_enemy)
			{
				if ((*target_cells_1)->ability != ABILITY_EARTH)
				{
					stone->possible_movements[0] = 1;
					return 1;
				}
				else
				{
					/* The first cell contains the enemy, but it is protected by Earth. Wrath remains right behind the stone, waiting for it to move.
					Therefore, Wrath cannot move this turn. */
					return 0;
				}
			}

			if (target_cells_2 != NULL)
			{
				if ((*target_cells_2)->coordinate == coordinate_of_closest_enemy)
				{
					if ((*target_cells_2)->ability != ABILITY_EARTH)
					{
						stone->possible_movements[0] = 2;
						return 1;
					}
					else
					{
						/* The enemy is on this cell, but it is protected by Earth, therefore Wrath goes to the cell right before this one. */
						stone->possible_movements[0] = 1;
						return 1;
					}
				}

				if (target_cells_3 != NULL)
				{
					if ((*target_cells_3)->coordinate == coordinate_of_closest_enemy)
					{
						if ((*target_cells_3)->ability != ABILITY_EARTH)
						{
							stone->possible_movements[0] = 3;
							return 1;
						}
						else
						{
							stone->possible_movements[0] = 2;
							return 1;
						}
					}

					if (target_cells_4 != NULL)
					{
						if ((*target_cells_4)->coordinate == coordinate_of_closest_enemy)
						{
							if ((*target_cells_4)->ability != ABILITY_EARTH)
							{
								stone->possible_movements[0] = 4;
								return 1;
							}
							else
							{
								stone->possible_movements[0] = 3;
								return 1;
							}
						}
					}
				}
			}

			/* The enemy is not on the next 4 cells, so it must be from the 5th onwards. We need to go the farthest cell we can reach that is not protected by Earth. */
			if (target_cells_4 != NULL && (*target_cells_4)->ability != ABILITY_EARTH)
			{
				stone->possible_movements[0] = 4;
				return 1;
			}
			else if (target_cells_3 != NULL && (*target_cells_3)->ability != ABILITY_EARTH)
			{
				stone->possible_movements[0] = 3;
				return 1;
			}
			else if (target_cells_2 != NULL && (*target_cells_2)->ability != ABILITY_EARTH)
			{
				stone->possible_movements[0] = 2;
				return 1;
			}
			else if ((*target_cells_1)->ability != ABILITY_EARTH)
			{
				stone->possible_movements[0] = 1;
				return 1;
			}
			/* Else: We simply wait to reach the "return 0" down below */
		}

		return 0;
	}
	else if (stone->id == ID_STONE_GREED)
	{
		/* Greed's first priority: An empty special cell */
		if ((*target_cells_1)->is_cell_special && (*target_cells_1)->stone_in_cell == NULL)
		{
			stone->possible_movements[0] = 1;
			return 1;
		}
		else if (target_cells_2 != NULL)
		{
			if ((*target_cells_2)->is_cell_special && (*target_cells_2)->stone_in_cell == NULL)
			{
				stone->possible_movements[0] = 2;
				return 1;
			}
			else if (target_cells_3 != NULL)
			{
				if ((*target_cells_3)->is_cell_special && (*target_cells_3)->stone_in_cell == NULL)
				{
					stone->possible_movements[0] = 3;
					return 1;
				}
				else if (target_cells_4 != NULL && (*target_cells_4)->is_cell_special && (*target_cells_4)->stone_in_cell == NULL)
				{
					stone->possible_movements[0] = 4;
					return 1;
				}
			}
		}

		/* Greed's second priority: The closest enemy not protected by Earth */
		if ((*target_cells_1)->stone_in_cell != NULL && (*target_cells_1)->stone_in_cell->player_id != current_player->id && (*target_cells_1)->ability != ABILITY_EARTH)
		{
			stone->possible_movements[0] = 1;
			return 1;
		}
		else if (target_cells_2 != NULL)
		{
			if ((*target_cells_2)->stone_in_cell != NULL && (*target_cells_2)->stone_in_cell->player_id != current_player->id && (*target_cells_2)->ability != ABILITY_EARTH)
			{
				stone->possible_movements[0] = 2;
				return 1;
			}
			else if (target_cells_3 != NULL)
			{
				if ((*target_cells_3)->stone_in_cell != NULL && (*target_cells_3)->stone_in_cell->player_id != current_player->id && (*target_cells_3)->ability != ABILITY_EARTH)
				{
					stone->possible_movements[0] = 3;
					return 1;
				}
				else if (target_cells_4 != NULL && (*target_cells_4)->stone_in_cell != NULL && (*target_cells_4)->stone_in_cell->player_id != current_player->id 
					&& (*target_cells_4)->ability != ABILITY_EARTH)
				{
					stone->possible_movements[0] = 4;
					return 1;
				}
			}
		}

		/* Greed's third priority: The farthest cell (empty, because if not it's either an ally stone or an unkillable enemy) */
		if (target_cells_4 != NULL && (*target_cells_4)->stone_in_cell == NULL)
		{
			stone->possible_movements[0] = 4;
			return 1;
		}
		else if (target_cells_3 != NULL && (*target_cells_3)->stone_in_cell == NULL)
		{
			stone->possible_movements[0] = 3;
			return 1;
		}
		else if (target_cells_2 != NULL && (*target_cells_2)->stone_in_cell == NULL)
		{
			stone->possible_movements[0] = 2;
			return 1;
		}
		else if ((*target_cells_1)->stone_in_cell == NULL)
		{
			stone->possible_movements[0] = 1;
			return 1;
		}
		else
		{
			return 0;
		}
	}

	if (target_cells_1 != NULL)
	{
		if ((*target_cells_1)->coordinate == 1)
		{
			/* It goes out of bounds */
			stone->possible_movements[j++] = 1;
			can_this_stone_move = 1;
		}
		else if ((*target_cells_1)->stone_in_cell == NULL)
		{
			/* The cell is empty */
			stone->possible_movements[j++] = 1;
			can_this_stone_move = 1;
		}
		else if ((*target_cells_1)->ability != ABILITY_EARTH && (*target_cells_1)->stone_in_cell->player_id != current_player->id)
		{
			/* Stone is not protected by Earth and is an enemy */
			stone->possible_movements[j++] = 1;
			can_this_stone_move = 1;
		}
	}

	if (target_cells_2 != NULL)
	{
		if ((*target_cells_2)->coordinate == 1)
		{
			stone->possible_movements[j++] = 2;
			can_this_stone_move = 1;
		}
		else if ((*target_cells_2)->stone_in_cell == NULL)
		{
			stone->possible_movements[j++] = 2;
			can_this_stone_move = 1;
		}
		else if ((*target_cells_2)->ability != ABILITY_EARTH && (*target_cells_2)->stone_in_cell->player_id != current_player->id)
		{
			stone->possible_movements[j++] = 2;
			can_this_stone_move = 1;
		}
	}

	if (target_cells_3 != NULL)
	{
		if ((*target_cells_3)->coordinate == 1)
		{
			stone->possible_movements[j++] = 3;
			can_this_stone_move = 1;
		}
		else if ((*target_cells_3)->stone_in_cell == NULL)
		{
			stone->possible_movements[j++] = 3;
			can_this_stone_move = 1;
		}
		else if ((*target_cells_3)->ability != ABILITY_EARTH && (*target_cells_3)->stone_in_cell->player_id != current_player->id)
		{
			stone->possible_movements[j++] = 3;
			can_this_stone_move = 1;
		}
	}

	if (target_cells_4 != NULL)
	{
		if ((*target_cells_4)->coordinate == 1)
		{
			stone->possible_movements[j++] = 4;
			can_this_stone_move = 1;
		}
		else if ((*target_cells_4)->stone_in_cell == NULL)
		{
			stone->possible_movements[j++] = 4;
			can_this_stone_move = 1;
		}
		else if ((*target_cells_4)->ability != ABILITY_EARTH && (*target_cells_4)->stone_in_cell->player_id != current_player->id)
		{
			stone->possible_movements[j++] = 4;
			can_this_stone_move = 1;
		}
	}

	return can_this_stone_move;
}

int move_stone(const int level, int number_of_cells_forward, Stone* chosen_stone, Cell*** target_cell, Player* current_player, Player* other_player)
{
	int i;
	int racetrack_index_of_origin_cell = 0;
	int pride_has_chosen = 0;
	*target_cell = &current_player->racetrack[14];

	/* I don't understand why, but racetrack_index_of_origin_cell needs to be set to 0, or after the first time entering the function, the variable will take a garbage value */

	for (i = 0; i < 14; ++i)
	{
		if ((*chosen_stone).coordinate == current_player->racetrack[i]->coordinate)
		{
			racetrack_index_of_origin_cell = i;
			break;
		}
	}

	if ((*chosen_stone).id == ID_STONE_PRIDE)
	{
		/* If possible, Pride wants to go out of bounds. As target_cell is already set to racetrack index 14, which means "out of bounds", we don't need to update it. */
		for (i = 0; i < 4; ++i)
		{
			if ((*chosen_stone).possible_movements[i] == 0)
				break;

			if (!pride_has_chosen)
			{
				if (racetrack_index_of_origin_cell + (*chosen_stone).possible_movements[i] >= 14)
				{
					pride_has_chosen = 1;
					printf("\nPride seizes the opportunity to get rid of %s, and leaves.\n\n", current_player->is_artificial_intelligence ? current_player->name : "you");
					break;
				}
			}
		}

		/* If pride couldn't go out of bounds, we need to find another destination. */
		if (!pride_has_chosen)
		{
			/* (i - 1) is the last valid index of possible_movements[]. */
			pride_has_chosen = i - 1 == 0 ? 0 : get_random_number_minmax(0, i - 1);
			if (number_of_cells_forward == (*chosen_stone).possible_movements[pride_has_chosen])
			{
				printf("\nPride refuses to move. The turn passes.\n\n");
				return 0;
			}
			else
			{
				printf("\n\"%s\", huh? Pride will move somewhere else.\n\n", 
					  number_of_cells_forward == 1 ? "One" 
					: number_of_cells_forward == 2 ? "Two" 
					: number_of_cells_forward == 3 ? "Three" 
					: "Four");

				number_of_cells_forward = (*chosen_stone).possible_movements[pride_has_chosen];
			}

			if ((*chosen_stone).coordinate == 0)
			{
				*target_cell = &current_player->racetrack[number_of_cells_forward - 1];
			}
			else
			{
				/* If we are here, it means that the target cannot be out of bounds, so there's no need to check if it is. */
				*target_cell = &current_player->racetrack[racetrack_index_of_origin_cell + number_of_cells_forward];
			}
		}
	}
	else
	{
		if ((*chosen_stone).coordinate == 0)
		{
			*target_cell = &current_player->racetrack[number_of_cells_forward - 1];
		}
		else
		{
			if (racetrack_index_of_origin_cell + number_of_cells_forward < 14)
				*target_cell = &current_player->racetrack[racetrack_index_of_origin_cell + number_of_cells_forward];
		}
	}

	if ((*chosen_stone).coordinate == 0)
		++(current_player->number_of_stones_on_board);
	else
	{
		current_player->racetrack[racetrack_index_of_origin_cell]->stone_in_cell = NULL;
		current_player->racetrack[racetrack_index_of_origin_cell]->ability = ABILITY_NONE;
	}
	if ((*(*target_cell))->coordinate == 1)
	{
		(*chosen_stone).coordinate = 1;
		--(current_player->number_of_playable_stones);
		--(current_player->number_of_stones_on_board);
		++(current_player->points);
	}
	else
	{
		if ((*(*target_cell))->stone_in_cell != NULL)
		{
			if (level == 1 || level == 3)
				(*(*target_cell))->stone_in_cell->coordinate = 0;
			else
			{
				(*(*target_cell))->stone_in_cell->coordinate = -1;
				--(other_player->number_of_playable_stones);
				--(other_player->number_of_stones_on_board);
				--(other_player->points);
				++(current_player->points);
			}
		}

		(*(*target_cell))->stone_in_cell = chosen_stone;
		(*chosen_stone).coordinate = (*(*target_cell))->coordinate;
	}
	return 1;
}

