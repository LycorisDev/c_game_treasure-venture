#include "../headers/lexicon.h"

/* Declared as extern in ../headers/lexicon.h */
char list_lexicon[NBR_WORDS][LENGTH_WORD];

void populate_list_lexicon(void)
{
    memcpy(LEXICON_1, "1", LENGTH_WORD);
    memcpy(LEXICON_2, "2", LENGTH_WORD);
    memcpy(LEXICON_3, "3", LENGTH_WORD);
    memcpy(LEXICON_AROUND, "around", LENGTH_WORD);
    memcpy(LEXICON_BOOK, "book", LENGTH_WORD);
    memcpy(LEXICON_BOOKS, "books", LENGTH_WORD);
    memcpy(LEXICON_CHARACTER, "character", LENGTH_WORD);
    memcpy(LEXICON_CLOCK, "clock", LENGTH_WORD);
    memcpy(LEXICON_DOOR, "door", LENGTH_WORD);
    memcpy(LEXICON_DOORS, "doors", LENGTH_WORD);
    memcpy(LEXICON_DROP, "drop", LENGTH_WORD);
    memcpy(LEXICON_ENTRY, "entry", LENGTH_WORD);
    memcpy(LEXICON_FIRST, "first", LENGTH_WORD);
    memcpy(LEXICON_GO, "go", LENGTH_WORD);
    memcpy(LEXICON_GRANDFATHER, "grandfather", LENGTH_WORD);
    memcpy(LEXICON_HALLWAY, "hallway", LENGTH_WORD);
    memcpy(LEXICON_HOLD, "hold", LENGTH_WORD);
    memcpy(LEXICON_INSIDE, "inside", LENGTH_WORD);
    memcpy(LEXICON_INVENTORY, "inventory", LENGTH_WORD);
    memcpy(LEXICON_KEY, "key", LENGTH_WORD);
    memcpy(LEXICON_LIBRARIAN, "librarian", LENGTH_WORD);
    memcpy(LEXICON_LIBRARY, "library", LENGTH_WORD);
    memcpy(LEXICON_LOOK, "look", LENGTH_WORD);
    memcpy(LEXICON_MAIN, "main", LENGTH_WORD);
    memcpy(LEXICON_OLD, "old", LENGTH_WORD);
    memcpy(LEXICON_ON, "on", LENGTH_WORD);
    memcpy(LEXICON_OUTSIDE, "outside", LENGTH_WORD);
    memcpy(LEXICON_PLAY, "play", LENGTH_WORD);
    memcpy(LEXICON_PLAYER, "player", LENGTH_WORD);
    memcpy(LEXICON_ROOM, "room", LENGTH_WORD);
    memcpy(LEXICON_SECOND, "second", LENGTH_WORD);
    memcpy(LEXICON_SIGN, "sign", LENGTH_WORD);
    memcpy(LEXICON_SHINY, "shiny", LENGTH_WORD);
    memcpy(LEXICON_TAKE, "take", LENGTH_WORD);
    memcpy(LEXICON_THING, "thing", LENGTH_WORD);
    memcpy(LEXICON_THIRD, "third", LENGTH_WORD);
    memcpy(LEXICON_USE, "use", LENGTH_WORD);
    return;
}

