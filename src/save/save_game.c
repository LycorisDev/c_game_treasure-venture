#include "treasure_venture.h"

void	save_game(t_man *man, int fd_save)
{
	int	i;

	dprintf(fd_save, "previous_location:%d\n",
		!man->characters[CHAR_PLAYER - 1].previous_location ? LOC_NONE : man->characters[CHAR_PLAYER - 1].previous_location->id);
	dprintf(fd_save, "current_location:%d\n", man->characters[CHAR_PLAYER - 1].current_location->id);

	dprintf(fd_save, "events:");
	for (i = 0; i < NBR_EVENTS; ++i)
	{
		if (!i)
			dprintf(fd_save, "%d", man->events[i]);
		else
			dprintf(fd_save, ",%d", man->events[i]);
	}
	dprintf(fd_save, "\n");

	dprintf(fd_save, "inventory:");
	for (i = 0; i < NBR_ITEMS; ++i)
	{
		if (!man->characters[CHAR_PLAYER - 1].inventory[i])
			break;

		if (!i)
			dprintf(fd_save, "%d", man->characters[CHAR_PLAYER - 1].inventory[i]->id);
		else
			dprintf(fd_save, ",%d", man->characters[CHAR_PLAYER - 1].inventory[i]->id);
	}
	dprintf(fd_save, "\n");

	return;
}
