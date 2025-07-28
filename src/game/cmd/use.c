#include "treasure_venture.h"

static t_item	*find_item_to_use(t_man *man);
static void		use_access_item(t_item *item_to_use);
static int		use_item_on_target(t_man *man, const t_item *item_to_use);

void	run_use(t_man *man)
{
	t_item	*item_to_use;
	int		bool_issue_is_target;

	item_to_use = 0;
	bool_issue_is_target = 0;
	if (!man->charas[0].inventory[0] && !man->charas[0].current_loc->items[0])
	{
		printf("There is nothing for you to use.\n\n");
		return;
	}

	if (man->cmd.object)
		item_to_use = find_item_to_use(man);

	if (item_to_use)
	{
		if (item_to_use->access)
			use_access_item(item_to_use);
		else if (item_to_use->bool_requires_target_for_use)
			bool_issue_is_target = use_item_on_target(man, item_to_use);
		else
		{
			printf("%s ", item_to_use->desc);
			printf("The %s %s seem to be of much use.\n\n",
				item_to_use->tags[0],
				item_to_use->bool_is_singular ? "doesn't" : "don't");
		}
	}

	if (bool_issue_is_target)
	{

	}
	else if (!man->cmd.object)
	{
		display_item_suggestions(man->charas[0].inventory, "use");
		display_item_suggestions(man->charas[0].current_loc->items, "use");
	}

	return;
}

static t_item	*find_item_to_use(t_man *man)
{
	t_item	*item_to_use;
	t_item	**inventory_items;
	t_item	**loc_items;
	int		bool_inventory_match;
	int		bool_loc_match;

	item_to_use = 0;
	inventory_items = retrieve_items(man->charas[0].inventory, man->cmd.object);
	loc_items = retrieve_items(man->charas[0].current_loc->items,
		man->cmd.object);
	bool_inventory_match = inventory_items && inventory_items[0];
	bool_loc_match = loc_items && loc_items[0];
	if (bool_inventory_match && bool_loc_match)
	{
		printf("Your inventory and vicinity both included, there is more "
			"than one item for which this tag works.\n");
		free(man->cmd.object);
		man->cmd.object = 0;
	}
	else if (bool_inventory_match)
	{
		if (inventory_items[1])
		{
			printf("There is more than one item in your inventory for "
				"which this tag works.\n");
			free(man->cmd.object);
			man->cmd.object = 0;
		}
		else
		{
			item_to_use = inventory_items[0];
		}
	}
	else if (bool_loc_match)
	{
		if (loc_items[1])
		{
			printf("There is more than one item in your vicinity for which "
				"this tag works.\n");
			free(man->cmd.object);
			man->cmd.object = 0;
		}
		else
		{
			item_to_use = loc_items[0];
		}
	}
	else
	{
		free(man->cmd.object);
		man->cmd.object = 0;
	}

	free(inventory_items);
	free(loc_items);
	return item_to_use;
}

static void	use_access_item(t_item *item_to_use)
{
	if (item_to_use->access == ACCESS_OPEN)
	{
		item_to_use->access = ACCESS_CLOSED;
		printf("You close the %s.\n\n",
			item_to_use->bool_is_singular ? "door" : "doors");
	}
	else if (item_to_use->access == ACCESS_CLOSED)
	{
		item_to_use->access = ACCESS_OPEN;
		printf("You open the %s.\n\n",
			item_to_use->bool_is_singular ? "door" : "doors");
	}
	else
	{
		printf("The %s %s locked.\n\n",
			item_to_use->bool_is_singular ? "door" : "doors",
			item_to_use->bool_is_singular ? "is" : "are");
	}
	return;
}

static int	use_item_on_target(t_man *man, const t_item *item_to_use)
{
	void		*target;
	t_item		**items;
	t_char		**charas;
	int			bool_item_match;
	int			bool_chara_match;
	int			bool_target_is_chara;

	target = 0;
	items = 0;
	charas = 0;
	bool_item_match = 0;
	bool_chara_match = 0;
	bool_target_is_chara = 0;
	if (!man->cmd.target || !man->cmd.preposition
		|| strcmp(man->cmd.preposition, "on"))
	{
		printf("Use the %s on who or what?\n\n", man->cmd.object);
		return 1;
	}

	items = retrieve_items(man->charas[0].current_loc->items, man->cmd.target);
	charas = retrieve_charas(man->charas[0].current_loc->charas,
		man->cmd.target);
	bool_item_match = items && items[0];
	bool_chara_match = charas && charas[0];

	if (bool_item_match && bool_chara_match)
	{
		printf("There is more than one target in your vicinity for which "
			"this tag works.\n\n");
	}
	else if (bool_item_match)
	{
		if (items[1])
			printf("There is more than one item in your vicinity for which "
				"this tag works.\n\n");
		else
			target = items[0];
	}
	else if (bool_chara_match)
	{
		if (charas[1])
			printf("There is more than one character in your vicinity for "
				"which this tag works.\n\n");
		else
		{
			target = charas[0];
			bool_target_is_chara = 1;
		}
	}
	else
	{
		printf("Use the %s on who or what?\n\n", man->cmd.object);
	}

	if (!target)
	{
		free(items);
		free(charas);
		return 1;
	}

	if (bool_target_is_chara)
	{
		if (target == &man->charas[0])
			printf("The %s %s nothing to you.\n\n", item_to_use->tags[1],
				item_to_use->bool_is_singular ? "does" : "do");
		else
			printf("The %s %s nothing to the %s.\n\n", item_to_use->tags[1],
				item_to_use->bool_is_singular ? "does" : "do",
				((t_char *)target)->tags[1]);
	}
	else if (!((t_item *)target)->access
		|| ((t_item *)target)->unlocked_with != item_to_use)
	{
		printf("The %s %s nothing to the %s.\n\n", item_to_use->tags[1],
			item_to_use->bool_is_singular ? "does" : "do",
			((t_item *)target)->tags[1]);
	}
	else if (((t_item *)target)->access == ACCESS_OPEN)
	{
		((t_item *)target)->access = ACCESS_LOCKED;
		printf("You close and lock the %s.\n\n",
			((t_item *)target)->bool_is_singular ? "door" : "doors");
	}
	else if (((t_item *)target)->access == ACCESS_CLOSED)
	{
		((t_item *)target)->access = ACCESS_LOCKED;
		printf("You lock the %s.\n\n",
			((t_item *)target)->bool_is_singular ? "door" : "doors");
	}
	else
	{
		((t_item *)target)->access = ACCESS_CLOSED;
		printf("You unlock the %s.\n\n",
			((t_item *)target)->bool_is_singular ? "door" : "doors");
	}

	free(items);
	free(charas);
	return 0;
}
