#include "treasure_venture.h"

#define FS '\x1C'

static void	set_str_to_lowercase(char *s);

const char	**get_input(void)
{
	size_t		i;
	char		*line;
	const char	**tokens;

	write(STDOUT_FILENO, "> ", 2);
	line = gnl(STDIN_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	if (!line)
		return 0;
	set_str_to_lowercase(line);
	i = 0;
	while (line[i])
	{
		if (isspace(line[i]))
			line[i] = FS;
		++i;
	}
	tokens = (const char **)split(line, FS);
	free(line);
	if (tokens && !tokens[0])
	{
		free(tokens);
		tokens = 0;
	}
	return tokens;
}

void	free_array(void **arr, void (*free_fct)(void *))
{
	size_t	i;

	if (!arr)
		return;
	if (free_fct)
	{
		i = 0;
		while (arr[i])
		{
			free_fct(arr[i]);
			++i;
		}
	}
	free(arr);
	return;
}

static void	set_str_to_lowercase(char *s)
{
	size_t	i;

	if (!s)
		return;
	i = 0;
	while (s[i])
	{
		s[i] = tolower(s[i]);
		++i;
	}
	return;
}
