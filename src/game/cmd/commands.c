#include "commands.h"
#include "parser.h"

static void	reset_command_elements(void);
static void	set_command_element(void *element, const int element_size,
				const int parser_start_index, const int parser_end_index);
static void	execute_action(void);

static const KeyFunc	g_command_list[] = 
{
	{"drop", &execute_drop},
	{"go", &execute_go},
	{"inventory", &execute_inventory},
	{"look", &execute_look},
	{"play", &execute_play},
	{"take", &execute_take},
	{"use", &execute_use},
	{0, &display_game_commands}
};

void	execute_game_command(void)
{
	int	i;
	int	command_word_length;
	int	verb_index;
	int	object_end_index;
	int	preposition_index;
	int	target_start_index;

	command_word_length = g_nbr_words_in_parser;
	verb_index = 0;
	object_end_index = -1;
	preposition_index = -1;
	target_start_index = -1;
	reset_command_elements();

	for (i = 0; i < g_nbr_words_in_parser; ++i)
	{
		if (!bool_word_is_in_lexicon(g_parser[i]))
		{
			printf("\t['%s' was not recognized.]\n\n", g_parser[i]);
			command_word_length = i;
			break;
		}

		if (preposition_index >= 0)
			continue;

		object_end_index = i;

		if (bool_word_is_preposition(g_parser[i]))
		{
			object_end_index = i - 1;
			preposition_index = i;
			target_start_index = i + 1;
		}
	}

	if (!command_word_length)
	{
		display_game_commands();
		return;
	}

	set_command_element(g_cmd.verb, sizeof(g_cmd.verb), verb_index, verb_index);
	set_command_element(g_cmd.object, sizeof(g_cmd.object), verb_index + 1,
		object_end_index);
	set_command_element(g_cmd.preposition, sizeof(g_cmd.preposition),
		preposition_index, preposition_index);
	set_command_element(g_cmd.target, sizeof(g_cmd.target), target_start_index,
		command_word_length - 1);

	execute_action();
	return;
}

void	display_game_commands(void)
{
	printf("\t['Menu']    ['Inventory']    ['Look']    ['Take']\n");
	printf("\t['Play']       ['Use']        ['Go']     ['Drop']\n");
	printf("\n");
	return;
}

static void	reset_command_elements(void)
{
	memset(&g_cmd, 0, sizeof(g_cmd));
	return;
}

static void	set_command_element(void *element, const int element_size,
				const int parser_start_index, const int parser_end_index)
{
	int			i;
	const int	max_len = element_size - 1;

	i = parser_start_index;
	if (parser_start_index > parser_end_index || parser_start_index < 0
		|| parser_end_index < 0)
		return;

	memcpy(element, g_parser[i++], max_len);

	while (i <= parser_end_index)
	{
		strncat(element, " ", get_available_length_in_string(max_len, element));
		strncat(element, g_parser[i++], get_available_length_in_string(max_len,
			element));
	}
	return;
}

static void	execute_action(void)
{
	int	i;

	i = 0;
	while (g_command_list[i].key)
	{
		if (!strcmp(g_cmd.verb, g_command_list[i].key))
		{
			g_command_list[i].func();
			return;
		}
		++i;
	}

	g_command_list[i].func();
	return;
}
