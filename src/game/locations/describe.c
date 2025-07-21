#include "treasure_venture.h"

void	describe_location(t_man *man, const t_location *location)
{
	int	i;

	/* Display location name */
	if (!man->characters[CHAR_PLAYER - 1].current_location->bool_is_indoors)
		printf("You are outside. ");
	else
		printf("You are in the %s. ", man->characters[CHAR_PLAYER - 1].current_location->tags[0]);

	/*
		TODO: Remove the need for this temporary fix. The geo_aff should be 
		described without being hardcoded, a bit like an event.
	*/
	if (location->bool_is_indoors)
		printf("%s ", location->description);
	else
		printf("The mansion in front of you gives you a bad feeling. Its "
			"main double doors don't look welcoming.");

	for (i = 0; i < NBR_ITEMS; ++i)
	{
		if (!location->items[i])
			break;

		/*
			Only mention items which are not an access to an exit, such as a 
			door
		*/
		if (!location->items[i]->access)
			printf("%s ", location->items[i]->desc_look_around);
	}

	printf("\n\n");
	return;
}
