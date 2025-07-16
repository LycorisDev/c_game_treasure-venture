#include "start.h"
#include "parser.h"
#include "commands.h"
#include "initialize.h"
#include "save.h"
#include "locations.h"
#include "output.h"

#define STATE_MENU 0
#define STATE_GAME 1
static int	game_state = STATE_MENU;
static int	is_game_ongoing = 0;

static void	execute_menu_command(const char *command);
static void	execute_submenu_new(void);
static void	execute_submenu_load(void);
static void	execute_submenu_save(void);
static void	execute_submenu_about(void);
static void	execute_submenu_quit(void);

static const KeyFunc	command_list[] = 
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
	if (yes_no_callback)
	{
		parse_yes_no();
	}
	else if (game_state == STATE_MENU)
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

	while (command_list[i].key)
	{
		if (!strcmp(command, command_list[i].key))
		{
			command_list[i].func();
			return;
		}
		++i;
	}

	command_list[i].func();
	return;
}

void	access_main_menu(void)
{
	game_state = STATE_MENU;
	reset_output();
	add_output("\t-[ TREASURE VENTURE ]-\n\n");
	add_output("\t[During the game, type 'Menu' to go back to the main menu.]\n\n");
	add_output("\t 'New Game'    'Load Game'    'Save'    'About'    'Quit'\n\n");
	return;
}

static void	execute_submenu_new(void)
{
	FILE	*save_file;

	save_file = 0;
	initialize_game(save_file);
	reset_output();
	add_output("\t[A new game will start...]\n");
	if ((save_file = fopen("save.txt", "r")))
	{
		add_output("\t[The save file still exists.]\n");
		fclose(save_file);
	}
	add_output("\n");

	game_state = STATE_GAME;
	is_game_ongoing = 1;
	describe_location(PLAYER->current_location);
	return;
}

static void	execute_submenu_load(void)
{
	FILE	*save_file;

	save_file = 0;
	reset_output();

	if ((save_file = fopen("save.txt", "r")))
	{
		initialize_game(save_file);
		fclose(save_file);
		add_output("\t[Your saved game will resume...]\n\n");
	}
	else
	{
		add_output("\t[No save could be found.]\n");
		if (is_game_ongoing)
			add_output("\t[The current game will resume...]\n\n");
		else
		{
			add_output("\t[A new game will start...]\n\n");
			initialize_game(save_file);
		}
	}

	game_state = STATE_GAME;
	is_game_ongoing = 1;
	describe_location(PLAYER->current_location);
	return;
}

static void	execute_submenu_save(void)
{
	FILE	*save_file;

	save_file = 0;
	if (!is_game_ongoing)
	{
		add_output("\t[A game needs to be started for it to be saved.]\n\n");
		return;
	}

	save_file = fopen("save.txt", "w+");
	save_game(save_file);
	fclose(save_file);
	add_output("\t[Game saved!]\n\n");

	if (game_state == STATE_GAME)
		describe_location(PLAYER->current_location);
	return;
}

static void	execute_submenu_about(void)
{
	add_output("\t[Visit the Itch.io page:]\n\thttps://lycorisdev.itch.io/treasure-venture\n\n");

	if (game_state == STATE_GAME)
		describe_location(PLAYER->current_location);
	return;
}

static void	execute_submenu_quit(void)
{
	close_window();
	return;
}
