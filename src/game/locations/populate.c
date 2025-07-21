#include "treasure_venture.h"

void	populate_list_locations(t_man *man)
{
	t_exit	exit_objects[NBR_LOCATIONS];

	exit_objects[1].to = man->locations + (LOC_OUTSIDE - 1);
	exit_objects[1].passage = man->items + (ITEM_ENTRY_DOORS - 1);
	exit_objects[2].to = man->locations + (LOC_MAIN_HALLWAY - 1);
	exit_objects[2].passage = man->items + (ITEM_ENTRY_DOORS - 1);
	exit_objects[3].to = man->locations + (LOC_OLD_LIBRARY - 1);
	exit_objects[3].passage = man->items + (ITEM_LIBRARY_DOOR - 1);
	exit_objects[4].to = man->locations + (LOC_MAIN_HALLWAY - 1);
	exit_objects[4].passage = man->items + (ITEM_LIBRARY_DOOR - 1);
	exit_objects[5].to = man->locations + (LOC_ROOM_1 - 1);
	exit_objects[5].passage = man->items + (ITEM_DOOR_ROOM_1 - 1);
	exit_objects[6].to = man->locations + (LOC_ROOM_2 - 1);
	exit_objects[6].passage = man->items + (ITEM_DOOR_ROOM_2 - 1);
	exit_objects[7].to = man->locations + (LOC_ROOM_3 - 1);
	exit_objects[7].passage = man->items + (ITEM_DOOR_ROOM_3 - 1);
	exit_objects[8].to = man->locations + (LOC_OLD_LIBRARY - 1);
	exit_objects[8].passage = man->items + (ITEM_DOOR_ROOM_1 - 1);
	exit_objects[9].to = man->locations + (LOC_OLD_LIBRARY - 1);
	exit_objects[9].passage = man->items + (ITEM_DOOR_ROOM_2 - 1);
	exit_objects[10].to = man->locations + (LOC_OLD_LIBRARY - 1);
	exit_objects[10].passage = man->items + (ITEM_DOOR_ROOM_3 - 1);

	memset(man->geo_aff, 0, NBR_GEO_AFF * sizeof(t_geo_aff));
	memset(man->locations, 0, NBR_LOCATIONS * sizeof(t_location));

	man->geo_aff[0].id = 1;
	memcpy(man->geo_aff[0].name, "world", 5);
	man->geo_aff[1].id = 2;
	memcpy(man->geo_aff[1].name, "mansion", 7);

	man->locations[LOC_OUTSIDE - 1].id = LOC_OUTSIDE;
	man->locations[LOC_OUTSIDE - 1].bool_is_indoors = 0;
	man->locations[LOC_OUTSIDE - 1].geo_aff = &(man->geo_aff[0]);
	memcpy(man->locations[LOC_OUTSIDE - 1].tags[0], "world", 5);
	memcpy(man->locations[LOC_OUTSIDE - 1].description, "", 1);
	man->locations[LOC_OUTSIDE - 1].exits[0] = exit_objects[2];
	man->locations[LOC_OUTSIDE - 1].items[0] = man->items + (ITEM_ENTRY_DOORS - 1);
	man->locations[LOC_OUTSIDE - 1].characters[0] = man->characters + (CHAR_PLAYER - 1);

	man->locations[LOC_MAIN_HALLWAY - 1].id = LOC_MAIN_HALLWAY;
	man->locations[LOC_MAIN_HALLWAY - 1].bool_is_indoors = 1;
	man->locations[LOC_MAIN_HALLWAY - 1].geo_aff = &(man->geo_aff[1]);
	memcpy(man->locations[LOC_MAIN_HALLWAY - 1].tags[0], "main hallway", 12);
	memcpy(man->locations[LOC_MAIN_HALLWAY - 1].tags[1], "hallway", 7);
	memcpy(man->locations[LOC_MAIN_HALLWAY - 1].description, "There is a heavy door topped "
		"with a sign.", 41);
	man->locations[LOC_MAIN_HALLWAY - 1].exits[0] = exit_objects[1];
	man->locations[LOC_MAIN_HALLWAY - 1].exits[1] = exit_objects[3];
	man->locations[LOC_MAIN_HALLWAY - 1].items[0] = man->items + (ITEM_ENTRY_DOORS - 1);
	man->locations[LOC_MAIN_HALLWAY - 1].items[1] = man->items + (ITEM_GRANDFATHER_CLOCK - 1);
	man->locations[LOC_MAIN_HALLWAY - 1].items[2] = man->items + (ITEM_LIBRARY_DOOR - 1);
	man->locations[LOC_MAIN_HALLWAY - 1].items[3] = man->items + (ITEM_LIBRARY_SIGN - 1);

	man->locations[LOC_OLD_LIBRARY - 1].id = LOC_OLD_LIBRARY;
	man->locations[LOC_OLD_LIBRARY - 1].bool_is_indoors = 1;
	man->locations[LOC_OLD_LIBRARY - 1].geo_aff = &(man->geo_aff[1]);
	memcpy(man->locations[LOC_OLD_LIBRARY - 1].tags[0], "old library", 11);
	memcpy(man->locations[LOC_OLD_LIBRARY - 1].tags[1], "library", 7);
	memcpy(man->locations[LOC_OLD_LIBRARY - 1].description, "A librarian is standing there, "
		"reading. In the back of the room, you can discern small doors. Three "
		"to be precise.", 114);
	man->locations[LOC_OLD_LIBRARY - 1].exits[0] = exit_objects[4];
	man->locations[LOC_OLD_LIBRARY - 1].exits[1] = exit_objects[5];
	man->locations[LOC_OLD_LIBRARY - 1].exits[2] = exit_objects[6];
	man->locations[LOC_OLD_LIBRARY - 1].exits[3] = exit_objects[7];
	man->locations[LOC_OLD_LIBRARY - 1].items[0] = man->items + (ITEM_LIBRARY_DOOR - 1);
	man->locations[LOC_OLD_LIBRARY - 1].items[1] = man->items + (ITEM_BOOKS - 1);
	man->locations[LOC_OLD_LIBRARY - 1].items[2] = man->items + (ITEM_DOOR_ROOM_1 - 1);
	man->locations[LOC_OLD_LIBRARY - 1].items[3] = man->items + (ITEM_DOOR_ROOM_2 - 1);
	man->locations[LOC_OLD_LIBRARY - 1].items[4] = man->items + (ITEM_DOOR_ROOM_3 - 1);
	man->locations[LOC_OLD_LIBRARY - 1].characters[0] = man->characters + (CHAR_LIBRARIAN - 1);

	man->locations[LOC_ROOM_1 - 1].id = LOC_ROOM_1;
	man->locations[LOC_ROOM_1 - 1].bool_is_indoors = 1;
	man->locations[LOC_ROOM_1 - 1].geo_aff = &(man->geo_aff[1]);
	memcpy(man->locations[LOC_ROOM_1 - 1].tags[0], "first room", 10);
	memcpy(man->locations[LOC_ROOM_1 - 1].tags[1], "room 1", 6);
	memcpy(man->locations[LOC_ROOM_1 - 1].description, "The room seems empty.", 21);
	man->locations[LOC_ROOM_1 - 1].exits[0] = exit_objects[8];
	man->locations[LOC_ROOM_1 - 1].items[0] = man->items + (ITEM_DOOR_ROOM_1 - 1);

	man->locations[LOC_ROOM_2 - 1].id = LOC_ROOM_2;
	man->locations[LOC_ROOM_2 - 1].bool_is_indoors = 1;
	man->locations[LOC_ROOM_2 - 1].geo_aff = &(man->geo_aff[1]);
	memcpy(man->locations[LOC_ROOM_2 - 1].tags[0], "second room", 11);
	memcpy(man->locations[LOC_ROOM_2 - 1].tags[1], "room 2", 6);
	memcpy(man->locations[LOC_ROOM_2 - 1].description, "The room seems empty.", 21);
	man->locations[LOC_ROOM_2 - 1].exits[0] = exit_objects[9];
	man->locations[LOC_ROOM_2 - 1].items[0] = man->items + (ITEM_DOOR_ROOM_2 - 1);
	man->locations[LOC_ROOM_2 - 1].items[1] = man->items + (ITEM_ENTRY_DOORS_KEY - 1);

	man->locations[LOC_ROOM_3 - 1].id = LOC_ROOM_3;
	man->locations[LOC_ROOM_3 - 1].bool_is_indoors = 1;
	man->locations[LOC_ROOM_3 - 1].geo_aff = &(man->geo_aff[1]);
	memcpy(man->locations[LOC_ROOM_3 - 1].tags[0], "third room", 10);
	memcpy(man->locations[LOC_ROOM_3 - 1].tags[1], "room 3", 6);
	memcpy(man->locations[LOC_ROOM_3 - 1].description, "The room seems empty.", 21);
	man->locations[LOC_ROOM_3 - 1].exits[0] = exit_objects[10];
	man->locations[LOC_ROOM_3 - 1].items[0] = man->items + (ITEM_DOOR_ROOM_3 - 1);
	return;
}
