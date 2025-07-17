#include "commands.h"
#include "characters.h"

static void	display_inventory(t_item **inventory);

void	execute_inventory(void)
{
	t_item	**items;

	items = 0;
	if (!PLAYER->inventory[0])
	{
		printf("You have no item on you.\n\n");
	}
	else if (!*g_cmd.object)
	{
		display_inventory(PLAYER->inventory);
	}
	else
	{
		items = retrieve_items(PLAYER->inventory, g_cmd.object);

		if (!items || !items[0])
			printf("You have no such item on you. Type 'inventory' to see "
				"your items.\n\n");
		else if (!items[1])
			printf("%s\n\n", items[0]->desc_look_item);
		else
			printf("There is more than one item in your inventory for "
				"which this tag works.\n\n");
	}

	free(items);
	return;
}

static void	display_inventory(t_item **inventory)
{
	int	i;

	printf("--------------------\n");
	printf("INVENTORY\n\n");
	printf("\t['Inventory [item]' to see the detailed description of an "
		"item.]\n\n");
	for (i = 0; i < NBR_ITEMS; ++i)
	{
		if (!inventory[i])
			break;
		printf("- [%s]\n\t%s\n", inventory[i]->tags[0],
			inventory[i]->description);
	}
	printf("--------------------\n\n");
	return;
}
