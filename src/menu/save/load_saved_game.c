#include "treasure_venture.h"

static int	set_id_loc_val(char *line, t_id_loc *id);
static int	set_int_arr(char *line, int *arr, size_t max_len);
static int	set_id_item_arr(char *line, t_id_item *arr, size_t max_len);
static void	move_player_to_location(t_man *man, t_id_loc prev, t_id_loc curr);
static void	apply_events(t_man *man, int events[NBR_EVENTS]);
static void	populate_inventory(t_man *man, t_id_item inventory[NBR_ITEMS]);

int	load_saved_game(t_man *man, const char *filepath)
{
	char		**lines;
	t_id_loc	id_loc_prev;
	t_id_loc	id_loc_curr;
	int			events[NBR_EVENTS];
	t_id_item	inventory[NBR_ITEMS];

	lines = read_file(filepath);
	if (!lines)
		return (0);
	if (!lines[0] || strncmp(lines[0], "previous_location:", 18)
		|| !set_id_loc_val(lines[0], &id_loc_prev))
		return (free_arr((void **)lines, free), 0);
	if (!lines[1] || strncmp(lines[1], "current_location:", 17)
		|| !set_id_loc_val(lines[1], &id_loc_curr))
		return (free_arr((void **)lines, free), 0);
	if (!lines[2] || strncmp(lines[2], "events:", 7)
		|| !set_int_arr(lines[2], events, NBR_EVENTS))
		return (free_arr((void **)lines, free), 0);
	int i = -1;
	while (++i < NBR_EVENTS && events[i] < 2);
	if (i < NBR_EVENTS)
		return (free_arr((void **)lines, free), 0);
	if (!lines[3] || strncmp(lines[3], "inventory:", 10)
		|| !set_id_item_arr(lines[3], inventory, NBR_ITEMS))
		return (free_arr((void **)lines, free), 0);
	free_arr((void **)lines, free);
	move_player_to_location(man, id_loc_prev, id_loc_curr);
	apply_events(man, events);
	populate_inventory(man, inventory);
	return (1);
}

static int	set_id_loc_val(char *line, t_id_loc *id)
{
	size_t	i;
	char	*ptr_val;
	char	**val;

	*id = 0;
	ptr_val = strchr(line, ':') + 1;
	if (!ptr_val)
		return (0);
	i = 0;
	while (ptr_val[i])
	{
		if (isspace(ptr_val[i]) || ptr_val[i] == ',')
			ptr_val[i] = FS;
		++i;
	}
	val = split(ptr_val, FS);
	if (count_arr((void **)val) == 1)
		*id = atoi(val[0]) - 1;
	free_arr((void **)val, free);
	return (*id >= 0);
}

static int	set_int_arr(char *line, int *arr, size_t max_len)
{
	size_t	i;
	char	*ptr_val;
	char	**val;

	memset(arr, 0, max_len * sizeof(int));
	ptr_val = strchr(line, ':') + 1;
	if (!ptr_val)
		return (0);
	i = 0;
	while (ptr_val[i])
	{
		if (isspace(ptr_val[i]) || ptr_val[i] == ',')
			ptr_val[i] = FS;
		++i;
	}
	val = split(ptr_val, FS);
	if (!val || count_arr((void **)val) > max_len)
		return (free_arr((void **)val, free), 0);
	i = 0;
	while (val[i] && i < max_len)
	{
		arr[i] = atoi(val[i]);
		if (arr[i] < 0 || (!arr[i] && strcmp(val[i], "0")))
			return (free_arr((void **)val, free), 0);
		++i;
	}
	return (free_arr((void **)val, free), 1);
}

static int	set_id_item_arr(char *line, t_id_item *arr, size_t max_len)
{
	size_t	i;
	char	*ptr_val;
	char	**val;

	memset(arr, 0, max_len * sizeof(int));
	ptr_val = strchr(line, ':') + 1;
	i = 0;
	while (ptr_val[i])
	{
		if (isspace(ptr_val[i]) || ptr_val[i] == ',')
			ptr_val[i] = FS;
		++i;
	}
	val = split(ptr_val, FS);
	if (!val || count_arr((void **)val) > max_len)
		return (free_arr((void **)val, free), 0);
	i = 0;
	while (val[i] && i < max_len)
	{
		arr[i] = atoi(val[i]);
		if (arr[i] < 0 || (!arr[i] && strcmp(val[i], "0")))
			return (free_arr((void **)val, free), 0);
		--arr[i];
		++i;
	}
	return (free_arr((void **)val, free), 1);
}

static void	move_player_to_location(t_man *man, t_id_loc prev, t_id_loc curr)
{
	int	i;
	int	j;

	man->characters[CHAR_PLAYER - 1].previous_location = man->locations + prev;
	man->characters[CHAR_PLAYER - 1].current_location = man->locations + curr;
	if (man->characters[CHAR_PLAYER - 1].current_location->id == LOC_OUTSIDE)
		return ;
	// Remove player from player's starter location (LOC_OUTSIDE)
	i = -1;
	while (++i < NBR_CHARACTERS)
	{
		if (!man->locations[LOC_OUTSIDE - 1].characters[i])
			break ;
		if (man->locations[LOC_OUTSIDE - 1].characters[i]
			== &man->characters[CHAR_PLAYER - 1])
		{
			j = NBR_CHARACTERS;
			while (--j >= 0)
			{
				if (man->locations[LOC_OUTSIDE - 1].characters[j])
				{
					man->locations[LOC_OUTSIDE - 1].characters[i]
						= man->locations[LOC_OUTSIDE - 1].characters[j];
					memset(man->locations[LOC_OUTSIDE - 1].characters + j, 0,
						sizeof(t_character *));
					i = NBR_CHARACTERS;
					break ;
				}
			}
		}
	}
	// Add the player to the current location
	i = -1;
	while (++i < NBR_CHARACTERS)
	{
		if (!man->characters[CHAR_PLAYER - 1].current_location->characters[i])
		{
			man->characters[CHAR_PLAYER - 1].current_location->characters[i]
				= &man->characters[CHAR_PLAYER - 1];
			break ;
		}
	}
	return ;
}

static void	apply_events(t_man *man, int events[NBR_EVENTS])
{
	if (events[0] == 0)
		run_event_first_time_player_enters_mansion(man);
	if (events[1] == 0)
		run_event_player_finds_entry_doors_key(man);
	return ;
}

static void	populate_inventory(t_man *man, t_id_item inventory[NBR_ITEMS])
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (++i < NBR_ITEMS)
	{
		if (inventory[i] == ITEM_NONE || j == NBR_ITEMS)
			break ;
		man->characters[CHAR_PLAYER - 1].inventory[j++] = man->items + inventory[i];
		// Search the item in all the locations, and remove it from the world:
		// - This feature wasn't even present, duplicating the items.
		// - I'll wait for the game's refactoring before touching this again.
	}
	return ;
}
