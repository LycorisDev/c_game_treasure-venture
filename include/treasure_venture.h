#ifndef TREASURE_VENTURE_H
# define TREASURE_VENTURE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <ctype.h>
# include <fcntl.h>
# ifdef _WIN32
#  include <windows.h>
# endif

# define SAVE_FILE "save.txt"
# define BIG_LENGTH_WORD (LENGTH_WORD * 3 + 2)
# define NBR_EVENTS 10
# define FLAG_ON    1
# define FLAG_OFF   0
# define NBR_WORDS   100
# define LENGTH_WORD 20
# define LENGTH_TAG         120
# define LENGTH_DESCRIPTION 512
# define NBR_TAGS           7
# define NBR_CHARACTERS 5
# define NBR_LOCATIONS  16
# define NBR_GEO_AFF    2
# define NBR_ITEMS      100
# define ACCESS_LOCKED 1
# define ACCESS_OPEN   2
# define ACCESS_CLOSED 3
# define INPUT_TOKEN_DELIMETERS "\n\t\"\\ .,/:?!^"
# define PARSER_NBR_WORDS       24

typedef struct s_character	t_character;
typedef struct s_location	t_location;
typedef struct s_geo_aff	t_geo_aff; /* Geographical Affiliation */
typedef struct s_exit		t_exit;
typedef struct s_item		t_item;

typedef enum e_game_state
{
	STATE_NONE,
	STATE_MENU,
	STATE_GAME
}	t_game_state;

typedef enum e_id_char
{
	CHAR_NONE,
	CHAR_PLAYER,
	CHAR_LIBRARIAN,
}	t_id_char;

typedef enum e_id_item
{
	ITEM_NONE,
	ITEM_ENTRY_DOORS,
	ITEM_GRANDFATHER_CLOCK,
	ITEM_LIBRARY_DOOR,
	ITEM_LIBRARY_SIGN,
	ITEM_BOOKS,
	ITEM_DOOR_ROOM_1,
	ITEM_DOOR_ROOM_2,
	ITEM_DOOR_ROOM_3,
	ITEM_ENTRY_DOORS_KEY,
}	t_id_item;

typedef enum e_id_loc
{
	LOC_NONE,
	LOC_OUTSIDE,
	LOC_MAIN_HALLWAY,
	LOC_OLD_LIBRARY,
	LOC_ROOM_1,
	LOC_ROOM_2,
	LOC_ROOM_3,
}	t_id_loc;

typedef enum e_id_lex
{
	LEX_1,
	LEX_2,
	LEX_3,
	LEX_AROUND,
	LEX_BACK,
	LEX_BOOK,
	LEX_BOOKS,
	LEX_CLOCK,
	LEX_DOOR,
	LEX_DOORS,
	LEX_DOUBLE,
	LEX_DROP,
	LEX_ENTRY,
	LEX_FIRST,
	LEX_GO,
	LEX_GRANDFATHER,
	LEX_HALLWAY,
	LEX_INSIDE,
	LEX_INVENTORY,
	LEX_KEY,
	LEX_LIBRARIAN,
	LEX_LIBRARY,
	LEX_LOOK,
	LEX_MAIN,
	LEX_MANSION,
	LEX_ME,
	LEX_MYSELF,
	LEX_OLD,
	LEX_ON,
	LEX_OUT,
	LEX_OUTSIDE,
	LEX_PLAY,
	LEX_PLAYER,
	LEX_ROOM,
	LEX_SECOND,
	LEX_SELF,
	LEX_SIGN,
	LEX_SHINY,
	LEX_TAKE,
	LEX_THING,
	LEX_THIRD,
	LEX_USE,
	LEX_WORLD,
}	t_id_lex;

typedef struct s_cmd
{
	char	verb[LENGTH_WORD];
	char	object[BIG_LENGTH_WORD];
	char	preposition[LENGTH_WORD];
	char	target[BIG_LENGTH_WORD];
}	t_cmd;

struct s_character
{
	t_id_char	id;
	char		tags[NBR_TAGS][LENGTH_TAG];
	char		description[LENGTH_DESCRIPTION];

	t_location	*previous_location;
	t_location	*current_location;
	t_item		*inventory[NBR_ITEMS];
};

struct s_item
{
	t_id_item	id;
	char		tags[NBR_TAGS][LENGTH_TAG];
	char		description[LENGTH_DESCRIPTION];

	char		desc_look_around[LENGTH_DESCRIPTION];
	char		desc_look_item[LENGTH_DESCRIPTION];
	int			bool_is_singular;
	int			access;
	t_item		*unlocked_with;
	int			bool_can_be_taken;
	int			bool_requires_target_for_use;
};

struct s_exit
{
	t_location	*to;
	t_item		*passage;
};

struct s_geo_aff
{
	int		id;
	char	name[LENGTH_TAG];
};

struct s_location
{
	t_id_loc	id;
	char		tags[NBR_TAGS][LENGTH_TAG];
	char		description[LENGTH_DESCRIPTION];

	int			bool_is_indoors;
	t_geo_aff	*geo_aff;
	t_exit		exits[NBR_LOCATIONS];

	t_item		*items[NBR_ITEMS];
	t_character	*characters[NBR_CHARACTERS];
};

typedef struct s_man
{
	int					is_game_ongoing;
	t_game_state		state;
	t_cmd				cmd;
	t_character			characters[NBR_CHARACTERS];
	int					events[NBR_EVENTS];
	t_item				items[NBR_ITEMS];
	char				lexicon[NBR_WORDS][LENGTH_WORD];

	t_location			locations[NBR_LOCATIONS];
	t_geo_aff			geo_aff[NBR_GEO_AFF];

	const char			**tokens;
}	t_man;

/* Init --------------------------------------------------------------------- */

void		clear_window(void);
void		close_window(void);
void		open_menu(t_man *man);
void		run_menu_cmd(t_man *man, const char **tokens);
void		initialize_game(t_man *man);
const char	**get_input(void);
int			ask_yes_no(void);
char		*gnl(int fd);
char		**split(const char *s, char c);
void		free_array(void **arr, void (*free_fct)(void *));

/* Save --------------------------------------------------------------------- */

void		save_game(t_man *man, int fd_save);
int			load_saved_game(t_man *man, int fd_save);

/* Lexicon ------------------------------------------------------------------ */

void		populate_list_lexicon(t_man *man);
int			bool_word_is_in_lexicon(t_man *man, const char *word);
int			bool_word_is_preposition(const char *word);

/* Locations ---------------------------------------------------------------- */

void		populate_list_locations(t_man *man);
void		describe_location(t_man *man, const t_location *location);
void		display_location_suggestions(t_location *origin);
t_exit		**retrieve_locations(t_location *origin, const char *parser);
t_exit		**retrieve_locations_with_passage_item(t_location *origin,
				const char *parser);

/* Items -------------------------------------------------------------------- */

void		populate_list_items(t_man *man);
void		display_item_suggestions(t_item **item_collection,
				const char *command);
t_item		**retrieve_items(t_item **item_collection, const char *parser);
t_item		**retrieve_takeable_items(t_item **item_collection,
				const char *parser);
int			bool_item_matches_parser(const t_item *item, const char *parser);

/* Characters --------------------------------------------------------------- */

void		populate_list_characters(t_man *man);
void		display_character_suggestions(t_man *man, t_character **character_collection,
				const char *command);
t_character	**retrieve_characters(t_character **character_collection,
				const char *parser);

/* Events ------------------------------------------------------------------- */

void		populate_list_events(t_man *man);
void		run_event_first_time_player_enters_mansion(t_man *man);
void		event_first_time_player_enters_mansion(t_man *man);
void		run_event_player_finds_entry_doors_key(t_man *man);
void		event_player_finds_entry_doors_key(t_man *man, const t_id_item id_item);

/* Commands ----------------------------------------------------------------- */

void		run_game_cmd(t_man *man, const char **tokens);
void		display_game_commands(void);
void		run_drop(t_man *man);
void		run_go(t_man *man);
void		run_inventory(t_man *man);
void		run_look(t_man *man);
void		run_play(t_man *man);
void		run_take(t_man *man);
void		run_use(t_man *man);

#endif
