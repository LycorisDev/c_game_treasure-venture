#ifndef INPUT_H
#define INPUT_H

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

int input_yes_no(void);
void flush_stdin(void);

#define INPUT_SIZE    40

#endif

