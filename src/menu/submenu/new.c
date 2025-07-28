#include "treasure_venture.h"

void	run_submenu_new(t_man *man)
{
	initialize_game(man);
	clear_window();
	printf("\t[A new game will start...]\n");
	if (access(SAVE_FILE, R_OK) != -1)
		printf("\t[The save file still exists.]\n");
	printf("\n");
	man->state = STATE_GAME;
	man->is_game_ongoing = 1;
	describe_loc(man, man->charas[0].current_loc);
	return ;
}
