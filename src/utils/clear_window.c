#include "treasure_venture.h"

void	clear_window(void)
{
	#ifdef _WIN32
	system("cls");
	#else
	write(STDOUT_FILENO, "\033c", 2);
	#endif
	return ;
}
