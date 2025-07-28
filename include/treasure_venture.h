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

# define FS '\x1C'
# define FS_STR "\x1C"
# define SAVE_FILE "save.txt"

# define NBR_EVENTS  10
# define NBR_TAGS    7
# define NBR_CHARAS  5
# define NBR_LOCS    16
# define NBR_GEO_AFF 2
# define NBR_ITEMS   100
# define LEN_WORD    20
# define LEN_TAG     120
# define LEN_DESC    512

typedef struct s_char		t_char;
typedef struct s_loc		t_loc;
typedef struct s_geo_aff	t_geo_aff; /* Geographical Affiliation */
typedef struct s_exit		t_exit;
typedef struct s_item		t_item;

typedef enum e_game_state
{
	STATE_QUIT,
	STATE_MENU,
	STATE_GAME
}	t_game_state;

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

typedef enum e_access
{
	ACCESS_NONE,
	ACCESS_LOCKED,
	ACCESS_OPEN,
	ACCESS_CLOSED
}	t_access;

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

typedef struct s_cmd
{
	char	*verb;
	char	*object;
	char	*preposition;
	char	*target;
}	t_cmd;

struct s_char
{
	int		id;
	char	tags[NBR_TAGS][LEN_TAG];
	char	desc[LEN_DESC];

	t_loc	*previous_loc;
	t_loc	*current_loc;
	t_item	*inventory[NBR_ITEMS];
};

struct s_item
{
	t_id_item	id;
	char		tags[NBR_TAGS][LEN_TAG];
	char		desc[LEN_DESC];

	char		desc_look_around[LEN_DESC];
	char		desc_look_item[LEN_DESC];
	int			bool_is_singular;
	int			access;
	t_item		*unlocked_with;
	int			bool_can_be_taken;
	int			bool_requires_target_for_use;
};

struct s_exit
{
	t_loc	*to;
	t_item	*passage;
};

struct s_geo_aff
{
	int		id;
	char	name[LEN_TAG];
};

struct s_loc
{
	t_id_loc	id;
	char		tags[NBR_TAGS][LEN_TAG];
	char		desc[LEN_DESC];

	int			bool_is_indoors;
	t_geo_aff	*geo_aff;
	t_exit		exits[NBR_LOCS];

	t_item		*items[NBR_ITEMS];
	t_char		*charas[NBR_CHARAS];
};

typedef struct s_man
{
	t_game_state	state;
	const char		**tokens;

	int				is_game_ongoing;
	t_cmd			cmd;
	t_char			charas[NBR_CHARAS];
	int				events[NBR_EVENTS];
	t_item			items[NBR_ITEMS];
	t_loc			locs[NBR_LOCS];
	t_geo_aff		geo_aff[NBR_GEO_AFF];
}	t_man;

/* Parser ------------------------------------------------------------------- */

const char	**get_input(void);
int			ask_yes_no(void);

/* Menu --------------------------------------------------------------------- */

void		open_menu(t_man *man);
void		run_menu_cmd(t_man *man, const char **tokens);
void		run_submenu_new(t_man *man);
void		run_submenu_load(t_man *man);
void		run_submenu_save(t_man *man);
void		run_submenu_about(t_man *man);
void		run_submenu_quit(t_man *man);
int			save_game(t_man *man, const char *filepath);
int			load_saved_game(t_man *man, const char *filepath);

/* Utils -------------------------------------------------------------------- */

void		clear_window(void);
char		*gnl(int fd);
char		**read_file(const char *filepath);
char		**split(const char *s, char c);
char		*strjoin(char const *s1, char const *s2);
size_t		count_arr(void **arr);
void		free_arr(void **arr, void (*free_fct)(void *));
void		remove_arr_elems(void **arr, size_t from, size_t to,
				void (*free_fct)(void *));

/* Misc --------------------------------------------------------------------- */

void		initialize_game(t_man *man);
void		populate_list_locs(t_man *man);
void		describe_loc(t_man *man, const t_loc *loc);
void		display_loc_suggestions(t_loc *origin);
t_exit		**retrieve_locs(t_loc *origin, const char *parser);
t_exit		**retrieve_locs_with_passage_item(t_loc *origin,
				const char *parser);
void		populate_list_items(t_man *man);
void		display_item_suggestions(t_item **item_collection,
				const char *command);
t_item		**retrieve_items(t_item **item_collection, const char *parser);
t_item		**retrieve_takeable_items(t_item **item_collection,
				const char *parser);
int			bool_item_matches_parser(const t_item *item, const char *parser);
void		populate_list_charas(t_man *man);
void		display_chara_suggestions(t_man *man,
				t_char **chara_collection, const char *command);
t_char		**retrieve_charas(t_char **chara_collection,
				const char *parser);
void		populate_list_events(t_man *man);
void		run_event_first_time_player_enters_mansion(t_man *man);
void		event_first_time_player_enters_mansion(t_man *man);
void		run_event_player_finds_entry_doors_key(t_man *man);
void		event_player_finds_entry_doors_key(t_man *man,
				const t_id_item id_item);
void		run_game_cmd(t_man *man, const char **tokens);
void		run_drop(t_man *man);
void		run_go(t_man *man);
void		run_inventory(t_man *man);
void		run_look(t_man *man);
void		run_play(t_man *man);
void		run_take(t_man *man);
void		run_use(t_man *man);

#endif
