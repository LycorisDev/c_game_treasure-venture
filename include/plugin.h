#ifndef PLUGIN_H
# define PLUGIN_H

# include <stdio.h>
# ifdef _WIN32
#  include <windows.h>
#  define LIB_HANDLE HMODULE
#  define LOAD_LIB(file) LoadLibrary(file)
#  define LIB_FUNC(handle, function) GetProcAddress(handle, function)
#  define UNLOAD_LIB(handle) FreeLibrary(handle)
#  define LIB_ERROR strerror(errno)
# else
#  include <dlfcn.h>
#  define LIB_HANDLE void*
#  define LOAD_LIB(file) dlopen(file, RTLD_NOW)
#  define LIB_FUNC(handle, function) dlsym(handle, function)
#  define UNLOAD_LIB(handle) dlclose(handle)
#  define LIB_ERROR dlerror()
# endif

void	run_plugin(const char *path, const char *name);

#endif
