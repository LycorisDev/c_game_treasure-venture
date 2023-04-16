#ifndef START_H
#define START_H

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
    #include <windows.h>
    #endif
#endif

#include "game.h"

/* sleep(1);
Sleep for 1 second. This function requires unistd.h on Unix, and Windows.h on Windows. */

void access_main_menu(const int has_game_begun);
int execute_submenu_newgame(void);
int execute_submenu_loadgame(const int has_game_begun);
int execute_submenu_save(const int has_game_begun);
void execute_submenu_about(const int is_game_ongoing);

#endif

