#include "../headers/game.h"
#include "../headers/events.h"
#include "../headers/go.h"
#include "../headers/commands.h"
#include "../headers/locations.h"

void execute_go(void)
{
    int i, j, k;
    int accessible_exits[NBR_LOCATIONS] = {0};
    int locked_exits[NBR_LOCATIONS] = {0};

    if (PLAYER->current_location->exits[0].to == NULL)
    {
        printf("\nThere is nowhere to go.\n\n");
    }
    else
    {
        if (strcmp(command.object, "") != 0)
        {
            /* "go back" = go to your previous location if possible */
            if (strcmp(command.object, "back") == 0)
            {
                if (PLAYER->previous_location == LOCATION_NONE)
                    memcpy(command.object, "", BIG_LENGTH_WORD);
                else
                {
                    for (i = 0; i <= NBR_LOCATIONS; ++i)
                    {
                        if (i == NBR_LOCATIONS || PLAYER->current_location->exits[i].to == NULL)
                        {
                            memcpy(command.object, "", BIG_LENGTH_WORD);
                            break;
                        }
                        else if (PLAYER->current_location->exits[i].to->location_id == PLAYER->previous_location->location_id)
                        {
                            if (PLAYER->current_location->exits[i].passage->access == ACCESS_NONE)
                            {
                                /* The player should never see this message */
                                printf("\nYou cannot access this place.\n\n");
                            }
                            else if (PLAYER->current_location->exits[i].passage->access == ACCESS_LOCKED)
                            {
                                printf("\nThe %s %s locked.\n\n", 
                                    PLAYER->current_location->exits[i].passage->is_singular ? "door" : "doors", 
                                    PLAYER->current_location->exits[i].passage->is_singular ? "is" : "are");
                            }
                            else
                            {
                                if (PLAYER->current_location->exits[i].passage->access == ACCESS_CLOSED)
                                {
                                    PLAYER->current_location->exits[i].passage->access = ACCESS_OPEN;
                                    printf("\nYou open the %s.", PLAYER->current_location->exits[i].passage->is_singular ? "door" : "doors");
                                }

                                PLAYER->previous_location = PLAYER->current_location;
                                PLAYER->current_location = PLAYER->current_location->exits[i].to;
                                EVENT_PLAYER_ENTERS_MANSION_FOR_THE_FIRST_TIME
                                printf("\n%s\n\n", PLAYER->current_location->description);
                            }
                            break;
                        }
                    }
                }
            }
            /* "go out" = go to the only exit */
            else if (strcmp(command.object, "out") == 0)
            {
                for (i = 0, j = 0, k = 0; i <= NBR_LOCATIONS; ++i)
                {
                    if (i == NBR_LOCATIONS || PLAYER->current_location->exits[i].to == NULL)
                        break;
                    else if (PLAYER->current_location->exits[i].passage->access != ACCESS_NONE)
                    {
                        if (PLAYER->current_location->exits[i].passage->access != ACCESS_LOCKED)
                            accessible_exits[j++] = i;
                        else
                            locked_exits[k++] = i;
                    }
                }

                /* There's not even one exit */
                if (!j && !k)
                {
                    /* The player should never see this message */
                    printf("\nYou cannot get out.\n\n");
                }
                /* Success: There is only one accessible exit */
                else if (j == 1)
                {
                    if (PLAYER->current_location->exits[accessible_exits[0]].passage->access == ACCESS_CLOSED)
                    {
                        PLAYER->current_location->exits[accessible_exits[0]].passage->access = ACCESS_OPEN;
                        printf("\nYou open the %s.", PLAYER->current_location->exits[accessible_exits[0]].passage->is_singular ? "door" : "doors");
                    }

                    PLAYER->previous_location = PLAYER->current_location;
                    PLAYER->current_location = PLAYER->current_location->exits[accessible_exits[0]].to;
                    EVENT_PLAYER_ENTERS_MANSION_FOR_THE_FIRST_TIME
                    printf("\n%s\n\n", PLAYER->current_location->description);
                }
                /* Almost success: There is only one exit but it is locked */
                else if (!j && k == 1)
                {
                    printf("\nThe %s %s locked.\n\n", 
                        PLAYER->current_location->exits[locked_exits[0]].passage->is_singular ? "door" : "doors", 
                        PLAYER->current_location->exits[locked_exits[0]].passage->is_singular ? "is" : "are");
                }
                /* Several accessible and/or locked exits. Which one does the player want? */
                else
                {
                    memcpy(command.object, "", BIG_LENGTH_WORD);
                }
            }
            else
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
                            /* The player should never see this message */
                            printf("\nYou cannot access this place.\n\n");
                        }
                        else if (PLAYER->current_location->exits[i].passage->access == ACCESS_LOCKED)
                        {
                            printf("\nThe %s %s locked.\n\n", 
                                PLAYER->current_location->exits[i].passage->is_singular ? "door" : "doors", 
                                PLAYER->current_location->exits[i].passage->is_singular ? "is" : "are");
                        }
                        else
                        {
                            if (PLAYER->current_location->exits[i].passage->access == ACCESS_CLOSED)
                            {
                                PLAYER->current_location->exits[i].passage->access = ACCESS_OPEN;
                                printf("\nYou open the %s.", PLAYER->current_location->exits[i].passage->is_singular ? "door" : "doors");
                            }

                            PLAYER->previous_location = PLAYER->current_location;
                            PLAYER->current_location = PLAYER->current_location->exits[i].to;
                            EVENT_PLAYER_ENTERS_MANSION_FOR_THE_FIRST_TIME
                            printf("\n%s\n\n", PLAYER->current_location->description);
                        }
                        break;
                    }
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

