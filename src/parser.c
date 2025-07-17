#include "treasure_venture.h"

static void	parse_input(const char *raw_input);
static void	reset_parser(void);
static void	str_to_lowercase(char dest[], const char *src);
static void	fill_parser(char input[]);

void	get_and_parse_input(void)
{
	char	input[INPUT_MAX_LENGTH] = {0};

	reset_parser();
	write(STDOUT_FILENO, "> ", 2);
	if (read(STDIN_FILENO, input, INPUT_MAX_LENGTH) != -1)
	{
		if (input[0] == '\n')
			return;
		parse_input(input);
	}
	write(STDOUT_FILENO, "\n", 1);
	return;
}

static void	parse_input(const char *raw_input)
{
	char	input[INPUT_MAX_LENGTH] = {0};

	reset_parser();

	if (!strlen(raw_input))
		return;

	str_to_lowercase(input, raw_input);
	fill_parser(input);
	return;
}

static void	reset_parser(void)
{
	memset(g_man.parser, 0, sizeof(g_man.parser));
	g_man.nbr_words_in_parser = 0;
	return;
}

static void	str_to_lowercase(char dest[], const char* src)
{
	int	i;

	for (i = 0; i < INPUT_MAX_LENGTH; ++i)
	{
		if (src[i] == '\0')
			break;
		dest[i] = tolower(src[i]);
	}
	return;
}

static void	fill_parser(char input[])
{
	char	*token;

	token = strtok(input, INPUT_TOKEN_DELIMETERS);
	while (token)
	{
		strcpy(g_man.parser[g_man.nbr_words_in_parser++], token);
		token = strtok(0, INPUT_TOKEN_DELIMETERS);
	}
	return;
}
