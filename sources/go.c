#include "../headers/go.h"
#include "../headers/main.h"
#include "../headers/game.h"
#include "../headers/events.h"
#include "../headers/commands.h"
#include "../headers/locations.h"
#include "../headers/items.h"

#define IF_NO_ACCESS(exit)          if (!exit->to || !exit->passage->access)\
                                    {\
                                        /* The player should never see this message */\
                                        add_output("You cannot access this place. ");\
                                    }

#define PRINT_ACCESS_LOCKED(exit)   add_output("The %s %s locked. ", exit->passage->is_singular ? "door" : "doors", exit->passage->is_singular ? "is" : "are");

#define IF_ACCESS_LOCKED(exit)      if (exit->passage->access == ACCESS_LOCKED)\
                                    {\
                                        PRINT_ACCESS_LOCKED(exit)\
                                    }

#define IF_LOCATION_FULL(exit)      if (exit->to->characters[NBR_CHARACTERS - 1])\
                                    {\
                                        add_output("The destination is full. No more characters can access this place. ");\
                                    }

static void cross_passage(Exit* exit);

void execute_go(void)
{
    int i, j, k;
    Exit** locations_with_same_tag_from_current_location = NULL;
    Exit** locations_with_same_tag_from_passage_items_in_current_location = NULL;
    /* For "go out": */
    Exit* accessible_exits[NBR_LOCATIONS] = {0};
    Exit* locked_exits[NBR_LOCATIONS] = {0};

    if (!PLAYER->current_location->exits[0].to)
    {
        add_output("\nThere is nowhere to go.\n\n");
    }
    else
    {
        if (*command.object)
        {
            /* "go inside" if outside of any building */
            if (!strcmp(command.object, "inside"))
            {
                if (PLAYER->current_location->type == LOCATION_TYPE_OUTSIDE)
                {
                    add_output("\n");
                    if (!PLAYER->current_location->exits[0].to)
                        add_output("There is nowhere to go.\n\n");
                    else IF_NO_ACCESS((PLAYER->current_location->exits + 0))
                    else IF_ACCESS_LOCKED((PLAYER->current_location->exits + 0))
                    else IF_LOCATION_FULL((PLAYER->current_location->exits + 0))
                    else
                        cross_passage((PLAYER->current_location->exits + 0));
                    add_output("\n\n");
                }
                else
                    memset(command.object, 0, sizeof(command.object));
            }
            /* "go outside" to leave the building */
            else if (!strcmp(command.object, "outside"))
            {
                if (PLAYER->current_location->type == LOCATION_TYPE_ROOM)
                {
                    for (i = 0; i < NBR_LOCATIONS; ++i)
                    {
                        if (!PLAYER->current_location->exits[i].to)
                        {
                            memset(command.object, 0, sizeof(command.object));
                            break;
                        }
                        else if (PLAYER->current_location->exits[i].to->type == LOCATION_TYPE_BUILDING)
                        {
                            add_output("\n");
                            IF_NO_ACCESS((PLAYER->current_location->exits + i))
                            else IF_ACCESS_LOCKED((PLAYER->current_location->exits + i))
                            else IF_LOCATION_FULL((PLAYER->current_location->exits + i))
                            else
                                cross_passage((PLAYER->current_location->exits + i));
                            add_output("\n\n");
                            break;
                        }
                    }
                }
                else
                    memset(command.object, 0, sizeof(command.object));
            }
            /* "go back" to go to your previous location if possible */
            else if (!strcmp(command.object, "back"))
            {
                if (!PLAYER->previous_location)
                    memset(command.object, 0, sizeof(command.object));
                else
                {
                    for (i = 0; i < NBR_LOCATIONS; ++i)
                    {
                        if (!PLAYER->current_location->exits[i].to)
                        {
                            memset(command.object, 0, sizeof(command.object));
                            break;
                        }
                        else if (PLAYER->current_location->exits[i].to == PLAYER->previous_location) 
                        {
                            add_output("\n");
                            IF_NO_ACCESS((PLAYER->current_location->exits + i))
                            else IF_ACCESS_LOCKED((PLAYER->current_location->exits + i))
                            else IF_LOCATION_FULL((PLAYER->current_location->exits + i))
                            else
                                cross_passage((PLAYER->current_location->exits + i));
                            add_output("\n\n");
                            break;
                        }
                        else if (PLAYER->current_location->exits[i].to->type == LOCATION_TYPE_BUILDING)
                        {
                            j = 0;
                            while (PLAYER->current_location->exits[i].to->exits[j].to)
                            {
                                if (PLAYER->current_location->exits[i].to->exits[j].to == PLAYER->previous_location)
                                {
                                    add_output("\n");
                                    IF_NO_ACCESS((PLAYER->current_location->exits + i))
                                    else IF_ACCESS_LOCKED((PLAYER->current_location->exits + i))
                                    else IF_LOCATION_FULL((PLAYER->current_location->exits + i))
                                    else
                                        cross_passage((PLAYER->current_location->exits + i));
                                    add_output("\n\n");
                                    break;
                                }
                                ++j;
                            }
                            break;
                        }
                    }
                }
            }
            /* "go out" to go to the only exit (if inside of a building) */
            else if (!strcmp(command.object, "out"))
            {
                if (PLAYER->current_location->type == LOCATION_TYPE_OUTSIDE)
                {
                    add_output("\nYou are already outside.\n\n");
                }
                else
                {
                    for (i = 0, j = 0, k = 0; i < NBR_LOCATIONS; ++i)
                    {
                        if (!PLAYER->current_location->exits[i].to)
                            break;
                        else if (PLAYER->current_location->exits[i].passage->access)
                        {
                            if (PLAYER->current_location->exits[i].passage->access != ACCESS_LOCKED)
                                accessible_exits[j++] = &(PLAYER->current_location->exits[i]);
                            else
                                locked_exits[k++] = &(PLAYER->current_location->exits[i]);
                        }
                    }

                    /* There's not even one exit */
                    if (!j && !k)
                    {
                        /* The player should never see this message */
                        add_output("\nYou cannot get out.\n\n");
                    }
                    /* Success: There is only one accessible exit */
                    else if (j == 1)
                    {
                        add_output("\n");
                        cross_passage(accessible_exits[0]);
                        add_output("\n\n");
                    }
                    /* Almost success: There is only one exit but it is locked */
                    else if (!j && k == 1)
                    {
                        add_output("\n");
                        PRINT_ACCESS_LOCKED(locked_exits[0])
                            add_output("\n\n");
                    }
                    /* Several accessible and/or locked exits. Which one does the player want? */
                    else
                    {
                        add_output("\nThere is more than one exit. Which one do you want?\n");
                        memset(command.object, 0, sizeof(command.object));
                    }
                }
            }
            else
            {
                locations_with_same_tag_from_current_location = retrieve_locations_by_parser_from_current_location(command.object);

                if (!locations_with_same_tag_from_current_location || !locations_with_same_tag_from_current_location[0])
                {
                    locations_with_same_tag_from_passage_items_in_current_location = retrieve_locations_by_parser_from_passage_items_in_current_location(command.object);

                    if (!locations_with_same_tag_from_passage_items_in_current_location || !locations_with_same_tag_from_passage_items_in_current_location[0])
                        memset(command.object, 0, sizeof(command.object));
                    else if (!locations_with_same_tag_from_passage_items_in_current_location[1])
                    {
                        add_output("\n");
                        IF_NO_ACCESS(locations_with_same_tag_from_passage_items_in_current_location[0])
                        else IF_ACCESS_LOCKED(locations_with_same_tag_from_passage_items_in_current_location[0])
                        else IF_LOCATION_FULL(locations_with_same_tag_from_passage_items_in_current_location[0])
                        else
                            cross_passage(locations_with_same_tag_from_passage_items_in_current_location[0]);
                        add_output("\n\n");
                    }
                    else
                    {
                        add_output("\nThere is more than one passage item in your vicinity for which this tag works.\n");
                        memset(command.object, 0, sizeof(command.object));
                    }
                }
                else if (!locations_with_same_tag_from_current_location[1])
                {
                    add_output("\n");
                    IF_NO_ACCESS(locations_with_same_tag_from_current_location[0])
                    else IF_ACCESS_LOCKED(locations_with_same_tag_from_current_location[0])
                    else IF_LOCATION_FULL(locations_with_same_tag_from_current_location[0])
                    else
                        cross_passage(locations_with_same_tag_from_current_location[0]);
                    add_output("\n\n");
                }
                else
                {
                    add_output("\nThere is more than one destination from your current location for which this tag works.\n");
                    memset(command.object, 0, sizeof(command.object));
                }
            }
        }

        if (!*command.object)
        {
            if (!PLAYER->current_location->exits[1].to)
            {
                if (PLAYER->current_location->exits[0].to->type == LOCATION_TYPE_BUILDING)
                {
                    if (PLAYER->current_location->type == LOCATION_TYPE_OUTSIDE)
                        add_output("\n\t[Try 'go inside'.]\n\n");
                    else
                        add_output("\n\t[Try 'go outside'.]\n\n");
                }
                else
                    add_output("\n\t[Try 'go %s'.]\n\n", PLAYER->current_location->exits[0].to->tags[0]);
            }
            else
            {
                add_output("\n\t[Try:]\n");
                for (i = 0; i < NBR_LOCATIONS; ++i)
                {
                    if (!PLAYER->current_location->exits[i].to)
                        break;

                    if (PLAYER->current_location->exits[i].to->type == LOCATION_TYPE_BUILDING)
                    {
                        if (PLAYER->current_location->type == LOCATION_TYPE_OUTSIDE)
                            add_output("\t\t['Go inside'.]\n");
                        else
                            add_output("\t\t['Go outside'.]\n");
                    }
                    else
                        add_output("\t\t['Go %s'.]\n", PLAYER->current_location->exits[i].to->tags[0]);
                }
                add_output("\n");
            }
        }
    }

    free(locations_with_same_tag_from_current_location);
    free(locations_with_same_tag_from_passage_items_in_current_location);
    return;
}

static void cross_passage(Exit* exit)
{
    int i, j;

    if (exit->passage->access == ACCESS_CLOSED)
    {
        exit->passage->access = ACCESS_OPEN;
        add_output("You open the %s and ", exit->passage->is_singular ? "door" : "doors");
    }
    else
    {
        add_output("You ");
    }

    /* Enter a building */
    if (PLAYER->current_location->type == LOCATION_TYPE_OUTSIDE && exit->to->type == LOCATION_TYPE_BUILDING)
    {
        for (i = 0; i < NBR_LOCATIONS; ++i)
        {
            if (!exit->to->exits[i].to)
                break;

            /* If the building has an exit that uses the same passage item AND this exit doesn't lead to our current location */
            if (exit->passage == exit->to->exits[i].passage && exit->to->exits[i].to != PLAYER->current_location)
            {
                /* The actual destination is not the building itself but the room the passage item leads to */
                exit = &(exit->to->exits[i]);
                break;
            }
        }

        add_output("cross the %s's threshold to find yourself in the %s. ", exit->to->inside_of->name, exit->to->name);
    }
    /* Exit a building */
    else if (PLAYER->current_location->type == LOCATION_TYPE_ROOM && exit->to->type == LOCATION_TYPE_BUILDING)
    {
        for (i = 0; i < NBR_LOCATIONS; ++i)
        {
            if (!exit->to->exits[i].to)
                break;

            /* If the building has an exit that uses the same passage item AND this exit doesn't lead to our current location */
            if (exit->passage == exit->to->exits[i].passage && exit->to->exits[i].to != PLAYER->current_location)
            {
                /* The actual destination is not the building itself but the outside location the passage item leads to */
                exit = &(exit->to->exits[i]);
                break;
            }
        }

        add_output("leave the %s. ", PLAYER->current_location->inside_of->name);
    }
    else
        add_output("enter the %s. ", exit->to->name);

    /* Update the player's previous and current locations */
    PLAYER->previous_location = PLAYER->current_location;
    PLAYER->current_location = exit->to;

    /* Remove the player from their previous location */
    for (i = 0; i < NBR_CHARACTERS; ++i)
    {
        if (!PLAYER->previous_location->characters[i])
            break;

        if (PLAYER->previous_location->characters[i] == PLAYER)
        {
            for (j = NBR_CHARACTERS - 1; j >= 0; --j)
            {
                if (PLAYER->previous_location->characters[j])
                {
                    PLAYER->previous_location->characters[i] = PLAYER->previous_location->characters[j];
                    memset((PLAYER->previous_location->characters + j), 0, sizeof(Character*));

                    i = NBR_CHARACTERS;
                    break;
                }
            }
        }
    }

    /* Add the player to their current location */
    for (i = 0; i < NBR_CHARACTERS; ++i)
    {
        /* Put the player in the first available spot */
        if (!PLAYER->current_location->characters[i])
        {
            PLAYER->current_location->characters[i] = PLAYER;
            break;
        }
    }

    event_first_time_player_enters_mansion();
    describe_location(PLAYER->current_location);
    return;
}

