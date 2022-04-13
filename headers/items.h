#ifndef ITEMS_H
#define ITEMS_H

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

void populate_list_items(void);
SameTag* retrieve_item_id_by_parser_from_current_location(const char* parser);
SameTag* retrieve_item_id_by_parser_from_inventory(const char* parser);
SameTag* retrieve_takeable_item_id_by_parser_from_current_location(const char* parser);
SameTag* retrieve_passage_item_id_by_parser_from_current_location(const char* parser);

#endif

