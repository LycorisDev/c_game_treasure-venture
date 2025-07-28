#include "treasure_venture.h"

static void	get_all_tags(char *p_str, t_item *object);

void	display_item_suggestions(t_item **item_collection, const char *command)
{
	int		i;
	char	*str_tags;

	str_tags = 0;
	if (!strcmp(command, "look"))
		printf("\t[Try 'look around']\n\n");

	if (!item_collection[0])
		return;

	str_tags = calloc(NBR_TAGS, LEN_TAG);

	printf("\t[Try:]\n");
	for (i = 0; i < NBR_ITEMS; ++i)
	{
		if (!item_collection[i])
			break;

		get_all_tags(str_tags, item_collection[i]);
		printf("\t\t['%s %s'.]\n", command, str_tags);
	}
	printf("\n");

	free(str_tags);
	return;
}

static void	get_all_tags(char *p_str, t_item *object)
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
