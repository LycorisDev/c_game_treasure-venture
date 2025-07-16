#include "main.h"
#include "misc.h"
#include "events.h"
#include "commands.h"
#include "locations.h"
#include "items.h"

static void	go_inside(void);
static void	go_outside(void);
static void	go_back(void);
static void	go_out(void);
static void	go_tag(void);

static int	bool_access_locked(const t_exit *exit);
static void	print_access_locked(const t_exit *exit);
static int	bool_location_is_full(const t_location *location);
static void	print_location_is_full(void);

static void	cross_passage(t_exit *exit);
static void	output_text_for_passage_crossing(const t_exit *exit);

void	execute_go(void)
{
	if (!PLAYER->current_location->exits[0].to)
	{
		add_output("There is nowhere to go.\n\n");
		return;
	}

	if (*g_cmd.object)
	{
		if (!strcmp(g_cmd.object, "inside"))
			go_inside();
		else if (!strcmp(g_cmd.object, "outside"))
			go_outside();
		else if (!strcmp(g_cmd.object, "back"))
			go_back();
		else if (!strcmp(g_cmd.object, "out"))
			go_out();
		else
			go_tag();
	}

	if (!*g_cmd.object)
		display_location_suggestions(PLAYER->current_location);
	return;
}

static void	go_inside(void)
{
	if (PLAYER->current_location->bool_is_indoors)
	{
		add_output("You're already inside of a building.\n\n");
		memset(g_cmd.object, 0, sizeof(g_cmd.object));
		return;
	}

	if (bool_access_locked(PLAYER->current_location->exits + 0))
		print_access_locked(PLAYER->current_location->exits + 0);
	else if (bool_location_is_full(PLAYER->current_location->exits[0].to))
		print_location_is_full();
	else
		cross_passage(PLAYER->current_location->exits + 0);
	return;
}

static void	go_outside(void)
{
	int	i;
	int	j;
	int	outside_indexes[NBR_LOCATIONS];

	if (!PLAYER->current_location->bool_is_indoors)
	{
		add_output("You're already outside.\n\n");
		memset(g_cmd.object, 0, sizeof(g_cmd.object));
		return;
	}

	memset(outside_indexes, -1, sizeof(outside_indexes));
	for (i = 0, j = 0; i < NBR_LOCATIONS; ++i)
	{
		if (!PLAYER->current_location->exits[i].to)
		{
			memset(g_cmd.object, 0, sizeof(g_cmd.object));
			break;
		}

		if (!PLAYER->current_location->exits[i].to->bool_is_indoors)
			outside_indexes[j++] = i;
	}

	if (outside_indexes[0] < 0)
	{
		add_output("No immediate exit leads outside of the building.\n\n");
		memset(g_cmd.object, 0, sizeof(g_cmd.object));
		return;
	}
	else if (outside_indexes[1] < 0)
	{
		if (bool_access_locked(PLAYER->current_location->exits + outside_indexes[0]))
			print_access_locked(PLAYER->current_location->exits + outside_indexes[0]);
		else if (bool_location_is_full(PLAYER->current_location->exits[outside_indexes[0]].to))
			print_location_is_full();
		else
			cross_passage(PLAYER->current_location->exits + outside_indexes[0]);
	}
	else
	{
		add_output("Different exits lead outside. Specify the one you want.\n\n");
		memset(g_cmd.object, 0, sizeof(g_cmd.object));
		return;
	}
	return;
}

static void	go_back(void)
{
	int	i;

	if (!PLAYER->previous_location)
	{
		add_output("You do not have a previous location.\n\n");
		memset(g_cmd.object, 0, sizeof(g_cmd.object));
		return;
	}

	for (i = 0; i < NBR_LOCATIONS; ++i)
	{
		if (!PLAYER->current_location->exits[i].to)
		{
			add_output("Your previous location cannot be accessed.\n\n");
			memset(g_cmd.object, 0, sizeof(g_cmd.object));
			return;
		}
		else if (PLAYER->previous_location == PLAYER->current_location->exits[i].to)
			break;
	}

	if (bool_access_locked(PLAYER->current_location->exits + i))
		print_access_locked(PLAYER->current_location->exits + i);
	else if (bool_location_is_full(PLAYER->previous_location))
		print_location_is_full();
	else
		cross_passage(PLAYER->current_location->exits + i);
	return;
}

static void	go_out(void)
{
	int		i;
	int		j;
	int		k;
	int		l;
	int		m;
	t_exit	*to_outside_and_accessible[NBR_LOCATIONS] = {0};
	t_exit	*to_outside_but_locked[NBR_LOCATIONS] = {0};
	t_exit	*other_and_accessible[NBR_LOCATIONS] = {0};
	t_exit	*other_but_locked[NBR_LOCATIONS] = {0};

	if (!PLAYER->current_location->bool_is_indoors)
	{
		add_output("You are already outside.\n\n");
		memset(g_cmd.object, 0, sizeof(g_cmd.object));
		return;
	}

	for (i = 0, j = 0, k = 0, l = 0, m = 0; i < NBR_LOCATIONS; ++i)
	{
		if (!PLAYER->current_location->exits[i].to)
			break;
		else if (!PLAYER->current_location->exits[i].to->bool_is_indoors)
		{
			if (PLAYER->current_location->exits[i].passage->access != ACCESS_LOCKED)
				to_outside_and_accessible[j++] = &(PLAYER->current_location->exits[i]);
			else
				to_outside_but_locked[k++] = &(PLAYER->current_location->exits[i]);
		}
		else
		{
			if (PLAYER->current_location->exits[i].passage->access != ACCESS_LOCKED)
				other_and_accessible[l++] = &(PLAYER->current_location->exits[i]);
			else
				other_but_locked[m++] = &(PLAYER->current_location->exits[i]);
		}
	}

	if (j)
	{
		if (j == 1)
		{
			cross_passage(to_outside_and_accessible[0]);
			return;
		}
	}
	else if (k)
	{
		if (k == 1)
		{
			print_access_locked(to_outside_but_locked[0]);
			memset(g_cmd.object, 0, sizeof(g_cmd.object));
			return;
		}
	}
	else if (l)
	{
		if (l == 1)
		{
			cross_passage(other_and_accessible[0]);
			return;
		}
	}
	else if (m)
	{
		if (m == 1)
		{
			print_access_locked(other_but_locked[0]);
			memset(g_cmd.object, 0, sizeof(g_cmd.object));
			return;
		}
	}

	add_output("There is more than one exit. Which one do you want?\n\n");
	memset(g_cmd.object, 0, sizeof(g_cmd.object));
	return;
}

static void	go_tag(void)
{
	int		bool_tag_is_passage_item;
	t_exit	**locations;

	bool_tag_is_passage_item = 0;
	locations = 0;
	locations = retrieve_locations(PLAYER->current_location, g_cmd.object);
	if (!locations || !locations[0])
	{
		locations = retrieve_locations_with_passage_item(PLAYER->current_location, g_cmd.object);
		if (!locations || !locations[0])
		{
			memset(g_cmd.object, 0, sizeof(g_cmd.object));
			free(locations);
			return;
		}
		else
			bool_tag_is_passage_item = 1;
	}

	if (!locations[1])
	{
		if (bool_access_locked(locations[0]))
			print_access_locked(locations[0]);
		else if (bool_location_is_full(locations[0]->to))
			print_location_is_full();
		else
			cross_passage(locations[0]);
	}
	else if (bool_tag_is_passage_item)
	{
		add_output("There is more than one passage item in your vicinity for which this tag works.\n");
		memset(g_cmd.object, 0, sizeof(g_cmd.object));
	}
	else
	{
		add_output("There is more than one destination from your current location for which this tag works.\n");
		memset(g_cmd.object, 0, sizeof(g_cmd.object));
	}

	free(locations);
	return;
}

static int	bool_access_locked(const t_exit *exit)
{
	return exit->passage->access == ACCESS_LOCKED;
}

static void	print_access_locked(const t_exit *exit)
{
	add_output("The %s %s locked.\n\n", exit->passage->bool_is_singular ? "door" : "doors", exit->passage->bool_is_singular ? "is" : "are");
	return;
}

static int	bool_location_is_full(const t_location *location)
{
	return !!location->characters[NBR_CHARACTERS - 1];
}

static void	print_location_is_full(void)
{
	add_output("The destination is full. No more characters can access this place.\n\n");
	return;
}

static void	cross_passage(t_exit *exit)
{
	int	i;
	int	index_last_char;

	index_last_char = -1;
	output_text_for_passage_crossing(exit);

	if (exit->passage->access == ACCESS_CLOSED)
		exit->passage->access = ACCESS_OPEN;

	PLAYER->previous_location = PLAYER->current_location;
	PLAYER->current_location = exit->to;

	for (i = NBR_CHARACTERS - 1; i >= 0; --i)
	{
		if (!PLAYER->previous_location->characters[i])
			continue;

		if (index_last_char < 0)
			index_last_char = i;

		if (PLAYER->previous_location->characters[i] == PLAYER)
		{
			PLAYER->previous_location->characters[i] = PLAYER->previous_location->characters[index_last_char];
			memset((PLAYER->previous_location->characters + index_last_char), 0, sizeof(t_character*));
			break;
		}
	}

	for (i = 0; i < NBR_CHARACTERS; ++i)
	{
		if (!PLAYER->current_location->characters[i])
		{
			PLAYER->current_location->characters[i] = PLAYER;
			break;
		}
	}

	event_first_time_player_enters_mansion();
	return;
}

static void	output_text_for_passage_crossing(const t_exit* exit)
{
	if (exit->passage->access == ACCESS_CLOSED)
	{
		add_output("You open the door%s and ", exit->passage->bool_is_singular ? "" : "s");
	}
	else
	{
		add_output("You ");
	}

	if (PLAYER->current_location->geo_aff->id != exit->to->geo_aff->id)
	{
		if (PLAYER->current_location->bool_is_indoors)
			add_output("leave the %s. ", PLAYER->current_location->geo_aff->name);
		else
			add_output("cross the %s's threshold to find yourself in the %s. ", exit->to->geo_aff->name, exit->to->tags[0]);
	}
	else
	{
		add_output("enter the %s. ", exit->to->tags[0]);
	}

	add_output("\n\n");
	return;
}
