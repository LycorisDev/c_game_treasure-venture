#include "plugin.h"

void	run_plugin(const char *path, const char *name)
{
	LIB_HANDLE	lib_obj;
	int			(*lib_func)();

	lib_obj = LOAD_LIB(path);
	if (!lib_obj)
	{
		fprintf(stderr, "\t[Error: The %s lib can't be loaded -> %s]\n",
			name, LIB_ERROR);
		return ;
	}
	// TODO: Change "start_twenty_squares" into "start"
	// TODO: Test the win64 version as well
	*(void **)(&lib_func) = LIB_FUNC(lib_obj, "start_twenty_squares");
	if (!lib_func)
	{
		fprintf(stderr, "\t[Error: The pointer to the %s lib start function "
			"can't be obtained -> %s]\n", name, LIB_ERROR);
		UNLOAD_LIB(lib_obj);
		return ;
	}
	(*lib_func)();
	UNLOAD_LIB(lib_obj);
	return ;
}
