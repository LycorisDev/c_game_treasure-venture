#include "treasure_venture.h"

void	initialize_game(t_man *man)
{
	populate_list_locs(man);
	populate_list_items(man);
	populate_list_charas(man);
	populate_list_events(man);
	return;
}
