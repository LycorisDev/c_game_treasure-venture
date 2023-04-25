#ifndef PARSER_H
#define PARSER_H

#ifndef STANDARD_LIBRARY_STDIO
#define STANDARD_LIBRARY_STDIO
#include <stdio.h>
#endif
#ifndef STANDARD_LIBRARY_STRING
#define STANDARD_LIBRARY_STRING
#include <string.h>
#endif
#ifndef STANDARD_LIBRARY_CTYPE
#define STANDARD_LIBRARY_CTYPE
#include <ctype.h>
#endif

/* For the LENGTH_WORD macro */
#include "lexicon.h"

#define INPUT_MAX_LENGTH        160
#define INPUT_TOKEN_DELIMETERS  "\n\t\"\\ .,/:?!^"
#define PARSER_NBR_WORDS        24

extern char parser[PARSER_NBR_WORDS][LENGTH_WORD];
extern int nbr_words_in_parser;

typedef void (*yes_no_callback_t)(const int);
extern yes_no_callback_t yes_no_callback;

void parse_input(const char* raw_input);
#ifndef GUI
void get_and_parse_cli_input(void);
#endif
void parse_yes_no(void);
int get_available_length_in_string(const int max_length, const char* str);

#endif

