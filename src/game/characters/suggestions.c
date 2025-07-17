#include "treasure_venture.h"

static void	get_all_tags(char *p_str, const int word_length,
				t_character *object);

void	display_character_suggestions(t_character **character_collection,
			const char* command)
{
	int		i;
	char	*str_tags;
	int		word_length;

	str_tags = 0;
	word_length = 0;
	if (!character_collection[0] 
			|| (!character_collection[1] && character_collection[0] == PLAYER))
		return;

	word_length = sizeof(character_collection[0]->tags[0]) + 3;
	str_tags = calloc(NBR_TAGS, word_length);

	printf("\t[Try:]\n");
	for (i = 0; i < NBR_CHARACTERS; ++i)
	{
		if (!character_collection[i])
			break;
		if (character_collection[i] == PLAYER)
			continue;

		get_all_tags(str_tags, word_length, character_collection[i]);
		printf("\t\t['%s %s'.]\n", command, str_tags);
	}
	printf("\n");

	free(str_tags);
	return;
}

static void	get_all_tags(char *p_str, const int word_length,
				t_character *object)
{
	int	i;

	strncpy(p_str, object->tags[0], word_length);

	for (i = 1; i < NBR_TAGS; ++i)
	{
		if (!object->tags[i][0])
			break;
		strcat(p_str, " / ");
		strncat(p_str, object->tags[i], word_length);
	}
	return;
}
