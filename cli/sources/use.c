#include "../headers/use.h"
#include "../headers/output.h"
#include "../headers/commands.h"
#include "../headers/items.h"
#include "../headers/characters.h"

static void use_item_on_target(const Item* used_item);

void execute_use(void)
{
    int i;
    Item* used_item = NULL;
    Item** items_with_same_tag_in_inventory = NULL;
    Item** items_with_same_tag_in_current_location = NULL;

    if (!PLAYER->inventory[0] && !PLAYER->current_location->items[0])
    {
        write_line("\nThere is nothing for you to use.\n\n");
    }
    else
    {
        if (*command.object)
        {
            items_with_same_tag_in_inventory = retrieve_items_by_parser_from_inventory(command.object);
            items_with_same_tag_in_current_location = retrieve_items_by_parser_from_current_location(command.object);

            if (!items_with_same_tag_in_inventory[0] && !items_with_same_tag_in_current_location[0])
                memset(command.object, 0, sizeof(command.object));
            else if (items_with_same_tag_in_inventory[0] && !items_with_same_tag_in_current_location[0])
            {
                if (!items_with_same_tag_in_inventory[1])
                {
                    used_item = items_with_same_tag_in_inventory[0];
                }
                else
                {
                    write_line("\nThere is more than one item in your inventory for which this tag works.\n");
                }
            }
            else if (!items_with_same_tag_in_inventory[0] && items_with_same_tag_in_current_location[0])
            {
                if (!items_with_same_tag_in_current_location[1])
                {
                    used_item = items_with_same_tag_in_current_location[0];
                }
                else
                {
                    write_line("\nThere is more than one item in your vicinity for which this tag works.\n");
                }
            }
            else
            {
                write_line("\nYour inventory and vicinity both included, there is more than one item for which this tag works.\n");
            }

            if (!used_item)
            {
                memset(command.object, 0, sizeof(command.object));
            }
            else if (used_item->access)
            {
                for (i = 0; i < NBR_LOCATIONS; ++i)
                {
                    if (!PLAYER->current_location->exits[i].to)
                    {
                        memset(command.object, 0, sizeof(command.object));
                        break;
                    }
                    else if (PLAYER->current_location->exits[i].passage == used_item)
                    {
                        if (PLAYER->current_location->exits[i].passage->access == ACCESS_LOCKED)
                        {
                            write_line("\nThe %s %s locked.\n\n", used_item->is_singular ? "door" : "doors", used_item->is_singular ? "is" : "are");
                        }
                        else if (PLAYER->current_location->exits[i].passage->access == ACCESS_OPEN)
                        {
                            PLAYER->current_location->exits[i].passage->access = ACCESS_CLOSED;
                            write_line("\nYou close the %s.\n\n", used_item->is_singular ? "door" : "doors");
                        }
                        else if (PLAYER->current_location->exits[i].passage->access == ACCESS_CLOSED)
                        {
                            PLAYER->current_location->exits[i].passage->access = ACCESS_OPEN;
                            write_line("\nYou open the %s.\n\n", used_item->is_singular ? "door" : "doors");
                        }
                        else
                        {
                            memset(command.object, 0, sizeof(command.object));
                        }
                        break;
                    }
                }
            }
            else if (used_item->requires_target_for_use)
            {
                if (strcmp(command.preposition, "on") || !*command.target)
                {
                    write_line("\n\t[The %s %s a target. Try specifying on who or what you want to use %s.]\n\n", 
                            command.object, used_item->is_singular ? "requires" : "require", used_item->is_singular ? "it" : "them");
                }
                else
                {
                    use_item_on_target(used_item);
                }
            }
            else
            {
                write_line("\n%s ", used_item->description_brief);
                write_line("The %s %s seem to be of much use.\n\n", used_item->tags[1], used_item->is_singular ? "doesn't" : "don't");
            }
        }
    }

    if (!*command.object)
    {
        write_line("\n\t[Try:]\n");
        for (i = 0; i < NBR_ITEMS; ++i)
        {
            if (!PLAYER->inventory[i])
                break;
            write_line("\t\t['Use %s'.]\n", PLAYER->inventory[i]->tags[0]);
        }
        for (i = 0; i < NBR_ITEMS; ++i)
        {
            if (!PLAYER->current_location->items[i])
                break;
            write_line("\t\t['Use %s'.]\n", PLAYER->current_location->items[i]->tags[0]);
        }
        write_line("\n");
    }

    free(items_with_same_tag_in_inventory);
    free(items_with_same_tag_in_current_location);
    return;
}

static void use_item_on_target(const Item* used_item)
{
    int is_target_a_character = 0;
    Item** items_with_same_tag_in_current_location = retrieve_items_by_parser_from_current_location(command.target);
    Character** characters_with_same_tag_in_current_location = retrieve_characters_by_parser_from_current_location(command.target);
    /* Can be either "Item*" or "Character*": */
    void* target = NULL;

    if (!items_with_same_tag_in_current_location[0] && !characters_with_same_tag_in_current_location[0])
    {
        memset(command.target, 0, sizeof(command.target));
    }
    else if (items_with_same_tag_in_current_location[0] && !characters_with_same_tag_in_current_location[0])
    {
        if (!items_with_same_tag_in_current_location[1])
        {
            target = items_with_same_tag_in_current_location[0];
            is_target_a_character = 0;
        }
        else
        {
            write_line("\nThere is more than one item in your vicinity for which this tag works.\n\n");
        }
    }
    else if (!items_with_same_tag_in_current_location[0] && characters_with_same_tag_in_current_location[0])
    {
        if (!characters_with_same_tag_in_current_location[1])
        {
            target = characters_with_same_tag_in_current_location[0];
            is_target_a_character = 1;
        }
        else
        {
            write_line("\nThere is more than one character in your vicinity for which this tag works.\n\n");
        }
    }
    else
    {
        write_line("\nThere is more than target in your vicinity for which this tag works.\n\n");
    }

    if (!target)
    {
        write_line("\n\t[Use the %s on what?]\n\n", command.object);
    }
    else if (is_target_a_character)
    {
        if (target == PLAYER)
            write_line("\nThe %s %s nothing to you.\n\n", used_item->tags[1], used_item->is_singular ? "does" : "do");
        else
            write_line("\nThe %s %s nothing to the %s.\n\n", used_item->tags[1], used_item->is_singular ? "does" : "do", ((Character*)target)->tags[1]);
    }
    else if (((Item*)target)->access && ((Item*)target)->unlocked_with == used_item)
    {
        switch (((Item*)target)->access)
        {
            case ACCESS_LOCKED:
                ((Item*)target)->access = ACCESS_CLOSED;
                write_line("\nYou unlock the %s.\n\n", ((Item*)target)->is_singular ? "door" : "doors");
                break;
            case ACCESS_OPEN:
                ((Item*)target)->access = ACCESS_LOCKED;
                write_line("\nYou close and lock the %s.\n\n", ((Item*)target)->is_singular ? "door" : "doors");
                break;
            case ACCESS_CLOSED:
                ((Item*)target)->access = ACCESS_LOCKED;
                write_line("\nYou lock the %s.\n\n", ((Item*)target)->is_singular ? "door" : "doors");
                break;
        }
    }
    else
    {
        write_line("\nThe %s %s nothing to the %s.\n\n", used_item->tags[1], used_item->is_singular ? "does" : "do", ((Item*)target)->tags[1]);
    }

    free(items_with_same_tag_in_current_location);
    free(characters_with_same_tag_in_current_location);
    return;
}

