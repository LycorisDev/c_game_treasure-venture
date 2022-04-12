#ifndef LEXICON_H
#define LEXICON_H

#ifndef STANDARD_LIBRARY_STRING
#define STANDARD_LIBRARY_STRING
#include <string.h>
#endif

void populate_list_lexicon(void);

#define NBR_WORDS 		100
#define LENGTH_WORD 	20

extern char list_lexicon[NBR_WORDS][LENGTH_WORD];

#define LEXICON_1              list_lexicon[0]
#define LEXICON_2              list_lexicon[1]
#define LEXICON_3              list_lexicon[2]
#define LEXICON_AROUND         list_lexicon[3]
#define LEXICON_BACK           list_lexicon[4]
#define LEXICON_BOOK           list_lexicon[5]
#define LEXICON_BOOKS          list_lexicon[6]
#define LEXICON_CHARACTER      list_lexicon[7]
#define LEXICON_CLOCK          list_lexicon[8]
#define LEXICON_DOOR           list_lexicon[9]
#define LEXICON_DOORS          list_lexicon[10]
#define LEXICON_DOUBLE         list_lexicon[11]
#define LEXICON_DROP           list_lexicon[12]
#define LEXICON_ENTRY          list_lexicon[13]
#define LEXICON_FIRST          list_lexicon[14]
#define LEXICON_GO             list_lexicon[15]
#define LEXICON_GRANDFATHER    list_lexicon[16]
#define LEXICON_HALLWAY        list_lexicon[17]
#define LEXICON_HOLD           list_lexicon[18]
#define LEXICON_INSIDE         list_lexicon[19]
#define LEXICON_INVENTORY      list_lexicon[20]
#define LEXICON_KEY            list_lexicon[21]
#define LEXICON_LIBRARIAN      list_lexicon[22]
#define LEXICON_LIBRARY        list_lexicon[23]
#define LEXICON_LOOK           list_lexicon[24]
#define LEXICON_MAIN           list_lexicon[25]
#define LEXICON_MANSION        list_lexicon[26]
#define LEXICON_ME             list_lexicon[27]
#define LEXICON_MYSELF         list_lexicon[28]
#define LEXICON_OLD            list_lexicon[29]
#define LEXICON_ON             list_lexicon[30]
#define LEXICON_OUT            list_lexicon[31]
#define LEXICON_OUTSIDE        list_lexicon[32]
#define LEXICON_PLAY           list_lexicon[33]
#define LEXICON_PLAYER         list_lexicon[34]
#define LEXICON_ROOM           list_lexicon[35]
#define LEXICON_SECOND         list_lexicon[36]
#define LEXICON_SIGN           list_lexicon[37]
#define LEXICON_SHINY          list_lexicon[38]
#define LEXICON_TAKE           list_lexicon[39]
#define LEXICON_THING          list_lexicon[40]
#define LEXICON_THIRD          list_lexicon[41]
#define LEXICON_USE            list_lexicon[42]

#endif

