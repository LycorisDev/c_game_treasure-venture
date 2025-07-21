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
	if (!man->characters[CHAR_PLAYER - 1].inventory[0] && !man->characters[CHAR_PLAYER - 1].current_location->items[0])
	{
		printf("There is nothing for you to use.\n\n");
		return;
	}

	if (*man->cmd.object)
		item_to_use = find_item_to_use(man);

	if (item_to_use)
	{
		if (item_to_use->access)
			use_access_item(item_to_use);
		else if (item_to_use->bool_requires_target_for_use)
			bool_issue_is_target = use_item_on_target(man, item_to_use);
		else
		{
			printf("%s ", item_to_use->description);
			printf("The %s %s seem to be of much use.\n\n",
				item_to_use->tags[1],
				item_to_use->bool_is_singular ? "doesn't" : "don't");
		}
	}

	if (bool_issue_is_target)
	{

	}
	else if (!*man->cmd.object)
	{
		display_item_suggestions(man->characters[CHAR_PLAYER - 1].inventory, "use");
		display_item_suggestions(man->characters[CHAR_PLAYER - 1].current_location->items, "use");
	}

	return;
}

static t_item	*find_item_to_use(t_man *man)
{
	t_item	*item_to_use;
	t_item	**inventory_items;
	t_item	**location_items;
	int		bool_inventory_match;
	int		bool_location_match;

	item_to_use = 0;
	inventory_items = retrieve_items(man->characters[CHAR_PLAYER - 1].inventory, man->cmd.object);
	location_items = retrieve_items(man->characters[CHAR_PLAYER - 1].current_location->items,
		man->cmd.object);
	bool_inventory_match = inventory_items && inventory_items[0];
	bool_location_match = location_items && location_items[0];
	if (bool_inventory_match && bool_location_match)
	{
		printf("Your inventory and vicinity both included, there is more "
			"than one item for which this tag works.\n");
		memset(man->cmd.object, 0, sizeof(man->cmd.object));
	}
	else if (bool_inventory_match)
	{
		if (inventory_items[1])
		{
			printf("There is more than one item in your inventory for "
				"which this tag works.\n");
			memset(man->cmd.object, 0, sizeof(man->cmd.object));
		}
		else
		{
			item_to_use = inventory_items[0];
		}
	}
	else if (bool_location_match)
	{
		if (location_items[1])
		{
			printf("There is more than one item in your vicinity for which "
				"this tag works.\n");
			memset(man->cmd.object, 0, sizeof(man->cmd.object));
		}
		else
		{
			item_to_use = location_items[0];
		}
	}
	else
	{
		memset(man->cmd.object, 0, sizeof(man->cmd.object));
	}

	free(inventory_items);
	free(location_items);
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
	t_character	**characters;
	int			bool_item_match;
	int			bool_character_match;
	int			bool_target_is_character;

	target = 0;
	items = 0;
	characters = 0;
	bool_item_match = 0;
	bool_character_match = 0;
	bool_target_is_character = 0;
	if (!*man->cmd.target || !*man->cmd.preposition
		|| strcmp(man->cmd.preposition, "on"))
	{
		printf("Use the %s on who or what?\n\n", man->cmd.object);
		return 1;
	}

	items = retrieve_items(man->characters[CHAR_PLAYER - 1].current_location->items, man->cmd.target);
	characters = retrieve_characters(man->characters[CHAR_PLAYER - 1].current_location->characters,
		man->cmd.target);
	bool_item_match = items && items[0];
	bool_character_match = characters && characters[0];

	if (bool_item_match && bool_character_match)
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
	else if (bool_character_match)
	{
		if (characters[1])
			printf("There is more than one character in your vicinity for "
				"which this tag works.\n\n");
		else
		{
			target = characters[0];
			bool_target_is_character = 1;
		}
	}
	else
	{
		printf("Use the %s on who or what?\n\n", man->cmd.object);
	}

	if (!target)
	{
		free(items);
		free(characters);
		return 1;
	}

	if (bool_target_is_character)
	{
		if (target == &man->characters[CHAR_PLAYER - 1])
			printf("The %s %s nothing to you.\n\n", item_to_use->tags[1],
				item_to_use->bool_is_singular ? "does" : "do");
		else
			printf("The %s %s nothing to the %s.\n\n", item_to_use->tags[1],
				item_to_use->bool_is_singular ? "does" : "do",
				((t_character *)target)->tags[1]);
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
	free(characters);
	return 0;
}
