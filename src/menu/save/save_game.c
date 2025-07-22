#include "treasure_venture.h"

static void	save_location(t_man *man, int fd_save);
static void	save_events(t_man *man, int fd_save);
static void	save_inventory(t_man *man, int fd_save);

int	save_game(t_man *man, const char *filepath)
{
	int	fd_save;

	fd_save = open(filepath, O_CREAT | O_RDWR, 0664);
	if (fd_save < 0)
		return (0);
	save_location(man, fd_save);
	save_events(man, fd_save);
	save_inventory(man, fd_save);
	close(fd_save);
	return (1);
}

static void	save_location(t_man *man, int fd_save)
{
	dprintf(fd_save, "previous_location:%d\n",
		man->characters[CHAR_PLAYER - 1].previous_location->id);
	dprintf(fd_save, "current_location:%d\n",
		man->characters[CHAR_PLAYER - 1].current_location->id);
	return ;
}

static void	save_events(t_man *man, int fd_save)
{
	int	i;

	dprintf(fd_save, "events:");
	i = -1;
	while (++i < NBR_EVENTS)
	{
		if (!i)
			dprintf(fd_save, "%d", man->events[i]);
		else
			dprintf(fd_save, ",%d", man->events[i]);
	}
	dprintf(fd_save, "\n");
	return ;
}

static void	save_inventory(t_man *man, int fd_save)
{
	int	i;

	dprintf(fd_save, "inventory:");
	i = -1;
	while (++i < NBR_ITEMS)
	{
		if (!man->characters[CHAR_PLAYER - 1].inventory[i])
			break ;
		if (!i)
			dprintf(fd_save, "%d",
				man->characters[CHAR_PLAYER - 1].inventory[i]->id);
		else
			dprintf(fd_save, ",%d",
				man->characters[CHAR_PLAYER - 1].inventory[i]->id);
	}
	dprintf(fd_save, "\n");
	return ;
}
