#include "treasure_venture.h"

void	populate_list_items(t_man *man)
{
	memset(man->items, 0, NBR_ITEMS * sizeof(t_item));

	man->items[ITEM_ENTRY_DOORS - 1].id = ITEM_ENTRY_DOORS;
	man->items[ITEM_ENTRY_DOORS - 1].bool_is_singular = 0;
	man->items[ITEM_ENTRY_DOORS - 1].access = ACCESS_CLOSED;
	man->items[ITEM_ENTRY_DOORS - 1].unlocked_with = man->items + (ITEM_ENTRY_DOORS_KEY - 1);
	man->items[ITEM_ENTRY_DOORS - 1].bool_can_be_taken = 0;
	man->items[ITEM_ENTRY_DOORS - 1].bool_requires_target_for_use = 0;
	strncpy(man->items[ITEM_ENTRY_DOORS - 1].tags[0], "main entry doors", LEN_TAG);
	strncpy(man->items[ITEM_ENTRY_DOORS - 1].tags[1], "main double doors", LEN_TAG);
	strncpy(man->items[ITEM_ENTRY_DOORS - 1].tags[2], "main doors", LEN_TAG);
	strncpy(man->items[ITEM_ENTRY_DOORS - 1].tags[3], "entry doors", LEN_TAG);
	strncpy(man->items[ITEM_ENTRY_DOORS - 1].tags[4], "double doors", LEN_TAG);
	strncpy(man->items[ITEM_ENTRY_DOORS - 1].tags[5], "doors", LEN_TAG);
	strncpy(man->items[ITEM_ENTRY_DOORS - 1].desc, "The entry doors of the mansion.",
		LEN_DESC);
	strncpy(man->items[ITEM_ENTRY_DOORS - 1].desc_look_around, "The entry doors of the "
		"mansion.", LEN_DESC);
	strncpy(man->items[ITEM_ENTRY_DOORS - 1].desc_look_item, "The entry doors of the mansion.",
		LEN_DESC);

	man->items[ITEM_GRANDFATHER_CLOCK - 1].id = ITEM_GRANDFATHER_CLOCK;
	man->items[ITEM_GRANDFATHER_CLOCK - 1].bool_is_singular = 1;
	man->items[ITEM_GRANDFATHER_CLOCK - 1].bool_can_be_taken = 0;
	man->items[ITEM_GRANDFATHER_CLOCK - 1].bool_requires_target_for_use = 0;
	strncpy(man->items[ITEM_GRANDFATHER_CLOCK - 1].tags[0], "grandfather clock", LEN_TAG);
	strncpy(man->items[ITEM_GRANDFATHER_CLOCK - 1].tags[1], "clock", LEN_TAG);
	strncpy(man->items[ITEM_GRANDFATHER_CLOCK - 1].desc, "A grandfather clock.", LEN_DESC);
	strncpy(man->items[ITEM_GRANDFATHER_CLOCK - 1].desc_look_around, "The loud ticks of the "
		"grandfather clock is nerve-wracking. You've always hated those.", LEN_DESC);
	strncpy(man->items[ITEM_GRANDFATHER_CLOCK - 1].desc_look_item, "The clock doesn't seem to "
		"hide any secret.", LEN_DESC);

	man->items[ITEM_LIBRARY_DOOR - 1].id = ITEM_LIBRARY_DOOR;
	man->items[ITEM_LIBRARY_DOOR - 1].bool_is_singular = 1;
	man->items[ITEM_LIBRARY_DOOR - 1].access = ACCESS_CLOSED;
	man->items[ITEM_LIBRARY_DOOR - 1].bool_can_be_taken = 0;
	man->items[ITEM_LIBRARY_DOOR - 1].bool_requires_target_for_use = 0;
	strncpy(man->items[ITEM_LIBRARY_DOOR - 1].tags[0], "old library door", LEN_TAG);
	strncpy(man->items[ITEM_LIBRARY_DOOR - 1].tags[1], "library door", LEN_TAG);
	strncpy(man->items[ITEM_LIBRARY_DOOR - 1].tags[2], "door", LEN_TAG);
	strncpy(man->items[ITEM_LIBRARY_DOOR - 1].desc, "The door to the old library.", LEN_DESC);
	strncpy(man->items[ITEM_LIBRARY_DOOR - 1].desc_look_around, "The door to the old library.",
		LEN_DESC);
	strncpy(man->items[ITEM_LIBRARY_DOOR - 1].desc_look_item, "The door to the old library.",
		LEN_DESC);

	man->items[ITEM_LIBRARY_SIGN - 1].id = ITEM_LIBRARY_SIGN;
	man->items[ITEM_LIBRARY_SIGN - 1].bool_is_singular = 1;
	man->items[ITEM_LIBRARY_SIGN - 1].bool_can_be_taken = 0;
	man->items[ITEM_LIBRARY_SIGN - 1].bool_requires_target_for_use = 0;
	strncpy(man->items[ITEM_LIBRARY_SIGN - 1].tags[0], "library sign", LEN_TAG);
	strncpy(man->items[ITEM_LIBRARY_SIGN - 1].tags[1], "sign", LEN_TAG);
	strncpy(man->items[ITEM_LIBRARY_SIGN - 1].desc, "A sign that reads 'Library'.", LEN_DESC);
	strncpy(man->items[ITEM_LIBRARY_SIGN - 1].desc_look_around, "", LEN_DESC);
	strncpy(man->items[ITEM_LIBRARY_SIGN - 1].desc_look_item, "A sign that reads 'Library'.",
		LEN_DESC);

	man->items[ITEM_BOOKS - 1].id = ITEM_BOOKS;
	man->items[ITEM_BOOKS - 1].bool_is_singular = 0;
	man->items[ITEM_BOOKS - 1].bool_can_be_taken = 0;
	man->items[ITEM_BOOKS - 1].bool_requires_target_for_use = 0;
	strncpy(man->items[ITEM_BOOKS - 1].tags[0], "books", LEN_TAG);
	strncpy(man->items[ITEM_BOOKS - 1].desc, "Books from the mansion's old library.",
		LEN_DESC);
	strncpy(man->items[ITEM_BOOKS - 1].desc_look_around, "The library walls are lined with "
		"old, dusty books.", LEN_DESC);
	strncpy(man->items[ITEM_BOOKS - 1].desc_look_item, "Let's not focus on the books.", LEN_DESC);

	man->items[ITEM_DOOR_ROOM_1 - 1].id = ITEM_DOOR_ROOM_1;
	man->items[ITEM_DOOR_ROOM_1 - 1].bool_is_singular = 1;
	man->items[ITEM_DOOR_ROOM_1 - 1].access = ACCESS_CLOSED;
	man->items[ITEM_DOOR_ROOM_1 - 1].bool_can_be_taken = 0;
	man->items[ITEM_DOOR_ROOM_1 - 1].bool_requires_target_for_use = 0;
	strncpy(man->items[ITEM_DOOR_ROOM_1 - 1].tags[0], "first room door", LEN_TAG);
	strncpy(man->items[ITEM_DOOR_ROOM_1 - 1].tags[1], "door room 1", LEN_TAG);
	strncpy(man->items[ITEM_DOOR_ROOM_1 - 1].tags[2], "door", LEN_TAG);
	strncpy(man->items[ITEM_DOOR_ROOM_1 - 1].desc, "The door to the first room.", LEN_DESC);
	strncpy(man->items[ITEM_DOOR_ROOM_1 - 1].desc_look_around, "The door to the first room.",
		LEN_DESC);
	strncpy(man->items[ITEM_DOOR_ROOM_1 - 1].desc_look_item, "The door to the first room.", LEN_DESC);

	man->items[ITEM_DOOR_ROOM_2 - 1].id = ITEM_DOOR_ROOM_2;
	man->items[ITEM_DOOR_ROOM_2 - 1].bool_is_singular = 1;
	man->items[ITEM_DOOR_ROOM_2 - 1].access = ACCESS_CLOSED;
	man->items[ITEM_DOOR_ROOM_2 - 1].bool_can_be_taken = 0;
	man->items[ITEM_DOOR_ROOM_2 - 1].bool_requires_target_for_use = 0;
	strncpy(man->items[ITEM_DOOR_ROOM_2 - 1].tags[0], "second room door", LEN_TAG);
	strncpy(man->items[ITEM_DOOR_ROOM_2 - 1].tags[1], "door room 2", LEN_TAG);
	strncpy(man->items[ITEM_DOOR_ROOM_2 - 1].tags[2], "door", LEN_TAG);
	strncpy(man->items[ITEM_DOOR_ROOM_2 - 1].desc, "The door to the second room.", LEN_DESC);
	strncpy(man->items[ITEM_DOOR_ROOM_2 - 1].desc_look_around, "The door to the second room.",
		LEN_DESC);
	strncpy(man->items[ITEM_DOOR_ROOM_2 - 1].desc_look_item, "The door to the second room.",
		LEN_DESC);

	man->items[ITEM_DOOR_ROOM_3 - 1].id = ITEM_DOOR_ROOM_3;
	man->items[ITEM_DOOR_ROOM_3 - 1].bool_is_singular = 1;
	man->items[ITEM_DOOR_ROOM_3 - 1].access = ACCESS_CLOSED;
	man->items[ITEM_DOOR_ROOM_3 - 1].bool_can_be_taken = 0;
	man->items[ITEM_DOOR_ROOM_3 - 1].bool_requires_target_for_use = 0;
	strncpy(man->items[ITEM_DOOR_ROOM_3 - 1].tags[0], "third room door", LEN_TAG);
	strncpy(man->items[ITEM_DOOR_ROOM_3 - 1].tags[1], "door room 3", LEN_TAG);
	strncpy(man->items[ITEM_DOOR_ROOM_3 - 1].tags[2], "door", LEN_TAG);
	strncpy(man->items[ITEM_DOOR_ROOM_3 - 1].desc, "The door to the third room.", LEN_DESC);
	strncpy(man->items[ITEM_DOOR_ROOM_3 - 1].desc_look_around, "The door to the third room.",
		LEN_DESC);
	strncpy(man->items[ITEM_DOOR_ROOM_3 - 1].desc_look_item, "The door to the third room.", LEN_DESC);

	man->items[ITEM_ENTRY_DOORS_KEY - 1].id = ITEM_ENTRY_DOORS_KEY;
	man->items[ITEM_ENTRY_DOORS_KEY - 1].bool_is_singular = 1;
	man->items[ITEM_ENTRY_DOORS_KEY - 1].bool_can_be_taken = 1;
	man->items[ITEM_ENTRY_DOORS_KEY - 1].bool_requires_target_for_use = 1;
	strncpy(man->items[ITEM_ENTRY_DOORS_KEY - 1].tags[0], "shiny thing", LEN_TAG);
	strncpy(man->items[ITEM_ENTRY_DOORS_KEY - 1].desc, "The key to the mansion's entry "
		"doors.", LEN_DESC);
	strncpy(man->items[ITEM_ENTRY_DOORS_KEY - 1].desc_look_around, "Something shiny, left "
		"unattended on the ground, catches your attention.", LEN_DESC);
	strncpy(man->items[ITEM_ENTRY_DOORS_KEY - 1].desc_look_item, "It's a key. It shines in a "
		"golden color, and a small note attached to it with a string reads "
		"\"Entry\".", LEN_DESC);
	return;
}
