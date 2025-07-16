#ifndef CHARACTERS_H
# define CHARACTERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "misc.h"
# include "locations.h"
# include "items.h"

struct s_character
{
	int			id;
	char		tags[NBR_TAGS][LENGTH_TAG];
	char		description[LENGTH_DESCRIPTION];

	t_location	*previous_location;
	t_location	*current_location;
	t_item		*inventory[NBR_ITEMS];
};

extern t_character	g_list_characters[NBR_CHARACTERS];

/* -------------------------------------------------------------------------- */
# define ID_CHARACTER_PLAYER    1
# define ID_CHARACTER_LIBRARIAN 2

# define PLAYER                 (g_list_characters + (ID_CHARACTER_PLAYER - 1))
# define CHARACTER_LIBRARIAN    (g_list_characters + (ID_CHARACTER_LIBRARIAN - 1))
/* -------------------------------------------------------------------------- */

void		populate_list_characters(void);
void		display_character_suggestions(t_character **character_collection,
				const char *command);
t_character	**retrieve_characters(t_character **character_collection,
				const char *parser);

#endif
