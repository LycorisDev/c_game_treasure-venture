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
char* retrieve_default_character_tag_by_id(const int character_id);
int retrieve_character_id_by_parser(const char* parser);
int bool_parser_and_character_id_do_match(const char* parser, const int character_id);

#endif

