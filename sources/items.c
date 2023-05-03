#include "../headers/items.h"
#include "../headers/main.h"

/* Declared as extern in ../headers/game.h, included in ../headers/items.h */
Item list_items[NBR_ITEMS];

static void get_all_tags(char* p_str, const int word_length, Item* object);

void populate_list_items(void)
{
    memset(list_items, 0, NBR_ITEMS * sizeof(Item));

    ITEM_ENTRY_DOORS->id = ID_ITEM_ENTRY_DOORS;
    ITEM_ENTRY_DOORS->bool_is_singular = 0;
    ITEM_ENTRY_DOORS->access = ACCESS_CLOSED;
    ITEM_ENTRY_DOORS->unlocked_with = ITEM_ENTRY_DOORS_KEY;
    ITEM_ENTRY_DOORS->bool_can_be_taken = 0;
    ITEM_ENTRY_DOORS->bool_requires_target_for_use = 0;
    memcpy(ITEM_ENTRY_DOORS->tags[0], "main entry doors", LENGTH_TAG);
    memcpy(ITEM_ENTRY_DOORS->tags[1], "main double doors", LENGTH_TAG);
    memcpy(ITEM_ENTRY_DOORS->tags[2], "main doors", LENGTH_TAG);
    memcpy(ITEM_ENTRY_DOORS->tags[3], "entry doors", LENGTH_TAG);
    memcpy(ITEM_ENTRY_DOORS->tags[4], "double doors", LENGTH_TAG);
    memcpy(ITEM_ENTRY_DOORS->tags[5], "doors", LENGTH_TAG);
    memcpy(ITEM_ENTRY_DOORS->description, "The entry doors of the mansion.", LENGTH_DESCRIPTION);
    memcpy(ITEM_ENTRY_DOORS->desc_look_around, "The entry doors of the mansion.", LENGTH_DESCRIPTION);
    memcpy(ITEM_ENTRY_DOORS->desc_look_item, "The entry doors of the mansion.", LENGTH_DESCRIPTION);

    ITEM_GRANDFATHER_CLOCK->id = ID_ITEM_GRANDFATHER_CLOCK;
    ITEM_GRANDFATHER_CLOCK->bool_is_singular = 1;
    ITEM_GRANDFATHER_CLOCK->bool_can_be_taken = 0;
    ITEM_GRANDFATHER_CLOCK->bool_requires_target_for_use = 0;
    memcpy(ITEM_GRANDFATHER_CLOCK->tags[0], "grandfather clock", LENGTH_TAG);
    memcpy(ITEM_GRANDFATHER_CLOCK->tags[1], "clock", LENGTH_TAG);
    memcpy(ITEM_GRANDFATHER_CLOCK->description, "A grandfather clock.", LENGTH_DESCRIPTION);
    memcpy(ITEM_GRANDFATHER_CLOCK->desc_look_around, "The loud ticks of the grandfather clock is nerve-wracking. You've always hated those.", LENGTH_DESCRIPTION);
    memcpy(ITEM_GRANDFATHER_CLOCK->desc_look_item, "The clock doesn't seem to hide any secret.", LENGTH_DESCRIPTION);

    ITEM_LIBRARY_DOOR->id = ID_ITEM_LIBRARY_DOOR;
    ITEM_LIBRARY_DOOR->bool_is_singular = 1;
    ITEM_LIBRARY_DOOR->access = ACCESS_CLOSED;
    ITEM_LIBRARY_DOOR->bool_can_be_taken = 0;
    ITEM_LIBRARY_DOOR->bool_requires_target_for_use = 0;
    memcpy(ITEM_LIBRARY_DOOR->tags[0], "old library door", LENGTH_TAG);
    memcpy(ITEM_LIBRARY_DOOR->tags[1], "library door", LENGTH_TAG);
    memcpy(ITEM_LIBRARY_DOOR->tags[2], "door", LENGTH_TAG);
    memcpy(ITEM_LIBRARY_DOOR->description, "The door to the old library.", LENGTH_DESCRIPTION);
    memcpy(ITEM_LIBRARY_DOOR->desc_look_around, "The door to the old library.", LENGTH_DESCRIPTION);
    memcpy(ITEM_LIBRARY_DOOR->desc_look_item, "The door to the old library.", LENGTH_DESCRIPTION);

    ITEM_LIBRARY_SIGN->id = ID_ITEM_LIBRARY_SIGN;
    ITEM_LIBRARY_SIGN->bool_is_singular = 1;
    ITEM_LIBRARY_SIGN->bool_can_be_taken = 0;
    ITEM_LIBRARY_SIGN->bool_requires_target_for_use = 0;
    memcpy(ITEM_LIBRARY_SIGN->tags[0], "library sign", LENGTH_TAG);
    memcpy(ITEM_LIBRARY_SIGN->tags[1], "sign", LENGTH_TAG);
    memcpy(ITEM_LIBRARY_SIGN->description, "A sign that reads 'Library'.", LENGTH_DESCRIPTION);
    memcpy(ITEM_LIBRARY_SIGN->desc_look_around, "", LENGTH_DESCRIPTION);
    memcpy(ITEM_LIBRARY_SIGN->desc_look_item, "A sign that reads 'Library'.", LENGTH_DESCRIPTION);

    ITEM_BOOKS->id = ID_ITEM_BOOKS;
    ITEM_BOOKS->bool_is_singular = 0;
    ITEM_BOOKS->bool_can_be_taken = 0;
    ITEM_BOOKS->bool_requires_target_for_use = 0;
    memcpy(ITEM_BOOKS->tags[0], "books", LENGTH_TAG);
    memcpy(ITEM_BOOKS->description, "Books from the mansion's old library.", LENGTH_DESCRIPTION);
    memcpy(ITEM_BOOKS->desc_look_around, "The library walls are lined with old, dusty books.", LENGTH_DESCRIPTION);
    memcpy(ITEM_BOOKS->desc_look_item, "Let's not focus on the books.", LENGTH_DESCRIPTION);

    ITEM_DOOR_ROOM_1->id = ID_ITEM_DOOR_ROOM_1;
    ITEM_DOOR_ROOM_1->bool_is_singular = 1;
    ITEM_DOOR_ROOM_1->access = ACCESS_CLOSED;
    ITEM_DOOR_ROOM_1->bool_can_be_taken = 0;
    ITEM_DOOR_ROOM_1->bool_requires_target_for_use = 0;
    memcpy(ITEM_DOOR_ROOM_1->tags[0], "first room door", LENGTH_TAG);
    memcpy(ITEM_DOOR_ROOM_1->tags[1], "door room 1", LENGTH_TAG);
    memcpy(ITEM_DOOR_ROOM_1->tags[2], "door", LENGTH_TAG);
    memcpy(ITEM_DOOR_ROOM_1->description, "The door to the first room.", LENGTH_DESCRIPTION);
    memcpy(ITEM_DOOR_ROOM_1->desc_look_around, "The door to the first room.", LENGTH_DESCRIPTION);
    memcpy(ITEM_DOOR_ROOM_1->desc_look_item, "The door to the first room.", LENGTH_DESCRIPTION);

    ITEM_DOOR_ROOM_2->id = ID_ITEM_DOOR_ROOM_2;
    ITEM_DOOR_ROOM_2->bool_is_singular = 1;
    ITEM_DOOR_ROOM_2->access = ACCESS_CLOSED;
    ITEM_DOOR_ROOM_2->bool_can_be_taken = 0;
    ITEM_DOOR_ROOM_2->bool_requires_target_for_use = 0;
    memcpy(ITEM_DOOR_ROOM_2->tags[0], "second room door", LENGTH_TAG);
    memcpy(ITEM_DOOR_ROOM_2->tags[1], "door room 2", LENGTH_TAG);
    memcpy(ITEM_DOOR_ROOM_2->tags[2], "door", LENGTH_TAG);
    memcpy(ITEM_DOOR_ROOM_2->description, "The door to the second room.", LENGTH_DESCRIPTION);
    memcpy(ITEM_DOOR_ROOM_2->desc_look_around, "The door to the second room.", LENGTH_DESCRIPTION);
    memcpy(ITEM_DOOR_ROOM_2->desc_look_item, "The door to the second room.", LENGTH_DESCRIPTION);

    ITEM_DOOR_ROOM_3->id = ID_ITEM_DOOR_ROOM_3;
    ITEM_DOOR_ROOM_3->bool_is_singular = 1;
    ITEM_DOOR_ROOM_3->access = ACCESS_CLOSED;
    ITEM_DOOR_ROOM_3->bool_can_be_taken = 0;
    ITEM_DOOR_ROOM_3->bool_requires_target_for_use = 0;
    memcpy(ITEM_DOOR_ROOM_3->tags[0], "third room door", LENGTH_TAG);
    memcpy(ITEM_DOOR_ROOM_3->tags[1], "door room 3", LENGTH_TAG);
    memcpy(ITEM_DOOR_ROOM_3->tags[2], "door", LENGTH_TAG);
    memcpy(ITEM_DOOR_ROOM_3->description, "The door to the third room.", LENGTH_DESCRIPTION);
    memcpy(ITEM_DOOR_ROOM_3->desc_look_around, "The door to the third room.", LENGTH_DESCRIPTION);
    memcpy(ITEM_DOOR_ROOM_3->desc_look_item, "The door to the third room.", LENGTH_DESCRIPTION);

    ITEM_ENTRY_DOORS_KEY->id = ID_ITEM_ENTRY_DOORS_KEY;
    ITEM_ENTRY_DOORS_KEY->bool_is_singular = 1;
    ITEM_ENTRY_DOORS_KEY->bool_can_be_taken = 1;
    ITEM_ENTRY_DOORS_KEY->bool_requires_target_for_use = 1;
    memcpy(ITEM_ENTRY_DOORS_KEY->tags[0], "shiny thing", LENGTH_TAG);
    memcpy(ITEM_ENTRY_DOORS_KEY->description, "The key to the mansion's entry doors.", LENGTH_DESCRIPTION);
    memcpy(ITEM_ENTRY_DOORS_KEY->desc_look_around, "Something shiny, left unattended on the ground, catches your attention.", LENGTH_DESCRIPTION);
    memcpy(ITEM_ENTRY_DOORS_KEY->desc_look_item, "It's a key. It shines in a golden color, and a small note attached to it with a string reads \"Entry\".", LENGTH_DESCRIPTION);
    return;
}

void display_item_suggestions(Item** item_collection, const char* command)
{
    int i;
    char* str_tags = NULL;
    int word_length = 0;

    if (!strcmp(command, "look"))
        add_output("\t[Try 'look around']\n\n");

    if (!item_collection[0])
        return;

    word_length = sizeof(item_collection[0]->tags[0]) + 3;
    str_tags = calloc(NBR_TAGS, word_length);

    add_output("\t[Try:]\n");
    for (i = 0; i < NBR_ITEMS; ++i)
    {
        if (!item_collection[i])
            break;

        get_all_tags(str_tags, word_length, item_collection[i]);
        add_output("\t\t['%s %s'.]\n", command, str_tags);
    }
    add_output("\n");

    free(str_tags);
    return;
}

Item** retrieve_items(Item** item_collection, const char* parser)
{
    int i, j;
    Item** items = calloc(NBR_ITEMS, sizeof(Item*));
    if (!items)
        return NULL;

    for (i = 0, j = 0; i < NBR_ITEMS; ++i)
    {
        if (!item_collection[i])
            break;

        if (!parser || bool_item_matches_parser(item_collection[i], parser))
            items[j++] = item_collection[i];
    }

    return items;
}

Item** retrieve_takeable_items(Item** item_collection, const char* parser)
{
    int i, j;
    Item** takeable_items = calloc(NBR_ITEMS, sizeof(Item*));
    if (!takeable_items)
        return NULL;

    for (i = 0, j = 0; i < NBR_ITEMS; ++i)
    {
        if (!item_collection[i])
            break;

        if (!item_collection[i]->bool_can_be_taken)
            continue;

        if (!parser || bool_item_matches_parser(item_collection[i], parser))
            takeable_items[j++] = item_collection[i];
    }

    return takeable_items;
}

int bool_item_matches_parser(const Item* item, const char* parser)
{
    int i;
    for (i = 0; i < NBR_TAGS; ++i)
    {
        if (!item->tags[i])
            return 0;

        if (!strcmp(parser, item->tags[i]))
            return 1;
    }
    return 0;
}

static void get_all_tags(char* p_str, const int word_length, Item* object)
{
    int i;

    strncpy(p_str, object->tags[0], word_length);

    for (i = 1; i < NBR_TAGS; ++i)
    {
        if (!object->tags[i][0])
            break;
        strcat(p_str, " / ");
        strncat(p_str, object->tags[i], word_length);
    }
    return;
}

