#include "treasure_venture.h"

int	ask_yes_no(void)
{
	const char	**tokens;
	int			res;

	res = -1;
	while (res < 0)
	{
		tokens = get_input();
		if (!tokens)
			res = 0;
		else if (tokens[0] && !tokens[1])
		{
			if (!strcmp(tokens[0], "yes") || !strcmp(tokens[0], "y"))
				res = 1;
			else if (!strcmp(tokens[0], "no") || !strcmp(tokens[0], "n"))
				res = 0;
		}
		free_array((void **)tokens, free);
	}
	return (res);
}
