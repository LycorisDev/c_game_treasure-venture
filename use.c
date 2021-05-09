#include "headers/use.h"
#include "headers/commands.h"
#include "headers/items.h"
#include "headers/characters.h"

void execute_use(void)
{
	int i, j;
	int used_item_id;
	int available_items_by_id[NBR_ITEMS] = {0};

	for (i = 0, j = 0; i < NBR_ITEMS; ++i)
	{
		if (PLAYER->list_of_items_by_id[i] == ID_ITEM_NONE)
			break;
		available_items_by_id[j++] = PLAYER->list_of_items_by_id[i];
	}
	for (i = 0; i < NBR_ITEMS; ++i)
	{
		if (PLAYER->current_location->list_of_items_by_id[i] == ID_ITEM_NONE)
			break;
		available_items_by_id[j++] = PLAYER->current_location->list_of_items_by_id[i];
	}

	if (available_items_by_id[0] == ID_ITEM_NONE)
	{
		printf("\nThere is nothing you can use.\n\n");
	}
	else
	{
		if (strcmp(command.object, "") != 0)
		{
			used_item_id = retrieve_item_id_by_parser(command.object);
			for (i = 0; i < NBR_ITEMS; ++i)
			{
				if (used_item_id == ID_ITEM_NONE || available_items_by_id[i] == ID_ITEM_NONE)
				{
					memcpy(command.object, "", BIG_LENGTH_WORD);
					break;
				}
				
				if (available_items_by_id[i] == used_item_id)
					break;
			}

			if (strcmp(command.object, "") != 0)
			{
				if (used_item_id == ID_ITEM_ENTRY_DOORS_KEY)
				{
					use_entry_doors_key(used_item_id);
				}
				else if (used_item_id == ID_ITEM_ENTRY_DOORS || used_item_id == ID_ITEM_LIBRARY_DOOR 
						|| used_item_id == ID_ITEM_DOOR_ROOM_1 || used_item_id == ID_ITEM_DOOR_ROOM_2 || used_item_id == ID_ITEM_DOOR_ROOM_3)
				{
					use_door(used_item_id);
				}
				else
				{
					printf("\n%s ", list_items[used_item_id].description);
					printf("The %s %s seem to be of much use.\n\n", command.object, list_items[used_item_id].is_singular ? "doesn't" : "don't");
				}
			}
		}
	
		if (strcmp(command.object, "") == 0)
		{
			if (available_items_by_id[1] == ID_ITEM_NONE)
			{
				printf("\n\t[Use what? Try 'use %s'.]\n\n", retrieve_default_item_tag_by_id(available_items_by_id[0]));
			}
			else
			{
				printf("\n\t[Use what? Try:]\n");
				for (i = 0; i < NBR_LOCATIONS; ++i)
				{
					if (available_items_by_id[i] == ID_ITEM_NONE)
						break;
					printf("\t\t['Use %s'.]\n", retrieve_default_item_tag_by_id(available_items_by_id[i]));
				}
				printf("\n");
			}
		}
	}
	return;
}

void use_entry_doors_key(const int used_item_id)
{
	int i;
	int target_id;
	if (strcmp(command.preposition, "on") != 0 || strcmp(command.target, "") == 0)
	{
		printf("\n\t[The %s %s a target. Try specifying on who or what you want to use %s.]\n\n", 
			command.object, list_items[used_item_id].is_singular ? "requires" : "require", list_items[used_item_id].is_singular ? "it" : "them");
	}
	else if (strcmp(command.target, "") != 0)
	{
		target_id = retrieve_item_id_by_parser(command.target);
		if (target_id == ID_ITEM_NONE)
		{
			target_id = retrieve_character_id_by_parser(command.target);
			if (target_id == ID_CHARACTER_NONE)
				printf("\n\t[Use the %s on what?]\n\n", command.object);
			else
				printf("\nThe %s %s nothing to the %s.\n\n", command.object, list_items[used_item_id].is_singular ? "does" : "do", command.target);
		}
		else if (target_id == ID_ITEM_ENTRY_DOORS)
		{
			for (i = 0; i < NBR_ITEMS; ++i)
			{
				if (PLAYER->current_location->list_of_items_by_id[i] == ID_ITEM_NONE)
				{
					printf("\n\t[Use the %s on what?]\n\n", command.object);
					break;
				}
				if (PLAYER->current_location->list_of_items_by_id[i] == ID_ITEM_ENTRY_DOORS)
				{
					if (PLAYER->current_location->exits[0].passage->access == ACCESS_LOCKED)
					{
						printf("\nYou unlock the %s.\n\n", list_items[target_id].is_singular ? "door" : "doors");
						PLAYER->current_location->exits[0].passage->access = ACCESS_CLOSED;
					}
					else
					{
						if (PLAYER->current_location->exits[0].passage->access == ACCESS_OPEN)
							printf("\nYou close the %s.", list_items[target_id].is_singular ? "door" : "doors");
						printf("\nYou lock the %s.\n\n", list_items[target_id].is_singular ? "door" : "doors");
						PLAYER->current_location->exits[0].passage->access = ACCESS_LOCKED;
					}
					break;
				}
			}
		}
		else
		{
			for (i = 0; i < NBR_ITEMS; ++i)
			{
				if (target_id == used_item_id || PLAYER->current_location->list_of_items_by_id[i] == ID_ITEM_NONE)
				{
					printf("\n\t[Use the %s on what?]\n\n", command.object);
					break;
				}
				if (PLAYER->current_location->list_of_items_by_id[i] == target_id)
				{
					printf("\nThe %s %s nothing to the %s.\n\n", command.object, list_items[used_item_id].is_singular ? "does" : "do", command.target);
					break;
				}
			}
		}
	}
	return;
}

void use_door(const int used_item_id)
{
	int i;
	for (i = 0; i < NBR_LOCATIONS; ++i)
	{
		if (PLAYER->current_location->exits[i].to == LOCATION_NONE)
			break;
		else if (PLAYER->current_location->exits[i].passage == (list_items + used_item_id))
		{
			EVENT_PLAYER_ENTERS_MANSION_FOR_THE_FIRST_TIME
			if (PLAYER->current_location->exits[i].passage->access == ACCESS_LOCKED)
			{
				printf("\nThe %s %s locked.\n\n", list_items[used_item_id].is_singular ? "door" : "doors", list_items[used_item_id].is_singular ? "is" : "are");
			}
			else if (PLAYER->current_location->exits[i].passage->access == ACCESS_OPEN)
			{
				PLAYER->current_location->exits[i].passage->access = ACCESS_CLOSED;
				printf("\nYou close the %s.\n\n", list_items[used_item_id].is_singular ? "door" : "doors");
			}
			else if (PLAYER->current_location->exits[i].passage->access == ACCESS_CLOSED)
			{
				PLAYER->current_location->exits[i].passage->access = ACCESS_OPEN;
				printf("\nYou open the %s.\n\n", list_items[used_item_id].is_singular ? "door" : "doors");
			}
			break;
		}
	}
	return;
}

