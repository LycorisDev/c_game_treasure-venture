#include "treasure_venture.h"

void	populate_list_events(t_man *man)
{
	memset(man->events, 0, NBR_EVENTS * sizeof(int));
	man->events[0] = 1;
	man->events[1] = 1;
	return;
}

/* -------------------------------------------------------------------------- */

void	run_event_first_time_player_enters_mansion(t_man *man)
{
	man->items[ITEM_ENTRY_DOORS - 1].access = ACCESS_LOCKED;
	man->events[0] = 0;
	return;
}

void	event_first_time_player_enters_mansion(t_man *man)
{
	if (man->events[0] == 1
		&& man->characters[CHAR_PLAYER - 1].current_location->id == LOC_MAIN_HALLWAY)
	{
		run_event_first_time_player_enters_mansion(man);
		printf("A distinct noise lets you know the entry doors have "
			"locked, seemingly all by themselves. You hope this is no haunting "
			"place.\n\n");
	}
	return;
}

/* -------------------------------------------------------------------------- */

void	run_event_player_finds_entry_doors_key(t_man *man)
{
	memcpy(man->items[ITEM_ENTRY_DOORS_KEY - 1].description, "The key to the mansion's entry "
		"doors.", 37);
	memcpy(man->items[ITEM_ENTRY_DOORS_KEY - 1].desc_look_around, "A key is left unattended "
		"on the ground.", 39);
	memcpy(man->items[ITEM_ENTRY_DOORS_KEY - 1].desc_look_item, "The key shines in a golden "
		"color, and a small note attached to it with a string reads \"Entry\".",
		94);
	memcpy(man->items[ITEM_ENTRY_DOORS_KEY - 1].tags[0], "main entry doors key", 20);
	memcpy(man->items[ITEM_ENTRY_DOORS_KEY - 1].tags[1], "main double doors key", 21);
	memcpy(man->items[ITEM_ENTRY_DOORS_KEY - 1].tags[2], "main doors key", 14);
	memcpy(man->items[ITEM_ENTRY_DOORS_KEY - 1].tags[3], "entry doors key", 15);
	memcpy(man->items[ITEM_ENTRY_DOORS_KEY - 1].tags[4], "double doors key", 16);
	memcpy(man->items[ITEM_ENTRY_DOORS_KEY - 1].tags[5], "key", 3);
	man->events[1] = 0;
	return;
}

void	event_player_finds_entry_doors_key(t_man *man, const t_id_item id_item)
{
	if (man->events[1] == 1 && id_item == ITEM_ENTRY_DOORS_KEY)
		run_event_player_finds_entry_doors_key(man);
	return;
}
