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

    LOCATION_NONE->location_id = 0;
    memcpy(LOCATION_NONE->description, "NO_DESCRIPTION", LENGTH_DESCRIPTION);
    LOCATION_NONE->exits[0] = exit_objects[0];
    LOCATION_NONE->list_of_items_by_id[0] = ID_ITEM_NONE;
    LOCATION_NONE->list_of_characters_by_id[0] = ID_CHARACTER_NONE;

    LOCATION_OUTSIDE->location_id = 1;
    memcpy(LOCATION_OUTSIDE->description, "You are outside of a mansion, in front of its main double doors.", LENGTH_DESCRIPTION);
    LOCATION_OUTSIDE->exits[0] = exit_objects[1];
    LOCATION_OUTSIDE->list_of_items_by_id[0] = ID_ITEM_ENTRY_DOORS;
    LOCATION_OUTSIDE->list_of_characters_by_id[0] = ID_CHARACTER_NONE;

    LOCATION_MAIN_HALLWAY->location_id = 2;
    memcpy(LOCATION_MAIN_HALLWAY->description, "You cross the mansion's threshold and find yourself in a large hallway. A distinct noise lets you know the entry doors have locked, seemingly all by themselves. You hope this is no haunting place. Anyway, the loud ticks of the grandfather clocks is nerve-wracking. You've always hated those. On your left is a heavy door, topped with a sign that reads 'Library.'", LENGTH_DESCRIPTION);
    LOCATION_MAIN_HALLWAY->exits[0] = exit_objects[2];
    LOCATION_MAIN_HALLWAY->exits[1] = exit_objects[3];
    LOCATION_MAIN_HALLWAY->list_of_items_by_id[0] = ID_ITEM_ENTRY_DOORS;
    LOCATION_MAIN_HALLWAY->list_of_items_by_id[1] = ID_ITEM_GRANDFATHER_CLOCK;
    LOCATION_MAIN_HALLWAY->list_of_items_by_id[2] = ID_ITEM_LIBRARY_DOOR;
    LOCATION_MAIN_HALLWAY->list_of_items_by_id[3] = ID_ITEM_LIBRARY_SIGN;
    LOCATION_MAIN_HALLWAY->list_of_characters_by_id[0] = ID_CHARACTER_NONE;

    LOCATION_OLD_LIBRARY->location_id = 3;
    memcpy(LOCATION_OLD_LIBRARY->description, "You are in a large library. The walls are lined with old, dusty books. A librarian is standing there, reading. In the back of the room, you can discern small doors. Three to be precise.", LENGTH_DESCRIPTION);
    LOCATION_OLD_LIBRARY->exits[0] = exit_objects[4];
    LOCATION_OLD_LIBRARY->exits[1] = exit_objects[5];
    LOCATION_OLD_LIBRARY->exits[2] = exit_objects[6];
    LOCATION_OLD_LIBRARY->exits[3] = exit_objects[7];
    LOCATION_OLD_LIBRARY->list_of_items_by_id[0] = ID_ITEM_LIBRARY_DOOR;
    LOCATION_OLD_LIBRARY->list_of_items_by_id[1] = ID_ITEM_BOOKS;
    LOCATION_OLD_LIBRARY->list_of_items_by_id[2] = ID_ITEM_DOOR_ROOM_1;
    LOCATION_OLD_LIBRARY->list_of_items_by_id[3] = ID_ITEM_DOOR_ROOM_2;
    LOCATION_OLD_LIBRARY->list_of_items_by_id[4] = ID_ITEM_DOOR_ROOM_3;
    LOCATION_OLD_LIBRARY->list_of_characters_by_id[0] = ID_CHARACTER_LIBRARIAN;

    LOCATION_ROOM_1->location_id = 4;
    memcpy(LOCATION_ROOM_1->description, "You are in the first room.", LENGTH_DESCRIPTION);
    LOCATION_ROOM_1->exits[0] = exit_objects[8];
    LOCATION_ROOM_1->list_of_items_by_id[0] = ID_ITEM_DOOR_ROOM_1;
    LOCATION_ROOM_1->list_of_characters_by_id[0] = ID_CHARACTER_NONE;

    LOCATION_ROOM_2->location_id = 5;
    memcpy(LOCATION_ROOM_2->description, "You are in the second room. Something shiny, left unattended on the ground, catches your attention.", LENGTH_DESCRIPTION);
    LOCATION_ROOM_2->exits[0] = exit_objects[9];
    LOCATION_ROOM_2->list_of_items_by_id[0] = ID_ITEM_DOOR_ROOM_2;
    LOCATION_ROOM_2->list_of_items_by_id[1] = ID_ITEM_ENTRY_DOORS_KEY;
    LOCATION_ROOM_2->list_of_characters_by_id[0] = ID_CHARACTER_NONE;

    LOCATION_ROOM_3->location_id = 6;
    memcpy(LOCATION_ROOM_3->description, "You are in the third room.", LENGTH_DESCRIPTION);
    LOCATION_ROOM_3->exits[0] = exit_objects[10];
    LOCATION_ROOM_3->list_of_items_by_id[0] = ID_ITEM_DOOR_ROOM_3;
    LOCATION_ROOM_3->list_of_characters_by_id[0] = ID_CHARACTER_NONE;
    return;
}

char* retrieve_default_location_tag_by_id(const int location_id)
{
    switch(location_id)
    {
        case ID_LOCATION_OUTSIDE:
            return "outside";
        case ID_LOCATION_MAIN_HALLWAY:
            if (PLAYER->current_location == LOCATION_OUTSIDE)
                return "inside";
            return "hallway";
        case ID_LOCATION_OLD_LIBRARY:
            return "library";
        case ID_LOCATION_ROOM_1:
            return "room 1";
        case ID_LOCATION_ROOM_2:
            return "room 2";
        case ID_LOCATION_ROOM_3:
            return "room 3";
        default:
            return "";
    }
}

int retrieve_location_id_by_parser(const char* parser)
{
    if (strcmp(parser, "outside") == 0 || strcmp(parser, "entry doors") == 0)
        return ID_LOCATION_OUTSIDE;
    else if (PLAYER->current_location == LOCATION_OUTSIDE && (strcmp(parser, "inside") == 0 || strcmp(parser, "entry doors") == 0))
        return ID_LOCATION_MAIN_HALLWAY;
    else if (PLAYER->current_location != LOCATION_OUTSIDE && (strcmp(parser, "main hallway") == 0 || strcmp(parser, "hallway") == 0 || strcmp(parser, "library door") == 0))
        return ID_LOCATION_MAIN_HALLWAY;
    else if (strcmp(parser, "old library") == 0 || strcmp(parser, "library") == 0)
        return ID_LOCATION_OLD_LIBRARY;
    else if (PLAYER->current_location == LOCATION_MAIN_HALLWAY && strcmp(parser, "library door") == 0)
        return ID_LOCATION_OLD_LIBRARY;
    else if (PLAYER->current_location == LOCATION_ROOM_1 && strcmp(parser, "door room 1") == 0)
        return ID_LOCATION_OLD_LIBRARY;
    else if (PLAYER->current_location == LOCATION_ROOM_2 && strcmp(parser, "door room 2") == 0)
        return ID_LOCATION_OLD_LIBRARY;
    else if (PLAYER->current_location == LOCATION_ROOM_3 && strcmp(parser, "door room 3") == 0)
        return ID_LOCATION_OLD_LIBRARY;
    else if (strcmp(parser, "first room") == 0 || strcmp(parser, "room 1") == 0 || strcmp(parser, "door room 1") == 0)
        return ID_LOCATION_ROOM_1;
    else if (strcmp(parser, "second room") == 0 || strcmp(parser, "room 2") == 0 || strcmp(parser, "door room 2") == 0)
        return ID_LOCATION_ROOM_2;
    else if (strcmp(parser, "third room") == 0 || strcmp(parser, "room 3") == 0 || strcmp(parser, "door room 3") == 0)
        return ID_LOCATION_ROOM_3;
    else
        return ID_LOCATION_NONE;
}

int bool_parser_and_location_id_do_match(const char* parser, const int location_id)
{
    switch(location_id)
    {
        case ID_LOCATION_OUTSIDE:
            return strcmp(parser, "outside") == 0 || strcmp(parser, "entry doors") == 0 ? 1 : 0;
        case ID_LOCATION_MAIN_HALLWAY:
            if (PLAYER->current_location == LOCATION_OUTSIDE)
                return strcmp(parser, "inside") == 0 || strcmp(parser, "entry doors") == 0 ? 1 : 0;	
            else
                return strcmp(parser, "main hallway") == 0 || strcmp(parser, "hallway") == 0 || strcmp(parser, "library door") == 0 ? 1 : 0;
        case ID_LOCATION_OLD_LIBRARY:
            if (strcmp(parser, "old library") == 0 || strcmp(parser, "library") == 0)
                return 1;
            else if (PLAYER->current_location == LOCATION_MAIN_HALLWAY && strcmp(parser, "library door") == 0)
                return 1;
            else if (PLAYER->current_location == LOCATION_ROOM_1 && strcmp(parser, "door room 1") == 0)
                return 1;
            else if (PLAYER->current_location == LOCATION_ROOM_2 && strcmp(parser, "door room 2") == 0)
                return 1;
            else if (PLAYER->current_location == LOCATION_ROOM_3 && strcmp(parser, "door room 3") == 0)
                return 1;
            else
                return 0;
        case ID_LOCATION_ROOM_1:
            return strcmp(parser, "first room") == 0 || strcmp(parser, "room 1") == 0 || strcmp(parser, "door room 1") == 0 ? 1 : 0;
        case ID_LOCATION_ROOM_2:
            return strcmp(parser, "second room") == 0 || strcmp(parser, "room 2") == 0 || strcmp(parser, "door room 2") == 0 ? 1 : 0;
        case ID_LOCATION_ROOM_3:
            return strcmp(parser, "third room") == 0 || strcmp(parser, "room 3") == 0 || strcmp(parser, "door room 3") == 0 ? 1 : 0;
        default:
            return 0;
    }
}

