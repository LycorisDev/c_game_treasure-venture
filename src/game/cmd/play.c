#include "treasure_venture.h"
#include "minigame.h"

static void	static_mini_game(const int yes_no);
/* static void	dynamic_mini_game(int yes_no); */

void	run_play(void)
{
	int	i;

	for (i = 0; i < NBR_CHARACTERS; ++i)
	{
		if (!PLAYER->current_location->characters[i])
		{
			printf("You see no one around you to play with.\n\n");
			return;
		}
		if (PLAYER->current_location->characters[i] == PLAYER)
			continue;
		break;
	}
	printf("\t[Do you want to play Twenty Squares with the %s? Yes/No]\n\n",
		PLAYER->current_location->characters[i]->tags[1]);
	g_man.yes_no_callback = &static_mini_game;
	describe_location(PLAYER->current_location);
	return;
}

static void	static_mini_game(const int yes_no)
{
	if (yes_no)
		start_twenty_squares();
	return;
}

/*
static void	dynamic_mini_game(int yes_no)
{
	LIB_HANDLE	mini_game_obj = 0;
	int			(*mini_game_func)() = 0;

	if (yes_no)
	{
		mini_game_obj = LOAD_LIB(LIB_PATH_20SQ);
		if (!mini_game_obj)
		{
			printf("\t[Error: The Twenty Squares library can't be loaded "
				"-> %s]\n", LIB_ERROR);
			return;
		}

		#ifdef _WIN32
		# pragma GCC diagnostic push
		# pragma GCC diagnostic ignored "-Wpedantic"
		#endif
		*(void **) (&mini_game_func) = LIB_FUNC(mini_game_obj,
			"start_twenty_squares");
		#ifdef _WIN32
		# pragma GCC diagnostic pop
		#endif
		if (!mini_game_func)
		{
			printf("\t[Error: The pointer to the Twenty Squares library "
				"start function can't be obtained -> %s]\n", LIB_ERROR);
			UNLOAD_LIB(mini_game_obj);
			return;
		}

		(*mini_game_func)();

		UNLOAD_LIB(mini_game_obj);
	}
	return;
}
*/
