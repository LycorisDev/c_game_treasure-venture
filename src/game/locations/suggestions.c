#include "treasure_venture.h"

static void	get_all_tags(char *p_str, t_loc *object);

void	display_loc_suggestions(t_loc *origin)
{
	int		i;
	char	*str_tags;
	int		bool_ins_out_already_printed;

	str_tags = 0;
	bool_ins_out_already_printed = 0;
	if (!origin || !origin->exits[0].to)
		return;

	str_tags = calloc(NBR_TAGS, LEN_TAG);

	printf("\t[Try:]\n");
	for (i = 0; i < NBR_LOCS; ++i)
	{
		if (!origin->exits[i].to)
			break;

		if (origin->geo_aff->id == origin->exits[i].to->geo_aff->id)
		{
			get_all_tags(str_tags, origin->exits[i].to);
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

static void	get_all_tags(char *p_str, t_loc *object)
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
