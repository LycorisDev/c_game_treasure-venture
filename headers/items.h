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
char* retrieve_default_item_tag_by_id(const int item_id);
int retrieve_item_id_by_parser(const char* parser);
int bool_parser_and_item_id_do_match(const char* parser, const int item_id);

#endif

