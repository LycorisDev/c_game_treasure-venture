#include "save.h"
#include "characters.h"

void	save_game(int fd_save)
{
	int	i;

	dprintf(fd_save, "previous_location:%d\n", !PLAYER->previous_location ? -1 : PLAYER->previous_location->id);
	dprintf(fd_save, "current_location:%d\n", PLAYER->current_location->id);

	dprintf(fd_save, "events:");
	for (i = 0; i < NBR_EVENTS; ++i)
	{
		if (!i)
			dprintf(fd_save, "%d", g_list_events[i]);
		else
			dprintf(fd_save, ",%d", g_list_events[i]);
	}
	dprintf(fd_save, "\n");

	dprintf(fd_save, "inventory:");
	for (i = 0; i < NBR_ITEMS; ++i)
	{
		if (!PLAYER->inventory[i])
			break;

		if (!i)
			dprintf(fd_save, "%d", PLAYER->inventory[i]->id);
		else
			dprintf(fd_save, ",%d", PLAYER->inventory[i]->id);
	}
	dprintf(fd_save, "\n");

	return;
}
