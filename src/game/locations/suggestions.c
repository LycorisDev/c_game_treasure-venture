#include "treasure_venture.h"

static void	get_all_tags(char *p_str, const int word_length,
				t_location *object);

void	display_location_suggestions(t_location *origin)
{
	int		i;
	char	*str_tags;
	int		word_length;
	int		bool_ins_out_already_printed;

	str_tags = 0;
	word_length = 0;
	bool_ins_out_already_printed = 0;
	if (!origin || !origin->exits[0].to)
		return;

	word_length = sizeof(origin->exits[0].to->tags[0]) + 3;
	str_tags = calloc(NBR_TAGS, word_length);

	printf("\t[Try:]\n");
	for (i = 0; i < NBR_LOCATIONS; ++i)
	{
		if (!origin->exits[i].to)
			break;

		if (origin->geo_aff->id == origin->exits[i].to->geo_aff->id)
		{
			get_all_tags(str_tags, word_length, origin->exits[i].to);
			printf("\t\t['Go %s'.]\n", str_tags);
			continue;
		}
		else if (bool_ins_out_already_printed)
			continue;

		bool_ins_out_already_printed = 1;
		if (origin->bool_is_indoors)
			printf("\t\t['Go outside'.]\n");
		else
			printf("\t\t['Go inside'.]\n");
	}
	printf("\n");

	free(str_tags);
	return;
}

static void	get_all_tags(char *p_str, const int word_length, t_location *object)
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
