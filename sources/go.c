#include "../headers/game.h"
#include "../headers/events.h"
#include "../headers/go.h"
#include "../headers/commands.h"
#include "../headers/locations.h"

#define IF_ACCESS_NONE(i)           if (PLAYER->current_location->exits[i].passage->access == ACCESS_NONE)\
                                    {\
                                        /* The player should never see this message */\
                                        printf("You cannot access this place. ");\
                                    }

#define PRINT_ACCESS_LOCKED(i)      printf("The %s %s locked. ",\
                                        PLAYER->current_location->exits[i].passage->is_singular ? "door" : "doors",\
                                        PLAYER->current_location->exits[i].passage->is_singular ? "is" : "are");

#define IF_ACCESS_LOCKED(i)         if (PLAYER->current_location->exits[i].passage->access == ACCESS_LOCKED)\
                                    {\
                                        PRINT_ACCESS_LOCKED(i)\
                                    }

#define IF_LOCATION_FULL(i)         if (PLAYER->current_location->exits[i].to->list_of_characters_by_id[NBR_CHARACTERS - 1] != ID_CHARACTER_NONE)\
                                    {\
                                        printf("The destination is full. No more characters can access this place. ");\
                                    }

void cross_passage(const int index)
{
    int i, j;

    if (PLAYER->current_location->exits[index].passage->access == ACCESS_CLOSED)
    {
        PLAYER->current_location->exits[index].passage->access = ACCESS_OPEN;
        printf("You open the %s and ", PLAYER->current_location->exits[index].passage->is_singular ? "door" : "doors");
    }
    else
    {
        printf("You ");
    }

    if (PLAYER->current_location->type == LOCATION_TYPE_OUTSIDE && PLAYER->current_location->exits[index].to->type == LOCATION_TYPE_ROOM)
        printf("cross the %s's threshold to find yourself in the %s. ", PLAYER->current_location->exits[index].to->inside_of->name, PLAYER->current_location->exits[index].to->name);
    else if (PLAYER->current_location->type == LOCATION_TYPE_ROOM && PLAYER->current_location->exits[index].to->type == LOCATION_TYPE_OUTSIDE)
        printf("leave the %s. ", PLAYER->current_location->inside_of->name);
    else
        printf("enter the %s. ", PLAYER->current_location->exits[index].to->name);

    /* Update the player's previous and current locations */
    PLAYER->previous_location = PLAYER->current_location;
    PLAYER->current_location = PLAYER->current_location->exits[index].to;

    /* Remove the player from their previous location */
    for (i = 0; i <= NBR_CHARACTERS; ++i)
    {
        if (i == NBR_CHARACTERS || PLAYER->previous_location->list_of_characters_by_id[i] == ID_CHARACTER_NONE)
            break;

        if (PLAYER->previous_location->list_of_characters_by_id[i] == ID_CHARACTER_PLAYER)
        {
            for (j = NBR_CHARACTERS - 1; j >= 0; --j)
            {
                if (PLAYER->previous_location->list_of_characters_by_id[j] != ID_CHARACTER_NONE)
                {
                    PLAYER->previous_location->list_of_characters_by_id[i] = PLAYER->previous_location->list_of_characters_by_id[j];
                    PLAYER->previous_location->list_of_characters_by_id[j] = ID_CHARACTER_NONE;

                    i = NBR_CHARACTERS;
                    break;
                }
            }
        }
    }

    /* Add the player to their current location */
    for (i = 0; i <= NBR_CHARACTERS; ++i)
    {
        /* Put the player in the first available spot */
        if (PLAYER->current_location->list_of_characters_by_id[i] == ID_CHARACTER_NONE)
        {
            PLAYER->current_location->list_of_characters_by_id[i] = ID_CHARACTER_PLAYER;
            break;
        }
    }

    EVENT_PLAYER_ENTERS_MANSION_FOR_THE_FIRST_TIME
    describe_location(PLAYER->current_location);
    return;
}

void execute_go(void)
{
    int i, j, k;
    int accessible_exits[NBR_LOCATIONS] = {0};
    int locked_exits[NBR_LOCATIONS] = {0};
    SameTag* locations_with_same_tag_from_current_location = NULL;

    if (PLAYER->current_location->exits[0].to == NULL)
    {
        printf("\nThere is nowhere to go.\n\n");
    }
    else
    {
        if (strcmp(command.object, "") != 0)
        {
            /* "go inside" if outside of any building */
            if (strcmp(command.object, "inside") == 0)
            {
                if (PLAYER->current_location->type == LOCATION_TYPE_OUTSIDE)
                {
                    printf("\n");
                    if (PLAYER->current_location->exits[0].to == NULL)
                        printf("There is nowhere to go.\n\n");
                    else IF_ACCESS_NONE(0)
                    else IF_ACCESS_LOCKED(0)
                    else IF_LOCATION_FULL(0)
                    else
                        cross_passage(0);
                    printf("\n\n");
                }
                else
                    memcpy(command.object, "", BIG_LENGTH_WORD);
            }
            /* "go outside" to leave the building */
            else if (strcmp(command.object, "outside") == 0)
            {
                if (PLAYER->current_location->type == LOCATION_TYPE_ROOM)
                {
                    for (i = 0; i <= NBR_LOCATIONS; ++i)
                    {
                        if (i == NBR_LOCATIONS || PLAYER->current_location->exits[i].to == NULL)
                        {
                            memcpy(command.object, "", BIG_LENGTH_WORD);
                            break;
                        }
                        else if (PLAYER->current_location->exits[i].to->type == LOCATION_TYPE_OUTSIDE)
                        {
                            printf("\n");
                            IF_ACCESS_NONE(i)
                            else IF_ACCESS_LOCKED(i)
                            else IF_LOCATION_FULL(i)
                            else
                                cross_passage(i);
                            printf("\n\n");
                            break;
                        }
                    }
                }
                else
                    memcpy(command.object, "", BIG_LENGTH_WORD);
            }
            /* "go back" to go to your previous location if possible */
            else if (strcmp(command.object, "back") == 0)
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
                        else if (PLAYER->current_location->exits[i].to->id == PLAYER->previous_location->id)
                        {
                            printf("\n");
                            IF_ACCESS_NONE(i)
                            else IF_ACCESS_LOCKED(i)
                            else IF_LOCATION_FULL(i)
                            else
                                cross_passage(i);
                            printf("\n\n");
                            break;
                        }
                    }
                }
            }
            /* "go out" to go to the only exit */
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
                    printf("\n");
                    cross_passage(accessible_exits[0]);
                    printf("\n\n");
                }
                /* Almost success: There is only one exit but it is locked */
                else if (!j && k == 1)
                {
                    printf("\n");
                    PRINT_ACCESS_LOCKED(locked_exits[0])
                    printf("\n\n");
                }
                /* Several accessible and/or locked exits. Which one does the player want? */
                else
                {
                    printf("\nThere is more than one exit. Which one do you want?\n");
                    memcpy(command.object, "", BIG_LENGTH_WORD);
                }
            }
            else
            {
                locations_with_same_tag_from_current_location = retrieve_location_id_by_parser_from_current_location(command.object);

                if (!locations_with_same_tag_from_current_location || locations_with_same_tag_from_current_location[0].id == ID_LOCATION_NONE)
                {
                    memcpy(command.object, "", BIG_LENGTH_WORD);
                }
                else if (locations_with_same_tag_from_current_location[1].id == ID_LOCATION_NONE)
                {
                    printf("\n");
                    IF_ACCESS_NONE(locations_with_same_tag_from_current_location[0].index)
                    else IF_ACCESS_LOCKED(locations_with_same_tag_from_current_location[0].index)
                    else IF_LOCATION_FULL(locations_with_same_tag_from_current_location[0].index)
                    else
                        cross_passage(locations_with_same_tag_from_current_location[0].index);
                    printf("\n\n");
                }
                else
                {
                    printf("\nThere is more than one destination from your current location for which this tag works.\n");
                    memcpy(command.object, "", BIG_LENGTH_WORD);
                }
            }
        }

        if (strcmp(command.object, "") == 0)
        {
            if (PLAYER->current_location->type == LOCATION_TYPE_OUTSIDE && PLAYER->current_location->exits[0].to->type == LOCATION_TYPE_ROOM)
            {
                printf("\n\t[Try 'go inside'.]\n\n");
            }
            else if (PLAYER->current_location->exits[1].to == NULL)
            {
                if (PLAYER->current_location->exits[0].to->type == LOCATION_TYPE_OUTSIDE && PLAYER->current_location->type == LOCATION_TYPE_ROOM)
                    printf("\n\t[Try 'go outside'.]\n\n");
                else
                    printf("\n\t[Try 'go %s'.]\n\n", PLAYER->current_location->exits[0].to->tags[0]);
            }
            else
            {
                printf("\n\t[Try:]\n");
                for (i = 0; i < NBR_LOCATIONS; ++i)
                {
                    if (PLAYER->current_location->exits[i].to == NULL)
                        break;

                    if (PLAYER->current_location->exits[i].to->type == LOCATION_TYPE_OUTSIDE && PLAYER->current_location->type == LOCATION_TYPE_ROOM)
                        printf("\t\t['Go outside'.]\n");
                    else
                        printf("\t\t['Go %s'.]\n", PLAYER->current_location->exits[i].to->tags[0]);
                }
                printf("\n");
            }
        }
    }

    free(locations_with_same_tag_from_current_location);
    return;
}

