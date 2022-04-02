#ifndef GAME_H
#define GAME_H

#define LENGTH_NAME           100
#define LENGTH_DESCRIPTION    512
#define NBR_LOCATIONS         16
#define NBR_ITEMS             100
#define NBR_CHARACTERS        5

typedef struct location Location;
typedef struct item Item;
typedef struct character Character;

typedef struct exit
{
    Location* from;
    Location* to;
    Item* passage;
} Exit;

struct location
{
    int location_id;
    char description[LENGTH_DESCRIPTION];
    Exit exits[NBR_LOCATIONS];
    int list_of_items_by_id[NBR_ITEMS];
    int list_of_characters_by_id[NBR_CHARACTERS];
};

struct item
{
    int item_id;
    int is_singular;
    int access;
    int can_be_taken;
    char name[LENGTH_NAME];
    char description[LENGTH_DESCRIPTION];
};

struct character
{
    int character_id;
    char description[LENGTH_DESCRIPTION];
    Location* previous_location;
    Location* current_location;
    int list_of_items_by_id[NBR_ITEMS];
};

extern Location list_locations[NBR_LOCATIONS];
extern Item list_items[NBR_ITEMS];
extern Character list_characters[NBR_CHARACTERS];

/* -------------------------------------------------------------------------------- */
#define ACCESS_NONE                  0
#define ACCESS_LOCKED                1
#define ACCESS_OPEN                  2
#define ACCESS_CLOSED                3
/* -------------------------------------------------------------------------------- */
#define ID_LOCATION_NONE             0
#define ID_LOCATION_OUTSIDE          1
#define ID_LOCATION_MAIN_HALLWAY     2
#define ID_LOCATION_OLD_LIBRARY      3
#define ID_LOCATION_ROOM_1           4
#define ID_LOCATION_ROOM_2           5
#define ID_LOCATION_ROOM_3           6

#define LOCATION_NONE                (list_locations + ID_LOCATION_NONE)
#define LOCATION_OUTSIDE             (list_locations + ID_LOCATION_OUTSIDE)
#define LOCATION_MAIN_HALLWAY        (list_locations + ID_LOCATION_MAIN_HALLWAY)
#define LOCATION_OLD_LIBRARY         (list_locations + ID_LOCATION_OLD_LIBRARY)
#define LOCATION_ROOM_1              (list_locations + ID_LOCATION_ROOM_1)
#define LOCATION_ROOM_2              (list_locations + ID_LOCATION_ROOM_2)
#define LOCATION_ROOM_3              (list_locations + ID_LOCATION_ROOM_3)
/* -------------------------------------------------------------------------------- */
#define ID_ITEM_NONE                 0
#define ID_ITEM_ENTRY_DOORS          1
#define ID_ITEM_GRANDFATHER_CLOCK    2
#define ID_ITEM_LIBRARY_DOOR         3
#define ID_ITEM_LIBRARY_SIGN         4
#define ID_ITEM_BOOKS                5
#define ID_ITEM_DOOR_ROOM_1          6
#define ID_ITEM_DOOR_ROOM_2          7
#define ID_ITEM_DOOR_ROOM_3          8
#define ID_ITEM_ENTRY_DOORS_KEY      9

#define ITEM_NONE                    (list_items + ID_ITEM_NONE)
#define ITEM_ENTRY_DOORS             (list_items + ID_ITEM_ENTRY_DOORS)
#define ITEM_GRANDFATHER_CLOCK       (list_items + ID_ITEM_GRANDFATHER_CLOCK)
#define ITEM_LIBRARY_DOOR            (list_items + ID_ITEM_LIBRARY_DOOR)
#define ITEM_LIBRARY_SIGN            (list_items + ID_ITEM_LIBRARY_SIGN)
#define ITEM_BOOKS                   (list_items + ID_ITEM_BOOKS)
#define ITEM_DOOR_ROOM_1             (list_items + ID_ITEM_DOOR_ROOM_1)
#define ITEM_DOOR_ROOM_2             (list_items + ID_ITEM_DOOR_ROOM_2)
#define ITEM_DOOR_ROOM_3             (list_items + ID_ITEM_DOOR_ROOM_3)
#define ITEM_ENTRY_DOORS_KEY         (list_items + ID_ITEM_ENTRY_DOORS_KEY)
/* -------------------------------------------------------------------------------- */
#define ID_CHARACTER_NONE            0
#define ID_CHARACTER_PLAYER          1
#define ID_CHARACTER_LIBRARIAN       2

#define CHARACTER_NONE               (list_characters + ID_CHARACTER_NONE)
#define PLAYER                       (list_characters + ID_CHARACTER_PLAYER)
#define CHARACTER_LIBRARIAN          (list_characters + ID_CHARACTER_LIBRARIAN)
/* -------------------------------------------------------------------------------- */

#endif

