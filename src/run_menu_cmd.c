#include "treasure_venture.h"

static void	run_submenu_new(t_man *man);
static void	run_submenu_load(t_man *man);
static void	run_submenu_save(t_man *man);
static void	run_submenu_about(t_man *man);
static void	run_submenu_quit(t_man *man);

void	run_menu_cmd(t_man *man, const char **tokens)
{
	if (!tokens || !tokens[0])
		open_menu(man);
	else if (!strcmp(tokens[0], "new"))
		run_submenu_new(man);
	else if (!strcmp(tokens[0], "load"))
		run_submenu_load(man);
	else if (!strcmp(tokens[0], "save"))
		run_submenu_save(man);
	else if (!strcmp(tokens[0], "about"))
		run_submenu_about(man);
	else if (!strcmp(tokens[0], "quit"))
		run_submenu_quit(man);
	else
		open_menu(man);
	return;
}

static void	run_submenu_new(t_man *man)
{
	initialize_game(man);
	clear_window();
	printf("\t[A new game will start...]\n");
	if (access(SAVE_FILE, R_OK) != -1)
		printf("\t[The save file still exists.]\n");
	printf("\n");
	man->state = STATE_GAME;
	man->is_game_ongoing = 1;
	describe_location(man, man->characters[CHAR_PLAYER - 1].current_location);
	return;
}

static void	run_submenu_load(t_man *man)
{
	int	fd_save;
	int	load_success;

	clear_window();
	fd_save = open(SAVE_FILE, O_RDONLY);
	if (fd_save != -1)
	{
		initialize_game(man);
		load_success = load_saved_game(man, fd_save);
		close(fd_save);
		if (!load_success)
			return;
		printf("\t[Your saved game will resume...]\n\n");
	}
	else
	{
		printf("\t[No save could be found.]\n");
		if (man->is_game_ongoing)
			printf("\t[The current game will resume...]\n\n");
		else
		{
			printf("\t[A new game will start...]\n\n");
			initialize_game(man);
		}
	}
	man->state = STATE_GAME;
	man->is_game_ongoing = 1;
	describe_location(man, man->characters[CHAR_PLAYER - 1].current_location);
	return;
}

static void	run_submenu_save(t_man *man)
{
	int	fd_save;

	if (!man->is_game_ongoing)
	{
		printf("\t[A game needs to be started for it to be saved.]\n\n");
		return;
	}
	fd_save = open(SAVE_FILE, O_CREAT | O_RDWR, 0664);
	save_game(man, fd_save);
	close(fd_save);
	printf("\t[Game saved!]\n\n");
	if (man->state == STATE_GAME)
		describe_location(man, man->characters[CHAR_PLAYER - 1].current_location);
	return;
}

static void	run_submenu_about(t_man *man)
{
	printf("\t[Visit the Itch.io page:]\n\t"
		"https://lycorisdev.itch.io/treasure-venture\n\n");
	if (man->state == STATE_GAME)
		describe_location(man, man->characters[CHAR_PLAYER - 1].current_location);
	return;
}

static void	run_submenu_quit(t_man *man)
{
	man->state = STATE_NONE;
	return;
}
