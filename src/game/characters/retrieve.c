#include "characters.h"

static int	bool_character_matches_parser(const t_character *character,
				const char *parser);

t_character	**retrieve_characters(t_character **character_collection,
				const char *parser)
{
	int			i;
	int			j;
	t_character	**characters;

	characters = calloc(NBR_CHARACTERS, sizeof(t_character *));
	if (!characters)
		return 0;

	for (i = 0, j = 0; i < NBR_CHARACTERS; ++i)
	{
		if (!character_collection[i])
			break;

		if (!parser || bool_character_matches_parser(character_collection[i],
			parser))
			characters[j++] = character_collection[i];
	}

	return characters;
}

static int	bool_character_matches_parser(const t_character *character,
				const char *parser)
{
	int	i;

	for (i = 0; i < NBR_TAGS; ++i)
	{
		if (!character->tags[i])
			return 0;

		if (!strcmp(parser, character->tags[i]))
			return 1;
	}
	return 0;
}
