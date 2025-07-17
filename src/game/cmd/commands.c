#include "treasure_venture.h"

static void	reset_command_elements(void);
static void	set_command_element(void *element, const int element_size,
				const int parser_start_index, const int parser_end_index);
static int	get_available_length_in_string(const int max_length,
				const char *str);
static void	run_action(const char *cmd);

void	run_game_command(void)
{
	int	i;
	int	command_word_length;
	int	verb_index;
	int	object_end_index;
	int	preposition_index;
	int	target_start_index;

	command_word_length = g_man.nbr_words_in_parser;
	verb_index = 0;
	object_end_index = -1;
	preposition_index = -1;
	target_start_index = -1;
	reset_command_elements();

	for (i = 0; i < g_man.nbr_words_in_parser; ++i)
	{
		if (!bool_word_is_in_lexicon(g_man.parser[i]))
		{
			printf("\t['%s' was not recognized.]\n\n", g_man.parser[i]);
			command_word_length = i;
			break;
		}

		if (preposition_index >= 0)
			continue;

		object_end_index = i;

		if (bool_word_is_preposition(g_man.parser[i]))
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

	set_command_element(g_man.cmd.verb, sizeof(g_man.cmd.verb), verb_index, verb_index);
	set_command_element(g_man.cmd.object, sizeof(g_man.cmd.object), verb_index + 1,
		object_end_index);
	set_command_element(g_man.cmd.preposition, sizeof(g_man.cmd.preposition),
		preposition_index, preposition_index);
	set_command_element(g_man.cmd.target, sizeof(g_man.cmd.target), target_start_index,
		command_word_length - 1);

	run_action(g_man.cmd.verb);
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
	memset(&g_man.cmd, 0, sizeof(g_man.cmd));
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

	memcpy(element, g_man.parser[i++], max_len);

	while (i <= parser_end_index)
	{
		strncat(element, " ", get_available_length_in_string(max_len, element));
		strncat(element, g_man.parser[i++],
			get_available_length_in_string(max_len, element));
	}
	return;
}

static int	get_available_length_in_string(const int max_length,
				const char *str)
{
	int	len_cat;

	len_cat = max_length - strlen(str);
	return len_cat < 0 ? 0 : len_cat;
}

static void	run_action(const char *cmd)
{
	static const KeyFunc	cmd_list[] = 
	{
		{0, &display_game_commands},
		{"drop", &run_drop},
		{"go", &run_go},
		{"inventory", &run_inventory},
		{"look", &run_look},
		{"play", &run_play},
		{"take", &run_take},
		{"use", &run_use}
	};
	int	i;

	if (!cmd || !*cmd)
	{
		cmd_list[0].func();
		return;
	}
	i = 1;
	while (cmd_list[i].key)
	{
		if (!strcmp(cmd, cmd_list[i].key))
		{
			cmd_list[i].func();
			return;
		}
		++i;
	}
	cmd_list[0].func();
	return;
}
