#include "treasure_venture.h"

void	populate_list_charas(t_man *man)
{
	memset(man->charas, 0, NBR_CHARAS * sizeof(t_char));

	man->charas[0].id = 0;
	strncpy(man->charas[0].tags[0], "player", LEN_TAG);
	strncpy(man->charas[0].tags[1], "self", LEN_TAG);
	strncpy(man->charas[0].tags[2], "me", LEN_TAG);
	strncpy(man->charas[0].tags[3], "myself", LEN_TAG);
	strncpy(man->charas[0].desc, "You're a quite handsome fellow.", LEN_DESC);
	man->charas[0].current_loc = &man->locs[LOC_OUTSIDE - 1];

	man->charas[1].id = 1;
	strncpy(man->charas[1].tags[0], "mansion librarian", LEN_TAG);
	strncpy(man->charas[1].tags[1], "librarian", LEN_TAG);
	strncpy(man->charas[1].desc, "The librarian seems friendly.", LEN_DESC);
	man->charas[1].current_loc = &man->locs[LOC_OLD_LIBRARY - 1];
	return;
}
