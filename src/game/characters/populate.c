#include "treasure_venture.h"

void	populate_list_characters(t_man *man)
{
	memset(man->characters, 0, NBR_CHARACTERS * sizeof(t_character));

	man->characters[CHAR_PLAYER - 1].id = CHAR_PLAYER;
	memcpy(man->characters[CHAR_PLAYER - 1].tags[0], "player", 6);
	memcpy(man->characters[CHAR_PLAYER - 1].tags[1], "self", 4);
	memcpy(man->characters[CHAR_PLAYER - 1].tags[2], "me", 2);
	memcpy(man->characters[CHAR_PLAYER - 1].tags[3], "myself", 6);
	memcpy(man->characters[CHAR_PLAYER - 1].description, "You're a quite handsome fellow.", 31);
	man->characters[CHAR_PLAYER - 1].current_location = &man->locations[LOC_OUTSIDE - 1];

	man->characters[CHAR_LIBRARIAN - 1].id = CHAR_LIBRARIAN;
	memcpy(man->characters[CHAR_LIBRARIAN - 1].tags[0], "mansion librarian", 17);
	memcpy(man->characters[CHAR_LIBRARIAN - 1].tags[1], "librarian", 9);
	memcpy(man->characters[CHAR_LIBRARIAN - 1].description, "The librarian seems friendly.", 29);
	man->characters[CHAR_LIBRARIAN - 1].current_location = &man->locations[LOC_OLD_LIBRARY - 1];
	return;
}
