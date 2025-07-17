#include "initialize.h"
#include "lexicon.h"
#include "locations.h"
#include "items.h"
#include "characters.h"
#include "events.h"

void	initialize_game(void)
{
	populate_list_lexicon();
	populate_list_locations();
	populate_list_items();
	populate_list_characters();
	populate_list_events();
	return;
}
