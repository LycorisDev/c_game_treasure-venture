#include "../headers/go.h"
#include "../headers/main.h"
#include "../headers/game.h"
#include "../headers/events.h"
#include "../headers/commands.h"
#include "../headers/locations.h"
#include "../headers/items.h"

/* TODO: This was for debugging purposes, remove it now */
#include "../headers/output.h"

static void go_inside(void);
static void go_outside(void);
static void go_back(void);
static void go_out(void);
static void go_tag(void);

static void cross_passage(Exit* exit);

static int bool_access_locked(const Exit* exit);
static void print_access_locked(const Exit* exit);
static int bool_location_is_full(const Location* location);
static void print_location_is_full(void);

void execute_go(void)
{
    if (!PLAYER->current_location->exits[0].to)
    {
        add_output("There is nowhere to go.\n\n");
        return;
    }

    if (*command.object)
    {
        if (!strcmp(command.object, "inside"))
            go_inside();
        else if (!strcmp(command.object, "outside"))
            go_outside();
        else if (!strcmp(command.object, "back"))
            go_back();
        else if (!strcmp(command.object, "out"))
            go_out();
        else
            go_tag();
    }

    if (!*command.object)
        display_location_suggestions(PLAYER->current_location);
    return;
}

static void go_inside(void)
{
    if (PLAYER->current_location->type != LOCATION_TYPE_OUTSIDE)
    {
        add_output("You're already inside of a building.\n\n");
        memset(command.object, 0, sizeof(command.object));
        return;
    }

    if (bool_access_locked(PLAYER->current_location->exits + 0))
        print_access_locked(PLAYER->current_location->exits + 0);
    else if (bool_location_is_full(PLAYER->current_location->exits[0].to))
        print_location_is_full();
    else
        cross_passage(PLAYER->current_location->exits + 0);
    return;
}

static void go_outside(void)
{
    int i, j;
    int outside_indexes[NBR_LOCATIONS];

    if (PLAYER->current_location->type == LOCATION_TYPE_OUTSIDE)
    {
        add_output("You're already outside.\n\n");
        memset(command.object, 0, sizeof(command.object));
        return;
    }

    memset(outside_indexes, -1, sizeof(outside_indexes));
    for (i = 0, j = 0; i < NBR_LOCATIONS; ++i)
    {
        if (!PLAYER->current_location->exits[i].to)
        {
            memset(command.object, 0, sizeof(command.object));
            break;
        }

        if (PLAYER->current_location->exits[i].to->type != LOCATION_TYPE_BUILDING)
            continue;

        outside_indexes[j++] = i;
    }

    if (outside_indexes[0] == -1)
    {
        add_output("No immediate exit leads outside of the building.\n\n");
        memset(command.object, 0, sizeof(command.object));
        return;
    }
    else if (outside_indexes[1] == -1)
    {
        if (bool_access_locked(PLAYER->current_location->exits + outside_indexes[0]))
            print_access_locked(PLAYER->current_location->exits + outside_indexes[0]);
        else if (bool_location_is_full(PLAYER->current_location->exits[outside_indexes[0]].to))
            print_location_is_full();
        else
            cross_passage(PLAYER->current_location->exits + outside_indexes[0]);
    }
    else
    {
        add_output("Different exits lead outside. Specify the one you want.\n\n");
        memset(command.object, 0, sizeof(command.object));
        return;
    }
    return;
}

static void go_back(void)
{
    int i;

    if (!PLAYER->previous_location)
    {
        add_output("You do not have a previous location.\n\n");
        memset(command.object, 0, sizeof(command.object));
        return;
    }

    for (i = 0; i < NBR_LOCATIONS; ++i)
    {
        if (!PLAYER->previous_location->exits[i].to)
        {
            add_output("Your previous location cannot be accessed.\n\n");
            memset(command.object, 0, sizeof(command.object));
            return;
        }
        else if (PLAYER->current_location == PLAYER->previous_location->exits[i].to)
            break;
        else if (PLAYER->current_location->inside_of == PLAYER->previous_location->exits[i].to)
            break;
    }

    if (bool_access_locked(PLAYER->previous_location->exits + i))
        print_access_locked(PLAYER->previous_location->exits + i);
    else if (bool_location_is_full(PLAYER->previous_location))
        print_location_is_full();
    /*
    TODO: This is not right, because cross_passage() will lead us back to our current location, aka no movement.
            But, if I try to rework the code so that it works, then it will be very complex with the shenanigans 
            going on with the buildings. So I need to refactor the building thing first.

    else
        cross_passage(PLAYER->previous_location->exits + i);
    */
    return;
}

static void go_out(void)
{
    int i, j, k;
    Exit* accessible_exits[NBR_LOCATIONS] = {0};
    Exit* locked_exits[NBR_LOCATIONS] = {0};

    if (PLAYER->current_location->type == LOCATION_TYPE_OUTSIDE)
    {
        add_output("You are already outside.\n\n");
        memset(command.object, 0, sizeof(command.object));
        return;
    }

    for (i = 0, j = 0, k = 0; i < NBR_LOCATIONS; ++i)
    {
        if (!PLAYER->current_location->exits[i].to)
            break;
        else if (PLAYER->current_location->exits[i].passage->access != ACCESS_LOCKED)
            accessible_exits[j++] = &(PLAYER->current_location->exits[i]);
        else
            locked_exits[k++] = &(PLAYER->current_location->exits[i]);
    }

    if (j == 1)
        cross_passage(accessible_exits[0]);
    else if (k == 1)
        print_access_locked(locked_exits[0]);
    else
    {
        add_output("There is more than one exit. Which one do you want?\n");
        memset(command.object, 0, sizeof(command.object));
    }

    return;
}

static void go_tag(void)
{
    int bool_tag_is_passage_item = 0;
    Exit** locations = NULL;

    locations = retrieve_locations(PLAYER->current_location, command.object);
    if (!locations || !locations[0])
    {
        locations = retrieve_locations_with_passage_item(PLAYER->current_location, command.object);
        if (!locations || !locations[0])
        {
            memset(command.object, 0, sizeof(command.object));
            free(locations);
            return;
        }
        else
            bool_tag_is_passage_item = 1;
    }

    if (!locations[1])
    {
        if (bool_access_locked(locations[0]))
            print_access_locked(locations[0]);
        else if (bool_location_is_full(locations[0]->to))
            print_location_is_full();
        else
            cross_passage(locations[0]);
    }
    else if (bool_tag_is_passage_item)
    {
        add_output("There is more than one passage item in your vicinity for which this tag works.\n");
        memset(command.object, 0, sizeof(command.object));
    }
    else
    {
        add_output("There is more than one destination from your current location for which this tag works.\n");
        memset(command.object, 0, sizeof(command.object));
    }

    free(locations);
    return;
}

/* TODO: Can't de-nest without a building/location refactoring */
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

    add_output("\n\n");
    event_first_time_player_enters_mansion();
    return;
}

static int bool_access_locked(const Exit* exit)
{
    return exit->passage->access == ACCESS_LOCKED;
}

static void print_access_locked(const Exit* exit)
{
    add_output("The %s %s locked.\n\n", exit->passage->is_singular ? "door" : "doors", exit->passage->is_singular ? "is" : "are");
    return;
}

static int bool_location_is_full(const Location* location)
{
    return location->characters[NBR_CHARACTERS - 1] != NULL;
}

static void print_location_is_full(void)
{
    add_output("The destination is full. No more characters can access this place.\n\n");
    return;
}

