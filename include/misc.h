#ifndef MISC_H
# define MISC_H

# define LENGTH_TAG         120
# define LENGTH_DESCRIPTION 512
# define NBR_TAGS           7

# define NBR_CHARACTERS 5
# define NBR_LOCATIONS  16
# define NBR_GEO_AFF    2
# define NBR_ITEMS      100

typedef struct s_character	t_character;
typedef struct s_location	t_location;
typedef struct s_geo_aff	t_geo_aff; /* Geographical Affiliation */
typedef struct s_exit		t_exit;
typedef struct s_item		t_item;

typedef struct
{
	const char	*key;
	void		(*func)(void);
}	KeyFunc;

# define ACCESS_LOCKED 1
# define ACCESS_OPEN   2
# define ACCESS_CLOSED 3

#endif
