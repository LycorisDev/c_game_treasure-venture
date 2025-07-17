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
# define INPUT_MAX_LENGTH       160
# define INPUT_TOKEN_DELIMETERS "\n\t\"\\ .,/:?!^"
# define PARSER_NBR_WORDS       24

typedef struct s_character	t_character;
typedef struct s_location	t_location;
typedef struct s_geo_aff	t_geo_aff; /* Geographical Affiliation */
typedef struct s_exit		t_exit;
typedef struct s_item		t_item;

typedef void	(*yes_no_callback_t)(const int);

typedef enum e_game_state
{
	STATE_NONE,
	STATE_MENU,
	STATE_GAME
}	t_game_state;

typedef struct
{
	const char	*key;
	void		(*func)(void);
}	KeyFunc;

typedef struct s_cmd
{
	char	verb[LENGTH_WORD];
	char	object[BIG_LENGTH_WORD];
	char	preposition[LENGTH_WORD];
	char	target[BIG_LENGTH_WORD];
}	t_cmd;

struct s_character
{
	int			id;
	char		tags[NBR_TAGS][LENGTH_TAG];
	char		description[LENGTH_DESCRIPTION];

	t_location	*previous_location;
	t_location	*current_location;
	t_item		*inventory[NBR_ITEMS];
};

struct s_item
{
	int		id;
	char	tags[NBR_TAGS][LENGTH_TAG];
	char	description[LENGTH_DESCRIPTION];

	char	desc_look_around[LENGTH_DESCRIPTION];
	char	desc_look_item[LENGTH_DESCRIPTION];
	int		bool_is_singular;
	int		access;
	t_item	*unlocked_with;
	int		bool_can_be_taken;
	int		bool_requires_target_for_use;
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
	int			id;
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

	char				parser[PARSER_NBR_WORDS][LENGTH_WORD];
	int					nbr_words_in_parser;
	yes_no_callback_t	yes_no_callback;
}	t_man;

extern t_man	g_man;

/* Init --------------------------------------------------------------------- */

void		clear_window(void);
void		close_window(void);
void		open_menu(void);
void		run_menu_cmd(const char *cmd);
void		initialize_game(void);
void		get_and_parse_input(void);

/* Save --------------------------------------------------------------------- */

void		save_game(int fd_save);
int			load_saved_game(int fd_save);

/* Lexicon ------------------------------------------------------------------ */

void		populate_list_lexicon(void);
int			bool_word_is_in_lexicon(const char *word);
int			bool_word_is_preposition(const char *word);

/* Locations ---------------------------------------------------------------- */

void		populate_list_locations(void);
void		describe_location(const t_location *location);
void		display_location_suggestions(t_location *origin);
t_exit		**retrieve_locations(t_location *origin, const char *parser);
t_exit		**retrieve_locations_with_passage_item(t_location *origin,
				const char *parser);

/* Items -------------------------------------------------------------------- */

void		populate_list_items(void);
void		display_item_suggestions(t_item **item_collection,
				const char *command);
t_item		**retrieve_items(t_item **item_collection, const char *parser);
t_item		**retrieve_takeable_items(t_item **item_collection,
				const char *parser);
int			bool_item_matches_parser(const t_item *item, const char *parser);

/* Characters --------------------------------------------------------------- */

void		populate_list_characters(void);
void		display_character_suggestions(t_character **character_collection,
				const char *command);
t_character	**retrieve_characters(t_character **character_collection,
				const char *parser);

/* Events ------------------------------------------------------------------- */

void		populate_list_events(void);
void		run_event_first_time_player_enters_mansion(void);
void		event_first_time_player_enters_mansion(void);
void		run_event_player_finds_entry_doors_key(void);
void		event_player_finds_entry_doors_key(const int id_item);

/* Commands ----------------------------------------------------------------- */

void		run_game_command(void);
void		display_game_commands(void);
void		run_drop(void);
void		run_go(void);
void		run_inventory(void);
void		run_look(void);
void		run_play(void);
void		run_take(void);
void		run_use(void);

/* -------------------------------------------------------------------------- */
# define ID_LOCATION_OUTSIDE      1
# define ID_LOCATION_MAIN_HALLWAY 2
# define ID_LOCATION_OLD_LIBRARY  3
# define ID_LOCATION_ROOM_1       4
# define ID_LOCATION_ROOM_2       5
# define ID_LOCATION_ROOM_3       6

# define LOCATION_OUTSIDE      (g_man.locations + (ID_LOCATION_OUTSIDE - 1))
# define LOCATION_MAIN_HALLWAY (g_man.locations + (ID_LOCATION_MAIN_HALLWAY - 1))
# define LOCATION_OLD_LIBRARY  (g_man.locations + (ID_LOCATION_OLD_LIBRARY - 1))
# define LOCATION_ROOM_1       (g_man.locations + (ID_LOCATION_ROOM_1 - 1))
# define LOCATION_ROOM_2       (g_man.locations + (ID_LOCATION_ROOM_2 - 1))
# define LOCATION_ROOM_3       (g_man.locations + (ID_LOCATION_ROOM_3 - 1))
/* -------------------------------------------------------------------------- */
# define ID_ITEM_ENTRY_DOORS       1
# define ID_ITEM_GRANDFATHER_CLOCK 2
# define ID_ITEM_LIBRARY_DOOR      3
# define ID_ITEM_LIBRARY_SIGN      4
# define ID_ITEM_BOOKS             5
# define ID_ITEM_DOOR_ROOM_1       6
# define ID_ITEM_DOOR_ROOM_2       7
# define ID_ITEM_DOOR_ROOM_3       8
# define ID_ITEM_ENTRY_DOORS_KEY   9

# define ITEM_ENTRY_DOORS       (g_man.items + (ID_ITEM_ENTRY_DOORS - 1))
# define ITEM_GRANDFATHER_CLOCK (g_man.items + (ID_ITEM_GRANDFATHER_CLOCK - 1))
# define ITEM_LIBRARY_DOOR      (g_man.items + (ID_ITEM_LIBRARY_DOOR - 1))
# define ITEM_LIBRARY_SIGN      (g_man.items + (ID_ITEM_LIBRARY_SIGN - 1))
# define ITEM_BOOKS             (g_man.items + (ID_ITEM_BOOKS - 1))
# define ITEM_DOOR_ROOM_1       (g_man.items + (ID_ITEM_DOOR_ROOM_1 - 1))
# define ITEM_DOOR_ROOM_2       (g_man.items + (ID_ITEM_DOOR_ROOM_2 - 1))
# define ITEM_DOOR_ROOM_3       (g_man.items + (ID_ITEM_DOOR_ROOM_3 - 1))
# define ITEM_ENTRY_DOORS_KEY   (g_man.items + (ID_ITEM_ENTRY_DOORS_KEY - 1))
/* -------------------------------------------------------------------------- */
# define ID_CHARACTER_PLAYER    1
# define ID_CHARACTER_LIBRARIAN 2

# define PLAYER              (g_man.characters + (ID_CHARACTER_PLAYER - 1))
# define CHARACTER_LIBRARIAN (g_man.characters + (ID_CHARACTER_LIBRARIAN - 1))
/* -------------------------------------------------------------------------- */
# define LEXICON_1				g_man.lexicon[0]
# define LEXICON_2				g_man.lexicon[1]
# define LEXICON_3				g_man.lexicon[2]
# define LEXICON_AROUND			g_man.lexicon[3]
# define LEXICON_BACK			g_man.lexicon[4]
# define LEXICON_BOOK			g_man.lexicon[5]
# define LEXICON_BOOKS			g_man.lexicon[6]
# define LEXICON_CLOCK			g_man.lexicon[7]
# define LEXICON_DOOR			g_man.lexicon[8]
# define LEXICON_DOORS			g_man.lexicon[9]
# define LEXICON_DOUBLE			g_man.lexicon[10]
# define LEXICON_DROP			g_man.lexicon[11]
# define LEXICON_ENTRY			g_man.lexicon[12]
# define LEXICON_FIRST			g_man.lexicon[13]
# define LEXICON_GO				g_man.lexicon[14]
# define LEXICON_GRANDFATHER	g_man.lexicon[15]
# define LEXICON_HALLWAY		g_man.lexicon[16]
# define LEXICON_INSIDE			g_man.lexicon[17]
# define LEXICON_INVENTORY		g_man.lexicon[18]
# define LEXICON_KEY			g_man.lexicon[19]
# define LEXICON_LIBRARIAN		g_man.lexicon[20]
# define LEXICON_LIBRARY		g_man.lexicon[21]
# define LEXICON_LOOK			g_man.lexicon[22]
# define LEXICON_MAIN			g_man.lexicon[23]
# define LEXICON_MANSION		g_man.lexicon[24]
# define LEXICON_ME				g_man.lexicon[25]
# define LEXICON_MYSELF			g_man.lexicon[26]
# define LEXICON_OLD			g_man.lexicon[27]
# define LEXICON_ON				g_man.lexicon[28]
# define LEXICON_OUT			g_man.lexicon[29]
# define LEXICON_OUTSIDE		g_man.lexicon[30]
# define LEXICON_PLAY			g_man.lexicon[31]
# define LEXICON_PLAYER			g_man.lexicon[32]
# define LEXICON_ROOM			g_man.lexicon[33]
# define LEXICON_SECOND			g_man.lexicon[34]
# define LEXICON_SELF			g_man.lexicon[35]
# define LEXICON_SIGN			g_man.lexicon[36]
# define LEXICON_SHINY			g_man.lexicon[37]
# define LEXICON_TAKE			g_man.lexicon[38]
# define LEXICON_THING			g_man.lexicon[39]
# define LEXICON_THIRD			g_man.lexicon[40]
# define LEXICON_USE			g_man.lexicon[41]
# define LEXICON_WORLD			g_man.lexicon[42]
/* -------------------------------------------------------------------------- */

#endif
