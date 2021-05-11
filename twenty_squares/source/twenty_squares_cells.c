#include "../headers/twenty_squares_cells.h"

void initialize_all_cells(Cell* all_cells)
{
	(all_cells +  0)->coordinate = 11;
	(all_cells +  0)->stone_in_cell = NULL;
	(all_cells +  0)->ability = ABILITY_NONE;
	(all_cells +  0)->is_cell_special = 1;

	(all_cells +  1)->coordinate = 21;
	(all_cells +  1)->stone_in_cell = NULL;
	(all_cells +  1)->ability = ABILITY_NONE;
	(all_cells +  1)->is_cell_special = 0;

	(all_cells +  2)->coordinate = 31;
	(all_cells +  2)->stone_in_cell = NULL;
	(all_cells +  2)->ability = ABILITY_NONE;
	(all_cells +  2)->is_cell_special = 1;

	(all_cells +  3)->coordinate = 12;
	(all_cells +  3)->stone_in_cell = NULL;
	(all_cells +  3)->ability = ABILITY_NONE;
	(all_cells +  3)->is_cell_special = 0;

	(all_cells +  4)->coordinate = 22;
	(all_cells +  4)->stone_in_cell = NULL;
	(all_cells +  4)->ability = ABILITY_NONE;
	(all_cells +  4)->is_cell_special = 0;

	(all_cells +  5)->coordinate = 32;
	(all_cells +  5)->stone_in_cell = NULL;
	(all_cells +  5)->ability = ABILITY_NONE;
	(all_cells +  5)->is_cell_special = 0;

	(all_cells +  6)->coordinate = 13;
	(all_cells +  6)->stone_in_cell = NULL;
	(all_cells +  6)->ability = ABILITY_NONE;
	(all_cells +  6)->is_cell_special = 0;

	(all_cells +  7)->coordinate = 23;
	(all_cells +  7)->stone_in_cell = NULL;
	(all_cells +  7)->ability = ABILITY_NONE;
	(all_cells +  7)->is_cell_special = 0;

	(all_cells +  8)->coordinate = 33;
	(all_cells +  8)->stone_in_cell = NULL;
	(all_cells +  8)->ability = ABILITY_NONE;
	(all_cells +  8)->is_cell_special = 0;

	(all_cells +  9)->coordinate = 14;
	(all_cells +  9)->stone_in_cell = NULL;
	(all_cells +  9)->ability = ABILITY_NONE;
	(all_cells +  9)->is_cell_special = 0;

	(all_cells + 10)->coordinate = 24;
	(all_cells + 10)->stone_in_cell = NULL;
	(all_cells + 10)->ability = ABILITY_NONE;
	(all_cells + 10)->is_cell_special = 1;

	(all_cells + 11)->coordinate = 34;
	(all_cells + 11)->stone_in_cell = NULL;
	(all_cells + 11)->ability = ABILITY_NONE;
	(all_cells + 11)->is_cell_special = 0;

	(all_cells + 12)->coordinate = 25;
	(all_cells + 12)->stone_in_cell = NULL;
	(all_cells + 12)->ability = ABILITY_NONE;
	(all_cells + 12)->is_cell_special = 0;

	(all_cells + 13)->coordinate = 26;
	(all_cells + 13)->stone_in_cell = NULL;
	(all_cells + 13)->ability = ABILITY_NONE;
	(all_cells + 13)->is_cell_special = 0;

	(all_cells + 14)->coordinate = 17;
	(all_cells + 14)->stone_in_cell = NULL;
	(all_cells + 14)->ability = ABILITY_NONE;
	(all_cells + 14)->is_cell_special = 1;

	(all_cells + 15)->coordinate = 27;
	(all_cells + 15)->stone_in_cell = NULL;
	(all_cells + 15)->ability = ABILITY_NONE;
	(all_cells + 15)->is_cell_special = 0;

	(all_cells + 16)->coordinate = 37;
	(all_cells + 16)->stone_in_cell = NULL;
	(all_cells + 16)->ability = ABILITY_NONE;
	(all_cells + 16)->is_cell_special = 1;

	(all_cells + 17)->coordinate = 18;
	(all_cells + 17)->stone_in_cell = NULL;
	(all_cells + 17)->ability = ABILITY_NONE;
	(all_cells + 17)->is_cell_special = 0;

	(all_cells + 18)->coordinate = 28;
	(all_cells + 18)->stone_in_cell = NULL;
	(all_cells + 18)->ability = ABILITY_NONE;
	(all_cells + 18)->is_cell_special = 0;

	(all_cells + 19)->coordinate = 38;
	(all_cells + 19)->stone_in_cell = NULL;
	(all_cells + 19)->ability = ABILITY_NONE;
	(all_cells + 19)->is_cell_special = 0;

	(all_cells + 20)->coordinate = 1;
	(all_cells + 20)->stone_in_cell = NULL;
	(all_cells + 20)->ability = ABILITY_NONE;
	(all_cells + 20)->is_cell_special = 0;
	return;
}

