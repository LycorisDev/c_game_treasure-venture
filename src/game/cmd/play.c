#include "treasure_venture.h"
#include "minigame.h"

static void	static_mini_game(void);
/* static void	dynamic_mini_game(void); */

void	run_play(t_man *man)
{
	int	i;

	for (i = 0; i < NBR_CHARACTERS; ++i)
	{
		if (!man->characters[CHAR_PLAYER - 1].current_location->characters[i])
		{
			printf("You see no one around you to play with.\n\n");
			return;
		}
		if (man->characters[CHAR_PLAYER - 1].current_location->characters[i] == &man->characters[CHAR_PLAYER - 1])
			continue;
		break;
	}
	printf("\t[Do you want to play Twenty Squares with the %s? Yes/No]\n\n",
		man->characters[CHAR_PLAYER - 1].current_location->characters[i]->tags[1]);
	if (ask_yes_no())
		static_mini_game();
	describe_location(man, man->characters[CHAR_PLAYER - 1].current_location);
	return;
}

static void	static_mini_game(void)
{
	start_twenty_squares();
	return;
}

/*
static void	dynamic_mini_game(void)
{
	LIB_HANDLE	mini_game_obj = 0;
	int			(*mini_game_func)() = 0;

	mini_game_obj = LOAD_LIB(LIB_PATH_20SQ);
	if (!mini_game_obj)
	{
		printf("\t[Error: The Twenty Squares library can't be loaded -> %s]\n",
				LIB_ERROR);
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
		printf("\t[Error: The pointer to the Twenty Squares library start "
				"function can't be obtained -> %s]\n", LIB_ERROR);
		UNLOAD_LIB(mini_game_obj);
		return;
	}
	(*mini_game_func)();
	UNLOAD_LIB(mini_game_obj);
	return;
}
*/
