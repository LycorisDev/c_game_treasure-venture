#include "treasure_venture.h"

static void	display_inventory(t_item **inventory);

void	run_inventory(t_man *man)
{
	t_item	**items;

	items = 0;
	if (!man->charas[0].inventory[0])
	{
		printf("You have no item on you.\n\n");
	}
	else if (!man->cmd.object)
	{
		display_inventory(man->charas[0].inventory);
	}
	else
	{
		items = retrieve_items(man->charas[0].inventory, man->cmd.object);

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
			inventory[i]->desc);
	}
	printf("--------------------\n\n");
	return;
}
