#include "treasure_venture.h"
#include "plugin.h"

#if defined _WIN64
# define LIB_PATH_20SQ "plugin/20SQ/lib20SQ64.dll"
#elif defined _WIN32
# define LIB_PATH_20SQ "plugin/20SQ/lib20SQ32.dll"
#else
# define LIB_PATH_20SQ "plugin/20SQ/lib20SQ.so"
#endif

void	run_play(t_man *man)
{
	int	i;

	for (i = 0; i < NBR_CHARAS; ++i)
	{
		if (!man->charas[0].current_loc->charas[i])
		{
			printf("You see no one around you to play with.\n\n");
			return;
		}
		if (man->charas[0].current_loc->charas[i] == &man->charas[0])
			continue;
		break;
	}
	printf("\t[Do you want to play Twenty Squares with the %s? Yes/No]\n\n",
		man->charas[0].current_loc->charas[i]->tags[1]);
	if (ask_yes_no())
		run_plugin(LIB_PATH_20SQ, "Twenty Squares");
	describe_loc(man, man->charas[0].current_loc);
	return;
}
