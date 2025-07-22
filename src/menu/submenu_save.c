#include "treasure_venture.h"

void	run_submenu_save(t_man *man)
{
	int	fd_save;

	if (!man->is_game_ongoing)
	{
		printf("\t[A game needs to be started for it to be saved.]\n\n");
		return ;
	}
	fd_save = open(SAVE_FILE, O_CREAT | O_RDWR, 0664);
	save_game(man, fd_save);
	close(fd_save);
	printf("\t[Game saved!]\n\n");
	if (man->state == STATE_GAME)
		describe_location(man,
			man->characters[CHAR_PLAYER - 1].current_location);
	return ;
}
