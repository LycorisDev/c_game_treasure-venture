#include "main.h"
#include "parser.h"
#include "start.h"
#include "characters.h"
#include "events.h"
#include "items.h"
#include "lexicon.h"
#include "locations.h"
#include "commands.h"

t_game_state		g_state = STATE_NONE;
t_cmd				g_cmd;
t_character			g_list_characters[NBR_CHARACTERS];
int					g_list_events[NBR_EVENTS];
t_item				g_list_items[NBR_ITEMS];
char				g_list_lexicon[NBR_WORDS][LENGTH_WORD];

t_location			g_list_locations[NBR_LOCATIONS];
t_geo_aff			g_list_geo_aff[NBR_GEO_AFF];

char				g_parser[PARSER_NBR_WORDS][LENGTH_WORD];
int					g_nbr_words_in_parser;
yes_no_callback_t	g_yes_no_callback = 0;

/* -------------------------------------------------------------------------- */

static void	set_utf8_encoding(void);

int	main(void)
{
	set_utf8_encoding();
	access_main_menu();
	while (g_state != STATE_NONE)
	{
		get_and_parse_input();
		interact();
	}
	clear_window();
	return EXIT_SUCCESS;
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

static void	set_utf8_encoding(void)
{
	#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	#endif
	return;
}
