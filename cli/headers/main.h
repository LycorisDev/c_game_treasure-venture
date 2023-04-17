#ifndef MAIN_H
#define MAIN_H

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
#ifndef STANDARD_LIBRARY_CTYPE
#define STANDARD_LIBRARY_CTYPE
#include <ctype.h>
#endif
#ifndef STANDARD_LIBRARY_UNISTD
#define STANDARD_LIBRARY_UNISTD
#include <unistd.h>
#endif
#ifndef STANDARD_LIBRARY_WINDOWS
#define STANDARD_LIBRARY_WINDOWS
    #ifdef _WIN32
    #include <Windows.h>
    #endif
#endif

#include "lexicon.h"
#include "game.h"

/* sleep(1);
Sleep for 1 second. This function requires unistd.h on Unix, and Windows.h on Windows. */

void clear_terminal(void);
void set_parser_with_input(void);
void flush_stdin(void);
void access_main_menu(const int has_game_begun);
int execute_submenu_newgame(void);
int execute_submenu_loadgame(const int has_game_begun);
int execute_submenu_save(const int has_game_begun);
void execute_submenu_about(const int is_game_ongoing);

#define BIG_LENGTH_WORD    (LENGTH_WORD * 3 + 2)
#define MAX_NBR_WORDS    100
#define MAX_SIZE         (MAX_NBR_WORDS * 24)
#define DELIMETERS       "\n\t\"\\ .,/:?!^"

extern char parser[MAX_NBR_WORDS][BIG_LENGTH_WORD];
extern int nbr_words_in_parser;

#endif

