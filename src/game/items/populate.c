#include "items.h"
#include "main.h"

void	populate_list_items(void)
{
	memset(g_list_items, 0, NBR_ITEMS * sizeof(t_item));

	ITEM_ENTRY_DOORS->id = ID_ITEM_ENTRY_DOORS;
	ITEM_ENTRY_DOORS->bool_is_singular = 0;
	ITEM_ENTRY_DOORS->access = ACCESS_CLOSED;
	ITEM_ENTRY_DOORS->unlocked_with = ITEM_ENTRY_DOORS_KEY;
	ITEM_ENTRY_DOORS->bool_can_be_taken = 0;
	ITEM_ENTRY_DOORS->bool_requires_target_for_use = 0;
	memcpy(ITEM_ENTRY_DOORS->tags[0], "main entry doors", 16);
	memcpy(ITEM_ENTRY_DOORS->tags[1], "main double doors", 17);
	memcpy(ITEM_ENTRY_DOORS->tags[2], "main doors", 10);
	memcpy(ITEM_ENTRY_DOORS->tags[3], "entry doors", 11);
	memcpy(ITEM_ENTRY_DOORS->tags[4], "double doors", 12);
	memcpy(ITEM_ENTRY_DOORS->tags[5], "doors", 5);
	memcpy(ITEM_ENTRY_DOORS->description, "The entry doors of the mansion.",
		31);
	memcpy(ITEM_ENTRY_DOORS->desc_look_around, "The entry doors of the "
		"mansion.", 31);
	memcpy(ITEM_ENTRY_DOORS->desc_look_item, "The entry doors of the mansion.",
		31);

	ITEM_GRANDFATHER_CLOCK->id = ID_ITEM_GRANDFATHER_CLOCK;
	ITEM_GRANDFATHER_CLOCK->bool_is_singular = 1;
	ITEM_GRANDFATHER_CLOCK->bool_can_be_taken = 0;
	ITEM_GRANDFATHER_CLOCK->bool_requires_target_for_use = 0;
	memcpy(ITEM_GRANDFATHER_CLOCK->tags[0], "grandfather clock", 17);
	memcpy(ITEM_GRANDFATHER_CLOCK->tags[1], "clock", 5);
	memcpy(ITEM_GRANDFATHER_CLOCK->description, "A grandfather clock.", 20);
	memcpy(ITEM_GRANDFATHER_CLOCK->desc_look_around, "The loud ticks of the "
		"grandfather clock is nerve-wracking. You've always hated those.", 85);
	memcpy(ITEM_GRANDFATHER_CLOCK->desc_look_item, "The clock doesn't seem to "
		"hide any secret.", 42);

	ITEM_LIBRARY_DOOR->id = ID_ITEM_LIBRARY_DOOR;
	ITEM_LIBRARY_DOOR->bool_is_singular = 1;
	ITEM_LIBRARY_DOOR->access = ACCESS_CLOSED;
	ITEM_LIBRARY_DOOR->bool_can_be_taken = 0;
	ITEM_LIBRARY_DOOR->bool_requires_target_for_use = 0;
	memcpy(ITEM_LIBRARY_DOOR->tags[0], "old library door", 16);
	memcpy(ITEM_LIBRARY_DOOR->tags[1], "library door", 12);
	memcpy(ITEM_LIBRARY_DOOR->tags[2], "door", 4);
	memcpy(ITEM_LIBRARY_DOOR->description, "The door to the old library.", 28);
	memcpy(ITEM_LIBRARY_DOOR->desc_look_around, "The door to the old library.",
		28);
	memcpy(ITEM_LIBRARY_DOOR->desc_look_item, "The door to the old library.",
		28);

	ITEM_LIBRARY_SIGN->id = ID_ITEM_LIBRARY_SIGN;
	ITEM_LIBRARY_SIGN->bool_is_singular = 1;
	ITEM_LIBRARY_SIGN->bool_can_be_taken = 0;
	ITEM_LIBRARY_SIGN->bool_requires_target_for_use = 0;
	memcpy(ITEM_LIBRARY_SIGN->tags[0], "library sign", 12);
	memcpy(ITEM_LIBRARY_SIGN->tags[1], "sign", 4);
	memcpy(ITEM_LIBRARY_SIGN->description, "A sign that reads 'Library'.", 28);
	memcpy(ITEM_LIBRARY_SIGN->desc_look_around, "", 1);
	memcpy(ITEM_LIBRARY_SIGN->desc_look_item, "A sign that reads 'Library'.",
		28);

	ITEM_BOOKS->id = ID_ITEM_BOOKS;
	ITEM_BOOKS->bool_is_singular = 0;
	ITEM_BOOKS->bool_can_be_taken = 0;
	ITEM_BOOKS->bool_requires_target_for_use = 0;
	memcpy(ITEM_BOOKS->tags[0], "books", 5);
	memcpy(ITEM_BOOKS->description, "Books from the mansion's old library.",
		37);
	memcpy(ITEM_BOOKS->desc_look_around, "The library walls are lined with "
		"old, dusty books.", 50);
	memcpy(ITEM_BOOKS->desc_look_item, "Let's not focus on the books.", 29);

	ITEM_DOOR_ROOM_1->id = ID_ITEM_DOOR_ROOM_1;
	ITEM_DOOR_ROOM_1->bool_is_singular = 1;
	ITEM_DOOR_ROOM_1->access = ACCESS_CLOSED;
	ITEM_DOOR_ROOM_1->bool_can_be_taken = 0;
	ITEM_DOOR_ROOM_1->bool_requires_target_for_use = 0;
	memcpy(ITEM_DOOR_ROOM_1->tags[0], "first room door", 15);
	memcpy(ITEM_DOOR_ROOM_1->tags[1], "door room 1", 11);
	memcpy(ITEM_DOOR_ROOM_1->tags[2], "door", 4);
	memcpy(ITEM_DOOR_ROOM_1->description, "The door to the first room.", 27);
	memcpy(ITEM_DOOR_ROOM_1->desc_look_around, "The door to the first room.",
		27);
	memcpy(ITEM_DOOR_ROOM_1->desc_look_item, "The door to the first room.", 27);

	ITEM_DOOR_ROOM_2->id = ID_ITEM_DOOR_ROOM_2;
	ITEM_DOOR_ROOM_2->bool_is_singular = 1;
	ITEM_DOOR_ROOM_2->access = ACCESS_CLOSED;
	ITEM_DOOR_ROOM_2->bool_can_be_taken = 0;
	ITEM_DOOR_ROOM_2->bool_requires_target_for_use = 0;
	memcpy(ITEM_DOOR_ROOM_2->tags[0], "second room door", 16);
	memcpy(ITEM_DOOR_ROOM_2->tags[1], "door room 2", 11);
	memcpy(ITEM_DOOR_ROOM_2->tags[2], "door", 4);
	memcpy(ITEM_DOOR_ROOM_2->description, "The door to the second room.", 28);
	memcpy(ITEM_DOOR_ROOM_2->desc_look_around, "The door to the second room.",
		28);
	memcpy(ITEM_DOOR_ROOM_2->desc_look_item, "The door to the second room.",
		28);

	ITEM_DOOR_ROOM_3->id = ID_ITEM_DOOR_ROOM_3;
	ITEM_DOOR_ROOM_3->bool_is_singular = 1;
	ITEM_DOOR_ROOM_3->access = ACCESS_CLOSED;
	ITEM_DOOR_ROOM_3->bool_can_be_taken = 0;
	ITEM_DOOR_ROOM_3->bool_requires_target_for_use = 0;
	memcpy(ITEM_DOOR_ROOM_3->tags[0], "third room door", 15);
	memcpy(ITEM_DOOR_ROOM_3->tags[1], "door room 3", 11);
	memcpy(ITEM_DOOR_ROOM_3->tags[2], "door", 4);
	memcpy(ITEM_DOOR_ROOM_3->description, "The door to the third room.", 27);
	memcpy(ITEM_DOOR_ROOM_3->desc_look_around, "The door to the third room.",
		27);
	memcpy(ITEM_DOOR_ROOM_3->desc_look_item, "The door to the third room.", 27);

	ITEM_ENTRY_DOORS_KEY->id = ID_ITEM_ENTRY_DOORS_KEY;
	ITEM_ENTRY_DOORS_KEY->bool_is_singular = 1;
	ITEM_ENTRY_DOORS_KEY->bool_can_be_taken = 1;
	ITEM_ENTRY_DOORS_KEY->bool_requires_target_for_use = 1;
	memcpy(ITEM_ENTRY_DOORS_KEY->tags[0], "shiny thing", 11);
	memcpy(ITEM_ENTRY_DOORS_KEY->description, "The key to the mansion's entry "
		"doors.", 37);
	memcpy(ITEM_ENTRY_DOORS_KEY->desc_look_around, "Something shiny, left "
		"unattended on the ground, catches your attention.", 71);
	memcpy(ITEM_ENTRY_DOORS_KEY->desc_look_item, "It's a key. It shines in a "
		"golden color, and a small note attached to it with a string reads "
		"\"Entry\".", 101);
	return;
}
