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
#ifndef STANDARD_LIBRARY_WINDOWS
#define STANDARD_LIBRARY_WINDOWS
    #ifdef _WIN32
    #include <windows.h>
    #endif
#endif

int input_yes_no(void);
void flush_stdin(void);

#define INPUT_SIZE    40

#endif

