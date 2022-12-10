#ifndef TWENTY_SQUARES_H
#define TWENTY_SQUARES_H

#ifndef STANDARD_LIBRARY_STDIO
#define STANDARD_LIBRARY_STDIO
#include <stdio.h>
#endif
#ifndef STANDARD_LIBRARY_STDLIB
#define STANDARD_LIBRARY_STDLIB
#include <stdlib.h>
#endif
#ifndef STANDARD_LIBRARY_STRING
#define STANDARD_LIBRARY_STRING
#include <string.h>
#endif
#ifndef STANDARD_LIBRARY_CTYPE
#define STANDARD_LIBRARY_CTYPE
#include <ctype.h>
#endif

#define ID_STONE_ONE                    1
#define ID_STONE_TWO                    2
#define ID_STONE_THREE                  3
#define ID_STONE_FOUR                   4
#define ID_STONE_FIVE                   5
#define ID_STONE_SIX                    6
#define ID_STONE_SEVEN                  7
#define ID_STONE_LUST                   8
#define ID_STONE_PRIDE                  9
#define ID_STONE_GLUTTONY               10
#define ID_STONE_SLOTH                  11
#define ID_STONE_ENVY                   12
#define ID_STONE_WRATH                  13
#define ID_STONE_GREED                  14

#define ABILITY_NONE                    0
#define ABILITY_CLASSIC                 1
#define ABILITY_AIR                     2
#define ABILITY_EARTH                   3
#define ABILITY_WATER                   4
#define ABILITY_FIRE                    5

#define DS_DECISION_PLAYER              0
#define DS_DECISION_USE                 1
#define DS_DECISION_DISCARD             2

#define INDEX_1_ON_4_INITIAL_ROAD       0
#define INDEX_2_ON_4_INITIAL_ROAD       1
#define INDEX_3_ON_4_INITIAL_ROAD       2
#define INDEX_4_ON_4_INITIAL_ROAD       3
#define INDEX_1_ON_8_COMMON_ROAD        4
#define INDEX_2_ON_8_COMMON_ROAD        5
#define INDEX_3_ON_8_COMMON_ROAD        6
#define INDEX_4_ON_8_COMMON_ROAD        7
#define INDEX_5_ON_8_COMMON_ROAD        8
#define INDEX_6_ON_8_COMMON_ROAD        9
#define INDEX_7_ON_8_COMMON_ROAD        10
#define INDEX_8_ON_8_COMMON_ROAD        11
#define INDEX_1_ON_2_END_ROAD           12
#define INDEX_2_ON_2_END_ROAD           13
#define INDEX_OUT_OF_BOUND              14
#define INDEX_1_ON_3_NO_KILLING_ROAD    11
#define INDEX_2_ON_3_NO_KILLING_ROAD    12
#define INDEX_3_ON_3_NO_KILLING_ROAD    13

#define LENGTH_STONE_NAME               9
#define LENGTH_PLAYER_NAME              11
#define PLAYER_ONE                      (players + 0)
#define PLAYER_TWO                      (players + 1)

typedef struct
{
    char name[LENGTH_STONE_NAME];
    int id;
    int player_id;
    int coordinate;
    int protected_by_earth;
    int can_stone_move;
    int possible_movements[4];
} Stone;

typedef struct
{
    int coordinate;
    Stone* stone_in_cell;
    int ability;
    int is_cell_special;
} Cell;

typedef struct
{
    int id;
    char name[11];
    int is_artificial_intelligence;
    int points;
    int number_of_playable_stones; /* Stones that aren't dead or won/saved, even if they can't move */
    int number_of_stones_on_board; /* Stones that are strictly on the board */
    Stone stoneset[7];
    Cell* racetrack[15]; /* The 15th element is INDEX_OUT_OF_BOUND and has a coordinate of "1" */
} Player;

#endif

