#ifndef LEXICON_H
# define LEXICON_H

# include <string.h>

void	populate_list_lexicon(void);
int		bool_word_is_in_lexicon(const char *word);
int		bool_word_is_preposition(const char *word);

# define NBR_WORDS   100
# define LENGTH_WORD 20

extern char	g_list_lexicon[NBR_WORDS][LENGTH_WORD];

# define LEXICON_1				g_list_lexicon[0]
# define LEXICON_2				g_list_lexicon[1]
# define LEXICON_3				g_list_lexicon[2]
# define LEXICON_AROUND			g_list_lexicon[3]
# define LEXICON_BACK			g_list_lexicon[4]
# define LEXICON_BOOK			g_list_lexicon[5]
# define LEXICON_BOOKS			g_list_lexicon[6]
# define LEXICON_CLOCK			g_list_lexicon[7]
# define LEXICON_DOOR			g_list_lexicon[8]
# define LEXICON_DOORS			g_list_lexicon[9]
# define LEXICON_DOUBLE			g_list_lexicon[10]
# define LEXICON_DROP			g_list_lexicon[11]
# define LEXICON_ENTRY			g_list_lexicon[12]
# define LEXICON_FIRST			g_list_lexicon[13]
# define LEXICON_GO				g_list_lexicon[14]
# define LEXICON_GRANDFATHER	g_list_lexicon[15]
# define LEXICON_HALLWAY		g_list_lexicon[16]
# define LEXICON_INSIDE			g_list_lexicon[17]
# define LEXICON_INVENTORY		g_list_lexicon[18]
# define LEXICON_KEY			g_list_lexicon[19]
# define LEXICON_LIBRARIAN		g_list_lexicon[20]
# define LEXICON_LIBRARY		g_list_lexicon[21]
# define LEXICON_LOOK			g_list_lexicon[22]
# define LEXICON_MAIN			g_list_lexicon[23]
# define LEXICON_MANSION		g_list_lexicon[24]
# define LEXICON_ME				g_list_lexicon[25]
# define LEXICON_MYSELF			g_list_lexicon[26]
# define LEXICON_OLD			g_list_lexicon[27]
# define LEXICON_ON				g_list_lexicon[28]
# define LEXICON_OUT			g_list_lexicon[29]
# define LEXICON_OUTSIDE		g_list_lexicon[30]
# define LEXICON_PLAY			g_list_lexicon[31]
# define LEXICON_PLAYER			g_list_lexicon[32]
# define LEXICON_ROOM			g_list_lexicon[33]
# define LEXICON_SECOND			g_list_lexicon[34]
# define LEXICON_SELF			g_list_lexicon[35]
# define LEXICON_SIGN			g_list_lexicon[36]
# define LEXICON_SHINY			g_list_lexicon[37]
# define LEXICON_TAKE			g_list_lexicon[38]
# define LEXICON_THING			g_list_lexicon[39]
# define LEXICON_THIRD			g_list_lexicon[40]
# define LEXICON_USE			g_list_lexicon[41]
# define LEXICON_WORLD			g_list_lexicon[42]

#endif
