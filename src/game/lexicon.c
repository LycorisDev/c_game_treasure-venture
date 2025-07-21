#include "treasure_venture.h"

void	populate_list_lexicon(t_man *man)
{
	memset(man->lexicon, 0, NBR_WORDS * LENGTH_WORD * sizeof(char));

	memcpy(&man->lexicon[LEX_1 - 1], "1", 1);
	memcpy(&man->lexicon[LEX_2 - 1], "2", 1);
	memcpy(&man->lexicon[LEX_3 - 1], "3", 1);
	memcpy(&man->lexicon[LEX_AROUND - 1], "around", 6);
	memcpy(&man->lexicon[LEX_BACK - 1], "back", 4);
	memcpy(&man->lexicon[LEX_BOOK - 1], "book", 4);
	memcpy(&man->lexicon[LEX_BOOKS - 1], "books", 5);
	memcpy(&man->lexicon[LEX_CLOCK - 1], "clock", 5);
	memcpy(&man->lexicon[LEX_DOOR - 1], "door", 4);
	memcpy(&man->lexicon[LEX_DOORS - 1], "doors", 5);
	memcpy(&man->lexicon[LEX_DOUBLE - 1], "double", 6);
	memcpy(&man->lexicon[LEX_DROP - 1], "drop", 4);
	memcpy(&man->lexicon[LEX_ENTRY - 1], "entry", 5);
	memcpy(&man->lexicon[LEX_FIRST - 1], "first", 5);
	memcpy(&man->lexicon[LEX_GO - 1], "go", 2);
	memcpy(&man->lexicon[LEX_GRANDFATHER - 1], "grandfather", 11);
	memcpy(&man->lexicon[LEX_HALLWAY - 1], "hallway", 7);
	memcpy(&man->lexicon[LEX_INSIDE - 1], "inside", 6);
	memcpy(&man->lexicon[LEX_INVENTORY - 1], "inventory", 9);
	memcpy(&man->lexicon[LEX_KEY - 1], "key", 3);
	memcpy(&man->lexicon[LEX_LIBRARIAN - 1], "librarian", 9);
	memcpy(&man->lexicon[LEX_LIBRARY - 1], "library", 7);
	memcpy(&man->lexicon[LEX_LOOK - 1], "look", 4);
	memcpy(&man->lexicon[LEX_MAIN - 1], "main", 4);
	memcpy(&man->lexicon[LEX_MANSION - 1], "mansion", 7);
	memcpy(&man->lexicon[LEX_ME - 1], "me", 2);
	memcpy(&man->lexicon[LEX_MYSELF - 1], "myself", 6);
	memcpy(&man->lexicon[LEX_OLD - 1], "old", 3);
	memcpy(&man->lexicon[LEX_ON - 1], "on", 2);
	memcpy(&man->lexicon[LEX_OUT - 1], "out", 3);
	memcpy(&man->lexicon[LEX_OUTSIDE - 1], "outside", 7);
	memcpy(&man->lexicon[LEX_PLAY - 1], "play", 4);
	memcpy(&man->lexicon[LEX_PLAYER - 1], "player", 6);
	memcpy(&man->lexicon[LEX_ROOM - 1], "room", 4);
	memcpy(&man->lexicon[LEX_SECOND - 1], "second", 6);
	memcpy(&man->lexicon[LEX_SELF - 1], "self", 4);
	memcpy(&man->lexicon[LEX_SIGN - 1], "sign", 4);
	memcpy(&man->lexicon[LEX_SHINY - 1], "shiny", 5);
	memcpy(&man->lexicon[LEX_TAKE - 1], "take", 4);
	memcpy(&man->lexicon[LEX_THING - 1], "thing", 5);
	memcpy(&man->lexicon[LEX_THIRD - 1], "third", 5);
	memcpy(&man->lexicon[LEX_USE - 1], "use", 3);
	memcpy(&man->lexicon[LEX_WORLD - 1], "world", 5);
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
