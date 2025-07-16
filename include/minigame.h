#ifndef MINIGAME_H
# define MINIGAME_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# ifdef _WIN32
#  include <windows.h>
# endif
/*
# ifdef _WIN32
#  include <windows.h>

#  define LIB_HANDLE HMODULE
#  define LOAD_LIB(file) LoadLibrary(file)
#  define LIB_FUNC(handle, function) GetProcAddress(handle, function)
#  define UNLOAD_LIB(handle) FreeLibrary(handle)
#  define LIB_ERROR strerror(errno)

#  ifdef _WIN64
#   define LIB_PATH_20SQ "../../plugins/twenty-squares/libts64.dll"
#  else
#   define LIB_PATH_20SQ "../../plugins/twenty-squares/libts32.dll"
#  endif
# else
#  include <dlfcn.h>

#  define LIB_HANDLE void*
#  define LOAD_LIB(file) dlopen(file, RTLD_NOW)
#  define LIB_FUNC(handle, function) dlsym(handle, function)
#  define UNLOAD_LIB(handle) dlclose(handle)
#  define LIB_ERROR dlerror()

#  define LIB_PATH_20SQ "plugins/twenty-squares/libts.so"
# endif
*/
# include "misc.h"

int	start_twenty_squares(void);

#endif
