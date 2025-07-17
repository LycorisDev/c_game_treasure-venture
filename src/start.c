#include "start.h"
#include "parser.h"
#include "commands.h"
#include "initialize.h"
#include "save.h"
#include "locations.h"

static void	execute_menu_command(const char *command);
static void	execute_submenu_new(void);
static void	execute_submenu_load(void);
static void	execute_submenu_save(void);
static void	execute_submenu_about(void);
static void	execute_submenu_quit(void);

static int				g_is_game_ongoing = 0;
static const KeyFunc	g_command_list[] = 
{
	{"about", &execute_submenu_about},
	{"load", &execute_submenu_load},
	{"new", &execute_submenu_new},
	{"quit", &execute_submenu_quit},
	{"save", &execute_submenu_save},
	{0, &access_main_menu}
};

void	interact(void)
{
	if (g_yes_no_callback)
	{
		parse_yes_no();
	}
	else if (g_state == STATE_MENU)
	{
		execute_menu_command(g_parser[0]);
	}
	else
	{
		if (!g_parser[0])
			display_game_commands();
		else if (strcmp(g_parser[0], "menu"))
			execute_game_command();
		else
			execute_menu_command(g_parser[1]);
	}
	return;
}

static void	execute_menu_command(const char *command)
{
	int	i;

	i = 0;
	if (!*command)
	{
		access_main_menu();
		return;
	}

	while (g_command_list[i].key)
	{
		if (!strcmp(command, g_command_list[i].key))
		{
			g_command_list[i].func();
			return;
		}
		++i;
	}

	g_command_list[i].func();
	return;
}

void	access_main_menu(void)
{
	g_state = STATE_MENU;
	clear_window();
	printf("\t-[ TREASURE VENTURE ]-\n\n");
	printf("\t[During the game, type 'Menu' to go back to the main "
		"menu.]\n\n");
	printf("\t 'New Game'    'Load Game'    'Save'    'About'    "
		"'Quit'\n\n");
	return;
}

static void	execute_submenu_new(void)
{
	initialize_game();
	clear_window();
	printf("\t[A new game will start...]\n");
	if (access(SAVE_FILE, R_OK) != -1)
		printf("\t[The save file still exists.]\n");
	printf("\n");

	g_state = STATE_GAME;
	g_is_game_ongoing = 1;
	describe_location(PLAYER->current_location);
	return;
}

static void	execute_submenu_load(void)
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
		if (g_is_game_ongoing)
			printf("\t[The current game will resume...]\n\n");
		else
		{
			printf("\t[A new game will start...]\n\n");
			initialize_game();
		}
	}

	g_state = STATE_GAME;
	g_is_game_ongoing = 1;
	describe_location(PLAYER->current_location);
	return;
}

static void	execute_submenu_save(void)
{
	int	fd_save;

	if (!g_is_game_ongoing)
	{
		printf("\t[A game needs to be started for it to be saved.]\n\n");
		return;
	}
	fd_save = open(SAVE_FILE, O_CREAT | O_RDWR, 0664);
	save_game(fd_save);
	close(fd_save);
	printf("\t[Game saved!]\n\n");

	if (g_state == STATE_GAME)
		describe_location(PLAYER->current_location);
	return;
}

static void	execute_submenu_about(void)
{
	printf("\t[Visit the Itch.io page:]\n\t"
		"https://lycorisdev.itch.io/treasure-venture\n\n");

	if (g_state == STATE_GAME)
		describe_location(PLAYER->current_location);
	return;
}

static void	execute_submenu_quit(void)
{
	g_state = STATE_NONE;
	return;
}
