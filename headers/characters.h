#ifndef CHARACTERS_H
#define CHARACTERS_H

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

void populate_list_characters(void);
void display_character_suggestions(Character** character_collection, const char* command);
Character** retrieve_characters(Character** character_collection, const char* parser);

#endif

