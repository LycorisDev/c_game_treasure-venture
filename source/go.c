#include "../headers/game.h"
#include "../headers/events.h"
#include "../headers/go.h"
#include "../headers/commands.h"
#include "../headers/locations.h"

void execute_go(void)
{
	int i;
	if (PLAYER->current_location->exits[0].to == NULL)
	{
		printf("\nThere is nowhere to go.\n\n");
	}
	else
	{
		if (strcmp(command.object, "") != 0)
		{
			for (i = 0; i <= NBR_LOCATIONS; ++i)
			{
				if (i == NBR_LOCATIONS || PLAYER->current_location->exits[i].to == NULL)
				{
					memcpy(command.object, "", BIG_LENGTH_WORD);
					break;
				}
				else if (bool_parser_and_location_id_do_match(command.object, PLAYER->current_location->exits[i].to->location_id))
				{
					if (PLAYER->current_location->exits[i].passage->access == ACCESS_NONE)
					{
						/* The player should never see this one */
						printf("\nYou cannot access this place.\n\n");
					}
					else if (PLAYER->current_location->exits[i].passage->access == ACCESS_LOCKED)
					{
						printf("\nThe %s %s locked.\n\n", PLAYER->current_location->exits[i].passage->is_singular ? "door" : "doors", 
							PLAYER->current_location->exits[i].passage->is_singular ? "is" : "are");
					}
					else
					{
						if (PLAYER->current_location->exits[i].passage->access == ACCESS_CLOSED)
						{
							PLAYER->current_location->exits[i].passage->access = ACCESS_OPEN;
							printf("\nYou open the %s.", PLAYER->current_location->exits[i].passage->is_singular ? "door" : "doors");
						}

						PLAYER->current_location = PLAYER->current_location->exits[i].to;
						EVENT_PLAYER_ENTERS_MANSION_FOR_THE_FIRST_TIME
						printf("\n%s\n\n", PLAYER->current_location->description);
					}
					break;
				}
			}
		}

		if (strcmp(command.object, "") == 0)
		{
			if (PLAYER->current_location->exits[1].to == NULL)
			{
				printf("\n\t[Go where? From here, try 'go %s'.]\n\n", retrieve_default_location_tag_by_id(PLAYER->current_location->exits[0].to->location_id));
			}
			else
			{
				printf("\n\t[Go where? From here, try:]\n");
				for (i = 0; i < NBR_LOCATIONS; ++i)
				{
					if (PLAYER->current_location->exits[i].to == NULL)
						break;
					printf("\t\t['Go %s'.]\n", retrieve_default_location_tag_by_id(PLAYER->current_location->exits[i].to->location_id));
				}
				printf("\n");
			}
		}
	}
	return;
}

