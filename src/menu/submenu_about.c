#include "treasure_venture.h"

void	run_submenu_about(t_man *man)
{
	printf("\t[Visit the Itch.io page:]\n\t"
		"https://lycorisdev.itch.io/treasure-venture\n\n");
	if (man->state == STATE_GAME)
		describe_location(man,
			man->characters[CHAR_PLAYER - 1].current_location);
	return ;
}
