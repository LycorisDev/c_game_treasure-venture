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

void populate_list_locations(void);
char* retrieve_default_location_tag_by_id(const int location_id);
int retrieve_location_id_by_parser(const char* parser);
int bool_parser_and_location_id_do_match(const char* parser, const int location_id);

#endif

