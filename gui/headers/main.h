#ifndef MAIN_H
#define MAIN_H

#ifndef STANDARD_LIBRARY_CTYPE
#define STANDARD_LIBRARY_CTYPE
#include <ctype.h>
#endif

void add_output(const char* format, ...);
void reset_output(void);
void close_window(void);

#define MAX_NBR_WORDS    100
#define MAX_SIZE         (MAX_NBR_WORDS * 24)
#define DELIMETERS       "\n\t\"\\ .,/:?!^"

extern char *parser[MAX_NBR_WORDS];
extern int nbr_words_in_parser;

#endif

