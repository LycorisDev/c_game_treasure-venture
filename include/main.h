#ifndef MAIN_H
# define MAIN_H

# ifdef CLI
#  include <stdio.h>
#  include <stdlib.h>
#  include <unistd.h>
#  ifdef _WIN32
#   include <windows.h>
#  endif
# endif
# include <stdarg.h>

void	add_output(const char *format, ...);
void	reset_output(void);
void	close_window(void);

#endif
