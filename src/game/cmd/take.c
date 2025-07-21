#include "treasure_venture.h"

static void	take_item(t_man *man, t_item *item_to_take);
static void	clean(t_item **p1, t_item **p2);

void	run_take(t_man *man)
{
	t_item	**takeable_items;
	t_item	**takeable_items_with_same_tag;

	takeable_items = retrieve_takeable_items(man->characters[CHAR_PLAYER - 1].current_location->items,
		0);
	takeable_items_with_same_tag = 0;
	if (!takeable_items || !takeable_items[0])
	{
		printf("There is nothing for you to take here.\n\n");
		clean(takeable_items, takeable_items_with_same_tag);
		return;
	}

	if (man->characters[CHAR_PLAYER - 1].inventory[NBR_ITEMS - 1])
	{
		printf("Your inventory is full.\n\n");
		clean(takeable_items, takeable_items_with_same_tag);
		return;
	}

	if (!*man->cmd.object)
	{
		display_item_suggestions(takeable_items, "take");
		clean(takeable_items, takeable_items_with_same_tag);
		return;
	}

	takeable_items_with_same_tag = retrieve_takeable_items(takeable_items,
		man->cmd.object);
	if (!takeable_items_with_same_tag || !takeable_items_with_same_tag[0])
	{
		display_item_suggestions(takeable_items, "take");
		clean(takeable_items, takeable_items_with_same_tag);
		return;
	}

	if (takeable_items_with_same_tag[1])
	{
		printf("There is more than one takeable item in your vicinity for "
			"which this tag works.\n");
		display_item_suggestions(takeable_items, "take");
		clean(takeable_items, takeable_items_with_same_tag);
		return;
	}

	take_item(man, takeable_items_with_same_tag[0]);
	clean(takeable_items, takeable_items_with_same_tag);
	return;
}

static void	take_item(t_man *man, t_item *item_to_take)
{
	int	i;
	int	index_of_last_location_item;

	index_of_last_location_item = -1;
	/* Place the item in the inventory */
	for (i = 0; i < NBR_ITEMS; ++i)
	{
		if (!man->characters[CHAR_PLAYER - 1].inventory[i])
		{
			man->characters[CHAR_PLAYER - 1].inventory[i] = item_to_take;
			break;
		}
	}

	/* Remove the item from the location */
	for (i = NBR_ITEMS - 1; i >= 0; --i)
	{
		if (!man->characters[CHAR_PLAYER - 1].current_location->items[i])
			continue;
		else
			index_of_last_location_item = i;

		if (man->characters[CHAR_PLAYER - 1].current_location->items[i] == item_to_take)
		{
			memset((man->characters[CHAR_PLAYER - 1].current_location->items + i), 0, sizeof(t_item *));
			break;
		}
	}

	/* Fill the gap */
	if (i != index_of_last_location_item)
	{
		man->characters[CHAR_PLAYER - 1].current_location->items[i]
			= man->characters[CHAR_PLAYER - 1].current_location->items[index_of_last_location_item];
		memset((man->characters[CHAR_PLAYER - 1].current_location->items + index_of_last_location_item),
			0, sizeof(t_item *));
	}

	event_player_finds_entry_doors_key(man, item_to_take->id);
	printf("'%s' added to your inventory.\n\n", item_to_take->tags[0]);
	return;
}

static void	clean(t_item **p1, t_item **p2)
{
	free(p1);
	free(p2);
	return;
}
