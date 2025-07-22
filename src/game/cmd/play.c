#include "treasure_venture.h"
#include "plugin.h"

#if defined _WIN64
# define LIB_PATH_20SQ "plugin/20SQ/libts64.dll"
#elif defined _WIN32
# define LIB_PATH_20SQ "plugin/20SQ/libts32.dll"
#else
# define LIB_PATH_20SQ "plugin/20SQ/libts.so"
#endif

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
		run_plugin(LIB_PATH_20SQ, "Twenty Squares");
	describe_location(man, man->characters[CHAR_PLAYER - 1].current_location);
	return;
}
