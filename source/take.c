#include "../headers/take.h"
#include "../headers/commands.h"
#include "../headers/items.h"

void execute_take(void)
{
	int i, j;
	int item_id = 0;
	int id_of_takeable_items[NBR_ITEMS] = {0};

	if (PLAYER->list_of_items_by_id[NBR_ITEMS - 1] != ID_ITEM_NONE)
	{
		printf("\nYour inventory is full.\n\n");
		return;
	}

	for (i = 0, j = 0; i < NBR_ITEMS; ++i)
	{
		if (PLAYER->current_location->list_of_items_by_id[i] == ID_ITEM_NONE)
			break;
		if (list_items[PLAYER->current_location->list_of_items_by_id[i]].can_be_taken == 1)
			id_of_takeable_items[j++] = PLAYER->current_location->list_of_items_by_id[i];
	}

	if (id_of_takeable_items[0] == ID_ITEM_NONE)
	{
		printf("\nThere is nothing for you to take here.\n\n");
		return;
	}

	if ((item_id = retrieve_item_id_by_parser(command.object)) == ID_ITEM_NONE)
		memcpy(command.object, "", BIG_LENGTH_WORD);
	else if (strcmp(command.object, "") != 0)
	{
		for (i = 0; i <= NBR_ITEMS; ++i)
		{
			if (i == NBR_ITEMS || id_of_takeable_items[i] == ID_ITEM_NONE)
			{
				memcpy(command.object, "", BIG_LENGTH_WORD);
				break;
			}
			else if (id_of_takeable_items[i] == item_id)
			{
				for (j = 0; j < NBR_ITEMS; ++j)
				{
					if (PLAYER->list_of_items_by_id[j] == ID_ITEM_NONE)
					{
						PLAYER->list_of_items_by_id[j] = item_id;
						for (i = 0; i < NBR_ITEMS; ++i)
						{
							if (PLAYER->current_location->list_of_items_by_id[i] == item_id)
							{
								PLAYER->current_location->list_of_items_by_id[i] = ID_ITEM_NONE;
								for (j = NBR_ITEMS - 1; j >= 0; --j)
								{
									if (PLAYER->current_location->list_of_items_by_id[j] != ID_ITEM_NONE)
									{
										if (i < j)
										{
											PLAYER->current_location->list_of_items_by_id[i] = PLAYER->current_location->list_of_items_by_id[j];
											PLAYER->current_location->list_of_items_by_id[j] = ID_ITEM_NONE;
										}
										break;
									}
								}
								break;
							}
						}
						break;
					}
				}
				if (item_id == ID_ITEM_ENTRY_DOORS_KEY)
					list_events[1] = FLAG_OFF;
				printf("\n'%s' added to your inventory.\n\n", list_items[item_id].name);
				break;
			}
		}
	}

	if (strcmp(command.object, "") == 0)
	{
		if (id_of_takeable_items[1] == ID_ITEM_NONE)
		{
			printf("\n\t[Take what? Try 'take %s'.]\n\n", retrieve_default_item_tag_by_id(id_of_takeable_items[0]));
		}
		else
		{
			printf("\n\t[Take what? Try:]\n");
			for (i = 0; i < NBR_ITEMS; ++i)
			{
				if (id_of_takeable_items[i] == ID_ITEM_NONE)
					break;
				printf("\t\t['Take %s'.]\n", retrieve_default_item_tag_by_id(id_of_takeable_items[i]));
			}
			printf("\n");
		}
	}
	return;
}

