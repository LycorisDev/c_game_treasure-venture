#include "../headers/main.h"
#include "../headers/input.h"
#include "../headers/commands.h"
#include "../headers/initialize.h"
#include "../headers/save.h"

/* Declared as extern in ../headers/main.h */
char *parser[MAX_NBR_WORDS];
int nbr_words_in_parser;

int main(void)
{
    access_main_menu(0);
    while (1)
    {
        set_parser_with_input();

        if (parser[0] == NULL || strcmp(parser[0], "menu") != 0)
        {
            parse_game_command();
        }
        else
        {
            if (parser[1] == NULL)
            {
                access_main_menu(1);
            }
            else if (strcmp(parser[1], "new") == 0)
            {
                execute_submenu_newgame();
            }
            else if (strcmp(parser[1], "load") == 0)
            {
                execute_submenu_loadgame(1);
            }
            else if (strcmp(parser[1], "save") == 0)
            {
                execute_submenu_save(1);
            }
            else if (strcmp(parser[1], "about") == 0)
            {
                execute_submenu_about(1);
            }
            else if (strcmp(parser[1], "quit") == 0)
            {
                clear_terminal();
                return EXIT_SUCCESS;
            }
        }
    }
    /* This return statement shouldn't be accessible. */
    return EXIT_FAILURE;
}

void set_parser_with_input(void)
{
    int i;
    char *token = NULL;
    char input[MAX_SIZE] = {0};
    memset(parser, 0, sizeof(parser));
    nbr_words_in_parser = 0;
    printf("> ");
    if (fgets(input, MAX_SIZE, stdin) != NULL)
    {
        if (input[0] == '\n')
            return;
        for (i = 0; i < MAX_SIZE; ++i)
        {
            if (input[i] == '\0')
                break;
            input[i] = tolower(input[i]);
        }

        token = strtok(input, DELIMETERS);
        while (token != NULL)
        {
            parser[nbr_words_in_parser++] = token;
            token = strtok (NULL, DELIMETERS);
        }
    }
    flush_stdin();
    return;
}

void access_main_menu(const int has_game_begun)
{
    int can_exit_main_menu = 0;
    clear_terminal();
    printf("\n\t[During the game, type 'Menu' to go back to the main menu.]\n");
    while (!can_exit_main_menu)
    {
        printf("\n\t 'New Game'    'Load Game'    'Save'    'About'    'Quit'\n\n");
        set_parser_with_input();

        if (parser[0] != NULL)
        {
            if (strcmp(parser[0], "new") == 0)
            {
                can_exit_main_menu = execute_submenu_newgame();
            }
            else if (strcmp(parser[0], "load") == 0)
            {
                can_exit_main_menu = execute_submenu_loadgame(has_game_begun);
            }
            else if (strcmp(parser[0], "save") == 0)
            {
                can_exit_main_menu = execute_submenu_save(has_game_begun);
            }
            else if (strcmp(parser[0], "about") == 0)
            {
                execute_submenu_about(0);
            }
            else if (strcmp(parser[0], "quit") == 0)
            {
                clear_terminal();
                exit(EXIT_SUCCESS);
            }
        }
    }
    return;
}

int execute_submenu_newgame(void)
{
    int can_exit_main_menu = 1;
    FILE* save_file = NULL;
    initialize_game(save_file);
    clear_terminal();
    printf("\n\t[A new game will start...]\n");

    if ((save_file = fopen("save.txt", "r")))
    {
        printf("\t[The save file still exists.]\n");
        fclose(save_file);
    }

    sleep(1);
    clear_terminal();
    printf("%s\n\n", PLAYER->current_location->description);
    return can_exit_main_menu;
}

int execute_submenu_loadgame(const int has_game_begun)
{
    int can_exit_main_menu = 1;
    FILE* save_file = NULL;

    if ((save_file = fopen("save.txt", "r")))
    {
        initialize_game(save_file);
        fclose(save_file);
        printf("\n\t[Your saved game will resume...]\n\n");
    }
    else
    {
        if (!has_game_begun)
            initialize_game(save_file);
        printf("\n\t[No save could be found.]\n");
        has_game_begun ? printf("\t[The current game will resume...]\n\n") : printf("\t[A new game will start...]\n\n");
    }

    sleep(1);
    clear_terminal();
    printf("%s\n\n", PLAYER->current_location->description);
    return can_exit_main_menu;
}

int execute_submenu_save(const int has_game_begun)
{
    int can_exit_main_menu = 0;
    FILE* save_file = NULL;

    if (has_game_begun == 0)
        printf("\n\t[A game needs to be started for it to be saved.]\n");
    else
    {
        can_exit_main_menu = 1;
        save_file = fopen("save.txt", "w+");
        save_game(save_file);
        fclose(save_file);
        printf("\n\t[Game saved!]\n\n");
        printf("%s\n\n", PLAYER->current_location->description);
    }
    return can_exit_main_menu;
}

void execute_submenu_about(const int is_game_ongoing)
{
    printf("\n\t[\"Prototype RPG\" is part of a VRMMORPG project named Persistence.]\n\t[This MMO is not done in one go, but one small game after another, Prototype being the first of them.]\n\t[The goal is to develop most of the gameplay, and possibly the lore as well, in a non-graphic manner.]\n\t[Once no more improvement can be made in this format, the work on the audiovisual aspect of the game will begin.]\n\n");
    printf("\t[For more information, visit my channel:]\n\thttps://www.youtube.com/channel/UCowO_RtloSQ3qnKmvymsBRA/\n");

    if (is_game_ongoing)
        printf("\n%s\n\n", PLAYER->current_location->description);
    return;
}

