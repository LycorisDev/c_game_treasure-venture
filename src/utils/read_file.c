#include "treasure_venture.h"

static char	*strjoin(char const *s1, char const *s2);
static char	*get_whole_file(int fd);
static char	*add_separator(char *line);
static void	remove_comments(char **lines);

char	**read_file(const char *filepath)
{
	int		fd;
	char	*whole;
	char	**lines;

	if (!filepath)
	{
		fprintf(stderr, "Error: No file path specified for reading\n");
		return (0);
	}
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Error: Couldn't open file \"%s\" for reading\n",
			filepath);
		return (0);
	}
	whole = get_whole_file(fd);
	close(fd);
	lines = split(whole, '\x1C');
	free(whole);
	remove_comments(lines);
	return (lines);
}

static char	*strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*joined;

	if (!s1 || !s2)
		return (0);
	len1 = strlen(s1);
	len2 = strlen(s2);
	joined = malloc((len1 + len2 + 1) * sizeof(char));
	if (!joined)
		return (0);
	strcpy(joined, s1);
	strcpy(joined + len1, s2);
	return (joined);
}

static char	*get_whole_file(int fd)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp1 = add_separator(gnl(fd));
	tmp2 = gnl(fd);
	while (tmp2)
	{
		tmp3 = strjoin(tmp1, tmp2);
		free(tmp1);
		free(tmp2);
		tmp1 = add_separator(tmp3);
		tmp2 = gnl(fd);
	}
	return (tmp1);
}

static char	*add_separator(char *line)
{
	size_t	len;
	char	*slash;
	char	*tmp;

	slash = 0;
	if (line)
	{
		len = strlen(line);
		if (!len)
			return (0);
		if (line[len - 1] == '\\')
			slash = line + (len - 1);
		else if (line[len - 2] == '\\')
			slash = line + (len - 2);
		if (slash)
			*slash = 0;
	}
	if (!slash)
	{
		tmp = strjoin(line, "\x1C");
		free(line);
		return (tmp);
	}
	return (line);
}

static void	remove_comments(char **lines)
{
	int		i;
	char	*comment;

	if (!lines)
		return ;
	i = 0;
	while (lines[i])
	{
		comment = strchr(lines[i], '#');
		if (comment)
			*comment = 0;
		if (comment == lines[i])
			remove_arr_elems((void **)lines, i, i, free);
		else
			++i;
	}
	return ;
}
