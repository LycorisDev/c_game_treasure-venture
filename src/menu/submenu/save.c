#include "treasure_venture.h"

void	run_submenu_save(t_man *man)
{
	if (!man->is_game_ongoing)
	{
		printf("\t[A game needs to be started for it to be saved.]\n\n");
		return ;
	}
	if (save_game(man, SAVE_FILE))
		printf("\t[Game saved!]\n\n");
	else
		fprintf(stderr, "\t[Error: Game failed to save.]\n\n");
	if (man->state == STATE_GAME)
		describe_location(man,
			man->characters[CHAR_PLAYER - 1].current_location);
	return ;
}
