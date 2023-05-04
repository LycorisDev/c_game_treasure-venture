#include "../headers/locations.h"
#include "../headers/main.h"
#include "../headers/items.h"

/* Declared as extern in ../headers/game.h, included in ../headers/locations.h */
Location list_locations[NBR_LOCATIONS];
GeoAff list_geo_aff[NBR_GEO_AFF];

static void get_all_tags(char* p_str, const int word_length, Location* object);
static int bool_location_matches_parser(const Location* destination, const char* parser);

void populate_list_locations(void)
{
    Exit exit_objects[NBR_LOCATIONS];
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

    memset(list_geo_aff, 0, NBR_GEO_AFF * sizeof(GeoAff));
    memset(list_locations, 0, NBR_LOCATIONS * sizeof(Location));

    list_geo_aff[0].id = 1;
    memcpy(list_geo_aff[0].name, "world", LENGTH_TAG);
    list_geo_aff[1].id = 2;
    memcpy(list_geo_aff[1].name, "mansion", LENGTH_TAG);

    LOCATION_OUTSIDE->id = ID_LOCATION_OUTSIDE;
    LOCATION_OUTSIDE->bool_is_indoors = 0;
    LOCATION_OUTSIDE->geo_aff = &(list_geo_aff[0]);
    memcpy(LOCATION_OUTSIDE->tags[0], "world", LENGTH_TAG);
    memcpy(LOCATION_OUTSIDE->description, "", LENGTH_DESCRIPTION);
    LOCATION_OUTSIDE->exits[0] = exit_objects[2];
    LOCATION_OUTSIDE->items[0] = ITEM_ENTRY_DOORS;
    LOCATION_OUTSIDE->characters[0] = PLAYER;

    LOCATION_MAIN_HALLWAY->id = ID_LOCATION_MAIN_HALLWAY;
    LOCATION_MAIN_HALLWAY->bool_is_indoors = 1;
    LOCATION_MAIN_HALLWAY->geo_aff = &(list_geo_aff[1]);
    memcpy(LOCATION_MAIN_HALLWAY->tags[0], "main hallway", LENGTH_TAG);
    memcpy(LOCATION_MAIN_HALLWAY->tags[1], "hallway", LENGTH_TAG);
    memcpy(LOCATION_MAIN_HALLWAY->description, "There is a heavy door topped with a sign.", LENGTH_DESCRIPTION);
    LOCATION_MAIN_HALLWAY->exits[0] = exit_objects[1];
    LOCATION_MAIN_HALLWAY->exits[1] = exit_objects[3];
    LOCATION_MAIN_HALLWAY->items[0] = ITEM_ENTRY_DOORS;
    LOCATION_MAIN_HALLWAY->items[1] = ITEM_GRANDFATHER_CLOCK;
    LOCATION_MAIN_HALLWAY->items[2] = ITEM_LIBRARY_DOOR;
    LOCATION_MAIN_HALLWAY->items[3] = ITEM_LIBRARY_SIGN;

    LOCATION_OLD_LIBRARY->id = ID_LOCATION_OLD_LIBRARY;
    LOCATION_OLD_LIBRARY->bool_is_indoors = 1;
    LOCATION_OLD_LIBRARY->geo_aff = &(list_geo_aff[1]);
    memcpy(LOCATION_OLD_LIBRARY->tags[0], "old library", LENGTH_TAG);
    memcpy(LOCATION_OLD_LIBRARY->tags[1], "library", LENGTH_TAG);
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
    LOCATION_ROOM_1->bool_is_indoors = 1;
    LOCATION_ROOM_1->geo_aff = &(list_geo_aff[1]);
    memcpy(LOCATION_ROOM_1->tags[0], "first room", LENGTH_TAG);
    memcpy(LOCATION_ROOM_1->tags[1], "room 1", LENGTH_TAG);
    memcpy(LOCATION_ROOM_1->description, "The room seems empty.", LENGTH_DESCRIPTION);
    LOCATION_ROOM_1->exits[0] = exit_objects[8];
    LOCATION_ROOM_1->items[0] = ITEM_DOOR_ROOM_1;

    LOCATION_ROOM_2->id = ID_LOCATION_ROOM_2;
    LOCATION_ROOM_2->bool_is_indoors = 1;
    LOCATION_ROOM_2->geo_aff = &(list_geo_aff[1]);
    memcpy(LOCATION_ROOM_2->tags[0], "second room", LENGTH_TAG);
    memcpy(LOCATION_ROOM_2->tags[1], "room 2", LENGTH_TAG);
    memcpy(LOCATION_ROOM_2->description, "The room seems empty.", LENGTH_DESCRIPTION);
    LOCATION_ROOM_2->exits[0] = exit_objects[9];
    LOCATION_ROOM_2->items[0] = ITEM_DOOR_ROOM_2;
    LOCATION_ROOM_2->items[1] = ITEM_ENTRY_DOORS_KEY;

    LOCATION_ROOM_3->id = ID_LOCATION_ROOM_3;
    LOCATION_ROOM_3->bool_is_indoors = 1;
    LOCATION_ROOM_3->geo_aff = &(list_geo_aff[1]);
    memcpy(LOCATION_ROOM_3->tags[0], "third room", LENGTH_TAG);
    memcpy(LOCATION_ROOM_3->tags[1], "room 3", LENGTH_TAG);
    memcpy(LOCATION_ROOM_3->description, "The room seems empty.", LENGTH_DESCRIPTION);
    LOCATION_ROOM_3->exits[0] = exit_objects[10];
    LOCATION_ROOM_3->items[0] = ITEM_DOOR_ROOM_3;
    return;
}

void describe_location(const Location* location)
{
    int i;

    /* Display location name */
    if (!PLAYER->current_location->bool_is_indoors)
        add_output("You are outside. ");
    else
        add_output("You are in the %s. ", PLAYER->current_location->tags[0]);

    /* TODO: Remove the need for this temporary fix. The geo_aff should be described without being hardcoded, a bit like an event. */
    if (location->bool_is_indoors)
        add_output("%s ", location->description);
    else
        add_output("The mansion in front of you gives you a bad feeling. Its main double doors don't look welcoming.");

    for (i = 0; i < NBR_ITEMS; ++i)
    {
        if (!location->items[i])
            break;

        /* Only mention items which are not an access to an exit, such as a door */
        if (!location->items[i]->access)
            add_output("%s ", location->items[i]->desc_look_around);
    }

    add_output("\n\n");
    return;
}

void display_location_suggestions(Location* origin)
{
    int i;
    char* str_tags = NULL;
    int word_length = 0;
    int bool_ins_out_already_printed = 0;

    if (!origin || !origin->exits[0].to)
        return;

    word_length = sizeof(origin->exits[0].to->tags[0]) + 3;
    str_tags = calloc(NBR_TAGS, word_length);

    add_output("\t[Try:]\n");
    for (i = 0; i < NBR_LOCATIONS; ++i)
    {
        if (!origin->exits[i].to)
            break;

        if (origin->geo_aff->id == origin->exits[i].to->geo_aff->id)
        {
            get_all_tags(str_tags, word_length, origin->exits[i].to);
            add_output("\t\t['Go %s'.]\n", str_tags);
            continue;
        }
        else if (bool_ins_out_already_printed)
            continue;

        bool_ins_out_already_printed = 1;
        if (origin->bool_is_indoors)
            add_output("\t\t['Go outside'.]\n");
        else
            add_output("\t\t['Go inside'.]\n");
    }
    add_output("\n");

    free(str_tags);
    return;
}

Exit** retrieve_locations(Location* origin, const char* parser)
{
    int i, j;
    Exit** locations = calloc(NBR_LOCATIONS, sizeof(Exit*));
    if (!locations)
        return NULL;

    for (i = 0, j = 0; i < NBR_LOCATIONS; ++i)
    {
        if (!origin->exits[i].to)
            break;

        /* "go [building]" */
        if (origin->geo_aff->id != origin->exits[i].to->geo_aff->id) 
        {
            if (!strcmp(parser, origin->exits[i].to->geo_aff->name))
                locations[j++] = &(origin->exits[i]);
            continue;
        }

        /* "go [room]" */
        if (bool_location_matches_parser(origin->exits[i].to, parser))
            locations[j++] = &(origin->exits[i]);
    }

    return locations;
}

Exit** retrieve_locations_with_passage_item(Location* origin, const char* parser)
{
    int i, j;
    Exit** exits = calloc(NBR_LOCATIONS, sizeof(Exit*));
    if (!exits)
        return NULL;

    for (i = 0, j = 0; i < NBR_LOCATIONS; ++i)
    {
        if (!origin->exits[i].to || !origin->exits[i].passage->access)
            break;

        if (bool_item_matches_parser(origin->exits[i].passage, parser))
            exits[j++] = &(origin->exits[i]);
    }

    return exits;
}

static void get_all_tags(char* p_str, const int word_length, Location* object)
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

static int bool_location_matches_parser(const Location* destination, const char* parser)
{
    int i;
    for (i = 0; i < NBR_TAGS; ++i)
    {
        if (!destination->tags[i])
            return 0;

        if (!strcmp(parser, destination->tags[i]))
            return 1;
    }
    return 0;
}

