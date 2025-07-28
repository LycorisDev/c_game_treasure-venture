#include "treasure_venture.h"

static int	bool_no_item_at_current_loc(t_man *man);
/* static int	bool_no_chara_at_current_loc(t_man *man); */
static int	bool_player_is_the_only_chara_at_current_loc(t_man *man);

void	run_look(t_man *man)
{
	t_item		**items_with_same_tag = 0;
	t_char		**charas_with_same_tag = 0;
	int			bool_item_match = 0;
	int			bool_chara_match = 0;
	int			bool_several_item_matches = 0;
	int			bool_several_chara_matches = 0;

	items_with_same_tag = 0;
	charas_with_same_tag = 0;
	bool_item_match = 0;
	bool_chara_match = 0;
	bool_several_item_matches = 0;
	bool_several_chara_matches = 0;
	if (man->cmd.object && !strcmp(man->cmd.object, "around"))
	{
		describe_loc(man, man->charas[0].current_loc);
		return;
	}
	if (!man->cmd.object || (bool_no_item_at_current_loc(man)
		&& bool_player_is_the_only_chara_at_current_loc(man)))
	{
		printf("\t[Try 'look around'.]\n\n");
		return;
	}

	if (man->cmd.object)
	{
		items_with_same_tag = retrieve_items(man->charas[0].current_loc->items,
			man->cmd.object);
		charas_with_same_tag = retrieve_charas
			(man->charas[0].current_loc->charas, man->cmd.object);

		bool_item_match = items_with_same_tag && items_with_same_tag[0];
		bool_chara_match = charas_with_same_tag
			&& charas_with_same_tag[0];

		bool_several_item_matches = bool_item_match && items_with_same_tag[1];
		bool_several_chara_matches = bool_chara_match
			&& charas_with_same_tag[1];

		if (!bool_item_match && !bool_chara_match)
		{
			free(man->cmd.object);
			man->cmd.object = 0;
		}
		else if (bool_several_item_matches && bool_several_chara_matches)
		{
			printf("There is more than one item and chara in your "
				"vicinity for which this tag works.\n");
			free(man->cmd.object);
			man->cmd.object = 0;
		}
		else if (bool_several_item_matches)
		{
			printf("There is more than one item in your vicinity for which "
				"this tag works.\n");
			free(man->cmd.object);
			man->cmd.object = 0;
		}
		else if (bool_several_chara_matches)
		{
			printf("There is more than one character in your vicinity for "
				"which this tag works.\n");
			free(man->cmd.object);
			man->cmd.object = 0;
		}
		else if (bool_item_match)
		{
			printf("%s\n\n", items_with_same_tag[0]->desc_look_item);
			event_player_finds_entry_doors_key(man, items_with_same_tag[0]->id);
		}
		else
		{
			printf("%s\n\n", charas_with_same_tag[0]->desc);
		}
	}

	if (!man->cmd.object)
	{
		display_item_suggestions(man->charas[0].current_loc->items, "look");
		display_chara_suggestions(man, man->charas[0].current_loc->charas,
			"look");
	}

	free(items_with_same_tag);
	free(charas_with_same_tag);
	return;
}

static int	bool_no_item_at_current_loc(t_man *man)
{
	return !man->charas[0].current_loc->items[0];
}

/*
static int	bool_no_chara_at_current_loc(t_man *man)
{
	return !man->charas[0].current_loc->charas[0];
}
*/

static int	bool_player_is_the_only_chara_at_current_loc(t_man *man)
{
	return man->charas[0].current_loc->charas[0] == &man->charas[0]
		&& !man->charas[0].current_loc->charas[1];
}
