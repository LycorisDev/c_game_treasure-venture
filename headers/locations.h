#ifndef LOCATIONS_H
#define LOCATIONS_H

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

#include "main.h"
#include "game.h"

void populate_list_locations(void);
void describe_location(const Location* location);
void display_location_suggestions(Location* origin);
Exit** retrieve_locations(Location* origin, const char* parser);
Exit** retrieve_locations_with_passage_item(Location* origin, const char* parser);

#endif

