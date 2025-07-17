#include "characters.h"

void	populate_list_characters(void)
{
	memset(g_list_characters, 0, NBR_CHARACTERS * sizeof(t_character));

	PLAYER->id = ID_CHARACTER_PLAYER;
	memcpy(PLAYER->tags[0], "player", 6);
	memcpy(PLAYER->tags[1], "self", 4);
	memcpy(PLAYER->tags[2], "me", 2);
	memcpy(PLAYER->tags[3], "myself", 6);
	memcpy(PLAYER->description, "You're a quite handsome fellow.", 31);
	PLAYER->current_location = LOCATION_OUTSIDE;

	CHARACTER_LIBRARIAN->id = ID_CHARACTER_LIBRARIAN;
	memcpy(CHARACTER_LIBRARIAN->tags[0], "mansion librarian", 17);
	memcpy(CHARACTER_LIBRARIAN->tags[1], "librarian", 9);
	memcpy(CHARACTER_LIBRARIAN->description, "The librarian seems friendly.", 29);
	CHARACTER_LIBRARIAN->current_location = LOCATION_OLD_LIBRARY;
	return;
}
