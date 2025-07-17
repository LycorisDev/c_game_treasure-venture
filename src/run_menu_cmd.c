#include "treasure_venture.h"

static void	run_submenu_new(void);
static void	run_submenu_load(void);
static void	run_submenu_save(void);
static void	run_submenu_about(void);
static void	run_submenu_quit(void);

void	run_menu_cmd(const char *cmd)
{
	static const KeyFunc	cmd_list[] = 
	{
		{0, &open_menu},
		{"about", &run_submenu_about},
		{"load", &run_submenu_load},
		{"new", &run_submenu_new},
		{"quit", &run_submenu_quit},
		{"save", &run_submenu_save}
	};
	int	i;

	if (!cmd || !*cmd)
	{
		cmd_list[0].func();
		return;
	}
	i = 1;
	while (cmd_list[i].key)
	{
		if (!strcmp(cmd, cmd_list[i].key))
		{
			cmd_list[i].func();
			return;
		}
		++i;
	}
	cmd_list[0].func();
	return;
}

static void	run_submenu_new(void)
{
	initialize_game();
	clear_window();
	printf("\t[A new game will start...]\n");
	if (access(SAVE_FILE, R_OK) != -1)
		printf("\t[The save file still exists.]\n");
	printf("\n");
	g_man.state = STATE_GAME;
	g_man.is_game_ongoing = 1;
	describe_location(PLAYER->current_location);
	return;
}

static void	run_submenu_load(void)
{
	int	fd_save;
	int	load_success;

	clear_window();
	fd_save = open(SAVE_FILE, O_RDONLY);
	if (fd_save != -1)
	{
		initialize_game();
		load_success = load_saved_game(fd_save);
		close(fd_save);
		if (!load_success)
			return;
		printf("\t[Your saved game will resume...]\n\n");
	}
	else
	{
		printf("\t[No save could be found.]\n");
		if (g_man.is_game_ongoing)
			printf("\t[The current game will resume...]\n\n");
		else
		{
			printf("\t[A new game will start...]\n\n");
			initialize_game();
		}
	}
	g_man.state = STATE_GAME;
	g_man.is_game_ongoing = 1;
	describe_location(PLAYER->current_location);
	return;
}

static void	run_submenu_save(void)
{
	int	fd_save;

	if (!g_man.is_game_ongoing)
	{
		printf("\t[A game needs to be started for it to be saved.]\n\n");
		return;
	}
	fd_save = open(SAVE_FILE, O_CREAT | O_RDWR, 0664);
	save_game(fd_save);
	close(fd_save);
	printf("\t[Game saved!]\n\n");
	if (g_man.state == STATE_GAME)
		describe_location(PLAYER->current_location);
	return;
}

static void	run_submenu_about(void)
{
	printf("\t[Visit the Itch.io page:]\n\t"
		"https://lycorisdev.itch.io/treasure-venture\n\n");
	if (g_man.state == STATE_GAME)
		describe_location(PLAYER->current_location);
	return;
}

static void	run_submenu_quit(void)
{
	g_man.state = STATE_NONE;
	return;
}
