#include "../headers/play.h"
#include "../headers/parser.h"
#include "../headers/characters.h"
#include "../headers/locations.h"

int input_yes_no(void)
{
    int i;
    char input[4] = {0};
    while (strcmp(input, "yes") && strcmp(input, "no"))
    {
        write_line("> ");
        if (fgets(input, 4, stdin))
        {
            for (i = 0; i < 4; ++i)
            {
                if (input[i] == '\n')
                {
                    input[i] = '\0';
                    break;
                }
                input[i] = tolower(input[i]);
            }
        }
        flush_stdin();
        write_line("\r");
    }
    return strcmp(input, "no");
}

int static_mini_game(const char* mini_game_name, const char* character)
{
    add_output("\n\t[Do you want to play %s with the %s? Yes/No]\n\n", mini_game_name, character);
    if (!input_yes_no())
        return EXIT_SUCCESS;
    return start_twenty_squares();
}

int dynamic_mini_game(const char* mini_game_name, const char* character)
{
    LIB_HANDLE mini_game_obj = NULL;
    int (*mini_game_func)() = NULL;
    int mini_game_result = EXIT_FAILURE;

    add_output("\n\t[Do you want to play %s with the %s? Yes/No]\n\n", mini_game_name, character);
    if (!input_yes_no())
        return EXIT_SUCCESS;

    mini_game_obj = LOAD_LIB(LIB_PATH_TWENTY_SQUARES);
    if (!mini_game_obj)
    {
        add_output("\n\t[Error: The %s library can't be loaded -> %s]\n", mini_game_name, LIB_ERROR);
        return EXIT_FAILURE;
    }

    #ifdef _WIN32
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wpedantic"
    #endif
    *(void **) (&mini_game_func) = LIB_FUNC(mini_game_obj, "start_twenty_squares");
    #ifdef _WIN32
        #pragma GCC diagnostic pop
    #endif
    if (!mini_game_func)
    {
        add_output("\n\t[Error: The pointer to the %s library start function can't be obtained -> %s]\n", mini_game_name, LIB_ERROR);
        UNLOAD_LIB(mini_game_obj);
        return EXIT_FAILURE;
    }

    mini_game_result = (*mini_game_func)();

    UNLOAD_LIB(mini_game_obj);

    return mini_game_result;
}

void execute_play(void)
{
    int i;
    int exit_mini_game = EXIT_FAILURE;
    char* mini_game_name = "Twenty Squares";

    for (i = 0; i < NBR_CHARACTERS; ++i)
    {
        if (!PLAYER->current_location->characters[i])
        {
            add_output("\nYou see no one around you to play with.\n\n");
            break;
        }

        if (PLAYER->current_location->characters[i] == PLAYER)
            continue;

        exit_mini_game = static_mini_game(mini_game_name, PLAYER->current_location->characters[i]->tags[1]);
        if (exit_mini_game == EXIT_FAILURE)
            add_output("\n\t[Error: Something went wrong with the '%s' mini-game.]\n", mini_game_name);

        LOCATION_NAME
        describe_location(PLAYER->current_location);
        add_output("\n\n");
        break;
    }

    return;
}

