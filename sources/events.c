#include "../headers/events.h"

/* Declared as extern in ../headers/events.h */
int list_events[NBR_EVENTS];

void populate_list_events(void)
{
    memset(list_events, FLAG_OFF, NBR_EVENTS * sizeof(int));
    list_events[0] = FLAG_ON;
    list_events[1] = FLAG_ON;
    return;
}

/* --- */

void execute_event_first_time_player_enters_mansion(void)
{
    ITEM_ENTRY_DOORS->access = ACCESS_LOCKED;
    list_events[0] = FLAG_OFF;
    return;
}

void event_first_time_player_enters_mansion(void)
{
    if (list_events[0] == FLAG_ON && PLAYER->current_location == LOCATION_MAIN_HALLWAY)
    {
        execute_event_first_time_player_enters_mansion();
        add_output("A distinct noise lets you know the entry doors have locked, seemingly all by themselves. You hope this is no haunting place.\n\n");
    }
    return;
}

/* --- */

void execute_event_player_finds_entry_doors_key(void)
{
    memcpy(ITEM_ENTRY_DOORS_KEY->description, "The key to the mansion's entry doors.", LENGTH_DESCRIPTION);
    memcpy(ITEM_ENTRY_DOORS_KEY->desc_look_around, "A key is left unattended on the ground.", LENGTH_DESCRIPTION);
    memcpy(ITEM_ENTRY_DOORS_KEY->desc_look_item, "The key shines in a golden color, and a small note attached to it with a string reads \"Entry\".", LENGTH_DESCRIPTION);
    memcpy(ITEM_ENTRY_DOORS_KEY->tags[0], "main entry doors key", LENGTH_TAG);
    memcpy(ITEM_ENTRY_DOORS_KEY->tags[1], "main double doors key", LENGTH_TAG);
    memcpy(ITEM_ENTRY_DOORS_KEY->tags[2], "main doors key", LENGTH_TAG);
    memcpy(ITEM_ENTRY_DOORS_KEY->tags[3], "entry doors key", LENGTH_TAG);
    memcpy(ITEM_ENTRY_DOORS_KEY->tags[4], "double doors key", LENGTH_TAG);
    memcpy(ITEM_ENTRY_DOORS_KEY->tags[5], "key", LENGTH_TAG);
    list_events[1] = FLAG_OFF;
    return;
}

void event_player_finds_entry_doors_key(const int id_item)
{
    if (list_events[1] == FLAG_ON && id_item == ID_ITEM_ENTRY_DOORS_KEY)
        execute_event_player_finds_entry_doors_key();
    return;
}

/* --- */

