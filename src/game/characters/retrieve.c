#include "treasure_venture.h"

static int	bool_chara_matches_parser(const t_char *chara,
				const char *parser);

t_char	**retrieve_charas(t_char **chara_collection,
			const char *parser)
{
	int		i;
	int		j;
	t_char	**charas;

	charas = calloc(NBR_CHARAS, sizeof(t_char *));
	if (!charas)
		return 0;

	for (i = 0, j = 0; i < NBR_CHARAS; ++i)
	{
		if (!chara_collection[i])
			break;

		if (!parser || bool_chara_matches_parser(chara_collection[i],
			parser))
			charas[j++] = chara_collection[i];
	}

	return charas;
}

static int	bool_chara_matches_parser(const t_char *chara,
				const char *parser)
{
	int	i;

	for (i = 0; i < NBR_TAGS; ++i)
	{
		if (!chara->tags[i])
			return 0;

		if (!strcmp(parser, chara->tags[i]))
			return 1;
	}
	return 0;
}
