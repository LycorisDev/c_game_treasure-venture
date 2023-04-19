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

#ifndef TERMINAL_UTF8_ENCODING
    #ifdef _WIN32
        #define TERMINAL_UTF8_ENCODING SetConsoleOutputCP(CP_UTF8);
    #else
        #define TERMINAL_UTF8_ENCODING
    #endif
#endif

#ifndef CLEAR_TERMINAL
    #ifdef _WIN32
	    #define CLEAR_TERMINAL system("cls");
    #elif defined(__ANDROID__)
	    #define CLEAR_TERMINAL system("clear");
    #else
	    #define CLEAR_TERMINAL write(STDOUT_FILENO, "\033c", 2);
    #endif
#endif

#define BIG_LENGTH_WORD    (LENGTH_WORD * 3 + 2)
#define MAX_NBR_WORDS    100
#define MAX_SIZE         (MAX_NBR_WORDS * 24)
#define DELIMETERS       "\n\t\"\\ .,/:?!^"

extern char parser[MAX_NBR_WORDS][BIG_LENGTH_WORD];
extern int nbr_words_in_parser;

typedef void (*yes_no_callback_t)(const int);
extern yes_no_callback_t yes_no_callback;

#endif

