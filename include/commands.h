#ifndef COMMANDS_H
# define COMMANDS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "lexicon.h"
# include "misc.h"
# include "events.h"

# define BIG_LENGTH_WORD (LENGTH_WORD * 3 + 2)

typedef struct s_cmd
{
	char	verb[LENGTH_WORD];
	char	object[BIG_LENGTH_WORD];
	char	preposition[LENGTH_WORD];
	char	target[BIG_LENGTH_WORD];
}	t_cmd;

extern t_cmd	g_cmd;

void	execute_game_command(void);
void	display_game_commands(void);

void	execute_drop(void);
void	execute_go(void);
void	execute_inventory(void);
void	execute_look(void);
void	execute_play(void);
void	execute_take(void);
void	execute_use(void);

#endif
