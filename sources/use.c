#include "../headers/use.h"
#include "../headers/commands.h"
#include "../headers/items.h"
#include "../headers/characters.h"

void execute_use(void)
{
    int i, used_item_id = ID_ITEM_NONE;
    SameTag* items_with_same_tag_in_inventory = NULL;
    SameTag* items_with_same_tag_in_current_location = NULL;

    if (PLAYER->list_of_items_by_id[0] == ID_ITEM_NONE && PLAYER->current_location->list_of_items_by_id[0] == ID_ITEM_NONE)
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
                    /* TODO */
                    printf("\nThere is more than one item in your inventory for which this tag works.\n\n");
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
                    /* TODO */
                    printf("\nThere is more than one item in your vicinity for which this tag works.\n\n");
                }
            }
            else
            {
                /* TODO: items both in the inventory and the current location (at least one of each) */
                printf("\nYour inventory and vicinity both included, there is more than one item for which this tag works.\n\n");
            }

            if (!used_item_id)
                memcpy(command.object, "", BIG_LENGTH_WORD);
            else
            {
                if (used_item_id == ID_ITEM_ENTRY_DOORS_KEY)
                {
                    use_entry_doors_key(used_item_id);
                }
                else if (used_item_id == ID_ITEM_ENTRY_DOORS || used_item_id == ID_ITEM_LIBRARY_DOOR 
                        || used_item_id == ID_ITEM_DOOR_ROOM_1 || used_item_id == ID_ITEM_DOOR_ROOM_2 || used_item_id == ID_ITEM_DOOR_ROOM_3)
                {
                    use_door(used_item_id);
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
            printf("\n\t[Use what? Try:]\n");
            for (i = 0; i < NBR_ITEMS; ++i)
            {
                if (PLAYER->list_of_items_by_id[i] == ID_ITEM_NONE)
                    break;
                printf("\t\t['Use %s'.]\n", list_items[PLAYER->list_of_items_by_id[i]].tags[0]);
            }
            for (i = 0; i < NBR_ITEMS; ++i)
            {
                if (PLAYER->current_location->list_of_items_by_id[i] == ID_ITEM_NONE)
                    break;
                printf("\t\t['Use %s'.]\n", list_items[PLAYER->current_location->list_of_items_by_id[i]].tags[0]);
            }
            printf("\n");
        }
    }

    free(items_with_same_tag_in_inventory);
    free(items_with_same_tag_in_current_location);
    return;
}

void use_entry_doors_key(const int used_item_id)
{
    int i, target_id, is_target_a_character;
    SameTag* items_with_same_tag_in_current_location = NULL;
    SameTag* characters_with_same_tag_in_current_location = NULL;

    if (strcmp(command.preposition, "on") != 0 || strcmp(command.target, "") == 0)
    {
        printf("\n\t[The %s %s a target. Try specifying on who or what you want to use %s.]\n\n", 
                command.object, list_items[used_item_id].is_singular ? "requires" : "require", list_items[used_item_id].is_singular ? "it" : "them");
    }
    else if (strcmp(command.target, "") != 0)
    {
        items_with_same_tag_in_current_location = retrieve_item_id_by_parser_from_current_location(command.target);
        characters_with_same_tag_in_current_location = retrieve_character_id_by_parser_from_current_location(command.target);

        if (items_with_same_tag_in_current_location[0].id == ID_ITEM_NONE && characters_with_same_tag_in_current_location[0].id == ID_CHARACTER_NONE)
            memcpy(command.target, "", BIG_LENGTH_WORD);
        else if (items_with_same_tag_in_current_location[0].id != ID_ITEM_NONE && characters_with_same_tag_in_current_location[0].id == ID_CHARACTER_NONE)
        {
            if (items_with_same_tag_in_current_location[1].id == ID_ITEM_NONE)
            {
                target_id = items_with_same_tag_in_current_location[0].id;
                is_target_a_character = 0;
            }
            else
            {
                /* TODO */
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
                /* TODO */
                printf("\nThere is more than one character in your vicinity for which this tag works.\n\n");
            }
        }
        else
        {
            /* TODO: items and characters both in current location (at least one of each) */
            printf("\nThere is more than target in your vicinity for which this tag works.\n\n");
        }

        if (!used_item_id)
            memcpy(command.target, "", BIG_LENGTH_WORD);
        else if (is_target_a_character && target_id == ID_CHARACTER_PLAYER)
        {
            printf("\nThe %s %s nothing to you.\n\n", command.object, list_items[used_item_id].is_singular ? "does" : "do");
        }
        else if (!is_target_a_character && target_id == ID_ITEM_ENTRY_DOORS)
        {
            for (i = 0; i < NBR_ITEMS; ++i)
            {
                if (PLAYER->current_location->list_of_items_by_id[i] == ID_ITEM_NONE)
                {
                    memcpy(command.target, "", BIG_LENGTH_WORD);
                    break;
                }

                if (PLAYER->current_location->list_of_items_by_id[i] == ID_ITEM_ENTRY_DOORS)
                {
                    if (PLAYER->current_location->exits[0].passage->access == ACCESS_LOCKED)
                    {
                        printf("\nYou unlock the %s.\n\n", list_items[target_id].is_singular ? "door" : "doors");
                        PLAYER->current_location->exits[0].passage->access = ACCESS_CLOSED;
                    }
                    else
                    {
                        if (PLAYER->current_location->exits[0].passage->access == ACCESS_OPEN)
                            printf("\nYou close the %s.", list_items[target_id].is_singular ? "door" : "doors");
                        printf("\nYou lock the %s.\n\n", list_items[target_id].is_singular ? "door" : "doors");
                        PLAYER->current_location->exits[0].passage->access = ACCESS_LOCKED;
                    }
                    break;
                }
            }
        }

        if (strcmp(command.target, "") == 0)
        {
            printf("\n\t[Use the %s on what?]\n\n", command.object);
        }
    }

    free(items_with_same_tag_in_current_location);
    free(characters_with_same_tag_in_current_location);
    return;
}

void use_door(const int used_item_id)
{
    int i;
    for (i = 0; i < NBR_LOCATIONS; ++i)
    {
        if (PLAYER->current_location->exits[i].to == LOCATION_NONE)
            break;
        else if (PLAYER->current_location->exits[i].passage == (list_items + used_item_id))
        {
            EVENT_PLAYER_ENTERS_MANSION_FOR_THE_FIRST_TIME
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
            break;
        }
    }
    return;
}

