#include "treasure_venture.h"

static void	go_inside(t_man *man);
static void	go_outside(t_man *man);
static void	go_back(t_man *man);
static void	go_out(t_man *man);
static void	go_tag(t_man *man);

static int	bool_access_locked(const t_exit *exit);
static void	print_access_locked(const t_exit *exit);
static int	bool_loc_is_full(const t_loc *loc);
static void	print_loc_is_full(void);

static void	cross_passage(t_man *man, t_exit *exit);
static void	output_text_for_passage_crossing(t_man *man, const t_exit* exit);

void	run_go(t_man *man)
{
	if (!man->charas[0].current_loc->exits[0].to)
	{
		printf("There is nowhere to go.\n\n");
		return;
	}

	if (man->cmd.object)
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

	if (!man->cmd.object)
		display_loc_suggestions(man->charas[0].current_loc);
	return;
}

static void	go_inside(t_man *man)
{
	if (man->charas[0].current_loc->bool_is_indoors)
	{
		printf("You're already inside of a building.\n\n");
		free(man->cmd.object);
		man->cmd.object = 0;
		return;
	}

	if (bool_access_locked(man->charas[0].current_loc->exits + 0))
		print_access_locked(man->charas[0].current_loc->exits + 0);
	else if (bool_loc_is_full(man->charas[0].current_loc->exits[0].to))
		print_loc_is_full();
	else
		cross_passage(man, man->charas[0].current_loc->exits + 0);
	return;
}

static void	go_outside(t_man *man)
{
	int	i;
	int	j;
	int	outside_indexes[NBR_LOCS];

	if (!man->charas[0].current_loc->bool_is_indoors)
	{
		printf("You're already outside.\n\n");
		free(man->cmd.object);
		man->cmd.object = 0;
		return;
	}

	memset(outside_indexes, -1, sizeof(outside_indexes));
	for (i = 0, j = 0; i < NBR_LOCS; ++i)
	{
		if (!man->charas[0].current_loc->exits[i].to)
		{
			free(man->cmd.object);
			man->cmd.object = 0;
			break;
		}

		if (!man->charas[0].current_loc->exits[i].to->bool_is_indoors)
			outside_indexes[j++] = i;
	}

	if (outside_indexes[0] < 0)
	{
		printf("No immediate exit leads outside of the building.\n\n");
		free(man->cmd.object);
		man->cmd.object = 0;
		return;
	}
	else if (outside_indexes[1] < 0)
	{
		if (bool_access_locked(man->charas[0].current_loc->exits
			+ outside_indexes[0]))
			print_access_locked(man->charas[0].current_loc->exits
			+ outside_indexes[0]);
		else if (bool_loc_is_full(man->charas[0].current_loc->exits
			[outside_indexes[0]].to))
			print_loc_is_full();
		else
			cross_passage(man, man->charas[0].current_loc->exits + outside_indexes[0]);
	}
	else
	{
		printf("Different exits lead outside. Specify the one you "
			"want.\n\n");
		free(man->cmd.object);
		man->cmd.object = 0;
		return;
	}
	return;
}

static void	go_back(t_man *man)
{
	int	i;

	if (!man->charas[0].previous_loc)
	{
		printf("You do not have a previous location.\n\n");
		free(man->cmd.object);
		man->cmd.object = 0;
		return;
	}

	for (i = 0; i < NBR_LOCS; ++i)
	{
		if (!man->charas[0].current_loc->exits[i].to)
		{
			printf("Your previous location cannot be accessed.\n\n");
			free(man->cmd.object);
			man->cmd.object = 0;
			return;
		}
		else if (man->charas[0].previous_loc
			== man->charas[0].current_loc->exits[i].to)
			break;
	}

	if (bool_access_locked(man->charas[0].current_loc->exits + i))
		print_access_locked(man->charas[0].current_loc->exits + i);
	else if (bool_loc_is_full(man->charas[0].previous_loc))
		print_loc_is_full();
	else
		cross_passage(man, man->charas[0].current_loc->exits + i);
	return;
}

static void	go_out(t_man *man)
{
	int		i;
	int		j;
	int		k;
	int		l;
	int		m;
	t_exit	*to_outside_and_accessible[NBR_LOCS] = {0};
	t_exit	*to_outside_but_locked[NBR_LOCS] = {0};
	t_exit	*other_and_accessible[NBR_LOCS] = {0};
	t_exit	*other_but_locked[NBR_LOCS] = {0};

	if (!man->charas[0].current_loc->bool_is_indoors)
	{
		printf("You are already outside.\n\n");
		free(man->cmd.object);
		man->cmd.object = 0;
		return;
	}

	for (i = 0, j = 0, k = 0, l = 0, m = 0; i < NBR_LOCS; ++i)
	{
		if (!man->charas[0].current_loc->exits[i].to)
			break;
		else if (!man->charas[0].current_loc->exits[i].to->bool_is_indoors)
		{
			if (man->charas[0].current_loc->exits[i].passage->access
				!= ACCESS_LOCKED)
				to_outside_and_accessible[j++]
					= &(man->charas[0].current_loc->exits[i]);
			else
				to_outside_but_locked[k++]
					= &(man->charas[0].current_loc->exits[i]);
		}
		else
		{
			if (man->charas[0].current_loc->exits[i].passage->access
				!= ACCESS_LOCKED)
				other_and_accessible[l++]
					= &(man->charas[0].current_loc->exits[i]);
			else
				other_but_locked[m++] = &(man->charas[0].current_loc->exits[i]);
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
			free(man->cmd.object);
			man->cmd.object = 0;
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
			free(man->cmd.object);
			man->cmd.object = 0;
			return;
		}
	}

	printf("There is more than one exit. Which one do you want?\n\n");
	free(man->cmd.object);
	man->cmd.object = 0;
	return;
}

static void	go_tag(t_man *man)
{
	int		bool_tag_is_passage_item;
	t_exit	**locs;

	bool_tag_is_passage_item = 0;
	locs = 0;
	locs = retrieve_locs(man->charas[0].current_loc, man->cmd.object);
	if (!locs || !locs[0])
	{
		locs = retrieve_locs_with_passage_item
			(man->charas[0].current_loc, man->cmd.object);
		if (!locs || !locs[0])
		{
			free(man->cmd.object);
			man->cmd.object = 0;
			free(locs);
			return;
		}
		else
			bool_tag_is_passage_item = 1;
	}

	if (!locs[1])
	{
		if (bool_access_locked(locs[0]))
			print_access_locked(locs[0]);
		else if (bool_loc_is_full(locs[0]->to))
			print_loc_is_full();
		else
			cross_passage(man, locs[0]);
	}
	else if (bool_tag_is_passage_item)
	{
		printf("There is more than one passage item in your vicinity for "
			"which this tag works.\n");
		free(man->cmd.object);
		man->cmd.object = 0;
	}
	else
	{
		printf("There is more than one destination from your current "
			"location for which this tag works.\n");
		free(man->cmd.object);
		man->cmd.object = 0;
	}

	free(locs);
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

static int	bool_loc_is_full(const t_loc *loc)
{
	return !!loc->charas[NBR_CHARAS - 1];
}

static void	print_loc_is_full(void)
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

	man->charas[0].previous_loc = man->charas[0].current_loc;
	man->charas[0].current_loc = exit->to;

	for (i = NBR_CHARAS - 1; i >= 0; --i)
	{
		if (!man->charas[0].previous_loc->charas[i])
			continue;

		if (index_last_char < 0)
			index_last_char = i;

		if (man->charas[0].previous_loc->charas[i] == &man->charas[0])
		{
			man->charas[0].previous_loc->charas[i]
				= man->charas[0].previous_loc->charas[index_last_char];
			memset(man->charas[0].previous_loc->charas + index_last_char, 0,
				sizeof(t_char *));
			break;
		}
	}

	for (i = 0; i < NBR_CHARAS; ++i)
	{
		if (!man->charas[0].current_loc->charas[i])
		{
			man->charas[0].current_loc->charas[i] = &man->charas[0];
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

	if (man->charas[0].current_loc->geo_aff->id != exit->to->geo_aff->id)
	{
		if (man->charas[0].current_loc->bool_is_indoors)
			printf("leave the %s. ",
				man->charas[0].current_loc->geo_aff->name);
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
