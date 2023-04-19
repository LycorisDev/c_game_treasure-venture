#ifndef PLAY_H
#define PLAY_H

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

#ifndef PLUGIN_HANDLER
#define PLUGIN_HANDLER
    #ifdef _WIN32 /* Defined for both 64 and 32-bit */
        #ifndef STANDARD_LIBRARY_WINDOWS
        #define STANDARD_LIBRARY_WINDOWS
        #include <windows.h>
        #endif

        #define LIB_HANDLE HMODULE
        #define LOAD_LIB(file) LoadLibrary(file)
        #define LIB_FUNC(handle, function) GetProcAddress(handle, function)
        #define UNLOAD_LIB(handle) FreeLibrary(handle)
        #define LIB_ERROR strerror(errno)

        #ifdef _WIN64
        #define LIB_PATH_TWENTY_SQUARES "../../plugins/twenty-squares/libts64.dll"
        #else
        #define LIB_PATH_TWENTY_SQUARES "../../plugins/twenty-squares/libts32.dll"
        #endif
    #else
        #ifndef STANDARD_LIBRARY_DLFCN
        #define STANDARD_LIBRARY_DLFCN
        #include <dlfcn.h>
        #endif

        #define LIB_HANDLE void*
        #define LOAD_LIB(file) dlopen(file, RTLD_NOW)
        #define LIB_FUNC(handle, function) dlsym(handle, function)
        #define UNLOAD_LIB(handle) dlclose(handle)
        #define LIB_ERROR dlerror()

        #define LIB_PATH_TWENTY_SQUARES "plugins/twenty-squares/libts.so"
    #endif
#endif

#include "game.h"

void execute_play(void);

/* Mini-game */
int start_twenty_squares(void);

#endif

