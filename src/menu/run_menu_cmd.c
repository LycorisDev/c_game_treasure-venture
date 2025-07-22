#include "treasure_venture.h"

static void	(*select_submenu(const char **tokens))(t_man *man);

void	run_menu_cmd(t_man *man, const char **tokens)
{
	void	(*submenu)(t_man *man);

	submenu = select_submenu(tokens);
	submenu(man);
	return ;
}

static void	(*select_submenu(const char **tokens))(t_man *man)
{
	size_t	count;

	count = count_arr((void **)tokens);
	if (!count)
		return (open_menu);
	else if (!strcmp(tokens[0], "new"))
	{
		if (count == 1 || (count == 2 && !strcmp(tokens[1], "game")))
			return (run_submenu_new);
	}
	else if (!strcmp(tokens[0], "load"))
	{
		if (count == 1 || (count == 2 && !strcmp(tokens[1], "game")))
			return (run_submenu_load);
	}
	else if (count == 1)
	{
		if (!strcmp(tokens[0], "save"))
			return (run_submenu_save);
		else if (!strcmp(tokens[0], "about"))
			return (run_submenu_about);
		else if (!strcmp(tokens[0], "quit"))
			return (run_submenu_quit);
	}
	return (open_menu);
}
