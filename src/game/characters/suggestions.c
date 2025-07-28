#include "treasure_venture.h"

static void	get_all_tags(char *p_str, t_char *object);

void	display_chara_suggestions(t_man *man, t_char **chara_collection,
			const char* command)
{
	int		i;
	char	*str_tags;

	str_tags = 0;
	if (!chara_collection[0] 
			|| (!chara_collection[1] && chara_collection[0] == &man->charas[0]))
		return;

	str_tags = calloc(NBR_TAGS, LEN_TAG);

	printf("\t[Try:]\n");
	for (i = 0; i < NBR_CHARAS; ++i)
	{
		if (!chara_collection[i])
			break;
		if (chara_collection[i] == &man->charas[0])
			continue;

		get_all_tags(str_tags, chara_collection[i]);
		printf("\t\t['%s %s'.]\n", command, str_tags);
	}
	printf("\n");

	free(str_tags);
	return;
}

static void	get_all_tags(char *p_str, t_char *object)
{
	int	i;

	strncpy(p_str, object->tags[0], LEN_TAG);

	for (i = 1; i < NBR_TAGS; ++i)
	{
		if (!object->tags[i][0])
			break;
		strcat(p_str, " / ");
		strncat(p_str, object->tags[i], LEN_TAG);
	}
	return;
}
