#include "treasure_venture.h"

static void	no_save_file(t_man *man);

void	run_submenu_load(t_man *man)
{
	int	fd_save;
	int	load_success;

	clear_window();
	fd_save = open(SAVE_FILE, O_RDONLY);
	if (fd_save < 0)
		no_save_file(man);
	else
	{
		initialize_game(man);
		load_success = load_saved_game(man, fd_save);
		close(fd_save);
		if (!load_success)
			return ;
		printf("\t[Your saved game will resume...]\n\n");
	}
	man->state = STATE_GAME;
	man->is_game_ongoing = 1;
	describe_location(man, man->characters[CHAR_PLAYER - 1].current_location);
	return ;
}

static void	no_save_file(t_man *man)
{
	printf("\t[No save could be found.]\n");
	if (man->is_game_ongoing)
		printf("\t[The current game will resume...]\n\n");
	else
	{
		printf("\t[A new game will start...]\n\n");
		initialize_game(man);
	}
	return ;
}
