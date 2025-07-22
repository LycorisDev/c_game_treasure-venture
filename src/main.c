#include "treasure_venture.h"

static void	set_utf8_encoding(void);

int	main(void)
{
	t_man	man;

	memset(&man, 0, sizeof(man));
	set_utf8_encoding();
	open_menu(&man);
	while (man.state)
	{
		man.tokens = get_input();
		if (man.state == STATE_MENU)
			run_menu_cmd(&man, man.tokens);
		else if (man.state == STATE_GAME)
			run_game_cmd(&man, man.tokens);
		free_arr((void **)man.tokens, free);
	}
	clear_window();
	return (0);
}

static void	set_utf8_encoding(void)
{
	#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	#endif
	return ;
}
