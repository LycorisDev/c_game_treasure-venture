#include "treasure_venture.h"

static void	display_game_commands(void);
static void	run_action(t_man *man, const char *action);
static void	free_cmd(t_cmd *cmd);

void	run_game_cmd(t_man *man, const char **tokens)
{
	int		i;
	int		i_preposition;
	char	*tmp;

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
	man->cmd.verb = strdup(tokens[0]);
	i = 0;
	while (tokens[++i])
	{
		if (!strcmp(tokens[i], "on"))
		{
			man->cmd.preposition = strdup(tokens[i]);
			break ;
		}
	}
	i_preposition = i;
	i = 0;
	while (tokens[++i] && i < i_preposition)
	{
		if (!man->cmd.object)
			man->cmd.object = strdup(tokens[i]);
		else
		{
			tmp = strjoin(man->cmd.object, " ");
			free(man->cmd.object);
			man->cmd.object = strjoin(tmp, tokens[i]);
			free(tmp);
		}
	}
	if (tokens[i])
	{
		while (tokens[++i])
		{
			if (!man->cmd.target)
				man->cmd.target = strdup(tokens[i]);
			else
			{
				tmp = strjoin(man->cmd.target, " ");
				free(man->cmd.target);
				man->cmd.target = strjoin(tmp, tokens[i]);
				free(tmp);
			}
		}
	}
	run_action(man, man->cmd.verb);
	free_cmd(&man->cmd);
	return;
}

static void	display_game_commands(void)
{
	printf("\t['Menu']    ['Inventory']    ['Look']    ['Take']\n");
	printf("\t['Play']       ['Use']        ['Go']     ['Drop']\n");
	printf("\n");
	return;
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

static void	free_cmd(t_cmd *cmd)
{
	free(cmd->verb);
	free(cmd->object);
	free(cmd->preposition);
	free(cmd->target);
	memset(cmd, 0, sizeof(t_cmd));
	return ;
}
