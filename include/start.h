#ifndef START_H
# define START_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <fcntl.h>
# include "misc.h"

typedef enum e_game_state
{
	STATE_MENU,
	STATE_GAME
}	t_game_state;

void	interact(void);
void	access_main_menu(void);

#endif
