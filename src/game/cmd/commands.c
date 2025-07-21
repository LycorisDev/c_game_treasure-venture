#include "treasure_venture.h"

static void	set_command_element(const char **tokens, void *element,
				const int element_size, const int parser_start_index,
				const int parser_end_index);
static int	get_available_length_in_string(const int max_length,
				const char *str);
static void	run_action(t_man *man, const char *action);

void	run_game_cmd(t_man *man, const char **tokens)
{
	int	i;
	int	command_word_length;
	int	verb_index;
	int	object_end_index;
	int	preposition_index;
	int	target_start_index;

	verb_index = 0;
	object_end_index = -1;
	preposition_index = -1;
	target_start_index = -1;
	memset(&man->cmd, 0, sizeof(man->cmd));

	if (!tokens || !tokens[0])
	{
		display_game_commands();
		return;
	}
	else if (!strcmp(tokens[0], "menu")) // e.g. "menu save"
	{
		run_menu_cmd(man, tokens + 1);
		return;
	}

	for (i = 0; tokens[i]; ++i)
	{
		if (!bool_word_is_in_lexicon(man, tokens[i]))
		{
			printf("\t['%s' was not recognized.]\n\n", tokens[i]);
			break;
		}

		if (preposition_index >= 0)
			continue;

		object_end_index = i;

		if (bool_word_is_preposition(tokens[i]))
		{
			object_end_index = i - 1;
			preposition_index = i;
			target_start_index = i + 1;
		}
	}

	command_word_length = i;
	if (!command_word_length)
	{
		display_game_commands();
		return;
	}

	set_command_element(tokens, man->cmd.verb, sizeof(man->cmd.verb), verb_index, verb_index);
	set_command_element(tokens, man->cmd.object, sizeof(man->cmd.object), verb_index + 1,
		object_end_index);
	set_command_element(tokens, man->cmd.preposition, sizeof(man->cmd.preposition),
		preposition_index, preposition_index);
	set_command_element(tokens, man->cmd.target, sizeof(man->cmd.target), target_start_index,
		command_word_length - 1);

	run_action(man, man->cmd.verb);
	return;
}

void	display_game_commands(void)
{
	printf("\t['Menu']    ['Inventory']    ['Look']    ['Take']\n");
	printf("\t['Play']       ['Use']        ['Go']     ['Drop']\n");
	printf("\n");
	return;
}

static void	set_command_element(const char **tokens, void *element,
				const int element_size, const int parser_start_index,
				const int parser_end_index)
{
	int			i;
	const int	max_len = element_size - 1;

	i = parser_start_index;
	if (parser_start_index > parser_end_index || parser_start_index < 0
		|| parser_end_index < 0)
		return;

	memcpy(element, tokens[i++], max_len);

	while (i <= parser_end_index)
	{
		strncat(element, " ", get_available_length_in_string(max_len, element));
		strncat(element, tokens[i++],
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

static void	run_action(t_man *man, const char *action)
{
	if (!action)
		display_game_commands();
	else if (!strcmp(action, "drop"))
		run_drop(man);
	else if (!strcmp(action, "go"))
		run_go(man);
	else if (!strcmp(action, "inventory"))
		run_inventory(man);
	else if (!strcmp(action, "look"))
		run_look(man);
	else if (!strcmp(action, "play"))
		run_play(man);
	else if (!strcmp(action, "take"))
		run_take(man);
	else if (!strcmp(action, "use"))
		run_use(man);
	else
		display_game_commands();
	return;
}
