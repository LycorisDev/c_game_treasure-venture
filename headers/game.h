#ifndef GAME_H
#define GAME_H

#define LENGTH_TAG            120
#define LENGTH_DESCRIPTION    512
#define NBR_TAGS              7
#define NBR_GEO_AFF           2
#define NBR_LOCATIONS         16
#define NBR_ITEMS             100
#define NBR_CHARACTERS        5

typedef struct
{
    const char* key;
    void (*func)(void);
} KeyFunc;

typedef struct location Location;
typedef struct item Item;
typedef struct character Character;

/* Geographical Affiliation */
typedef struct
{
    int id;
    char name[LENGTH_TAG];
} GeoAff;

typedef struct exit
{
    Location* to;
    Item* passage;
} Exit;

struct location
{
    int id;
    char tags[NBR_TAGS][LENGTH_TAG];
    char description[LENGTH_DESCRIPTION];

    int bool_is_indoors;
    GeoAff* geo_aff;
    Exit exits[NBR_LOCATIONS];

    Item* items[NBR_ITEMS];
    Character* characters[NBR_CHARACTERS];
};

struct item
{
    int id;
    char tags[NBR_TAGS][LENGTH_TAG];
    char description[LENGTH_DESCRIPTION];

    char desc_look_around[LENGTH_DESCRIPTION];
    char desc_look_item[LENGTH_DESCRIPTION];
    int bool_is_singular;
    int access;
    Item* unlocked_with;
    int bool_can_be_taken;
    int bool_requires_target_for_use;
};

struct character
{
    int id;
    char tags[NBR_TAGS][LENGTH_TAG];
    char description[LENGTH_DESCRIPTION];

    Location* previous_location;
    Location* current_location;
    Item* inventory[NBR_ITEMS];
};

extern GeoAff list_geo_aff[NBR_GEO_AFF];
extern Location list_locations[NBR_LOCATIONS];
extern Item list_items[NBR_ITEMS];
extern Character list_characters[NBR_CHARACTERS];

/* -------------------------------------------------------------------------------- */
#define ACCESS_LOCKED                1
#define ACCESS_OPEN                  2
#define ACCESS_CLOSED                3
/* -------------------------------------------------------------------------------- */
#define ID_LOCATION_OUTSIDE          1
#define ID_LOCATION_MAIN_HALLWAY     2
#define ID_LOCATION_OLD_LIBRARY      3
#define ID_LOCATION_ROOM_1           4
#define ID_LOCATION_ROOM_2           5
#define ID_LOCATION_ROOM_3           6

#define LOCATION_OUTSIDE             (list_locations + (ID_LOCATION_OUTSIDE - 1))
#define LOCATION_MAIN_HALLWAY        (list_locations + (ID_LOCATION_MAIN_HALLWAY - 1))
#define LOCATION_OLD_LIBRARY         (list_locations + (ID_LOCATION_OLD_LIBRARY - 1))
#define LOCATION_ROOM_1              (list_locations + (ID_LOCATION_ROOM_1 - 1))
#define LOCATION_ROOM_2              (list_locations + (ID_LOCATION_ROOM_2 - 1))
#define LOCATION_ROOM_3              (list_locations + (ID_LOCATION_ROOM_3 - 1))
/* -------------------------------------------------------------------------------- */
#define ID_ITEM_ENTRY_DOORS          1
#define ID_ITEM_GRANDFATHER_CLOCK    2
#define ID_ITEM_LIBRARY_DOOR         3
#define ID_ITEM_LIBRARY_SIGN         4
#define ID_ITEM_BOOKS                5
#define ID_ITEM_DOOR_ROOM_1          6
#define ID_ITEM_DOOR_ROOM_2          7
#define ID_ITEM_DOOR_ROOM_3          8
#define ID_ITEM_ENTRY_DOORS_KEY      9

#define ITEM_ENTRY_DOORS             (list_items + (ID_ITEM_ENTRY_DOORS - 1))
#define ITEM_GRANDFATHER_CLOCK       (list_items + (ID_ITEM_GRANDFATHER_CLOCK - 1))
#define ITEM_LIBRARY_DOOR            (list_items + (ID_ITEM_LIBRARY_DOOR - 1))
#define ITEM_LIBRARY_SIGN            (list_items + (ID_ITEM_LIBRARY_SIGN - 1))
#define ITEM_BOOKS                   (list_items + (ID_ITEM_BOOKS - 1))
#define ITEM_DOOR_ROOM_1             (list_items + (ID_ITEM_DOOR_ROOM_1 - 1))
#define ITEM_DOOR_ROOM_2             (list_items + (ID_ITEM_DOOR_ROOM_2 - 1))
#define ITEM_DOOR_ROOM_3             (list_items + (ID_ITEM_DOOR_ROOM_3 - 1))
#define ITEM_ENTRY_DOORS_KEY         (list_items + (ID_ITEM_ENTRY_DOORS_KEY - 1))
/* -------------------------------------------------------------------------------- */
#define ID_CHARACTER_PLAYER          1
#define ID_CHARACTER_LIBRARIAN       2

#define PLAYER                       (list_characters + (ID_CHARACTER_PLAYER - 1))
#define CHARACTER_LIBRARIAN          (list_characters + (ID_CHARACTER_LIBRARIAN - 1))
/* -------------------------------------------------------------------------------- */

#endif

