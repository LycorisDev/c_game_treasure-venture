#include "treasure_venture.h"

int	load_saved_game(t_man *man, const char *filepath)
{
	char		**lines;
	t_id_loc	id_loc_prev;
	t_id_loc	id_loc_curr;

	/*
		TODO: Check for whether the save file is valid before modifying the 
		current game. It must not be modified to then realize that the save 
		file has been tampered with.
	*/
	lines = read_file(filepath);
	if (!lines)
		return (0);
	//
	/*
		previous_location:2
		current_location:3
		events:0,1,0,0,0,0,0,0,0,0
		inventory:
	*/
	/*
		- The key must be "previous_location", otherwise return 0.
		- The value must be an int. If there's a non-digit character, return 0.
		- The value is an ID. It must be positive and match an existing 
		location (not be too big).
		-> id_loc_prev
	*/
	/*
		- The key must be "current_location", otherwise return 0.
		- The value must be an int. If there's a non-digit character, return 0.
		- The value is an ID. It must be positive and match an existing 
		location (not be too big).
		- If the current location is full, that is to say it doesn't have space 
		for another character, return 0.
		-> id_loc_curr
	*/
	man->characters[CHAR_PLAYER - 1].previous_location = man->locations + id_loc_prev;
	man->characters[CHAR_PLAYER - 1].current_location = man->locations + id_loc_curr;
	//
	free_arr((void **)lines, free);





	/*
		TODO: Instead of having to move the player, or even other characters as 
		well as items, only populate the elements which cannot move nor be 
		modified (use the "can_be_taken" var). And only then, check if the save 
		file has data about it, and use this data to SET the element. If there 
		is no data, then you can use a default value.

		Note that the item list of locations isn't saved, this needs to change, 
		because this would duplicate the key for example if it's already in the 
		player inventory.

		The current solution is only fine because this is the beginning of the 
		game, when a lot of movements occur, it's hell.
	*/
	if (man->characters[CHAR_PLAYER - 1].current_location->id != LOC_OUTSIDE)
	{
		/* Remove player from player's starter location (LOCATION_OUTSIDE) */
		for (i = 0; i < NBR_CHARACTERS; ++i)
		{
			if (!man->locations[LOC_OUTSIDE - 1].characters[i])
				break;
			if (man->locations[LOC_OUTSIDE - 1].characters[i]
				== &man->characters[CHAR_PLAYER - 1])
			{
				for (j = NBR_CHARACTERS - 1; j >= 0; --j)
				{
					if (man->locations[LOC_OUTSIDE - 1].characters[j])
					{
						man->locations[LOC_OUTSIDE - 1].characters[i]
							= man->locations[LOC_OUTSIDE - 1].characters[j];
						memset(man->locations[LOC_OUTSIDE - 1].characters + j,
							0, sizeof(t_character *));
						i = NBR_CHARACTERS;
						break;
					}
				}
			}
		}

		/* Add the player to the current location */
		for (i = 0; i < NBR_CHARACTERS; ++i)
		{
			if (!man->characters[CHAR_PLAYER - 1]
				.current_location->characters[i])
			{
				man->characters[CHAR_PLAYER - 1].current_location->characters[i]
					= &man->characters[CHAR_PLAYER - 1];
				break;
			}
		}
	}

	if (!save_buffer[4] || strcmp(save_buffer[4], "events"))
		return 0;

	for (i = 0; i < NBR_EVENTS; ++i)
	{
		id = strtol(save_buffer[5 + i], &end_ptr, 10);
		if (id != 1 && id != 0)
			return 0;
		/* TODO: Handle events better instead of looping */
		else if (id == 0)
		{
			switch (i)
			{
				case 0:
					run_event_first_time_player_enters_mansion(man);
					break;
				case 1:
					run_event_player_finds_entry_doors_key(man);
					break;
			}
		}
	}

	if (!save_buffer[5 + NBR_EVENTS]
		|| strcmp(save_buffer[5 + NBR_EVENTS], "inventory"))
		return 0;

	for (i = 0; i < NBR_ITEMS; ++i)
	{
		id = strtol(save_buffer[6 + NBR_EVENTS + i], &end_ptr, 10) - 1;
		if (save_buffer[6 + NBR_EVENTS + i] == end_ptr || *end_ptr != '\0'
			|| (id < 1 || id > (NBR_ITEMS - 1)))
			break;
		else
			man->characters[CHAR_PLAYER - 1].inventory[i] = (man->items + id);
	}
	return 1;
}
