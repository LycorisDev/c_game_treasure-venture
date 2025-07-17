#include "treasure_venture.h"

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

	memset(g_man.geo_aff, 0, NBR_GEO_AFF * sizeof(t_geo_aff));
	memset(g_man.locations, 0, NBR_LOCATIONS * sizeof(t_location));

	g_man.geo_aff[0].id = 1;
	memcpy(g_man.geo_aff[0].name, "world", 5);
	g_man.geo_aff[1].id = 2;
	memcpy(g_man.geo_aff[1].name, "mansion", 7);

	LOCATION_OUTSIDE->id = ID_LOCATION_OUTSIDE;
	LOCATION_OUTSIDE->bool_is_indoors = 0;
	LOCATION_OUTSIDE->geo_aff = &(g_man.geo_aff[0]);
	memcpy(LOCATION_OUTSIDE->tags[0], "world", 5);
	memcpy(LOCATION_OUTSIDE->description, "", 1);
	LOCATION_OUTSIDE->exits[0] = exit_objects[2];
	LOCATION_OUTSIDE->items[0] = ITEM_ENTRY_DOORS;
	LOCATION_OUTSIDE->characters[0] = PLAYER;

	LOCATION_MAIN_HALLWAY->id = ID_LOCATION_MAIN_HALLWAY;
	LOCATION_MAIN_HALLWAY->bool_is_indoors = 1;
	LOCATION_MAIN_HALLWAY->geo_aff = &(g_man.geo_aff[1]);
	memcpy(LOCATION_MAIN_HALLWAY->tags[0], "main hallway", 12);
	memcpy(LOCATION_MAIN_HALLWAY->tags[1], "hallway", 7);
	memcpy(LOCATION_MAIN_HALLWAY->description, "There is a heavy door topped "
		"with a sign.", 41);
	LOCATION_MAIN_HALLWAY->exits[0] = exit_objects[1];
	LOCATION_MAIN_HALLWAY->exits[1] = exit_objects[3];
	LOCATION_MAIN_HALLWAY->items[0] = ITEM_ENTRY_DOORS;
	LOCATION_MAIN_HALLWAY->items[1] = ITEM_GRANDFATHER_CLOCK;
	LOCATION_MAIN_HALLWAY->items[2] = ITEM_LIBRARY_DOOR;
	LOCATION_MAIN_HALLWAY->items[3] = ITEM_LIBRARY_SIGN;

	LOCATION_OLD_LIBRARY->id = ID_LOCATION_OLD_LIBRARY;
	LOCATION_OLD_LIBRARY->bool_is_indoors = 1;
	LOCATION_OLD_LIBRARY->geo_aff = &(g_man.geo_aff[1]);
	memcpy(LOCATION_OLD_LIBRARY->tags[0], "old library", 11);
	memcpy(LOCATION_OLD_LIBRARY->tags[1], "library", 7);
	memcpy(LOCATION_OLD_LIBRARY->description, "A librarian is standing there, "
		"reading. In the back of the room, you can discern small doors. Three "
		"to be precise.", 114);
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
	LOCATION_ROOM_1->geo_aff = &(g_man.geo_aff[1]);
	memcpy(LOCATION_ROOM_1->tags[0], "first room", 10);
	memcpy(LOCATION_ROOM_1->tags[1], "room 1", 6);
	memcpy(LOCATION_ROOM_1->description, "The room seems empty.", 21);
	LOCATION_ROOM_1->exits[0] = exit_objects[8];
	LOCATION_ROOM_1->items[0] = ITEM_DOOR_ROOM_1;

	LOCATION_ROOM_2->id = ID_LOCATION_ROOM_2;
	LOCATION_ROOM_2->bool_is_indoors = 1;
	LOCATION_ROOM_2->geo_aff = &(g_man.geo_aff[1]);
	memcpy(LOCATION_ROOM_2->tags[0], "second room", 11);
	memcpy(LOCATION_ROOM_2->tags[1], "room 2", 6);
	memcpy(LOCATION_ROOM_2->description, "The room seems empty.", 21);
	LOCATION_ROOM_2->exits[0] = exit_objects[9];
	LOCATION_ROOM_2->items[0] = ITEM_DOOR_ROOM_2;
	LOCATION_ROOM_2->items[1] = ITEM_ENTRY_DOORS_KEY;

	LOCATION_ROOM_3->id = ID_LOCATION_ROOM_3;
	LOCATION_ROOM_3->bool_is_indoors = 1;
	LOCATION_ROOM_3->geo_aff = &(g_man.geo_aff[1]);
	memcpy(LOCATION_ROOM_3->tags[0], "third room", 10);
	memcpy(LOCATION_ROOM_3->tags[1], "room 3", 6);
	memcpy(LOCATION_ROOM_3->description, "The room seems empty.", 21);
	LOCATION_ROOM_3->exits[0] = exit_objects[10];
	LOCATION_ROOM_3->items[0] = ITEM_DOOR_ROOM_3;
	return;
}
