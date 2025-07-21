#include "treasure_venture.h"

static void	set_utf8_encoding(void);

int	main(void)
{
	t_man	man;

	memset(&man, 0, sizeof(man));
	set_utf8_encoding();
	open_menu(&man);
	while (man.state)
	{
		man.tokens = get_input();
		//
		if (man.yes_no_callback)
		{
			if (man.tokens)
			{
				if (!strcmp(man.tokens[0], "yes"))
				{
					man.yes_no_callback(1);
					man.yes_no_callback = 0;
				}
				else if (!strcmp(man.tokens[0], "no"))
				{
					man.yes_no_callback(0);
					man.yes_no_callback = 0;
				}
			}
		}
		//
		else if (man.state == STATE_MENU)
			run_menu_cmd(&man, man.tokens);
		else if (man.state == STATE_GAME)
			run_game_cmd(&man, man.tokens);
		free_array((void **)man.tokens, free);
	}
	clear_window();
	return EXIT_SUCCESS;
}

void	open_menu(t_man *man)
{
	man->state = STATE_MENU;
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

void	initialize_game(t_man *man)
{
	populate_list_lexicon(man);
	populate_list_locations(man);
	populate_list_items(man);
	populate_list_characters(man);
	populate_list_events(man);
	return;
}

static void	set_utf8_encoding(void)
{
	#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	#endif
	return;
}
