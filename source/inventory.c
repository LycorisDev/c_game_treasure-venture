#include "../headers/inventory.h"
#include "../headers/commands.h"
#include "../headers/characters.h"

void execute_inventory(void)
{
	int i;
	if (strcmp(command.object, "") == 0 || strcmp(command.object, "player") == 0)
	{
		if (PLAYER->list_of_items_by_id[0] == ID_ITEM_NONE)
			printf("\nYou have no item on you.\n\n");
		else
		{
			printf("\nPLAYER INVENTORY\n");
			for (i = 0; i < NBR_ITEMS; ++i)
			{
				if (PLAYER->list_of_items_by_id[i] == ID_ITEM_NONE)
					break;
				printf("- %s.\n", list_items[PLAYER->list_of_items_by_id[i]].name);
			}
			printf("\n");
		}
		return;
	}
	else
	{
		for (i = 0; i < NBR_CHARACTERS; ++i)
		{
			if (PLAYER->current_location->list_of_characters_by_id[i] == ID_CHARACTER_NONE)
				break;
			if (PLAYER->current_location->list_of_characters_by_id[i] == ID_CHARACTER_PLAYER)
				continue;

			if (PLAYER->current_location->list_of_characters_by_id[i] == ID_CHARACTER_LIBRARIAN && strcmp(command.object, "librarian") == 0)
			{
				if (CHARACTER_LIBRARIAN->list_of_items_by_id[0] == ID_ITEM_NONE)
					printf("\nThey have no item on them.\n\n");
				else
				{
					printf("\nLIBRARIAN INVENTORY\n");
					for (i = 0; i < NBR_ITEMS; ++i)
					{
						if (CHARACTER_LIBRARIAN->list_of_items_by_id[i] == ID_ITEM_NONE)
							break;
						printf("- %s.\n", list_items[CHARACTER_LIBRARIAN->list_of_items_by_id[i]].name);
					}
					printf("\n");
				}
				return;
			}
		}	
	}

	printf("\n\t[I do not recognize this character. Try:]\n");
	printf("\t\t[- 'Inventory' or 'Inventory player'.]\n");
	for (i = 0; i < NBR_CHARACTERS; ++i)
	{
		if (PLAYER->current_location->list_of_characters_by_id[i] == ID_CHARACTER_NONE)
			break;
		if (PLAYER->current_location->list_of_characters_by_id[i] == ID_CHARACTER_PLAYER)
			continue;
		printf("\t\t[- 'Inventory %s'.]\n", retrieve_default_character_tag_by_id(PLAYER->current_location->list_of_characters_by_id[i]));
	}
	printf("\n");
	return;
}

