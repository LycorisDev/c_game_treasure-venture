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
void display_item_suggestions(Item** item_collection, const char* command);
Item** retrieve_items(Item** item_collection, const char* parser);
Item** retrieve_takeable_items(Item** item_collection, const char* parser);
int bool_item_matches_parser(const Item* item, const char* parser);

#endif

