#ifndef PARSER_H
#define PARSER_H

#ifndef STANDARD_LIBRARY_STRING
#define STANDARD_LIBRARY_STRING
#include <string.h>
#endif
#ifndef STANDARD_LIBRARY_CTYPE
#define STANDARD_LIBRARY_CTYPE
#include <ctype.h>
#endif

#include "lexicon.h"
#define BIG_LENGTH_WORD    (LENGTH_WORD * 3 + 2)

#define MAX_NBR_WORDS    100
#define MAX_SIZE         (MAX_NBR_WORDS * 24)
#define DELIMETERS       "\n\t\"\\ .,/:?!^"

extern char parser[MAX_NBR_WORDS][BIG_LENGTH_WORD];
extern int nbr_words_in_parser;

typedef void (*yes_no_callback_t)(const int);
extern yes_no_callback_t yes_no_callback;

void parse_input(const char* raw_input);
void parse_yes_no(void);

#endif

