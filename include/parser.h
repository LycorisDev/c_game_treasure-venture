#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <ctype.h>
# include "lexicon.h" /* For the LENGTH_WORD macro */

# define INPUT_MAX_LENGTH       160
# define INPUT_TOKEN_DELIMETERS "\n\t\"\\ .,/:?!^"
# define PARSER_NBR_WORDS       24

extern char					g_parser[PARSER_NBR_WORDS][LENGTH_WORD];
extern int					g_nbr_words_in_parser;

typedef void				(*yes_no_callback_t)(const int);
extern yes_no_callback_t	g_yes_no_callback;

void	parse_input(const char *raw_input);
void	parse_yes_no(void);
int		get_available_length_in_string(const int max_length, const char *str);
void	get_and_parse_input(void);

#endif
