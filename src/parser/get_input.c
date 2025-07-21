#include "treasure_venture.h"

#define FS '\x1C'

static void	set_to_lowercase(char *s);
static void	set_whitespaces_to_fs(char *s);

const char	**get_input(void)
{
	char		*line;
	const char	**tokens;

	write(STDOUT_FILENO, "> ", 2);
	line = gnl(STDIN_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	if (!line)
		return 0;
	set_to_lowercase(line);
	set_whitespaces_to_fs(line);
	tokens = (const char **)split(line, FS);
	free(line);
	return tokens;
}

static void	set_to_lowercase(char *s)
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

static void	set_whitespaces_to_fs(char *s)
{
	size_t	i;

	if (!s)
		return;
	i = 0;
	while (s[i])
	{
		if (isspace(s[i]))
			s[i] = FS;
		++i;
	}
	return;
}
