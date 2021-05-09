#include "headers/look.h"
#include "headers/commands.h"
#include "headers/items.h"
#include "headers/characters.h"

void execute_look(void)
{
	int i, item_id, character_id;
	if (strcmp(command.object, "around") == 0)
	{
		printf("\n%s\n\n", PLAYER->current_location->description);
	}
	else if (NO_ITEM_AT_CURRENT_LOCATION && (NO_CHARACTER_AT_CURRENT_LOCATION || PLAYER_IS_ONLY_CHARACTER_AT_CURRENT_LOCATION))
	{
		printf("\n\t[Look what? Try 'look around'.]\n\n");
	}
	else
	{
		if (strcmp(command.object, "") != 0)
		{
			item_id = retrieve_item_id_by_parser(command.object);
			character_id = retrieve_character_id_by_parser(command.object);

			if (item_id != ID_ITEM_NONE)
			{
				for (i = 0; i <= NBR_ITEMS; ++i)
				{					
					if (PLAYER->current_location->list_of_items_by_id[i] == item_id)
					{
						printf("\n%s\n\n", list_items[item_id].description);
						if (item_id == ID_ITEM_ENTRY_DOORS_KEY)
							list_events[1] = FLAG_OFF;
						break;
					}

					if (PLAYER->current_location->list_of_items_by_id[i] == ID_ITEM_NONE)
					{
						memcpy(command.object, "", BIG_LENGTH_WORD);
						break;
					}
				}		
			}
			else if (character_id != ID_CHARACTER_NONE)
			{
				for (i = 0; i <= NBR_CHARACTERS; ++i)
				{					
					if (PLAYER->current_location->list_of_characters_by_id[i] == character_id)
					{
						printf("\n%s\n\n", list_characters[character_id].description);
						break;
					}

					if (PLAYER->current_location->list_of_characters_by_id[i] == ID_CHARACTER_NONE)
					{
						memcpy(command.object, "", BIG_LENGTH_WORD);
						break;
					}
				}
			}
			else
				memcpy(command.object, "", BIG_LENGTH_WORD);
		}

		if (strcmp(command.object, "") == 0)
		{
			printf("\n\t[Look what? Try:]\n");
			printf("\t\t['Look around'.]\n");
			for (i = 0; i < NBR_ITEMS; ++i)
			{
				if (PLAYER->current_location->list_of_items_by_id[i] == 0)
					break;
				printf("\t\t['Look %s'.]\n", retrieve_default_item_tag_by_id(PLAYER->current_location->list_of_items_by_id[i]));
			}
			for (i = 0; i < NBR_CHARACTERS; ++i)
			{
				if (PLAYER->current_location->list_of_characters_by_id[i] == ID_CHARACTER_NONE)
					break;
				if (PLAYER->current_location->list_of_characters_by_id[i] == ID_CHARACTER_PLAYER)
					continue;
				printf("\t\t['Look %s'.]\n", retrieve_default_character_tag_by_id(PLAYER->current_location->list_of_characters_by_id[i]));
			}
			printf("\n");
		}
	}
	return;
}

