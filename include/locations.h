#ifndef LOCATIONS_H
# define LOCATIONS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "main.h"
# include "misc.h"
# include "characters.h"
# include "items.h"

struct s_exit
{
	t_location	*to;
	t_item		*passage;
};

struct s_geo_aff
{
	int		id;
	char	name[LENGTH_TAG];
};

struct s_location
{
	int			id;
	char		tags[NBR_TAGS][LENGTH_TAG];
	char		description[LENGTH_DESCRIPTION];

	int			bool_is_indoors;
	t_geo_aff	*geo_aff;
	t_exit		exits[NBR_LOCATIONS];

	t_item		*items[NBR_ITEMS];
	t_character	*characters[NBR_CHARACTERS];
};

extern t_location	g_list_locations[NBR_LOCATIONS];
extern t_geo_aff	g_list_geo_aff[NBR_GEO_AFF];

/* -------------------------------------------------------------------------- */
# define ID_LOCATION_OUTSIDE      1
# define ID_LOCATION_MAIN_HALLWAY 2
# define ID_LOCATION_OLD_LIBRARY  3
# define ID_LOCATION_ROOM_1       4
# define ID_LOCATION_ROOM_2       5
# define ID_LOCATION_ROOM_3       6

# define LOCATION_OUTSIDE         (g_list_locations + (ID_LOCATION_OUTSIDE - 1))
# define LOCATION_MAIN_HALLWAY    (g_list_locations + (ID_LOCATION_MAIN_HALLWAY - 1))
# define LOCATION_OLD_LIBRARY     (g_list_locations + (ID_LOCATION_OLD_LIBRARY - 1))
# define LOCATION_ROOM_1          (g_list_locations + (ID_LOCATION_ROOM_1 - 1))
# define LOCATION_ROOM_2          (g_list_locations + (ID_LOCATION_ROOM_2 - 1))
# define LOCATION_ROOM_3          (g_list_locations + (ID_LOCATION_ROOM_3 - 1))
/* -------------------------------------------------------------------------- */

void	populate_list_locations(void);
void	describe_location(const t_location *location);
void	display_location_suggestions(t_location *origin);
t_exit	**retrieve_locations(t_location *origin, const char *parser);
t_exit	**retrieve_locations_with_passage_item(t_location *origin,
			const char *parser);

#endif
