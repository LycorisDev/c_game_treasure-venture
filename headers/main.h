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
#include "game.h"
#ifndef CTYPE_LIBRARY
#define CTYPE_LIBRARY
#include <ctype.h>
#endif
#ifndef SLEEP_FUNCTION
#define SLEEP_FUNCTION
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#endif

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

#define MAX_NBR_WORDS    100
#define MAX_SIZE         (MAX_NBR_WORDS * 24)
#define DELIMETERS       "\n\t\"\\ .,/:?!^"

char *parser[MAX_NBR_WORDS];
int nbr_words_in_parser;

#endif

