#include "treasure_venture.h"

void	initialize_game(t_man *man)
{
	populate_list_lexicon(man);
	populate_list_locations(man);
	populate_list_items(man);
	populate_list_characters(man);
	populate_list_events(man);
	return;
}
