#ifndef SAVE_H
# define SAVE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "misc.h"

# define SAVE_FILE "save.txt"

void	save_game(int fd_save);
int		load_saved_game(int fd_save);

#endif
