#include "treasure_venture.h"

static int	bool_loc_matches_parser(const t_loc *destination,
				const char *parser);

t_exit	**retrieve_locs(t_loc *origin, const char *parser)
{
	int		i;
	int		j;
	t_exit	**locs;

	locs = calloc(NBR_LOCS, sizeof(t_exit *));
	if (!locs)
		return 0;

	for (i = 0, j = 0; i < NBR_LOCS; ++i)
	{
		if (!origin->exits[i].to)
			break;

		/* "go [building]" */
		if (origin->geo_aff->id != origin->exits[i].to->geo_aff->id) 
		{
			if (!strcmp(parser, origin->exits[i].to->geo_aff->name))
				locs[j++] = &(origin->exits[i]);
			continue;
		}

		/* "go [room]" */
		if (bool_loc_matches_parser(origin->exits[i].to, parser))
			locs[j++] = &(origin->exits[i]);
	}

	return locs;
}

t_exit	**retrieve_locs_with_passage_item(t_loc *origin,
			const char *parser)
{
	int		i;
	int		j;
	t_exit	**exits;

	exits = calloc(NBR_LOCS, sizeof(t_exit *));
	if (!exits)
		return 0;

	for (i = 0, j = 0; i < NBR_LOCS; ++i)
	{
		if (!origin->exits[i].to || !origin->exits[i].passage->access)
			break;

		if (bool_item_matches_parser(origin->exits[i].passage, parser))
			exits[j++] = &(origin->exits[i]);
	}

	return exits;
}

static int	bool_loc_matches_parser(const t_loc *destination,
				const char *parser)
{
	int	i;

	for (i = 0; i < NBR_TAGS; ++i)
	{
		if (!destination->tags[i])
			return 0;

		if (!strcmp(parser, destination->tags[i]))
			return 1;
	}
	return 0;
}
