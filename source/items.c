#include "../headers/items.h"

/* Declared as extern in ../headers/game.h, included in ../headers/items.h */
Item list_items[NBR_ITEMS];
/* Declared as extern in ../headers/events.h, included in ../headers/items.h */
int list_events[NBR_EVENTS];

void populate_list_items(void)
{
    ITEM_NONE->item_id = ID_ITEM_NONE;
    ITEM_NONE->is_singular = 1;
    ITEM_NONE->access = ACCESS_NONE;
    ITEM_NONE->can_be_taken = 0;
    memcpy(ITEM_NONE->name, "NO_NAME", LENGTH_NAME);
    memcpy(ITEM_NONE->description, "NO_ITEM", LENGTH_DESCRIPTION);

    ITEM_ENTRY_DOORS->item_id = ID_ITEM_ENTRY_DOORS;
    ITEM_ENTRY_DOORS->is_singular = 0;
    ITEM_ENTRY_DOORS->access = ACCESS_CLOSED;
    ITEM_ENTRY_DOORS->can_be_taken = 0;
    memcpy(ITEM_ENTRY_DOORS->name, "Doors", LENGTH_NAME);
    memcpy(ITEM_ENTRY_DOORS->description, "The entry doors of the mansion.", LENGTH_DESCRIPTION);

    ITEM_GRANDFATHER_CLOCK->item_id = ID_ITEM_GRANDFATHER_CLOCK;
    ITEM_GRANDFATHER_CLOCK->is_singular = 1;
    ITEM_GRANDFATHER_CLOCK->access = ACCESS_NONE;
    ITEM_GRANDFATHER_CLOCK->can_be_taken = 0;
    memcpy(ITEM_GRANDFATHER_CLOCK->name, "Grandfather Clock", LENGTH_NAME);
    memcpy(ITEM_GRANDFATHER_CLOCK->description, "A grandfather clock.", LENGTH_DESCRIPTION);

    ITEM_LIBRARY_DOOR->item_id = ID_ITEM_LIBRARY_DOOR;
    ITEM_LIBRARY_DOOR->is_singular = 1;
    ITEM_LIBRARY_DOOR->access = ACCESS_CLOSED;
    ITEM_LIBRARY_DOOR->can_be_taken = 0;
    memcpy(ITEM_LIBRARY_DOOR->name, "Door", LENGTH_NAME);
    memcpy(ITEM_LIBRARY_DOOR->description, "The door to the old library.", LENGTH_DESCRIPTION);

    ITEM_LIBRARY_SIGN->item_id = ID_ITEM_LIBRARY_SIGN;
    ITEM_LIBRARY_SIGN->is_singular = 1;
    ITEM_LIBRARY_SIGN->access = ACCESS_NONE;
    ITEM_LIBRARY_SIGN->can_be_taken = 0;
    memcpy(ITEM_LIBRARY_SIGN->name, "Sign", LENGTH_NAME);
    memcpy(ITEM_LIBRARY_SIGN->description, "A sign that reads 'Library'.", LENGTH_DESCRIPTION);

    ITEM_BOOKS->item_id = ID_ITEM_BOOKS;
    ITEM_BOOKS->is_singular = 0;
    ITEM_BOOKS->access = ACCESS_NONE;
    ITEM_BOOKS->can_be_taken = 0;
    memcpy(ITEM_BOOKS->name, "Books", LENGTH_NAME);
    memcpy(ITEM_BOOKS->description, "Let's not focus on the books.", LENGTH_DESCRIPTION);

    ITEM_DOOR_ROOM_1->item_id = ID_ITEM_DOOR_ROOM_1;
    ITEM_DOOR_ROOM_1->is_singular = 1;
    ITEM_DOOR_ROOM_1->access = ACCESS_CLOSED;
    ITEM_DOOR_ROOM_1->can_be_taken = 0;
    memcpy(ITEM_DOOR_ROOM_1->name, "Door", LENGTH_NAME);
    memcpy(ITEM_DOOR_ROOM_1->description, "The door to the first room.", LENGTH_DESCRIPTION);

    ITEM_DOOR_ROOM_2->item_id = ID_ITEM_DOOR_ROOM_2;
    ITEM_DOOR_ROOM_2->is_singular = 1;
    ITEM_DOOR_ROOM_2->access = ACCESS_CLOSED;
    ITEM_DOOR_ROOM_2->can_be_taken = 0;
    memcpy(ITEM_DOOR_ROOM_2->name, "Door", LENGTH_NAME);
    memcpy(ITEM_DOOR_ROOM_2->description, "The door to the second room.", LENGTH_DESCRIPTION);

    ITEM_DOOR_ROOM_3->item_id = ID_ITEM_DOOR_ROOM_3;
    ITEM_DOOR_ROOM_3->is_singular = 1;
    ITEM_DOOR_ROOM_3->access = ACCESS_CLOSED;
    ITEM_DOOR_ROOM_3->can_be_taken = 0;
    memcpy(ITEM_DOOR_ROOM_3->name, "Door", LENGTH_NAME);
    memcpy(ITEM_DOOR_ROOM_3->description, "The door to the third room.", LENGTH_DESCRIPTION);

    ITEM_ENTRY_DOORS_KEY->item_id = ID_ITEM_ENTRY_DOORS_KEY;
    ITEM_ENTRY_DOORS_KEY->is_singular = 1;
    ITEM_ENTRY_DOORS_KEY->access = ACCESS_NONE;
    ITEM_ENTRY_DOORS_KEY->can_be_taken = 1;
    memcpy(ITEM_ENTRY_DOORS_KEY->name, "Key", LENGTH_NAME);
    memcpy(ITEM_ENTRY_DOORS_KEY->description, "This is the key to the entry doors.", LENGTH_DESCRIPTION);
    return;
}

char* retrieve_default_item_tag_by_id(const int item_id)
{
    switch(item_id)
    {
        case ID_ITEM_ENTRY_DOORS:
            return "entry doors";
        case ID_ITEM_GRANDFATHER_CLOCK:
            return "clock";
        case ID_ITEM_LIBRARY_DOOR:
            return "library door";
        case ID_ITEM_LIBRARY_SIGN:
            return "sign";
        case ID_ITEM_BOOKS:
            return "books";
        case ID_ITEM_DOOR_ROOM_1:
            return "door room 1";
        case ID_ITEM_DOOR_ROOM_2:
            return "door room 2";
        case ID_ITEM_DOOR_ROOM_3:
            return "door room 3";
        case ID_ITEM_ENTRY_DOORS_KEY:
            EVENT_PLAYER_FINDS_ENTRY_DOORS_KEY_1_ON_3
        default:
            return "";
    }
}

int retrieve_item_id_by_parser(const char* parser)
{
    if (strcmp(parser, "entry doors") == 0)
        return ID_ITEM_ENTRY_DOORS;
    else if (strcmp(parser, "grandfather clock") == 0 || strcmp(parser, "clock") == 0)
        return ID_ITEM_GRANDFATHER_CLOCK;
    else if (strcmp(parser, "library door") == 0)
        return ID_ITEM_LIBRARY_DOOR;
    else if (strcmp(parser, "library sign") == 0 || strcmp(parser, "sign") == 0)
        return ID_ITEM_LIBRARY_SIGN;
    else if (strcmp(parser, "books") == 0)
        return ID_ITEM_BOOKS;
    else if (strcmp(parser, "door room 1") == 0)
        return ID_ITEM_DOOR_ROOM_1;
    else if (strcmp(parser, "door room 2") == 0)
        return ID_ITEM_DOOR_ROOM_2;
    else if (strcmp(parser, "door room 3") == 0)
        return ID_ITEM_DOOR_ROOM_3;
    else if EVENT_PLAYER_FINDS_ENTRY_DOORS_KEY_2_ON_3
    else
        return ID_ITEM_NONE;
}

int bool_parser_and_item_id_do_match(const char* parser, const int item_id)
{
    switch(item_id)
    {
        case ID_ITEM_ENTRY_DOORS:
            return strcmp(parser, "entry doors") == 0 ? 1 : 0;
        case ID_ITEM_GRANDFATHER_CLOCK:
            return strcmp(parser, "grandfather clock") == 0 || strcmp(parser, "clock") == 0 ? 1 : 0;
        case ID_ITEM_LIBRARY_DOOR:
            return strcmp(parser, "library door") == 0 ? 1 : 0;
        case ID_ITEM_LIBRARY_SIGN:
            return strcmp(parser, "library sign") == 0 || strcmp(parser, "sign") == 0 ? 1 : 0;
        case ID_ITEM_BOOKS:
            return strcmp(parser, "books") == 0 ? 1 : 0;
        case ID_ITEM_DOOR_ROOM_1:
            return strcmp(parser, "door room 1") == 0 ? 1 : 0;
        case ID_ITEM_DOOR_ROOM_2:
            return strcmp(parser, "door room 2") == 0 ? 1 : 0;
        case ID_ITEM_DOOR_ROOM_3:
            return strcmp(parser, "door room 3") == 0 ? 1 : 0;
        case ID_ITEM_ENTRY_DOORS_KEY:
            EVENT_PLAYER_FINDS_ENTRY_DOORS_KEY_3_ON_3
        default:
            return 0;
    }
}

