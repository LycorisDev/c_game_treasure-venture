#include "events.h"
#include "characters.h"
#include "items.h"

int	g_list_events[NBR_EVENTS]; /* Declared as extern in events.h */

void	populate_list_events(void)
{
	memset(g_list_events, FLAG_OFF, NBR_EVENTS * sizeof(int));
	g_list_events[0] = FLAG_ON;
	g_list_events[1] = FLAG_ON;
	return;
}

/* -------------------------------------------------------------------------- */

void	execute_event_first_time_player_enters_mansion(void)
{
	ITEM_ENTRY_DOORS->access = ACCESS_LOCKED;
	g_list_events[0] = FLAG_OFF;
	return;
}

void	event_first_time_player_enters_mansion(void)
{
	if (g_list_events[0] == FLAG_ON && PLAYER->current_location == LOCATION_MAIN_HALLWAY)
	{
		execute_event_first_time_player_enters_mansion();
		add_output("A distinct noise lets you know the entry doors have locked, seemingly all by themselves. You hope this is no haunting place.\n\n");
	}
	return;
}

/* -------------------------------------------------------------------------- */

void	execute_event_player_finds_entry_doors_key(void)
{
	memcpy(ITEM_ENTRY_DOORS_KEY->description, "The key to the mansion's entry doors.", 37);
	memcpy(ITEM_ENTRY_DOORS_KEY->desc_look_around, "A key is left unattended on the ground.", 39);
	memcpy(ITEM_ENTRY_DOORS_KEY->desc_look_item, "The key shines in a golden color, and a small note attached to it with a string reads \"Entry\".", 94);
	memcpy(ITEM_ENTRY_DOORS_KEY->tags[0], "main entry doors key", 20);
	memcpy(ITEM_ENTRY_DOORS_KEY->tags[1], "main double doors key", 21);
	memcpy(ITEM_ENTRY_DOORS_KEY->tags[2], "main doors key", 14);
	memcpy(ITEM_ENTRY_DOORS_KEY->tags[3], "entry doors key", 15);
	memcpy(ITEM_ENTRY_DOORS_KEY->tags[4], "double doors key", 16);
	memcpy(ITEM_ENTRY_DOORS_KEY->tags[5], "key", 3);
	g_list_events[1] = FLAG_OFF;
	return;
}

void	event_player_finds_entry_doors_key(const int id_item)
{
	if (g_list_events[1] == FLAG_ON && id_item == ID_ITEM_ENTRY_DOORS_KEY)
		execute_event_player_finds_entry_doors_key();
	return;
}
