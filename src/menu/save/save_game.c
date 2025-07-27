#include "treasure_venture.h"

static void	save_location(t_man *man, FILE *save_file);
static void	save_events(t_man *man, FILE *save_file);
static void	save_inventory(t_man *man, FILE *save_file);

int	save_game(t_man *man, const char *filepath)
{
	FILE	*save_file;

	save_file = fopen(filepath, "w");
	if (!save_file)
		return (0);
	save_location(man, save_file);
	save_events(man, save_file);
	save_inventory(man, save_file);
	fclose(save_file);
	return (1);
}

static void	save_location(t_man *man, FILE *save_file)
{
	fprintf(save_file, "previous_location:%d\n",
		man->characters[CHAR_PLAYER - 1].previous_location->id);
	fprintf(save_file, "current_location:%d\n",
		man->characters[CHAR_PLAYER - 1].current_location->id);
	return ;
}

static void	save_events(t_man *man, FILE *save_file)
{
	int	i;

	fprintf(save_file, "events:");
	i = -1;
	while (++i < NBR_EVENTS)
	{
		if (!i)
			fprintf(save_file, "%d", man->events[i]);
		else
			fprintf(save_file, ",%d", man->events[i]);
	}
	fprintf(save_file, "\n");
	return ;
}

static void	save_inventory(t_man *man, FILE *save_file)
{
	int	i;

	fprintf(save_file, "inventory:");
	i = -1;
	while (++i < NBR_ITEMS)
	{
		if (!man->characters[CHAR_PLAYER - 1].inventory[i])
			break ;
		if (!i)
			fprintf(save_file, "%d",
				man->characters[CHAR_PLAYER - 1].inventory[i]->id);
		else
			fprintf(save_file, ",%d",
				man->characters[CHAR_PLAYER - 1].inventory[i]->id);
	}
	fprintf(save_file, "\n");
	return ;
}
