#include "treasure_venture.h"

static void	save_loc(t_man *man, FILE *save_file);
static void	save_events(t_man *man, FILE *save_file);
static void	save_inventory(t_man *man, FILE *save_file);

int	save_game(t_man *man, const char *filepath)
{
	FILE	*save_file;

	save_file = fopen(filepath, "w");
	if (!save_file)
	{
		fprintf(stderr, "\t[Error: Couldn't create %s as save file]\n\n",
			filepath);
		return (0);
	}
	save_loc(man, save_file);
	save_events(man, save_file);
	save_inventory(man, save_file);
	fclose(save_file);
	return (1);
}

static void	save_loc(t_man *man, FILE *save_file)
{
	fprintf(save_file, "previous_location:%d\n",
		!man->charas[0].previous_loc ? 0 : man->charas[0].previous_loc->id);
	fprintf(save_file, "current_location:%d\n",
		!man->charas[0].current_loc ? 0 : man->charas[0].current_loc->id);
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
		if (!man->charas[0].inventory[i])
			break ;
		if (!i)
			fprintf(save_file, "%d",
				man->charas[0].inventory[i]->id);
		else
			fprintf(save_file, ",%d",
				man->charas[0].inventory[i]->id);
	}
	fprintf(save_file, "\n");
	return ;
}
