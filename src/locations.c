#include "locations.h"
#include "main.h"
#include "items.h"

static void	get_all_tags(char *p_str, const int word_length, t_location *object);
static int	bool_location_matches_parser(const t_location *destination,
				const char *parser);

t_location	g_list_locations[NBR_LOCATIONS]; /* Declared as extern in locations.h */
t_geo_aff	g_list_geo_aff[NBR_GEO_AFF]; /* Declared as extern in locations.h */

void	populate_list_locations(void)
{
	t_exit	exit_objects[NBR_LOCATIONS];

	exit_objects[1].to = LOCATION_OUTSIDE;
	exit_objects[1].passage = ITEM_ENTRY_DOORS;
	exit_objects[2].to = LOCATION_MAIN_HALLWAY;
	exit_objects[2].passage = ITEM_ENTRY_DOORS;
	exit_objects[3].to = LOCATION_OLD_LIBRARY;
	exit_objects[3].passage = ITEM_LIBRARY_DOOR;
	exit_objects[4].to = LOCATION_MAIN_HALLWAY;
	exit_objects[4].passage = ITEM_LIBRARY_DOOR;
	exit_objects[5].to = LOCATION_ROOM_1;
	exit_objects[5].passage = ITEM_DOOR_ROOM_1;
	exit_objects[6].to = LOCATION_ROOM_2;
	exit_objects[6].passage = ITEM_DOOR_ROOM_2;
	exit_objects[7].to = LOCATION_ROOM_3;
	exit_objects[7].passage = ITEM_DOOR_ROOM_3;
	exit_objects[8].to = LOCATION_OLD_LIBRARY;
	exit_objects[8].passage = ITEM_DOOR_ROOM_1;
	exit_objects[9].to = LOCATION_OLD_LIBRARY;
	exit_objects[9].passage = ITEM_DOOR_ROOM_2;
	exit_objects[10].to = LOCATION_OLD_LIBRARY;
	exit_objects[10].passage = ITEM_DOOR_ROOM_3;

	memset(g_list_geo_aff, 0, NBR_GEO_AFF * sizeof(t_geo_aff));
	memset(g_list_locations, 0, NBR_LOCATIONS * sizeof(t_location));

	g_list_geo_aff[0].id = 1;
	memcpy(g_list_geo_aff[0].name, "world", 5);
	g_list_geo_aff[1].id = 2;
	memcpy(g_list_geo_aff[1].name, "mansion", 7);

	LOCATION_OUTSIDE->id = ID_LOCATION_OUTSIDE;
	LOCATION_OUTSIDE->bool_is_indoors = 0;
	LOCATION_OUTSIDE->geo_aff = &(g_list_geo_aff[0]);
	memcpy(LOCATION_OUTSIDE->tags[0], "world", 5);
	memcpy(LOCATION_OUTSIDE->description, "", 1);
	LOCATION_OUTSIDE->exits[0] = exit_objects[2];
	LOCATION_OUTSIDE->items[0] = ITEM_ENTRY_DOORS;
	LOCATION_OUTSIDE->characters[0] = PLAYER;

	LOCATION_MAIN_HALLWAY->id = ID_LOCATION_MAIN_HALLWAY;
	LOCATION_MAIN_HALLWAY->bool_is_indoors = 1;
	LOCATION_MAIN_HALLWAY->geo_aff = &(g_list_geo_aff[1]);
	memcpy(LOCATION_MAIN_HALLWAY->tags[0], "main hallway", 12);
	memcpy(LOCATION_MAIN_HALLWAY->tags[1], "hallway", 7);
	memcpy(LOCATION_MAIN_HALLWAY->description, "There is a heavy door topped with a sign.", 41);
	LOCATION_MAIN_HALLWAY->exits[0] = exit_objects[1];
	LOCATION_MAIN_HALLWAY->exits[1] = exit_objects[3];
	LOCATION_MAIN_HALLWAY->items[0] = ITEM_ENTRY_DOORS;
	LOCATION_MAIN_HALLWAY->items[1] = ITEM_GRANDFATHER_CLOCK;
	LOCATION_MAIN_HALLWAY->items[2] = ITEM_LIBRARY_DOOR;
	LOCATION_MAIN_HALLWAY->items[3] = ITEM_LIBRARY_SIGN;

	LOCATION_OLD_LIBRARY->id = ID_LOCATION_OLD_LIBRARY;
	LOCATION_OLD_LIBRARY->bool_is_indoors = 1;
	LOCATION_OLD_LIBRARY->geo_aff = &(g_list_geo_aff[1]);
	memcpy(LOCATION_OLD_LIBRARY->tags[0], "old library", 11);
	memcpy(LOCATION_OLD_LIBRARY->tags[1], "library", 7);
	memcpy(LOCATION_OLD_LIBRARY->description, "A librarian is standing there, reading. In the back of the room, you can discern small doors. Three to be precise.", 114);
	LOCATION_OLD_LIBRARY->exits[0] = exit_objects[4];
	LOCATION_OLD_LIBRARY->exits[1] = exit_objects[5];
	LOCATION_OLD_LIBRARY->exits[2] = exit_objects[6];
	LOCATION_OLD_LIBRARY->exits[3] = exit_objects[7];
	LOCATION_OLD_LIBRARY->items[0] = ITEM_LIBRARY_DOOR;
	LOCATION_OLD_LIBRARY->items[1] = ITEM_BOOKS;
	LOCATION_OLD_LIBRARY->items[2] = ITEM_DOOR_ROOM_1;
	LOCATION_OLD_LIBRARY->items[3] = ITEM_DOOR_ROOM_2;
	LOCATION_OLD_LIBRARY->items[4] = ITEM_DOOR_ROOM_3;
	LOCATION_OLD_LIBRARY->characters[0] = CHARACTER_LIBRARIAN;

	LOCATION_ROOM_1->id = ID_LOCATION_ROOM_1;
	LOCATION_ROOM_1->bool_is_indoors = 1;
	LOCATION_ROOM_1->geo_aff = &(g_list_geo_aff[1]);
	memcpy(LOCATION_ROOM_1->tags[0], "first room", 10);
	memcpy(LOCATION_ROOM_1->tags[1], "room 1", 6);
	memcpy(LOCATION_ROOM_1->description, "The room seems empty.", 21);
	LOCATION_ROOM_1->exits[0] = exit_objects[8];
	LOCATION_ROOM_1->items[0] = ITEM_DOOR_ROOM_1;

	LOCATION_ROOM_2->id = ID_LOCATION_ROOM_2;
	LOCATION_ROOM_2->bool_is_indoors = 1;
	LOCATION_ROOM_2->geo_aff = &(g_list_geo_aff[1]);
	memcpy(LOCATION_ROOM_2->tags[0], "second room", 11);
	memcpy(LOCATION_ROOM_2->tags[1], "room 2", 6);
	memcpy(LOCATION_ROOM_2->description, "The room seems empty.", 21);
	LOCATION_ROOM_2->exits[0] = exit_objects[9];
	LOCATION_ROOM_2->items[0] = ITEM_DOOR_ROOM_2;
	LOCATION_ROOM_2->items[1] = ITEM_ENTRY_DOORS_KEY;

	LOCATION_ROOM_3->id = ID_LOCATION_ROOM_3;
	LOCATION_ROOM_3->bool_is_indoors = 1;
	LOCATION_ROOM_3->geo_aff = &(g_list_geo_aff[1]);
	memcpy(LOCATION_ROOM_3->tags[0], "third room", 10);
	memcpy(LOCATION_ROOM_3->tags[1], "room 3", 6);
	memcpy(LOCATION_ROOM_3->description, "The room seems empty.", 21);
	LOCATION_ROOM_3->exits[0] = exit_objects[10];
	LOCATION_ROOM_3->items[0] = ITEM_DOOR_ROOM_3;
	return;
}

void	describe_location(const t_location *location)
{
	int	i;

	/* Display location name */
	if (!PLAYER->current_location->bool_is_indoors)
		add_output("You are outside. ");
	else
		add_output("You are in the %s. ", PLAYER->current_location->tags[0]);

	/* TODO: Remove the need for this temporary fix. The geo_aff should be described without being hardcoded, a bit like an event. */
	if (location->bool_is_indoors)
		add_output("%s ", location->description);
	else
		add_output("The mansion in front of you gives you a bad feeling. Its main double doors don't look welcoming.");

	for (i = 0; i < NBR_ITEMS; ++i)
	{
		if (!location->items[i])
			break;

		/* Only mention items which are not an access to an exit, such as a door */
		if (!location->items[i]->access)
			add_output("%s ", location->items[i]->desc_look_around);
	}

	add_output("\n\n");
	return;
}

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

	add_output("\t[Try:]\n");
	for (i = 0; i < NBR_LOCATIONS; ++i)
	{
		if (!origin->exits[i].to)
			break;

		if (origin->geo_aff->id == origin->exits[i].to->geo_aff->id)
		{
			get_all_tags(str_tags, word_length, origin->exits[i].to);
			add_output("\t\t['Go %s'.]\n", str_tags);
			continue;
		}
		else if (bool_ins_out_already_printed)
			continue;

		bool_ins_out_already_printed = 1;
		if (origin->bool_is_indoors)
			add_output("\t\t['Go outside'.]\n");
		else
			add_output("\t\t['Go inside'.]\n");
	}
	add_output("\n");

	free(str_tags);
	return;
}

t_exit	**retrieve_locations(t_location *origin, const char *parser)
{
	int		i;
	int		j;
	t_exit	**locations;

	locations = calloc(NBR_LOCATIONS, sizeof(t_exit *));
	if (!locations)
		return 0;

	for (i = 0, j = 0; i < NBR_LOCATIONS; ++i)
	{
		if (!origin->exits[i].to)
			break;

		/* "go [building]" */
		if (origin->geo_aff->id != origin->exits[i].to->geo_aff->id) 
		{
			if (!strcmp(parser, origin->exits[i].to->geo_aff->name))
				locations[j++] = &(origin->exits[i]);
			continue;
		}

		/* "go [room]" */
		if (bool_location_matches_parser(origin->exits[i].to, parser))
			locations[j++] = &(origin->exits[i]);
	}

	return locations;
}

t_exit	**retrieve_locations_with_passage_item(t_location *origin,
			const char *parser)
{
	int		i;
	int		j;
	t_exit	**exits;

	exits = calloc(NBR_LOCATIONS, sizeof(t_exit *));
	if (!exits)
		return 0;

	for (i = 0, j = 0; i < NBR_LOCATIONS; ++i)
	{
		if (!origin->exits[i].to || !origin->exits[i].passage->access)
			break;

		if (bool_item_matches_parser(origin->exits[i].passage, parser))
			exits[j++] = &(origin->exits[i]);
	}

	return exits;
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

static int	bool_location_matches_parser(const t_location *destination,
				const char *parser)
{
	int	i;

	for (i = 0; i < NBR_TAGS; ++i)
	{
		if (!destination->tags[i])
			return 0;

		if (!strcmp(parser, destination->tags[i]))
			return 1;
	}
	return 0;
}
