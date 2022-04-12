#include "../headers/locations.h"

/* Declared as extern in ../headers/game.h, included in ../headers/locations.h */
Location list_locations[NBR_LOCATIONS];

void populate_list_locations(void)
{
    Exit exit_objects[NBR_LOCATIONS];
    exit_objects[0].from = LOCATION_NONE;
    exit_objects[0].to = LOCATION_NONE;
    exit_objects[0].passage = ITEM_NONE;
    exit_objects[1].from = LOCATION_OUTSIDE;
    exit_objects[1].to = LOCATION_MAIN_HALLWAY;
    exit_objects[1].passage = ITEM_ENTRY_DOORS;
    exit_objects[2].from = LOCATION_MAIN_HALLWAY;
    exit_objects[2].to = LOCATION_OUTSIDE;
    exit_objects[2].passage = ITEM_ENTRY_DOORS;
    exit_objects[3].from = LOCATION_MAIN_HALLWAY;
    exit_objects[3].to = LOCATION_OLD_LIBRARY;
    exit_objects[3].passage = ITEM_LIBRARY_DOOR;
    exit_objects[4].from = LOCATION_OLD_LIBRARY;
    exit_objects[4].to = LOCATION_MAIN_HALLWAY;
    exit_objects[4].passage = ITEM_LIBRARY_DOOR;
    exit_objects[5].from = LOCATION_OLD_LIBRARY;
    exit_objects[5].to = LOCATION_ROOM_1;
    exit_objects[5].passage = ITEM_DOOR_ROOM_1;
    exit_objects[6].from = LOCATION_OLD_LIBRARY;
    exit_objects[6].to = LOCATION_ROOM_2;
    exit_objects[6].passage = ITEM_DOOR_ROOM_2;
    exit_objects[7].from = LOCATION_OLD_LIBRARY;
    exit_objects[7].to = LOCATION_ROOM_3;
    exit_objects[7].passage = ITEM_DOOR_ROOM_3;
    exit_objects[8].from = LOCATION_ROOM_1;
    exit_objects[8].to = LOCATION_OLD_LIBRARY;
    exit_objects[8].passage = ITEM_DOOR_ROOM_1;
    exit_objects[9].from = LOCATION_ROOM_2;
    exit_objects[9].to = LOCATION_OLD_LIBRARY;
    exit_objects[9].passage = ITEM_DOOR_ROOM_2;
    exit_objects[10].from = LOCATION_ROOM_3;
    exit_objects[10].to = LOCATION_OLD_LIBRARY;
    exit_objects[10].passage = ITEM_DOOR_ROOM_3;

    LOCATION_NONE->id = ID_LOCATION_NONE;
    LOCATION_NONE->type = LOCATION_TYPE_NONE;
    LOCATION_NONE->inside_of = LOCATION_NONE;
    memcpy(LOCATION_NONE->name, "NO_NAME", LENGTH_NAME);
    memcpy(LOCATION_NONE->tags[0], "NO_TAG", LENGTH_NAME);
    memcpy(LOCATION_NONE->description, "NO_DESCRIPTION.", LENGTH_DESCRIPTION);
    LOCATION_NONE->exits[0] = exit_objects[0];
    LOCATION_NONE->list_of_locations_by_id[0] = ID_LOCATION_NONE;
    LOCATION_NONE->list_of_items_by_id[0] = ID_ITEM_NONE;
    LOCATION_NONE->list_of_characters_by_id[0] = ID_CHARACTER_NONE;

    LOCATION_OUTSIDE->id = ID_LOCATION_OUTSIDE;
    LOCATION_OUTSIDE->type = LOCATION_TYPE_OUTSIDE;
    LOCATION_OUTSIDE->inside_of = LOCATION_NONE;
    memcpy(LOCATION_OUTSIDE->name, "world", LENGTH_NAME);
    memcpy(LOCATION_OUTSIDE->tags[0], "world", LENGTH_NAME);
    memcpy(LOCATION_OUTSIDE->description, "", LENGTH_DESCRIPTION);
    LOCATION_OUTSIDE->exits[0] = exit_objects[1];
    LOCATION_OUTSIDE->list_of_locations_by_id[0] = ID_LOCATION_MANSION;
    LOCATION_OUTSIDE->list_of_items_by_id[0] = ID_ITEM_ENTRY_DOORS;
    LOCATION_OUTSIDE->list_of_characters_by_id[0] = ID_CHARACTER_PLAYER;

    LOCATION_MANSION->id = ID_LOCATION_MANSION;
    LOCATION_MANSION->type = LOCATION_TYPE_BUILDING;
    LOCATION_MANSION->inside_of = LOCATION_OUTSIDE;
    memcpy(LOCATION_MANSION->name, "mansion", LENGTH_NAME);
    memcpy(LOCATION_MANSION->tags[0], "mansion", LENGTH_NAME);
    memcpy(LOCATION_MANSION->description, "The mansion in front of you gives you a bad feeling. Its main double doors don't look welcoming.", LENGTH_DESCRIPTION);
    LOCATION_MANSION->exits[0] = exit_objects[1];
    LOCATION_MANSION->list_of_locations_by_id[0] = ID_LOCATION_MAIN_HALLWAY;
    LOCATION_MANSION->list_of_locations_by_id[1] = ID_LOCATION_OLD_LIBRARY;
    LOCATION_MANSION->list_of_locations_by_id[2] = ID_LOCATION_ROOM_1;
    LOCATION_MANSION->list_of_locations_by_id[3] = ID_LOCATION_ROOM_2;
    LOCATION_MANSION->list_of_locations_by_id[4] = ID_LOCATION_ROOM_3;
    LOCATION_MANSION->list_of_items_by_id[0] = ID_ITEM_ENTRY_DOORS;
    LOCATION_MANSION->list_of_characters_by_id[0] = ID_CHARACTER_NONE;

    LOCATION_MAIN_HALLWAY->id = ID_LOCATION_MAIN_HALLWAY;
    LOCATION_MAIN_HALLWAY->type = LOCATION_TYPE_ROOM;
    LOCATION_MAIN_HALLWAY->inside_of = LOCATION_MANSION;
    memcpy(LOCATION_MAIN_HALLWAY->name, "main hallway", LENGTH_NAME);
    memcpy(LOCATION_MAIN_HALLWAY->tags[0], "hallway", LENGTH_NAME);
    memcpy(LOCATION_MAIN_HALLWAY->tags[1], "main hallway", LENGTH_NAME);
    memcpy(LOCATION_MAIN_HALLWAY->description, "There is a heavy door topped with a sign.", LENGTH_DESCRIPTION);
    LOCATION_MAIN_HALLWAY->exits[0] = exit_objects[2];
    LOCATION_MAIN_HALLWAY->exits[1] = exit_objects[3];
    LOCATION_MAIN_HALLWAY->list_of_locations_by_id[0] = ID_LOCATION_NONE;
    LOCATION_MAIN_HALLWAY->list_of_items_by_id[0] = ID_ITEM_ENTRY_DOORS;
    LOCATION_MAIN_HALLWAY->list_of_items_by_id[1] = ID_ITEM_GRANDFATHER_CLOCK;
    LOCATION_MAIN_HALLWAY->list_of_items_by_id[2] = ID_ITEM_LIBRARY_DOOR;
    LOCATION_MAIN_HALLWAY->list_of_items_by_id[3] = ID_ITEM_LIBRARY_SIGN;
    LOCATION_MAIN_HALLWAY->list_of_characters_by_id[0] = ID_CHARACTER_NONE;

    LOCATION_OLD_LIBRARY->id = ID_LOCATION_OLD_LIBRARY;
    LOCATION_OLD_LIBRARY->type = LOCATION_TYPE_ROOM;
    LOCATION_OLD_LIBRARY->inside_of = LOCATION_MANSION;
    memcpy(LOCATION_OLD_LIBRARY->name, "old library", LENGTH_NAME);
    memcpy(LOCATION_OLD_LIBRARY->tags[0], "library", LENGTH_NAME);
    memcpy(LOCATION_OLD_LIBRARY->tags[1], "old library", LENGTH_NAME);
    memcpy(LOCATION_OLD_LIBRARY->description, "A librarian is standing there, reading. In the back of the room, you can discern small doors. Three to be precise.", LENGTH_DESCRIPTION);
    LOCATION_OLD_LIBRARY->exits[0] = exit_objects[4];
    LOCATION_OLD_LIBRARY->exits[1] = exit_objects[5];
    LOCATION_OLD_LIBRARY->exits[2] = exit_objects[6];
    LOCATION_OLD_LIBRARY->exits[3] = exit_objects[7];
    LOCATION_OLD_LIBRARY->list_of_locations_by_id[0] = ID_LOCATION_NONE;
    LOCATION_OLD_LIBRARY->list_of_items_by_id[0] = ID_ITEM_LIBRARY_DOOR;
    LOCATION_OLD_LIBRARY->list_of_items_by_id[1] = ID_ITEM_BOOKS;
    LOCATION_OLD_LIBRARY->list_of_items_by_id[2] = ID_ITEM_DOOR_ROOM_1;
    LOCATION_OLD_LIBRARY->list_of_items_by_id[3] = ID_ITEM_DOOR_ROOM_2;
    LOCATION_OLD_LIBRARY->list_of_items_by_id[4] = ID_ITEM_DOOR_ROOM_3;
    LOCATION_OLD_LIBRARY->list_of_characters_by_id[0] = ID_CHARACTER_LIBRARIAN;

    LOCATION_ROOM_1->id = ID_LOCATION_ROOM_1;
    LOCATION_ROOM_1->type = LOCATION_TYPE_ROOM;
    LOCATION_ROOM_1->inside_of = LOCATION_MANSION;
    memcpy(LOCATION_ROOM_1->name, "first room", LENGTH_NAME);
    memcpy(LOCATION_ROOM_1->tags[0], "room 1", LENGTH_NAME);
    memcpy(LOCATION_ROOM_1->tags[1], "first room", LENGTH_NAME);
    memcpy(LOCATION_ROOM_1->description, "The room seems empty.", LENGTH_DESCRIPTION);
    LOCATION_ROOM_1->exits[0] = exit_objects[8];
    LOCATION_ROOM_1->list_of_locations_by_id[0] = ID_LOCATION_NONE;
    LOCATION_ROOM_1->list_of_items_by_id[0] = ID_ITEM_DOOR_ROOM_1;
    LOCATION_ROOM_1->list_of_characters_by_id[0] = ID_CHARACTER_NONE;

    LOCATION_ROOM_2->id = ID_LOCATION_ROOM_2;
    LOCATION_ROOM_2->type = LOCATION_TYPE_ROOM;
    LOCATION_ROOM_2->inside_of = LOCATION_MANSION;
    memcpy(LOCATION_ROOM_2->name, "second room", LENGTH_NAME);
    memcpy(LOCATION_ROOM_2->tags[0], "room 2", LENGTH_NAME);
    memcpy(LOCATION_ROOM_2->tags[1], "second room", LENGTH_NAME);
    memcpy(LOCATION_ROOM_2->description, "The room seems empty.", LENGTH_DESCRIPTION);
    LOCATION_ROOM_2->exits[0] = exit_objects[9];
    LOCATION_ROOM_2->list_of_locations_by_id[0] = ID_LOCATION_NONE;
    LOCATION_ROOM_2->list_of_items_by_id[0] = ID_ITEM_DOOR_ROOM_2;
    LOCATION_ROOM_2->list_of_items_by_id[1] = ID_ITEM_ENTRY_DOORS_KEY;
    LOCATION_ROOM_2->list_of_characters_by_id[0] = ID_CHARACTER_NONE;

    LOCATION_ROOM_3->id = ID_LOCATION_ROOM_3;
    LOCATION_ROOM_3->type = LOCATION_TYPE_ROOM;
    LOCATION_ROOM_3->inside_of = LOCATION_MANSION;
    memcpy(LOCATION_ROOM_3->name, "third room", LENGTH_NAME);
    memcpy(LOCATION_ROOM_3->tags[0], "room 3", LENGTH_NAME);
    memcpy(LOCATION_ROOM_3->tags[1], "third room", LENGTH_NAME);
    memcpy(LOCATION_ROOM_3->description, "The room seems empty.", LENGTH_DESCRIPTION);
    LOCATION_ROOM_3->exits[0] = exit_objects[10];
    LOCATION_ROOM_3->list_of_locations_by_id[0] = ID_LOCATION_NONE;
    LOCATION_ROOM_3->list_of_items_by_id[0] = ID_ITEM_DOOR_ROOM_3;
    LOCATION_ROOM_3->list_of_characters_by_id[0] = ID_CHARACTER_NONE;
    return;
}

void describe_location(const Location* location)
{
    int i;

    /* Temporary: If we are outside, print the description of the first location in "outside"'s location list. Turns out there's only one, the mansion. */
    if (location->type == LOCATION_TYPE_OUTSIDE)
        printf("%s ", list_locations[location->list_of_locations_by_id[0]].description);
    else
        printf("%s ", location->description);

    for (i = 0; i < NBR_ITEMS; ++i)
    {
        if (location->list_of_items_by_id[i] == ID_ITEM_NONE)
            break;

        /* Only mention items which are not an access to an exit, such as a door */
        if (list_items[location->list_of_items_by_id[i]].access == ACCESS_NONE)
            printf("%s ", list_items[location->list_of_items_by_id[i]].description_obvious);
    }
}

SameTag* retrieve_location_id_by_parser_from_current_location(const char* parser)
{
    int i, j, k;
    SameTag* locations_with_same_tag = calloc(NBR_LOCATIONS, sizeof(SameTag));
    if (!locations_with_same_tag)
        return NULL;

    for (i = 0, k = 0; i <= NBR_LOCATIONS; ++i)
    {
        if (i == NBR_LOCATIONS || PLAYER->current_location->exits[i].to->id == ID_LOCATION_NONE)
            break;

        for (j = 0; j <= NBR_TAGS; ++j)
        {
            if (j == NBR_TAGS || PLAYER->current_location->exits[i].to->tags[j] == NULL)
                break;

            if (strcmp(parser, PLAYER->current_location->exits[i].to->tags[j]) == 0)
            {
                locations_with_same_tag[k].index = i;
                locations_with_same_tag[k++].id = PLAYER->current_location->exits[i].to->id;
                break;
            }
        }
    }

    return locations_with_same_tag;
}

