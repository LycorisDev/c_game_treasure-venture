#include "treasure_venture.h"

void	populate_list_locs(t_man *man)
{
	t_exit	exit_objects[NBR_LOCS];

	exit_objects[1].to = man->locs + (LOC_OUTSIDE - 1);
	exit_objects[1].passage = man->items + (ITEM_ENTRY_DOORS - 1);
	exit_objects[2].to = man->locs + (LOC_MAIN_HALLWAY - 1);
	exit_objects[2].passage = man->items + (ITEM_ENTRY_DOORS - 1);
	exit_objects[3].to = man->locs + (LOC_OLD_LIBRARY - 1);
	exit_objects[3].passage = man->items + (ITEM_LIBRARY_DOOR - 1);
	exit_objects[4].to = man->locs + (LOC_MAIN_HALLWAY - 1);
	exit_objects[4].passage = man->items + (ITEM_LIBRARY_DOOR - 1);
	exit_objects[5].to = man->locs + (LOC_ROOM_1 - 1);
	exit_objects[5].passage = man->items + (ITEM_DOOR_ROOM_1 - 1);
	exit_objects[6].to = man->locs + (LOC_ROOM_2 - 1);
	exit_objects[6].passage = man->items + (ITEM_DOOR_ROOM_2 - 1);
	exit_objects[7].to = man->locs + (LOC_ROOM_3 - 1);
	exit_objects[7].passage = man->items + (ITEM_DOOR_ROOM_3 - 1);
	exit_objects[8].to = man->locs + (LOC_OLD_LIBRARY - 1);
	exit_objects[8].passage = man->items + (ITEM_DOOR_ROOM_1 - 1);
	exit_objects[9].to = man->locs + (LOC_OLD_LIBRARY - 1);
	exit_objects[9].passage = man->items + (ITEM_DOOR_ROOM_2 - 1);
	exit_objects[10].to = man->locs + (LOC_OLD_LIBRARY - 1);
	exit_objects[10].passage = man->items + (ITEM_DOOR_ROOM_3 - 1);

	memset(man->geo_aff, 0, NBR_GEO_AFF * sizeof(t_geo_aff));
	memset(man->locs, 0, NBR_LOCS * sizeof(t_loc));

	man->geo_aff[0].id = 1;
	strncpy(man->geo_aff[0].name, "world", LEN_TAG);
	man->geo_aff[1].id = 2;
	strncpy(man->geo_aff[1].name, "mansion", LEN_TAG);

	man->locs[LOC_OUTSIDE - 1].id = LOC_OUTSIDE;
	man->locs[LOC_OUTSIDE - 1].bool_is_indoors = 0;
	man->locs[LOC_OUTSIDE - 1].geo_aff = &(man->geo_aff[0]);
	strncpy(man->locs[LOC_OUTSIDE - 1].tags[0], "world", LEN_TAG);
	strncpy(man->locs[LOC_OUTSIDE - 1].desc, "", LEN_DESC);
	man->locs[LOC_OUTSIDE - 1].exits[0] = exit_objects[2];
	man->locs[LOC_OUTSIDE - 1].items[0] = man->items + (ITEM_ENTRY_DOORS - 1);
	man->locs[LOC_OUTSIDE - 1].charas[0] = &man->charas[0]; // Player

	man->locs[LOC_MAIN_HALLWAY - 1].id = LOC_MAIN_HALLWAY;
	man->locs[LOC_MAIN_HALLWAY - 1].bool_is_indoors = 1;
	man->locs[LOC_MAIN_HALLWAY - 1].geo_aff = &(man->geo_aff[1]);
	strncpy(man->locs[LOC_MAIN_HALLWAY - 1].tags[0], "main hallway", LEN_TAG);
	strncpy(man->locs[LOC_MAIN_HALLWAY - 1].tags[1], "hallway", LEN_TAG);
	strncpy(man->locs[LOC_MAIN_HALLWAY - 1].desc, "There is a heavy door topped "
		"with a sign.", LEN_DESC);
	man->locs[LOC_MAIN_HALLWAY - 1].exits[0] = exit_objects[1];
	man->locs[LOC_MAIN_HALLWAY - 1].exits[1] = exit_objects[3];
	man->locs[LOC_MAIN_HALLWAY - 1].items[0] = man->items + (ITEM_ENTRY_DOORS - 1);
	man->locs[LOC_MAIN_HALLWAY - 1].items[1] = man->items + (ITEM_GRANDFATHER_CLOCK - 1);
	man->locs[LOC_MAIN_HALLWAY - 1].items[2] = man->items + (ITEM_LIBRARY_DOOR - 1);
	man->locs[LOC_MAIN_HALLWAY - 1].items[3] = man->items + (ITEM_LIBRARY_SIGN - 1);

	man->locs[LOC_OLD_LIBRARY - 1].id = LOC_OLD_LIBRARY;
	man->locs[LOC_OLD_LIBRARY - 1].bool_is_indoors = 1;
	man->locs[LOC_OLD_LIBRARY - 1].geo_aff = &(man->geo_aff[1]);
	strncpy(man->locs[LOC_OLD_LIBRARY - 1].tags[0], "old library", LEN_TAG);
	strncpy(man->locs[LOC_OLD_LIBRARY - 1].tags[1], "library", LEN_TAG);
	strncpy(man->locs[LOC_OLD_LIBRARY - 1].desc, "A librarian is standing there, "
		"reading. In the back of the room, you can discern small doors. Three "
		"to be precise.", LEN_DESC);
	man->locs[LOC_OLD_LIBRARY - 1].exits[0] = exit_objects[4];
	man->locs[LOC_OLD_LIBRARY - 1].exits[1] = exit_objects[5];
	man->locs[LOC_OLD_LIBRARY - 1].exits[2] = exit_objects[6];
	man->locs[LOC_OLD_LIBRARY - 1].exits[3] = exit_objects[7];
	man->locs[LOC_OLD_LIBRARY - 1].items[0] = man->items + (ITEM_LIBRARY_DOOR - 1);
	man->locs[LOC_OLD_LIBRARY - 1].items[1] = man->items + (ITEM_BOOKS - 1);
	man->locs[LOC_OLD_LIBRARY - 1].items[2] = man->items + (ITEM_DOOR_ROOM_1 - 1);
	man->locs[LOC_OLD_LIBRARY - 1].items[3] = man->items + (ITEM_DOOR_ROOM_2 - 1);
	man->locs[LOC_OLD_LIBRARY - 1].items[4] = man->items + (ITEM_DOOR_ROOM_3 - 1);
	man->locs[LOC_OLD_LIBRARY - 1].charas[0] = &man->charas[1]; // Librarian

	man->locs[LOC_ROOM_1 - 1].id = LOC_ROOM_1;
	man->locs[LOC_ROOM_1 - 1].bool_is_indoors = 1;
	man->locs[LOC_ROOM_1 - 1].geo_aff = &(man->geo_aff[1]);
	strncpy(man->locs[LOC_ROOM_1 - 1].tags[0], "first room", LEN_TAG);
	strncpy(man->locs[LOC_ROOM_1 - 1].tags[1], "room 1", LEN_TAG);
	strncpy(man->locs[LOC_ROOM_1 - 1].desc, "The room seems empty.", LEN_DESC);
	man->locs[LOC_ROOM_1 - 1].exits[0] = exit_objects[8];
	man->locs[LOC_ROOM_1 - 1].items[0] = man->items + (ITEM_DOOR_ROOM_1 - 1);

	man->locs[LOC_ROOM_2 - 1].id = LOC_ROOM_2;
	man->locs[LOC_ROOM_2 - 1].bool_is_indoors = 1;
	man->locs[LOC_ROOM_2 - 1].geo_aff = &(man->geo_aff[1]);
	strncpy(man->locs[LOC_ROOM_2 - 1].tags[0], "second room", LEN_TAG);
	strncpy(man->locs[LOC_ROOM_2 - 1].tags[1], "room 2", LEN_TAG);
	strncpy(man->locs[LOC_ROOM_2 - 1].desc, "The room seems empty.", LEN_DESC);
	man->locs[LOC_ROOM_2 - 1].exits[0] = exit_objects[9];
	man->locs[LOC_ROOM_2 - 1].items[0] = man->items + (ITEM_DOOR_ROOM_2 - 1);
	man->locs[LOC_ROOM_2 - 1].items[1] = man->items + (ITEM_ENTRY_DOORS_KEY - 1);

	man->locs[LOC_ROOM_3 - 1].id = LOC_ROOM_3;
	man->locs[LOC_ROOM_3 - 1].bool_is_indoors = 1;
	man->locs[LOC_ROOM_3 - 1].geo_aff = &(man->geo_aff[1]);
	strncpy(man->locs[LOC_ROOM_3 - 1].tags[0], "third room", LEN_TAG);
	strncpy(man->locs[LOC_ROOM_3 - 1].tags[1], "room 3", LEN_TAG);
	strncpy(man->locs[LOC_ROOM_3 - 1].desc, "The room seems empty.", LEN_DESC);
	man->locs[LOC_ROOM_3 - 1].exits[0] = exit_objects[10];
	man->locs[LOC_ROOM_3 - 1].items[0] = man->items + (ITEM_DOOR_ROOM_3 - 1);
	return;
}
