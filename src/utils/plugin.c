#include "plugin.h"

# ifdef _WIN32
const char	*win_dlerror(void)
{
	static char buf[512];
	DWORD err = GetLastError();
	FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, err, 0, buf, sizeof(buf), NULL);
	return buf;
}
#endif

void	run_plugin(const char *path, const char *name)
{
	LIB_HANDLE	lib_obj;
	int			(*lib_func)(int argc, char **argv);

	lib_obj = LOAD_LIB(path);
	if (!lib_obj)
	{
		fprintf(stderr, "\t[Error: The %s lib can't be loaded -> %s]\n\n",
			name, LIB_ERROR);
		return ;
	}
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wpedantic"
	#pragma GCC diagnostic ignored "-Wcast-function-type"
	lib_func = (int (*)(int, char **))LIB_FUNC(lib_obj, "start");
	#pragma GCC diagnostic pop
	if (!lib_func)
	{
		fprintf(stderr, "\t[Error: The pointer to the %s lib start function "
			"can't be obtained -> %s]\n\n", name, LIB_ERROR);
		UNLOAD_LIB(lib_obj);
		return ;
	}
	(*lib_func)(0, NULL);
	UNLOAD_LIB(lib_obj);
	return ;
}
