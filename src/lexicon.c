#include "lexicon.h"

/* Declared as extern in lexicon.h */
char	g_list_lexicon[NBR_WORDS][LENGTH_WORD];

void	populate_list_lexicon(void)
{
	memset(g_list_lexicon, 0, NBR_WORDS * LENGTH_WORD * sizeof(char));

	memcpy(LEXICON_1, "1", 1);
	memcpy(LEXICON_2, "2", 1);
	memcpy(LEXICON_3, "3", 1);
	memcpy(LEXICON_AROUND, "around", 6);
	memcpy(LEXICON_BACK, "back", 4);
	memcpy(LEXICON_BOOK, "book", 4);
	memcpy(LEXICON_BOOKS, "books", 5);
	memcpy(LEXICON_CLOCK, "clock", 5);
	memcpy(LEXICON_DOOR, "door", 4);
	memcpy(LEXICON_DOORS, "doors", 5);
	memcpy(LEXICON_DOUBLE, "double", 6);
	memcpy(LEXICON_DROP, "drop", 4);
	memcpy(LEXICON_ENTRY, "entry", 5);
	memcpy(LEXICON_FIRST, "first", 5);
	memcpy(LEXICON_GO, "go", 2);
	memcpy(LEXICON_GRANDFATHER, "grandfather", 11);
	memcpy(LEXICON_HALLWAY, "hallway", 7);
	memcpy(LEXICON_INSIDE, "inside", 6);
	memcpy(LEXICON_INVENTORY, "inventory", 9);
	memcpy(LEXICON_KEY, "key", 3);
	memcpy(LEXICON_LIBRARIAN, "librarian", 9);
	memcpy(LEXICON_LIBRARY, "library", 7);
	memcpy(LEXICON_LOOK, "look", 4);
	memcpy(LEXICON_MAIN, "main", 4);
	memcpy(LEXICON_MANSION, "mansion", 7);
	memcpy(LEXICON_ME, "me", 2);
	memcpy(LEXICON_MYSELF, "myself", 6);
	memcpy(LEXICON_OLD, "old", 3);
	memcpy(LEXICON_ON, "on", 2);
	memcpy(LEXICON_OUT, "out", 3);
	memcpy(LEXICON_OUTSIDE, "outside", 7);
	memcpy(LEXICON_PLAY, "play", 4);
	memcpy(LEXICON_PLAYER, "player", 6);
	memcpy(LEXICON_ROOM, "room", 4);
	memcpy(LEXICON_SECOND, "second", 6);
	memcpy(LEXICON_SELF, "self", 4);
	memcpy(LEXICON_SIGN, "sign", 4);
	memcpy(LEXICON_SHINY, "shiny", 5);
	memcpy(LEXICON_TAKE, "take", 4);
	memcpy(LEXICON_THING, "thing", 5);
	memcpy(LEXICON_THIRD, "third", 5);
	memcpy(LEXICON_USE, "use", 3);
	memcpy(LEXICON_WORLD, "world", 5);
	return;
}

int	bool_word_is_in_lexicon(const char *word)
{
	int	i;

	for (i = 0; i < NBR_WORDS; ++i)
	{
		if (!g_list_lexicon[i][0])
			return 0;

		if (!strcmp(word, g_list_lexicon[i]))
			return 1;
	}
	return 0;
}

int	bool_word_is_preposition(const char *word)
{
	return !strcmp(word, "on");
}
