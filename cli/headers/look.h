#ifndef LOOK_H
#define LOOK_H

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

#include "game.h"
#include "events.h"

void execute_look(void);

#define NO_ITEM_AT_CURRENT_LOCATION                     (!PLAYER->current_location->items[0])
#define NO_CHARACTER_AT_CURRENT_LOCATION                (!PLAYER->current_location->characters[0])
#define PLAYER_IS_ONLY_CHARACTER_AT_CURRENT_LOCATION    (PLAYER->current_location->characters[0] == PLAYER && !PLAYER->current_location->characters[1])

#endif

