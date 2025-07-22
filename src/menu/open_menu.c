#include "treasure_venture.h"

void	open_menu(t_man *man)
{
	man->state = STATE_MENU;
	clear_window();
	printf("\t-[ TREASURE VENTURE ]-\n\n");
	printf("\t[During the game, type 'Menu' to go back to the main menu.]\n\n");
	printf("\t 'New Game'    'Load Game'    'Save'    'About'    'Quit'\n\n");
	return ;
}
