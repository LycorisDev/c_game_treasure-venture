#include "../headers/locations.h"

/* Declared as extern in ../headers/game.h, included in ../headers/locations.h */
Location list_locations[NBR_LOCATIONS];

void populate_list_locations(void)
{
    Exit exit_objects[NBR_LOCATIONS];
    exit_objects[0].to = LOCATION_MANSION;
    exit_objects[0].passage = ITEM_ENTRY_DOORS;
    exit_objects[1].to = LOCATION_OUTSIDE;
    exit_objects[1].passage = ITEM_ENTRY_DOORS;
    exit_objects[2].to = LOCATION_MAIN_HALLWAY;
    exit_objects[2].passage = ITEM_ENTRY_DOORS;
    exit_objects[3].to = LOCATION_OLD_LIBRARY;
    exit_objects[3].passage = ITEM_LIBRARY_DOOR;
    exit_objects[4].to = LOCATION_MAIN_HALLWAY;
    exit_objects[4].passage = ITEM_LIBRARY_DOOR;
    exit_objects[5].to = LOCATION_ROOM_1;
    exit_objects[5].passage = ITEM_DOOR_ROOM_1;
    exit_objects[6].to = LOCATION_ROOM_2;
    exit_objects[6].passage = ITEM_DOOR_ROOM_2;
    exit_objects[7].to = LOCATION_ROOM_3;
    exit_objects[7].passage = ITEM_DOOR_ROOM_3;
    exit_objects[8].to = LOCATION_OLD_LIBRARY;
    exit_objects[8].passage = ITEM_DOOR_ROOM_1;
    exit_objects[9].to = LOCATION_OLD_LIBRARY;
    exit_objects[9].passage = ITEM_DOOR_ROOM_2;
    exit_objects[10].to = LOCATION_OLD_LIBRARY;
    exit_objects[10].passage = ITEM_DOOR_ROOM_3;

    memset(list_locations, 0, NBR_LOCATIONS * sizeof(Location));

    LOCATION_OUTSIDE->id = ID_LOCATION_OUTSIDE;
    LOCATION_OUTSIDE->type = LOCATION_TYPE_OUTSIDE;
    memcpy(LOCATION_OUTSIDE->name, "world", LENGTH_NAME);
    memcpy(LOCATION_OUTSIDE->tags[0], "world", LENGTH_NAME);
    memcpy(LOCATION_OUTSIDE->tags[1], "world", LENGTH_NAME);
    memcpy(LOCATION_OUTSIDE->description, "", LENGTH_DESCRIPTION);
    LOCATION_OUTSIDE->exits[0] = exit_objects[0];
    LOCATION_OUTSIDE->locations[0] = LOCATION_MANSION;
    LOCATION_OUTSIDE->items[0] = ITEM_ENTRY_DOORS;
    LOCATION_OUTSIDE->characters[0] = PLAYER;

    LOCATION_MANSION->id = ID_LOCATION_MANSION;
    LOCATION_MANSION->type = LOCATION_TYPE_BUILDING;
    LOCATION_MANSION->inside_of = LOCATION_OUTSIDE;
    memcpy(LOCATION_MANSION->name, "mansion", LENGTH_NAME);
    memcpy(LOCATION_MANSION->tags[0], "mansion", LENGTH_NAME);
    memcpy(LOCATION_MANSION->tags[1], "mansion", LENGTH_NAME);
    memcpy(LOCATION_MANSION->description, "The mansion in front of you gives you a bad feeling. Its main double doors don't look welcoming.", LENGTH_DESCRIPTION);
    LOCATION_MANSION->exits[0] = exit_objects[1];
    LOCATION_MANSION->exits[1] = exit_objects[2];
    LOCATION_MANSION->locations[0] = LOCATION_MAIN_HALLWAY;
    LOCATION_MANSION->locations[1] = LOCATION_OLD_LIBRARY;
    LOCATION_MANSION->locations[2] = LOCATION_ROOM_1;
    LOCATION_MANSION->locations[3] = LOCATION_ROOM_2;
    LOCATION_MANSION->locations[4] = LOCATION_ROOM_3;
    LOCATION_MANSION->items[0] = ITEM_ENTRY_DOORS;

    LOCATION_MAIN_HALLWAY->id = ID_LOCATION_MAIN_HALLWAY;
    LOCATION_MAIN_HALLWAY->type = LOCATION_TYPE_ROOM;
    LOCATION_MAIN_HALLWAY->inside_of = LOCATION_MANSION;
    memcpy(LOCATION_MAIN_HALLWAY->name, "main hallway", LENGTH_NAME);
    memcpy(LOCATION_MAIN_HALLWAY->tags[0], "hallway / main hallway", LENGTH_NAME);
    memcpy(LOCATION_MAIN_HALLWAY->tags[1], "hallway", LENGTH_NAME);
    memcpy(LOCATION_MAIN_HALLWAY->tags[2], "main hallway", LENGTH_NAME);
    memcpy(LOCATION_MAIN_HALLWAY->description, "There is a heavy door topped with a sign.", LENGTH_DESCRIPTION);
    LOCATION_MAIN_HALLWAY->exits[0] = exit_objects[0];
    LOCATION_MAIN_HALLWAY->exits[1] = exit_objects[3];
    LOCATION_MAIN_HALLWAY->items[0] = ITEM_ENTRY_DOORS;
    LOCATION_MAIN_HALLWAY->items[1] = ITEM_GRANDFATHER_CLOCK;
    LOCATION_MAIN_HALLWAY->items[2] = ITEM_LIBRARY_DOOR;
    LOCATION_MAIN_HALLWAY->items[3] = ITEM_LIBRARY_SIGN;

    LOCATION_OLD_LIBRARY->id = ID_LOCATION_OLD_LIBRARY;
    LOCATION_OLD_LIBRARY->type = LOCATION_TYPE_ROOM;
    LOCATION_OLD_LIBRARY->inside_of = LOCATION_MANSION;
    memcpy(LOCATION_OLD_LIBRARY->name, "old library", LENGTH_NAME);
    memcpy(LOCATION_OLD_LIBRARY->tags[0], "library / old library", LENGTH_NAME);
    memcpy(LOCATION_OLD_LIBRARY->tags[1], "library", LENGTH_NAME);
    memcpy(LOCATION_OLD_LIBRARY->tags[2], "old library", LENGTH_NAME);
    memcpy(LOCATION_OLD_LIBRARY->description, "A librarian is standing there, reading. In the back of the room, you can discern small doors. Three to be precise.", LENGTH_DESCRIPTION);
    LOCATION_OLD_LIBRARY->exits[0] = exit_objects[4];
    LOCATION_OLD_LIBRARY->exits[1] = exit_objects[5];
    LOCATION_OLD_LIBRARY->exits[2] = exit_objects[6];
    LOCATION_OLD_LIBRARY->exits[3] = exit_objects[7];
    LOCATION_OLD_LIBRARY->items[0] = ITEM_LIBRARY_DOOR;
    LOCATION_OLD_LIBRARY->items[1] = ITEM_BOOKS;
    LOCATION_OLD_LIBRARY->items[2] = ITEM_DOOR_ROOM_1;
    LOCATION_OLD_LIBRARY->items[3] = ITEM_DOOR_ROOM_2;
    LOCATION_OLD_LIBRARY->items[4] = ITEM_DOOR_ROOM_3;
    LOCATION_OLD_LIBRARY->characters[0] = CHARACTER_LIBRARIAN;

    LOCATION_ROOM_1->id = ID_LOCATION_ROOM_1;
    LOCATION_ROOM_1->type = LOCATION_TYPE_ROOM;
    LOCATION_ROOM_1->inside_of = LOCATION_MANSION;
    memcpy(LOCATION_ROOM_1->name, "first room", LENGTH_NAME);
    memcpy(LOCATION_ROOM_1->tags[0], "room 1 / first room", LENGTH_NAME);
    memcpy(LOCATION_ROOM_1->tags[1], "room 1", LENGTH_NAME);
    memcpy(LOCATION_ROOM_1->tags[2], "first room", LENGTH_NAME);
    memcpy(LOCATION_ROOM_1->description, "The room seems empty.", LENGTH_DESCRIPTION);
    LOCATION_ROOM_1->exits[0] = exit_objects[8];
    LOCATION_ROOM_1->items[0] = ITEM_DOOR_ROOM_1;

    LOCATION_ROOM_2->id = ID_LOCATION_ROOM_2;
    LOCATION_ROOM_2->type = LOCATION_TYPE_ROOM;
    LOCATION_ROOM_2->inside_of = LOCATION_MANSION;
    memcpy(LOCATION_ROOM_2->name, "second room", LENGTH_NAME);
    memcpy(LOCATION_ROOM_2->tags[0], "room 2 / second room", LENGTH_NAME);
    memcpy(LOCATION_ROOM_2->tags[1], "room 2", LENGTH_NAME);
    memcpy(LOCATION_ROOM_2->tags[2], "second room", LENGTH_NAME);
    memcpy(LOCATION_ROOM_2->description, "The room seems empty.", LENGTH_DESCRIPTION);
    LOCATION_ROOM_2->exits[0] = exit_objects[9];
    LOCATION_ROOM_2->items[0] = ITEM_DOOR_ROOM_2;
    LOCATION_ROOM_2->items[1] = ITEM_ENTRY_DOORS_KEY;

    LOCATION_ROOM_3->id = ID_LOCATION_ROOM_3;
    LOCATION_ROOM_3->type = LOCATION_TYPE_ROOM;
    LOCATION_ROOM_3->inside_of = LOCATION_MANSION;
    memcpy(LOCATION_ROOM_3->name, "third room", LENGTH_NAME);
    memcpy(LOCATION_ROOM_3->tags[0], "room 3 / third room", LENGTH_NAME);
    memcpy(LOCATION_ROOM_3->tags[1], "room 3", LENGTH_NAME);
    memcpy(LOCATION_ROOM_3->tags[2], "third room", LENGTH_NAME);
    memcpy(LOCATION_ROOM_3->description, "The room seems empty.", LENGTH_DESCRIPTION);
    LOCATION_ROOM_3->exits[0] = exit_objects[10];
    LOCATION_ROOM_3->items[0] = ITEM_DOOR_ROOM_3;
    return;
}

void describe_location(const Location* location)
{
    int i;

    /* Temporary: If we are outside, print the description of the first location in "outside"'s location list. Turns out there's only one, the mansion. */
    if (location->type == LOCATION_TYPE_OUTSIDE)
        printf("%s ", location->locations[0]->description);
    else
        printf("%s ", location->description);

    for (i = 0; i < NBR_ITEMS; ++i)
    {
        if (!location->items[i])
            break;

        /* Only mention items which are not an access to an exit, such as a door */
        if (!location->items[i]->access)
            printf("%s ", location->items[i]->description_obvious);
    }
}

Exit** retrieve_locations_by_parser_from_current_location(const char* parser)
{
    int i, j, k;
    Exit** locations_with_same_tag = calloc(NBR_LOCATIONS, sizeof(Exit*));
    if (!locations_with_same_tag)
        return NULL;

    for (i = 0, k = 0; i < NBR_LOCATIONS; ++i)
    {
        if (!PLAYER->current_location->exits[i].to)
            break;

        for (j = 1; j < NBR_TAGS; ++j)
        {
            if (!PLAYER->current_location->exits[i].to->tags[j])
                break;

            /* If you exit the building */
            if (PLAYER->current_location->exits[i].to->type == LOCATION_TYPE_BUILDING && PLAYER->current_location->type == LOCATION_TYPE_ROOM)
            {
                /* You must not use "go [current building]" but you can use the tag of the outside location (which is the first of the building's exits) */
                if (!strcmp(parser, PLAYER->current_location->exits[i].to->exits[0].to->tags[1]))
                    locations_with_same_tag[k++] = &(PLAYER->current_location->exits[i]);
                break;
            }
            else if (!strcmp(parser, PLAYER->current_location->exits[i].to->tags[j]))
            {
                locations_with_same_tag[k++] = &(PLAYER->current_location->exits[i]);
                break;
            }
        }
    }

    return locations_with_same_tag;
}

Exit** retrieve_locations_by_parser_from_passage_items_in_current_location(const char* parser)
{
    int i, j, k;
    Exit** locations_with_same_tag = calloc(NBR_LOCATIONS, sizeof(Exit*));
    if (!locations_with_same_tag)
        return NULL;

    for (i = 0, k = 0; i < NBR_LOCATIONS; ++i)
    {
        if (!PLAYER->current_location->exits[i].to || !PLAYER->current_location->exits[i].passage->access)
            break;

        for (j = 1; j < NBR_TAGS; ++j)
        {
            if (!PLAYER->current_location->exits[i].passage->tags[j])
                break;

            if (!strcmp(parser, PLAYER->current_location->exits[i].passage->tags[j]))
            {
                locations_with_same_tag[k++] = &(PLAYER->current_location->exits[i]);
                break;
            }
        }
    }

    return locations_with_same_tag;
}

