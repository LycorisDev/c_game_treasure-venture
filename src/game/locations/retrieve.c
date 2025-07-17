#include "treasure_venture.h"

static int	bool_location_matches_parser(const t_location *destination,
				const char *parser);

t_exit	**retrieve_locations(t_location *origin, const char *parser)
{
	int		i;
	int		j;
	t_exit	**locations;

	locations = calloc(NBR_LOCATIONS, sizeof(t_exit *));
	if (!locations)
		return 0;

	for (i = 0, j = 0; i < NBR_LOCATIONS; ++i)
	{
		if (!origin->exits[i].to)
			break;

		/* "go [building]" */
		if (origin->geo_aff->id != origin->exits[i].to->geo_aff->id) 
		{
			if (!strcmp(parser, origin->exits[i].to->geo_aff->name))
				locations[j++] = &(origin->exits[i]);
			continue;
		}

		/* "go [room]" */
		if (bool_location_matches_parser(origin->exits[i].to, parser))
			locations[j++] = &(origin->exits[i]);
	}

	return locations;
}

t_exit	**retrieve_locations_with_passage_item(t_location *origin,
			const char *parser)
{
	int		i;
	int		j;
	t_exit	**exits;

	exits = calloc(NBR_LOCATIONS, sizeof(t_exit *));
	if (!exits)
		return 0;

	for (i = 0, j = 0; i < NBR_LOCATIONS; ++i)
	{
		if (!origin->exits[i].to || !origin->exits[i].passage->access)
			break;

		if (bool_item_matches_parser(origin->exits[i].passage, parser))
			exits[j++] = &(origin->exits[i]);
	}

	return exits;
}

static int	bool_location_matches_parser(const t_location *destination,
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
