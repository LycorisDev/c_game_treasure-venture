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
	memcpy(man->items[ITEM_ENTRY_DOORS - 1].tags[0], "main entry doors", 16);
	memcpy(man->items[ITEM_ENTRY_DOORS - 1].tags[1], "main double doors", 17);
	memcpy(man->items[ITEM_ENTRY_DOORS - 1].tags[2], "main doors", 10);
	memcpy(man->items[ITEM_ENTRY_DOORS - 1].tags[3], "entry doors", 11);
	memcpy(man->items[ITEM_ENTRY_DOORS - 1].tags[4], "double doors", 12);
	memcpy(man->items[ITEM_ENTRY_DOORS - 1].tags[5], "doors", 5);
	memcpy(man->items[ITEM_ENTRY_DOORS - 1].description, "The entry doors of the mansion.",
		31);
	memcpy(man->items[ITEM_ENTRY_DOORS - 1].desc_look_around, "The entry doors of the "
		"mansion.", 31);
	memcpy(man->items[ITEM_ENTRY_DOORS - 1].desc_look_item, "The entry doors of the mansion.",
		31);

	man->items[ITEM_GRANDFATHER_CLOCK - 1].id = ITEM_GRANDFATHER_CLOCK;
	man->items[ITEM_GRANDFATHER_CLOCK - 1].bool_is_singular = 1;
	man->items[ITEM_GRANDFATHER_CLOCK - 1].bool_can_be_taken = 0;
	man->items[ITEM_GRANDFATHER_CLOCK - 1].bool_requires_target_for_use = 0;
	memcpy(man->items[ITEM_GRANDFATHER_CLOCK - 1].tags[0], "grandfather clock", 17);
	memcpy(man->items[ITEM_GRANDFATHER_CLOCK - 1].tags[1], "clock", 5);
	memcpy(man->items[ITEM_GRANDFATHER_CLOCK - 1].description, "A grandfather clock.", 20);
	memcpy(man->items[ITEM_GRANDFATHER_CLOCK - 1].desc_look_around, "The loud ticks of the "
		"grandfather clock is nerve-wracking. You've always hated those.", 85);
	memcpy(man->items[ITEM_GRANDFATHER_CLOCK - 1].desc_look_item, "The clock doesn't seem to "
		"hide any secret.", 42);

	man->items[ITEM_LIBRARY_DOOR - 1].id = ITEM_LIBRARY_DOOR;
	man->items[ITEM_LIBRARY_DOOR - 1].bool_is_singular = 1;
	man->items[ITEM_LIBRARY_DOOR - 1].access = ACCESS_CLOSED;
	man->items[ITEM_LIBRARY_DOOR - 1].bool_can_be_taken = 0;
	man->items[ITEM_LIBRARY_DOOR - 1].bool_requires_target_for_use = 0;
	memcpy(man->items[ITEM_LIBRARY_DOOR - 1].tags[0], "old library door", 16);
	memcpy(man->items[ITEM_LIBRARY_DOOR - 1].tags[1], "library door", 12);
	memcpy(man->items[ITEM_LIBRARY_DOOR - 1].tags[2], "door", 4);
	memcpy(man->items[ITEM_LIBRARY_DOOR - 1].description, "The door to the old library.", 28);
	memcpy(man->items[ITEM_LIBRARY_DOOR - 1].desc_look_around, "The door to the old library.",
		28);
	memcpy(man->items[ITEM_LIBRARY_DOOR - 1].desc_look_item, "The door to the old library.",
		28);

	man->items[ITEM_LIBRARY_SIGN - 1].id = ITEM_LIBRARY_SIGN;
	man->items[ITEM_LIBRARY_SIGN - 1].bool_is_singular = 1;
	man->items[ITEM_LIBRARY_SIGN - 1].bool_can_be_taken = 0;
	man->items[ITEM_LIBRARY_SIGN - 1].bool_requires_target_for_use = 0;
	memcpy(man->items[ITEM_LIBRARY_SIGN - 1].tags[0], "library sign", 12);
	memcpy(man->items[ITEM_LIBRARY_SIGN - 1].tags[1], "sign", 4);
	memcpy(man->items[ITEM_LIBRARY_SIGN - 1].description, "A sign that reads 'Library'.", 28);
	memcpy(man->items[ITEM_LIBRARY_SIGN - 1].desc_look_around, "", 1);
	memcpy(man->items[ITEM_LIBRARY_SIGN - 1].desc_look_item, "A sign that reads 'Library'.",
		28);

	man->items[ITEM_BOOKS - 1].id = ITEM_BOOKS;
	man->items[ITEM_BOOKS - 1].bool_is_singular = 0;
	man->items[ITEM_BOOKS - 1].bool_can_be_taken = 0;
	man->items[ITEM_BOOKS - 1].bool_requires_target_for_use = 0;
	memcpy(man->items[ITEM_BOOKS - 1].tags[0], "books", 5);
	memcpy(man->items[ITEM_BOOKS - 1].description, "Books from the mansion's old library.",
		37);
	memcpy(man->items[ITEM_BOOKS - 1].desc_look_around, "The library walls are lined with "
		"old, dusty books.", 50);
	memcpy(man->items[ITEM_BOOKS - 1].desc_look_item, "Let's not focus on the books.", 29);

	man->items[ITEM_DOOR_ROOM_1 - 1].id = ITEM_DOOR_ROOM_1;
	man->items[ITEM_DOOR_ROOM_1 - 1].bool_is_singular = 1;
	man->items[ITEM_DOOR_ROOM_1 - 1].access = ACCESS_CLOSED;
	man->items[ITEM_DOOR_ROOM_1 - 1].bool_can_be_taken = 0;
	man->items[ITEM_DOOR_ROOM_1 - 1].bool_requires_target_for_use = 0;
	memcpy(man->items[ITEM_DOOR_ROOM_1 - 1].tags[0], "first room door", 15);
	memcpy(man->items[ITEM_DOOR_ROOM_1 - 1].tags[1], "door room 1", 11);
	memcpy(man->items[ITEM_DOOR_ROOM_1 - 1].tags[2], "door", 4);
	memcpy(man->items[ITEM_DOOR_ROOM_1 - 1].description, "The door to the first room.", 27);
	memcpy(man->items[ITEM_DOOR_ROOM_1 - 1].desc_look_around, "The door to the first room.",
		27);
	memcpy(man->items[ITEM_DOOR_ROOM_1 - 1].desc_look_item, "The door to the first room.", 27);

	man->items[ITEM_DOOR_ROOM_2 - 1].id = ITEM_DOOR_ROOM_2;
	man->items[ITEM_DOOR_ROOM_2 - 1].bool_is_singular = 1;
	man->items[ITEM_DOOR_ROOM_2 - 1].access = ACCESS_CLOSED;
	man->items[ITEM_DOOR_ROOM_2 - 1].bool_can_be_taken = 0;
	man->items[ITEM_DOOR_ROOM_2 - 1].bool_requires_target_for_use = 0;
	memcpy(man->items[ITEM_DOOR_ROOM_2 - 1].tags[0], "second room door", 16);
	memcpy(man->items[ITEM_DOOR_ROOM_2 - 1].tags[1], "door room 2", 11);
	memcpy(man->items[ITEM_DOOR_ROOM_2 - 1].tags[2], "door", 4);
	memcpy(man->items[ITEM_DOOR_ROOM_2 - 1].description, "The door to the second room.", 28);
	memcpy(man->items[ITEM_DOOR_ROOM_2 - 1].desc_look_around, "The door to the second room.",
		28);
	memcpy(man->items[ITEM_DOOR_ROOM_2 - 1].desc_look_item, "The door to the second room.",
		28);

	man->items[ITEM_DOOR_ROOM_3 - 1].id = ITEM_DOOR_ROOM_3;
	man->items[ITEM_DOOR_ROOM_3 - 1].bool_is_singular = 1;
	man->items[ITEM_DOOR_ROOM_3 - 1].access = ACCESS_CLOSED;
	man->items[ITEM_DOOR_ROOM_3 - 1].bool_can_be_taken = 0;
	man->items[ITEM_DOOR_ROOM_3 - 1].bool_requires_target_for_use = 0;
	memcpy(man->items[ITEM_DOOR_ROOM_3 - 1].tags[0], "third room door", 15);
	memcpy(man->items[ITEM_DOOR_ROOM_3 - 1].tags[1], "door room 3", 11);
	memcpy(man->items[ITEM_DOOR_ROOM_3 - 1].tags[2], "door", 4);
	memcpy(man->items[ITEM_DOOR_ROOM_3 - 1].description, "The door to the third room.", 27);
	memcpy(man->items[ITEM_DOOR_ROOM_3 - 1].desc_look_around, "The door to the third room.",
		27);
	memcpy(man->items[ITEM_DOOR_ROOM_3 - 1].desc_look_item, "The door to the third room.", 27);

	man->items[ITEM_ENTRY_DOORS_KEY - 1].id = ITEM_ENTRY_DOORS_KEY;
	man->items[ITEM_ENTRY_DOORS_KEY - 1].bool_is_singular = 1;
	man->items[ITEM_ENTRY_DOORS_KEY - 1].bool_can_be_taken = 1;
	man->items[ITEM_ENTRY_DOORS_KEY - 1].bool_requires_target_for_use = 1;
	memcpy(man->items[ITEM_ENTRY_DOORS_KEY - 1].tags[0], "shiny thing", 11);
	memcpy(man->items[ITEM_ENTRY_DOORS_KEY - 1].description, "The key to the mansion's entry "
		"doors.", 37);
	memcpy(man->items[ITEM_ENTRY_DOORS_KEY - 1].desc_look_around, "Something shiny, left "
		"unattended on the ground, catches your attention.", 71);
	memcpy(man->items[ITEM_ENTRY_DOORS_KEY - 1].desc_look_item, "It's a key. It shines in a "
		"golden color, and a small note attached to it with a string reads "
		"\"Entry\".", 101);
	return;
}
