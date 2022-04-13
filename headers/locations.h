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

#include "game.h"

#define LOCATION_NAME   if (PLAYER->current_location->inside_of->id == ID_LOCATION_NONE)\
                            printf("\nYou are outside. ");\
                        else\
                            printf("\nYou are in the %s. ", PLAYER->current_location->name);

void populate_list_locations(void);
void describe_location(const Location* location);
SameTag* retrieve_location_id_by_parser_from_current_location(const char* parser);

#endif

