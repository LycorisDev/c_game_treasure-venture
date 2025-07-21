#include "treasure_venture.h"

static int	bool_no_item_at_current_location(t_man *man);
/* static int	bool_no_character_at_current_location(t_man *man); */
static int	bool_player_is_the_only_character_at_current_location(t_man *man);

void	run_look(t_man *man)
{
	t_item		**items_with_same_tag = 0;
	t_character	**characters_with_same_tag = 0;
	int			bool_item_match = 0;
	int			bool_character_match = 0;
	int			bool_several_item_matches = 0;
	int			bool_several_character_matches = 0;

	items_with_same_tag = 0;
	characters_with_same_tag = 0;
	bool_item_match = 0;
	bool_character_match = 0;
	bool_several_item_matches = 0;
	bool_several_character_matches = 0;
	if (!strcmp(man->cmd.object, "around"))
	{
		describe_location(man, man->characters[CHAR_PLAYER - 1].current_location);
		return;
	}
	if (bool_no_item_at_current_location(man)
		&& bool_player_is_the_only_character_at_current_location(man))
	{
		printf("\t[Try 'look around'.]\n\n");
		return;
	}

	if (*man->cmd.object)
	{
		items_with_same_tag = retrieve_items(man->characters[CHAR_PLAYER - 1].current_location->items,
			man->cmd.object);
		characters_with_same_tag = retrieve_characters
			(man->characters[CHAR_PLAYER - 1].current_location->characters, man->cmd.object);

		bool_item_match = items_with_same_tag && items_with_same_tag[0];
		bool_character_match = characters_with_same_tag
			&& characters_with_same_tag[0];

		bool_several_item_matches = bool_item_match && items_with_same_tag[1];
		bool_several_character_matches = bool_character_match
			&& characters_with_same_tag[1];

		if (!bool_item_match && !bool_character_match)
		{
			memset(man->cmd.object, 0, sizeof(man->cmd.object));
		}
		else if (bool_several_item_matches && bool_several_character_matches)
		{
			printf("There is more than one item and character in your "
				"vicinity for which this tag works.\n");
			memset(man->cmd.object, 0, sizeof(man->cmd.object));
		}
		else if (bool_several_item_matches)
		{
			printf("There is more than one item in your vicinity for which "
				"this tag works.\n");
			memset(man->cmd.object, 0, sizeof(man->cmd.object));
		}
		else if (bool_several_character_matches)
		{
			printf("There is more than one character in your vicinity for "
				"which this tag works.\n");
			memset(man->cmd.object, 0, sizeof(man->cmd.object));
		}
		else if (bool_item_match)
		{
			printf("%s\n\n", items_with_same_tag[0]->desc_look_item);
			event_player_finds_entry_doors_key(man, items_with_same_tag[0]->id);
		}
		else
		{
			printf("%s\n\n", characters_with_same_tag[0]->description);
		}
	}

	if (!*man->cmd.object)
	{
		display_item_suggestions(man->characters[CHAR_PLAYER - 1].current_location->items, "look");
		display_character_suggestions(man, man->characters[CHAR_PLAYER - 1].current_location->characters,
			"look");
	}

	free(items_with_same_tag);
	free(characters_with_same_tag);
	return;
}

static int	bool_no_item_at_current_location(t_man *man)
{
	return !man->characters[CHAR_PLAYER - 1].current_location->items[0];
}

/*
static int	bool_no_character_at_current_location(t_man *man)
{
	return !man->characters[CHAR_PLAYER - 1].current_location->characters[0];
}
*/

static int	bool_player_is_the_only_character_at_current_location(t_man *man)
{
	return man->characters[CHAR_PLAYER - 1].current_location->characters[0] == &man->characters[CHAR_PLAYER - 1]
		&& !man->characters[CHAR_PLAYER - 1].current_location->characters[1];
}
