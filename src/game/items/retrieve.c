#include "items.h"
#include "main.h"

t_item	**retrieve_items(t_item **item_collection, const char *parser)
{
	int		i;
	int		j;
	t_item	**items;

	items = calloc(NBR_ITEMS, sizeof(t_item *));
	if (!items)
		return 0;

	for (i = 0, j = 0; i < NBR_ITEMS; ++i)
	{
		if (!item_collection[i])
			break;

		if (!parser || bool_item_matches_parser(item_collection[i], parser))
			items[j++] = item_collection[i];
	}

	return items;
}

t_item	**retrieve_takeable_items(t_item **item_collection, const char *parser)
{
	int		i;
	int		j;
	t_item	**takeable_items;

	takeable_items = calloc(NBR_ITEMS, sizeof(t_item *));
	if (!takeable_items)
		return 0;

	for (i = 0, j = 0; i < NBR_ITEMS; ++i)
	{
		if (!item_collection[i])
			break;

		if (!item_collection[i]->bool_can_be_taken)
			continue;

		if (!parser || bool_item_matches_parser(item_collection[i], parser))
			takeable_items[j++] = item_collection[i];
	}

	return takeable_items;
}

int	bool_item_matches_parser(const t_item *item, const char *parser)
{
	int	i;

	for (i = 0; i < NBR_TAGS; ++i)
	{
		if (!item->tags[i])
			return 0;

		if (!strcmp(parser, item->tags[i]))
			return 1;
	}
	return 0;
}
