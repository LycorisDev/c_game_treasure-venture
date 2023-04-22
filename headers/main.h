#ifndef MAIN_H
#define MAIN_H

#ifdef CLI
    #ifndef STANDARD_LIBRARY_STDIO
    #define STANDARD_LIBRARY_STDIO
    #include <stdio.h>
    #endif
    #ifndef STANDARD_LIBRARY_STDLIB
    #define STANDARD_LIBRARY_STDLIB
    #include <stdlib.h>
    #endif
    #ifndef STANDARD_LIBRARY_UNISTD
    #define STANDARD_LIBRARY_UNISTD
    #include <unistd.h>
    #endif
    #ifndef STANDARD_LIBRARY_WINDOWS
    #define STANDARD_LIBRARY_WINDOWS
        #ifdef _WIN32
        #include <windows.h>
        #endif
    #endif
#endif

#ifndef STANDARD_LIBRARY_STDARG
#define STANDARD_LIBRARY_STDARG
#include <stdarg.h>
#endif

void add_output(const char* format, ...);
void reset_output(void);
void close_window(void);

#endif

