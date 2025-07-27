#include "treasure_venture.h"

void	populate_list_lexicon(t_man *man)
{
	memset(man->lexicon, 0, NBR_WORDS * LENGTH_WORD * sizeof(char));
	memcpy(&man->lexicon[LEX_1], "1", 1);
	memcpy(&man->lexicon[LEX_2], "2", 1);
	memcpy(&man->lexicon[LEX_3], "3", 1);
	memcpy(&man->lexicon[LEX_AROUND], "around", 6);
	memcpy(&man->lexicon[LEX_BACK], "back", 4);
	memcpy(&man->lexicon[LEX_BOOK], "book", 4);
	memcpy(&man->lexicon[LEX_BOOKS], "books", 5);
	memcpy(&man->lexicon[LEX_CLOCK], "clock", 5);
	memcpy(&man->lexicon[LEX_DOOR], "door", 4);
	memcpy(&man->lexicon[LEX_DOORS], "doors", 5);
	memcpy(&man->lexicon[LEX_DOUBLE], "double", 6);
	memcpy(&man->lexicon[LEX_DROP], "drop", 4);
	memcpy(&man->lexicon[LEX_ENTRY], "entry", 5);
	memcpy(&man->lexicon[LEX_FIRST], "first", 5);
	memcpy(&man->lexicon[LEX_GO], "go", 2);
	memcpy(&man->lexicon[LEX_GRANDFATHER], "grandfather", 11);
	memcpy(&man->lexicon[LEX_HALLWAY], "hallway", 7);
	memcpy(&man->lexicon[LEX_INSIDE], "inside", 6);
	memcpy(&man->lexicon[LEX_INVENTORY], "inventory", 9);
	memcpy(&man->lexicon[LEX_KEY], "key", 3);
	memcpy(&man->lexicon[LEX_LIBRARIAN], "librarian", 9);
	memcpy(&man->lexicon[LEX_LIBRARY], "library", 7);
	memcpy(&man->lexicon[LEX_LOOK], "look", 4);
	memcpy(&man->lexicon[LEX_MAIN], "main", 4);
	memcpy(&man->lexicon[LEX_MANSION], "mansion", 7);
	memcpy(&man->lexicon[LEX_ME], "me", 2);
	memcpy(&man->lexicon[LEX_MYSELF], "myself", 6);
	memcpy(&man->lexicon[LEX_OLD], "old", 3);
	memcpy(&man->lexicon[LEX_ON], "on", 2);
	memcpy(&man->lexicon[LEX_OUT], "out", 3);
	memcpy(&man->lexicon[LEX_OUTSIDE], "outside", 7);
	memcpy(&man->lexicon[LEX_PLAY], "play", 4);
	memcpy(&man->lexicon[LEX_PLAYER], "player", 6);
	memcpy(&man->lexicon[LEX_ROOM], "room", 4);
	memcpy(&man->lexicon[LEX_SECOND], "second", 6);
	memcpy(&man->lexicon[LEX_SELF], "self", 4);
	memcpy(&man->lexicon[LEX_SIGN], "sign", 4);
	memcpy(&man->lexicon[LEX_SHINY], "shiny", 5);
	memcpy(&man->lexicon[LEX_TAKE], "take", 4);
	memcpy(&man->lexicon[LEX_THING], "thing", 5);
	memcpy(&man->lexicon[LEX_THIRD], "third", 5);
	memcpy(&man->lexicon[LEX_USE], "use", 3);
	memcpy(&man->lexicon[LEX_WORLD], "world", 5);
	return;
}

int	bool_word_is_in_lexicon(t_man *man, const char *word)
{
	int	i;

	for (i = 0; i < NBR_WORDS; ++i)
	{
		if (!man->lexicon[i][0])
			return 0;

		if (!strcmp(word, man->lexicon[i]))
			return 1;
	}
	return 0;
}

int	bool_word_is_preposition(const char *word)
{
	return !strcmp(word, "on");
}
