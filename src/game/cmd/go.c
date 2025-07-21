#include "treasure_venture.h"

static void	go_inside(t_man *man);
static void	go_outside(t_man *man);
static void	go_back(t_man *man);
static void	go_out(t_man *man);
static void	go_tag(t_man *man);

static int	bool_access_locked(const t_exit *exit);
static void	print_access_locked(const t_exit *exit);
static int	bool_location_is_full(const t_location *location);
static void	print_location_is_full(void);

static void	cross_passage(t_man *man, t_exit *exit);
static void	output_text_for_passage_crossing(t_man *man, const t_exit* exit);

void	run_go(t_man *man)
{
	if (!man->characters[CHAR_PLAYER - 1].current_location->exits[0].to)
	{
		printf("There is nowhere to go.\n\n");
		return;
	}

	if (*man->cmd.object)
	{
		if (!strcmp(man->cmd.object, "inside"))
			go_inside(man);
		else if (!strcmp(man->cmd.object, "outside"))
			go_outside(man);
		else if (!strcmp(man->cmd.object, "back"))
			go_back(man);
		else if (!strcmp(man->cmd.object, "out"))
			go_out(man);
		else
			go_tag(man);
	}

	if (!*man->cmd.object)
		display_location_suggestions(man->characters[CHAR_PLAYER - 1].current_location);
	return;
}

static void	go_inside(t_man *man)
{
	if (man->characters[CHAR_PLAYER - 1].current_location->bool_is_indoors)
	{
		printf("You're already inside of a building.\n\n");
		memset(man->cmd.object, 0, sizeof(man->cmd.object));
		return;
	}

	if (bool_access_locked(man->characters[CHAR_PLAYER - 1].current_location->exits + 0))
		print_access_locked(man->characters[CHAR_PLAYER - 1].current_location->exits + 0);
	else if (bool_location_is_full(man->characters[CHAR_PLAYER - 1].current_location->exits[0].to))
		print_location_is_full();
	else
		cross_passage(man, man->characters[CHAR_PLAYER - 1].current_location->exits + 0);
	return;
}

static void	go_outside(t_man *man)
{
	int	i;
	int	j;
	int	outside_indexes[NBR_LOCATIONS];

	if (!man->characters[CHAR_PLAYER - 1].current_location->bool_is_indoors)
	{
		printf("You're already outside.\n\n");
		memset(man->cmd.object, 0, sizeof(man->cmd.object));
		return;
	}

	memset(outside_indexes, -1, sizeof(outside_indexes));
	for (i = 0, j = 0; i < NBR_LOCATIONS; ++i)
	{
		if (!man->characters[CHAR_PLAYER - 1].current_location->exits[i].to)
		{
			memset(man->cmd.object, 0, sizeof(man->cmd.object));
			break;
		}

		if (!man->characters[CHAR_PLAYER - 1].current_location->exits[i].to->bool_is_indoors)
			outside_indexes[j++] = i;
	}

	if (outside_indexes[0] < 0)
	{
		printf("No immediate exit leads outside of the building.\n\n");
		memset(man->cmd.object, 0, sizeof(man->cmd.object));
		return;
	}
	else if (outside_indexes[1] < 0)
	{
		if (bool_access_locked(man->characters[CHAR_PLAYER - 1].current_location->exits
			+ outside_indexes[0]))
			print_access_locked(man->characters[CHAR_PLAYER - 1].current_location->exits
			+ outside_indexes[0]);
		else if (bool_location_is_full(man->characters[CHAR_PLAYER - 1].current_location->exits
			[outside_indexes[0]].to))
			print_location_is_full();
		else
			cross_passage(man, man->characters[CHAR_PLAYER - 1].current_location->exits + outside_indexes[0]);
	}
	else
	{
		printf("Different exits lead outside. Specify the one you "
			"want.\n\n");
		memset(man->cmd.object, 0, sizeof(man->cmd.object));
		return;
	}
	return;
}

static void	go_back(t_man *man)
{
	int	i;

	if (!man->characters[CHAR_PLAYER - 1].previous_location)
	{
		printf("You do not have a previous location.\n\n");
		memset(man->cmd.object, 0, sizeof(man->cmd.object));
		return;
	}

	for (i = 0; i < NBR_LOCATIONS; ++i)
	{
		if (!man->characters[CHAR_PLAYER - 1].current_location->exits[i].to)
		{
			printf("Your previous location cannot be accessed.\n\n");
			memset(man->cmd.object, 0, sizeof(man->cmd.object));
			return;
		}
		else if (man->characters[CHAR_PLAYER - 1].previous_location
			== man->characters[CHAR_PLAYER - 1].current_location->exits[i].to)
			break;
	}

	if (bool_access_locked(man->characters[CHAR_PLAYER - 1].current_location->exits + i))
		print_access_locked(man->characters[CHAR_PLAYER - 1].current_location->exits + i);
	else if (bool_location_is_full(man->characters[CHAR_PLAYER - 1].previous_location))
		print_location_is_full();
	else
		cross_passage(man, man->characters[CHAR_PLAYER - 1].current_location->exits + i);
	return;
}

static void	go_out(t_man *man)
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

	if (!man->characters[CHAR_PLAYER - 1].current_location->bool_is_indoors)
	{
		printf("You are already outside.\n\n");
		memset(man->cmd.object, 0, sizeof(man->cmd.object));
		return;
	}

	for (i = 0, j = 0, k = 0, l = 0, m = 0; i < NBR_LOCATIONS; ++i)
	{
		if (!man->characters[CHAR_PLAYER - 1].current_location->exits[i].to)
			break;
		else if (!man->characters[CHAR_PLAYER - 1].current_location->exits[i].to->bool_is_indoors)
		{
			if (man->characters[CHAR_PLAYER - 1].current_location->exits[i].passage->access
				!= ACCESS_LOCKED)
				to_outside_and_accessible[j++]
					= &(man->characters[CHAR_PLAYER - 1].current_location->exits[i]);
			else
				to_outside_but_locked[k++]
					= &(man->characters[CHAR_PLAYER - 1].current_location->exits[i]);
		}
		else
		{
			if (man->characters[CHAR_PLAYER - 1].current_location->exits[i].passage->access
				!= ACCESS_LOCKED)
				other_and_accessible[l++]
					= &(man->characters[CHAR_PLAYER - 1].current_location->exits[i]);
			else
				other_but_locked[m++] = &(man->characters[CHAR_PLAYER - 1].current_location->exits[i]);
		}
	}

	if (j)
	{
		if (j == 1)
		{
			cross_passage(man, to_outside_and_accessible[0]);
			return;
		}
	}
	else if (k)
	{
		if (k == 1)
		{
			print_access_locked(to_outside_but_locked[0]);
			memset(man->cmd.object, 0, sizeof(man->cmd.object));
			return;
		}
	}
	else if (l)
	{
		if (l == 1)
		{
			cross_passage(man, other_and_accessible[0]);
			return;
		}
	}
	else if (m)
	{
		if (m == 1)
		{
			print_access_locked(other_but_locked[0]);
			memset(man->cmd.object, 0, sizeof(man->cmd.object));
			return;
		}
	}

	printf("There is more than one exit. Which one do you want?\n\n");
	memset(man->cmd.object, 0, sizeof(man->cmd.object));
	return;
}

static void	go_tag(t_man *man)
{
	int		bool_tag_is_passage_item;
	t_exit	**locations;

	bool_tag_is_passage_item = 0;
	locations = 0;
	locations = retrieve_locations(man->characters[CHAR_PLAYER - 1].current_location, man->cmd.object);
	if (!locations || !locations[0])
	{
		locations = retrieve_locations_with_passage_item
			(man->characters[CHAR_PLAYER - 1].current_location, man->cmd.object);
		if (!locations || !locations[0])
		{
			memset(man->cmd.object, 0, sizeof(man->cmd.object));
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
			cross_passage(man, locations[0]);
	}
	else if (bool_tag_is_passage_item)
	{
		printf("There is more than one passage item in your vicinity for "
			"which this tag works.\n");
		memset(man->cmd.object, 0, sizeof(man->cmd.object));
	}
	else
	{
		printf("There is more than one destination from your current "
			"location for which this tag works.\n");
		memset(man->cmd.object, 0, sizeof(man->cmd.object));
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
	printf("The %s %s locked.\n\n",
		exit->passage->bool_is_singular ? "door"
		: "doors", exit->passage->bool_is_singular ? "is" : "are");
	return;
}

static int	bool_location_is_full(const t_location *location)
{
	return !!location->characters[NBR_CHARACTERS - 1];
}

static void	print_location_is_full(void)
{
	printf("The destination is full. No more characters can access this "
		"place.\n\n");
	return;
}

static void	cross_passage(t_man *man, t_exit *exit)
{
	int	i;
	int	index_last_char;

	index_last_char = -1;
	output_text_for_passage_crossing(man, exit);

	if (exit->passage->access == ACCESS_CLOSED)
		exit->passage->access = ACCESS_OPEN;

	man->characters[CHAR_PLAYER - 1].previous_location = man->characters[CHAR_PLAYER - 1].current_location;
	man->characters[CHAR_PLAYER - 1].current_location = exit->to;

	for (i = NBR_CHARACTERS - 1; i >= 0; --i)
	{
		if (!man->characters[CHAR_PLAYER - 1].previous_location->characters[i])
			continue;

		if (index_last_char < 0)
			index_last_char = i;

		if (man->characters[CHAR_PLAYER - 1].previous_location->characters[i] == &man->characters[CHAR_PLAYER - 1])
		{
			man->characters[CHAR_PLAYER - 1].previous_location->characters[i]
				= man->characters[CHAR_PLAYER - 1].previous_location->characters[index_last_char];
			memset(man->characters[CHAR_PLAYER - 1].previous_location->characters + index_last_char, 0,
				sizeof(t_character*));
			break;
		}
	}

	for (i = 0; i < NBR_CHARACTERS; ++i)
	{
		if (!man->characters[CHAR_PLAYER - 1].current_location->characters[i])
		{
			man->characters[CHAR_PLAYER - 1].current_location->characters[i] = &man->characters[CHAR_PLAYER - 1];
			break;
		}
	}

	event_first_time_player_enters_mansion(man);
	return;
}

static void	output_text_for_passage_crossing(t_man *man, const t_exit* exit)
{
	if (exit->passage->access == ACCESS_CLOSED)
	{
		printf("You open the door%s and ",
			exit->passage->bool_is_singular ? "" : "s");
	}
	else
	{
		printf("You ");
	}

	if (man->characters[CHAR_PLAYER - 1].current_location->geo_aff->id != exit->to->geo_aff->id)
	{
		if (man->characters[CHAR_PLAYER - 1].current_location->bool_is_indoors)
			printf("leave the %s. ",
				man->characters[CHAR_PLAYER - 1].current_location->geo_aff->name);
		else
			printf("cross the %s's threshold to find yourself in the %s. ",
				exit->to->geo_aff->name, exit->to->tags[0]);
	}
	else
	{
		printf("enter the %s. ", exit->to->tags[0]);
	}

	printf("\n\n");
	return;
}
