#include "treasure_venture.h"

static void	drop_item(t_man *man, t_item *item_to_drop);

void	run_drop(t_man *man)
{
	t_item	**items_with_same_tag;

	items_with_same_tag = 0;
	if (man->characters[CHAR_PLAYER - 1].current_location->items[NBR_ITEMS - 1])
	{
		printf("This place cannot hold any more item.\n\n");
		return;
	}
	else if (!man->characters[CHAR_PLAYER - 1].inventory[0])
	{
		printf("You have no item on you.\n\n");
		return;
	}
	else if (*man->cmd.object)
	{
		items_with_same_tag = retrieve_items(man->characters[CHAR_PLAYER - 1].inventory, man->cmd.object);

		if (!items_with_same_tag || !items_with_same_tag[0])
		{
			memset(man->cmd.object, 0, sizeof(man->cmd.object));
		}
		else if (items_with_same_tag[1])
		{
			printf("There is more than one item in your inventory for "
				"which this tag works.\n\n");
			display_item_suggestions(items_with_same_tag, "drop");
		}
		else if (man->characters[CHAR_PLAYER - 1].current_location->items[NBR_ITEMS - 1])
		{
			printf("The current location is full. No more items can be "
				"added.\n\n");
		}
		else
		{
			drop_item(man, items_with_same_tag[0]);
		}
	}

	if (!*man->cmd.object)
		display_item_suggestions(man->characters[CHAR_PLAYER - 1].inventory, "drop");

	free(items_with_same_tag);
	return;
}

static void	drop_item(t_man *man, t_item *item_to_drop)
{
	int	i;
	int	index_of_last_inventory_item;

	index_of_last_inventory_item = 0;
	for (i = 0; i < NBR_ITEMS; ++i)
	{
		/* Look for an empty spot in the current location's item list */
		if (!man->characters[CHAR_PLAYER - 1].current_location->items[i])
		{
			/* Put the dropped item there */
			man->characters[CHAR_PLAYER - 1].current_location->items[i] = item_to_drop;
			break;
		}
	}

	for (i = NBR_ITEMS - 1; i >= 0; --i)
	{
		/*
			Dropping the item is likely to leave a gap in the inventory.
			Therefore, look for the last item of the inventory as to later 
			put it in the dropped item's place.
		*/
		if (!man->characters[CHAR_PLAYER - 1].inventory[i])
			continue;
		else
			index_of_last_inventory_item = i;

		/* Remove the dropped item from the inventory */
		if (man->characters[CHAR_PLAYER - 1].inventory[i] == item_to_drop)
		{
			memset(man->characters[CHAR_PLAYER - 1].inventory + i, 0, sizeof(t_item *));
			break;
		}
	}

	/* Fill the gap */
	if (i != index_of_last_inventory_item)
	{
		man->characters[CHAR_PLAYER - 1].inventory[i] = man->characters[CHAR_PLAYER - 1].inventory[index_of_last_inventory_item];
		memset(man->characters[CHAR_PLAYER - 1].inventory + index_of_last_inventory_item, 0,
			sizeof(t_item *));
	}

	printf("'%s' dropped.\n\n", item_to_drop->tags[0]);
	return;
}
