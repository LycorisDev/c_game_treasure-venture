#include "../headers/use.h"
#include "../headers/commands.h"
#include "../headers/items.h"
#include "../headers/characters.h"

void execute_use(void)
{
    int i, used_item_id = ID_ITEM_NONE;
    SameTag* items_with_same_tag_in_inventory = NULL;
    SameTag* items_with_same_tag_in_current_location = NULL;

    if (PLAYER->inventory[0] == ID_ITEM_NONE && PLAYER->current_location->list_of_items_by_id[0] == ID_ITEM_NONE)
    {
        printf("\nThere is nothing for you to use.\n\n");
    }
    else
    {
        if (strcmp(command.object, "") != 0)
        {
            items_with_same_tag_in_inventory = retrieve_item_id_by_parser_from_inventory(command.object);
            items_with_same_tag_in_current_location = retrieve_item_id_by_parser_from_current_location(command.object);

            if (items_with_same_tag_in_inventory[0].id == ID_ITEM_NONE && items_with_same_tag_in_current_location[0].id == ID_ITEM_NONE)
                memcpy(command.object, "", BIG_LENGTH_WORD);
            else if (items_with_same_tag_in_inventory[0].id != ID_ITEM_NONE && items_with_same_tag_in_current_location[0].id == ID_ITEM_NONE)
            {
                if (items_with_same_tag_in_inventory[1].id == ID_ITEM_NONE)
                {
                    used_item_id = items_with_same_tag_in_inventory[0].id;
                }
                else
                {
                    printf("\nThere is more than one item in your inventory for which this tag works.\n");
                }
            }
            else if (items_with_same_tag_in_inventory[0].id == ID_ITEM_NONE && items_with_same_tag_in_current_location[0].id != ID_ITEM_NONE)
            {
                if (items_with_same_tag_in_current_location[1].id == ID_ITEM_NONE)
                {
                    used_item_id = items_with_same_tag_in_current_location[0].id;
                }
                else
                {
                    printf("\nThere is more than one item in your vicinity for which this tag works.\n");
                }
            }
            else
            {
                printf("\nYour inventory and vicinity both included, there is more than one item for which this tag works.\n");
            }

            if (!used_item_id)
            {
                memcpy(command.object, "", BIG_LENGTH_WORD);
            }
            else if (list_items[used_item_id].access != ACCESS_NONE)
            {
                for (i = 0; i < NBR_LOCATIONS; ++i)
                {
                    if (PLAYER->current_location->exits[i].to == LOCATION_NONE)
                    {
                        memcpy(command.object, "", BIG_LENGTH_WORD);
                        break;
                    }
                    else if (PLAYER->current_location->exits[i].passage == (list_items + used_item_id))
                    {
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
                        else
                        {
                            memcpy(command.object, "", BIG_LENGTH_WORD);
                        }
                        break;
                    }
                }
            }
            else if (list_items[used_item_id].requires_target_for_use)
            {
                if (strcmp(command.preposition, "on") != 0 || strcmp(command.target, "") == 0)
                {
                    printf("\n\t[The %s %s a target. Try specifying on who or what you want to use %s.]\n\n", 
                            command.object, list_items[used_item_id].is_singular ? "requires" : "require", list_items[used_item_id].is_singular ? "it" : "them");
                }
                else
                {
                    use_item_on_target(used_item_id);
                }
            }
            else
            {
                printf("\n%s ", list_items[used_item_id].description_brief);
                printf("The %s %s seem to be of much use.\n\n", command.object, list_items[used_item_id].is_singular ? "doesn't" : "don't");
            }
        }
    }

    if (strcmp(command.object, "") == 0)
    {
        printf("\n\t[Try:]\n");
        for (i = 0; i < NBR_ITEMS; ++i)
        {
            if (PLAYER->inventory[i] == ID_ITEM_NONE)
                break;
            printf("\t\t['Use %s'.]\n", list_items[PLAYER->inventory[i]].tags[0]);
        }
        for (i = 0; i < NBR_ITEMS; ++i)
        {
            if (PLAYER->current_location->list_of_items_by_id[i] == ID_ITEM_NONE)
                break;
            printf("\t\t['Use %s'.]\n", list_items[PLAYER->current_location->list_of_items_by_id[i]].tags[0]);
        }
        printf("\n");
    }

    free(items_with_same_tag_in_inventory);
    free(items_with_same_tag_in_current_location);
    return;
}

void use_item_on_target(const int used_item_id)
{
    int target_id = 0, is_target_a_character = 0;
    SameTag* items_with_same_tag_in_current_location = retrieve_item_id_by_parser_from_current_location(command.target);
    SameTag* characters_with_same_tag_in_current_location = retrieve_character_id_by_parser_from_current_location(command.target);

    if (items_with_same_tag_in_current_location[0].id == ID_ITEM_NONE && characters_with_same_tag_in_current_location[0].id == ID_CHARACTER_NONE)
    {
        memcpy(command.target, "", BIG_LENGTH_WORD);
    }
    else if (items_with_same_tag_in_current_location[0].id != ID_ITEM_NONE && characters_with_same_tag_in_current_location[0].id == ID_CHARACTER_NONE)
    {
        if (items_with_same_tag_in_current_location[1].id == ID_ITEM_NONE)
        {
            target_id = items_with_same_tag_in_current_location[0].id;
            is_target_a_character = 0;
        }
        else
        {
            printf("\nThere is more than one item in your vicinity for which this tag works.\n\n");
        }
    }
    else if (items_with_same_tag_in_current_location[0].id == ID_ITEM_NONE && characters_with_same_tag_in_current_location[0].id != ID_CHARACTER_NONE)
    {
        if (characters_with_same_tag_in_current_location[1].id == ID_ITEM_NONE)
        {
            target_id = characters_with_same_tag_in_current_location[0].id;
            is_target_a_character = 1;
        }
        else
        {
            printf("\nThere is more than one character in your vicinity for which this tag works.\n\n");
        }
    }
    else
    {
        printf("\nThere is more than target in your vicinity for which this tag works.\n\n");
    }

    if (!target_id)
    {
        printf("\n\t[Use the %s on what?]\n\n", command.object);
    }
    else if (is_target_a_character)
    {
        if (target_id == ID_CHARACTER_PLAYER)
            printf("\nThe %s %s nothing to you.\n\n", command.object, list_items[used_item_id].is_singular ? "does" : "do");
        else
            printf("\nThe %s %s nothing to the %s.\n\n", command.object, list_items[used_item_id].is_singular ? "does" : "do", list_characters[target_id].tags[0]);
    }
    else if (list_items[target_id].access != ACCESS_NONE && list_items[target_id].unlocked_with == used_item_id)
    {
        switch (list_items[target_id].access)
        {
            case ACCESS_LOCKED:
                list_items[target_id].access = ACCESS_CLOSED;
                printf("\nYou unlock the %s.\n\n", list_items[target_id].is_singular ? "door" : "doors");
                break;
            case ACCESS_OPEN:
                list_items[target_id].access = ACCESS_LOCKED;
                printf("\nYou close and lock the %s.\n\n", list_items[target_id].is_singular ? "door" : "doors");
                break;
            case ACCESS_CLOSED:
                list_items[target_id].access = ACCESS_LOCKED;
                printf("\nYou lock the %s.\n\n", list_items[target_id].is_singular ? "door" : "doors");
                break;
        }
    }
    else
    {
        printf("\nThe %s %s nothing to the %s.\n\n", command.object, list_items[used_item_id].is_singular ? "does" : "do", list_items[target_id].tags[0]);
    }

    free(items_with_same_tag_in_current_location);
    free(characters_with_same_tag_in_current_location);
    return;
}

