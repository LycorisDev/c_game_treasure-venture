#include "treasure_venture.h"

static void	set_utf8_encoding(void);

t_man	g_man;

int	main(void)
{
	bzero(&g_man, sizeof(g_man));
	set_utf8_encoding();
	open_menu();
	while (g_man.state)
	{
		get_and_parse_input();
		if (g_man.yes_no_callback)
		{
			if (g_man.parser[0])
			{
				if (!strcmp(g_man.parser[0], "yes"))
				{
					g_man.yes_no_callback(1);
					g_man.yes_no_callback = 0;
				}
				else if (!strcmp(g_man.parser[0], "no"))
				{
					g_man.yes_no_callback(0);
					g_man.yes_no_callback = 0;
				}
			}
		}
		else if (g_man.state == STATE_MENU)
		{
			run_menu_cmd(g_man.parser[0]);
		}
		else if (g_man.state == STATE_GAME)
		{
			if (!strcmp(g_man.parser[0], "menu")) /* e.g. "menu save" */
				run_menu_cmd(g_man.parser[1]);
			else
				run_game_command();
		}
	}
	clear_window();
	return EXIT_SUCCESS;
}

void	open_menu(void)
{
	g_man.state = STATE_MENU;
	clear_window();
	printf("\t-[ TREASURE VENTURE ]-\n\n");
	printf("\t[During the game, type 'Menu' to go back to the main menu.]\n\n");
	printf("\t 'New Game'    'Load Game'    'Save'    'About'    'Quit'\n\n");
	return;
}

void	clear_window(void)
{
	#ifdef _WIN32
	system("cls");
	#elif defined(__ANDROID__)
	system("clear");
	#else
	write(STDOUT_FILENO, "\033c", 2);
	#endif
	return;
}

void	initialize_game(void)
{
	populate_list_lexicon();
	populate_list_locations();
	populate_list_items();
	populate_list_characters();
	populate_list_events();
	return;
}

static void	set_utf8_encoding(void)
{
	#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	#endif
	return;
}
