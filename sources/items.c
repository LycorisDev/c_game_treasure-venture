#include "../headers/items.h"

/* Declared as extern in ../headers/game.h, included in ../headers/items.h */
Item list_items[NBR_ITEMS];

void populate_list_items(void)
{
    memset(list_items, 0, NBR_ITEMS * sizeof(Item));

    ITEM_ENTRY_DOORS->id = ID_ITEM_ENTRY_DOORS;
    ITEM_ENTRY_DOORS->is_singular = 0;
    ITEM_ENTRY_DOORS->access = ACCESS_CLOSED;
    ITEM_ENTRY_DOORS->unlocked_with = ITEM_ENTRY_DOORS_KEY;
    ITEM_ENTRY_DOORS->can_be_taken = 0;
    ITEM_ENTRY_DOORS->requires_target_for_use = 0;
    memcpy(ITEM_ENTRY_DOORS->name, "Entry doors", LENGTH_NAME);
    memcpy(ITEM_ENTRY_DOORS->tags[0], "doors / entry doors / double doors / main doors / main entry doors / main double doors", LENGTH_NAME);
    memcpy(ITEM_ENTRY_DOORS->tags[1], "doors", LENGTH_NAME);
    memcpy(ITEM_ENTRY_DOORS->tags[2], "entry doors", LENGTH_NAME);
    memcpy(ITEM_ENTRY_DOORS->tags[3], "double doors", LENGTH_NAME);
    memcpy(ITEM_ENTRY_DOORS->tags[4], "main doors", LENGTH_NAME);
    memcpy(ITEM_ENTRY_DOORS->tags[5], "main entry doors", LENGTH_NAME);
    memcpy(ITEM_ENTRY_DOORS->tags[6], "main double doors", LENGTH_NAME);
    memcpy(ITEM_ENTRY_DOORS->description_brief, "The entry doors of the mansion.", LENGTH_DESCRIPTION);
    memcpy(ITEM_ENTRY_DOORS->description_obvious, "The entry doors of the mansion.", LENGTH_DESCRIPTION);
    memcpy(ITEM_ENTRY_DOORS->description_detailed, "The entry doors of the mansion.", LENGTH_DESCRIPTION);

    ITEM_GRANDFATHER_CLOCK->id = ID_ITEM_GRANDFATHER_CLOCK;
    ITEM_GRANDFATHER_CLOCK->is_singular = 1;
    ITEM_GRANDFATHER_CLOCK->can_be_taken = 0;
    ITEM_GRANDFATHER_CLOCK->requires_target_for_use = 0;
    memcpy(ITEM_GRANDFATHER_CLOCK->name, "Grandfather clock", LENGTH_NAME);
    memcpy(ITEM_GRANDFATHER_CLOCK->tags[0], "clock / grandfather clock", LENGTH_NAME);
    memcpy(ITEM_GRANDFATHER_CLOCK->tags[1], "clock", LENGTH_NAME);
    memcpy(ITEM_GRANDFATHER_CLOCK->tags[2], "grandfather clock", LENGTH_NAME);
    memcpy(ITEM_GRANDFATHER_CLOCK->description_brief, "A grandfather clock.", LENGTH_DESCRIPTION);
    memcpy(ITEM_GRANDFATHER_CLOCK->description_obvious, "The loud ticks of the grandfather clock is nerve-wracking. You've always hated those.", LENGTH_DESCRIPTION);
    memcpy(ITEM_GRANDFATHER_CLOCK->description_detailed, "The clock doesn't seem to hide any secret.", LENGTH_DESCRIPTION);

    ITEM_LIBRARY_DOOR->id = ID_ITEM_LIBRARY_DOOR;
    ITEM_LIBRARY_DOOR->is_singular = 1;
    ITEM_LIBRARY_DOOR->access = ACCESS_CLOSED;
    ITEM_LIBRARY_DOOR->can_be_taken = 0;
    ITEM_LIBRARY_DOOR->requires_target_for_use = 0;
    memcpy(ITEM_LIBRARY_DOOR->name, "Library door", LENGTH_NAME);
    memcpy(ITEM_LIBRARY_DOOR->tags[0], "door / library door / old library door", LENGTH_NAME);
    memcpy(ITEM_LIBRARY_DOOR->tags[1], "door", LENGTH_NAME);
    memcpy(ITEM_LIBRARY_DOOR->tags[2], "library door", LENGTH_NAME);
    memcpy(ITEM_LIBRARY_DOOR->tags[3], "old library door", LENGTH_NAME);
    memcpy(ITEM_LIBRARY_DOOR->description_brief, "The door to the old library.", LENGTH_DESCRIPTION);
    memcpy(ITEM_LIBRARY_DOOR->description_obvious, "The door to the old library.", LENGTH_DESCRIPTION);
    memcpy(ITEM_LIBRARY_DOOR->description_detailed, "The door to the old library.", LENGTH_DESCRIPTION);

    ITEM_LIBRARY_SIGN->id = ID_ITEM_LIBRARY_SIGN;
    ITEM_LIBRARY_SIGN->is_singular = 1;
    ITEM_LIBRARY_SIGN->can_be_taken = 0;
    ITEM_LIBRARY_SIGN->requires_target_for_use = 0;
    memcpy(ITEM_LIBRARY_SIGN->name, "Library sign", LENGTH_NAME);
    memcpy(ITEM_LIBRARY_SIGN->tags[0], "sign / library sign", LENGTH_NAME);
    memcpy(ITEM_LIBRARY_SIGN->tags[1], "sign", LENGTH_NAME);
    memcpy(ITEM_LIBRARY_SIGN->tags[2], "library sign", LENGTH_NAME);
    memcpy(ITEM_LIBRARY_SIGN->description_brief, "A sign that reads 'Library'.", LENGTH_DESCRIPTION);
    memcpy(ITEM_LIBRARY_SIGN->description_obvious, "", LENGTH_DESCRIPTION);
    memcpy(ITEM_LIBRARY_SIGN->description_detailed, "A sign that reads 'Library'.", LENGTH_DESCRIPTION);

    ITEM_BOOKS->id = ID_ITEM_BOOKS;
    ITEM_BOOKS->is_singular = 0;
    ITEM_BOOKS->can_be_taken = 0;
    ITEM_BOOKS->requires_target_for_use = 0;
    memcpy(ITEM_BOOKS->name, "Books", LENGTH_NAME);
    memcpy(ITEM_BOOKS->tags[0], "books", LENGTH_NAME);
    memcpy(ITEM_BOOKS->tags[1], "books", LENGTH_NAME);
    memcpy(ITEM_BOOKS->description_brief, "Books from the mansion's old library.", LENGTH_DESCRIPTION);
    memcpy(ITEM_BOOKS->description_obvious, "The library walls are lined with old, dusty books.", LENGTH_DESCRIPTION);
    memcpy(ITEM_BOOKS->description_detailed, "Let's not focus on the books.", LENGTH_DESCRIPTION);

    ITEM_DOOR_ROOM_1->id = ID_ITEM_DOOR_ROOM_1;
    ITEM_DOOR_ROOM_1->is_singular = 1;
    ITEM_DOOR_ROOM_1->access = ACCESS_CLOSED;
    ITEM_DOOR_ROOM_1->can_be_taken = 0;
    ITEM_DOOR_ROOM_1->requires_target_for_use = 0;
    memcpy(ITEM_DOOR_ROOM_1->name, "First room door", LENGTH_NAME);
    memcpy(ITEM_DOOR_ROOM_1->tags[0], "door / door room 1 / first room door", LENGTH_NAME);
    memcpy(ITEM_DOOR_ROOM_1->tags[1], "door", LENGTH_NAME);
    memcpy(ITEM_DOOR_ROOM_1->tags[2], "door room 1", LENGTH_NAME);
    memcpy(ITEM_DOOR_ROOM_1->tags[3], "first room door", LENGTH_NAME);
    memcpy(ITEM_DOOR_ROOM_1->description_brief, "The door to the first room.", LENGTH_DESCRIPTION);
    memcpy(ITEM_DOOR_ROOM_1->description_obvious, "The door to the first room.", LENGTH_DESCRIPTION);
    memcpy(ITEM_DOOR_ROOM_1->description_detailed, "The door to the first room.", LENGTH_DESCRIPTION);

    ITEM_DOOR_ROOM_2->id = ID_ITEM_DOOR_ROOM_2;
    ITEM_DOOR_ROOM_2->is_singular = 1;
    ITEM_DOOR_ROOM_2->access = ACCESS_CLOSED;
    ITEM_DOOR_ROOM_2->can_be_taken = 0;
    ITEM_DOOR_ROOM_2->requires_target_for_use = 0;
    memcpy(ITEM_DOOR_ROOM_2->name, "Second room door", LENGTH_NAME);
    memcpy(ITEM_DOOR_ROOM_2->tags[0], "door / door room 2 / second room door", LENGTH_NAME);
    memcpy(ITEM_DOOR_ROOM_2->tags[1], "door", LENGTH_NAME);
    memcpy(ITEM_DOOR_ROOM_2->tags[2], "door room 2", LENGTH_NAME);
    memcpy(ITEM_DOOR_ROOM_2->tags[3], "second room door", LENGTH_NAME);
    memcpy(ITEM_DOOR_ROOM_2->description_brief, "The door to the second room.", LENGTH_DESCRIPTION);
    memcpy(ITEM_DOOR_ROOM_2->description_obvious, "The door to the second room.", LENGTH_DESCRIPTION);
    memcpy(ITEM_DOOR_ROOM_2->description_detailed, "The door to the second room.", LENGTH_DESCRIPTION);

    ITEM_DOOR_ROOM_3->id = ID_ITEM_DOOR_ROOM_3;
    ITEM_DOOR_ROOM_3->is_singular = 1;
    ITEM_DOOR_ROOM_3->access = ACCESS_CLOSED;
    ITEM_DOOR_ROOM_3->can_be_taken = 0;
    ITEM_DOOR_ROOM_3->requires_target_for_use = 0;
    memcpy(ITEM_DOOR_ROOM_3->name, "Third room door", LENGTH_NAME);
    memcpy(ITEM_DOOR_ROOM_3->tags[0], "door / door room 3 / third room door", LENGTH_NAME);
    memcpy(ITEM_DOOR_ROOM_3->tags[1], "door", LENGTH_NAME);
    memcpy(ITEM_DOOR_ROOM_3->tags[2], "door room 3", LENGTH_NAME);
    memcpy(ITEM_DOOR_ROOM_3->tags[3], "third room door", LENGTH_NAME);
    memcpy(ITEM_DOOR_ROOM_3->description_brief, "The door to the third room.", LENGTH_DESCRIPTION);
    memcpy(ITEM_DOOR_ROOM_3->description_obvious, "The door to the third room.", LENGTH_DESCRIPTION);
    memcpy(ITEM_DOOR_ROOM_3->description_detailed, "The door to the third room.", LENGTH_DESCRIPTION);

    ITEM_ENTRY_DOORS_KEY->id = ID_ITEM_ENTRY_DOORS_KEY;
    ITEM_ENTRY_DOORS_KEY->is_singular = 1;
    ITEM_ENTRY_DOORS_KEY->can_be_taken = 1;
    ITEM_ENTRY_DOORS_KEY->requires_target_for_use = 1;
    memcpy(ITEM_ENTRY_DOORS_KEY->name, "Key", LENGTH_NAME);
    memcpy(ITEM_ENTRY_DOORS_KEY->tags[0], "shiny thing", LENGTH_NAME);
    memcpy(ITEM_ENTRY_DOORS_KEY->tags[1], "shiny thing", LENGTH_NAME);
    memcpy(ITEM_ENTRY_DOORS_KEY->description_brief, "The key to the mansion's entry doors.", LENGTH_DESCRIPTION);
    memcpy(ITEM_ENTRY_DOORS_KEY->description_obvious, "Something shiny, left unattended on the ground, catches your attention.", LENGTH_DESCRIPTION);
    memcpy(ITEM_ENTRY_DOORS_KEY->description_detailed, "It's a key. It shines in a golden color, and a small note attached to it with a string reads \"Entry\".", LENGTH_DESCRIPTION);
    return;
}

Item** retrieve_items_by_parser_from_current_location(const char* parser)
{
    int i, j, k;
    Item** items_with_same_tag = calloc(NBR_ITEMS, sizeof(Item*));
    if (!items_with_same_tag)
        return NULL;

    for (i = 0, k = 0; i < NBR_ITEMS; ++i)
    {
        if (!PLAYER->current_location->items[i])
            break;

        for (j = 1; j < NBR_TAGS; ++j)
        {
            if (!PLAYER->current_location->items[i]->tags[j])
                break;

            if (!strcmp(parser, PLAYER->current_location->items[i]->tags[j]))
            {
                items_with_same_tag[k++] = PLAYER->current_location->items[i];
                break;
            }
        }
    }

    return items_with_same_tag;
}

Item** retrieve_items_by_parser_from_inventory(const char* parser)
{
    int i, j, k;
    Item** items_with_same_tag = calloc(NBR_ITEMS, sizeof(Item*));
    if (!items_with_same_tag)
        return NULL;

    for (i = 0, k = 0; i < NBR_ITEMS; ++i)
    {
        if (!PLAYER->inventory[i])
            break;

        for (j = 1; j < NBR_TAGS; ++j)
        {
            if (!PLAYER->inventory[i]->tags[j])
                break;

            if (!strcmp(parser, PLAYER->inventory[i]->tags[j]))
            {
                items_with_same_tag[k++] = PLAYER->inventory[i];
                break;
            }
        }
    }

    return items_with_same_tag;
}

Item** retrieve_takeable_items_by_parser_from_current_location(const char* parser)
{
    int i, j, k;
    Item** items_with_same_tag = calloc(NBR_ITEMS, sizeof(Item*));
    if (!items_with_same_tag)
        return NULL;

    for (i = 0, k = 0; i < NBR_ITEMS; ++i)
    {
        if (!PLAYER->current_location->items[i])
            break;

        if (PLAYER->current_location->items[i]->can_be_taken)
        {
            for (j = 1; j < NBR_TAGS; ++j)
            {
                if (!PLAYER->current_location->items[i]->tags[j])
                    break;

                if (!strcmp(parser, PLAYER->current_location->items[i]->tags[j]))
                {
                    items_with_same_tag[k++] = PLAYER->current_location->items[i];
                    break;
                }
            }
        }
    }

    return items_with_same_tag;
}

