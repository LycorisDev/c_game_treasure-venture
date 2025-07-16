#ifndef ITEMS_H
# define ITEMS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "misc.h"
# include "events.h"

struct s_item
{
	int		id;
	char	tags[NBR_TAGS][LENGTH_TAG];
	char	description[LENGTH_DESCRIPTION];

	char	desc_look_around[LENGTH_DESCRIPTION];
	char	desc_look_item[LENGTH_DESCRIPTION];
	int		bool_is_singular;
	int		access;
	t_item	*unlocked_with;
	int		bool_can_be_taken;
	int		bool_requires_target_for_use;
};

extern t_item	g_list_items[NBR_ITEMS];

/* -------------------------------------------------------------------------- */
# define ID_ITEM_ENTRY_DOORS       1
# define ID_ITEM_GRANDFATHER_CLOCK 2
# define ID_ITEM_LIBRARY_DOOR      3
# define ID_ITEM_LIBRARY_SIGN      4
# define ID_ITEM_BOOKS             5
# define ID_ITEM_DOOR_ROOM_1       6
# define ID_ITEM_DOOR_ROOM_2       7
# define ID_ITEM_DOOR_ROOM_3       8
# define ID_ITEM_ENTRY_DOORS_KEY   9

# define ITEM_ENTRY_DOORS          (g_list_items + (ID_ITEM_ENTRY_DOORS - 1))
# define ITEM_GRANDFATHER_CLOCK    (g_list_items + (ID_ITEM_GRANDFATHER_CLOCK - 1))
# define ITEM_LIBRARY_DOOR         (g_list_items + (ID_ITEM_LIBRARY_DOOR - 1))
# define ITEM_LIBRARY_SIGN         (g_list_items + (ID_ITEM_LIBRARY_SIGN - 1))
# define ITEM_BOOKS                (g_list_items + (ID_ITEM_BOOKS - 1))
# define ITEM_DOOR_ROOM_1          (g_list_items + (ID_ITEM_DOOR_ROOM_1 - 1))
# define ITEM_DOOR_ROOM_2          (g_list_items + (ID_ITEM_DOOR_ROOM_2 - 1))
# define ITEM_DOOR_ROOM_3          (g_list_items + (ID_ITEM_DOOR_ROOM_3 - 1))
# define ITEM_ENTRY_DOORS_KEY      (g_list_items + (ID_ITEM_ENTRY_DOORS_KEY - 1))
/* -------------------------------------------------------------------------- */

void	populate_list_items(void);
void	display_item_suggestions(t_item **item_collection, const char *command);
t_item	**retrieve_items(t_item **item_collection, const char *parser);
t_item	**retrieve_takeable_items(t_item **item_collection, const char *parser);
int		bool_item_matches_parser(const t_item *item, const char *parser);

#endif
