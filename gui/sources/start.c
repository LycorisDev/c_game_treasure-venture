#include "../headers/start.h"
#include "../headers/main.h"
#include "../headers/commands.h"
#include "../headers/initialize.h"
#include "../headers/save.h"
#include "../headers/locations.h"

void interact(void)
{
    access_main_menu(0);
    while (1)
    {
        set_parser_with_input();

        if (!parser[0] || strcmp(parser[0], "menu"))
        {
            parse_game_command();
        }
        else
        {
            if (!parser[1])
            {
                access_main_menu(1);
            }
            else if (!strcmp(parser[1], "new"))
            {
                execute_submenu_newgame();
            }
            else if (!strcmp(parser[1], "load"))
            {
                execute_submenu_loadgame(1);
            }
            else if (!strcmp(parser[1], "save"))
            {
                execute_submenu_save(1);
            }
            else if (!strcmp(parser[1], "about"))
            {
                execute_submenu_about(1);
            }
            else if (!strcmp(parser[1], "quit"))
            {
                reset_output();
                close_window();
                return;
            }
            else
            {
                access_main_menu(1);
            }
        }
    }
    /* This return statement shouldn't be accessible. */
    return;
}

void access_main_menu(const int has_game_begun)
{
    int can_exit_main_menu = 0;

    reset_output();
    add_output("\n\t[During the game, type 'Menu' to go back to the main menu.]\n");

    while (!can_exit_main_menu)
    {
        add_output("\n\t 'New Game'    'Load Game'    'Save'    'About'    'Quit'\n\n");
        set_parser_with_input();

        if (parser[0])
        {
            if (!strcmp(parser[0], "new"))
            {
                can_exit_main_menu = execute_submenu_newgame();
            }
            else if (!strcmp(parser[0], "load"))
            {
                can_exit_main_menu = execute_submenu_loadgame(has_game_begun);
            }
            else if (!strcmp(parser[0], "save"))
            {
                can_exit_main_menu = execute_submenu_save(has_game_begun);
            }
            else if (!strcmp(parser[0], "about"))
            {
                execute_submenu_about(0);
            }
            else if (!strcmp(parser[0], "quit"))
            {
                reset_output();
                close_window();
                return;
            }
            else
            {
                reset_output();
                add_output("\n\t[During the game, type 'Menu' to go back to the main menu.]\n");
            }
        }
        else
        {
            reset_output();
            add_output("\n\t[During the game, type 'Menu' to go back to the main menu.]\n");
        }
    }
    return;
}

int execute_submenu_newgame(void)
{
    int can_exit_main_menu = 1;
    FILE* save_file = NULL;
    initialize_game(save_file);
    reset_output();
    write_line("\n\t[A new game will start...]\n");

    if ((save_file = fopen("save.txt", "r")))
    {
        write_line("\t[The save file still exists.]\n");
        fclose(save_file);
    }

    sleep(1);
    reset_output();
    LOCATION_NAME
    describe_location(PLAYER->current_location);
    write_line("\n\n");
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
        write_line("\n\t[Your saved game will resume...]\n\n");
    }
    else
    {
        if (!has_game_begun)
            initialize_game(save_file);
        write_line("\n\t[No save could be found.]\n");
        has_game_begun ? write_line("\t[The current game will resume...]\n\n") : write_line("\t[A new game will start...]\n\n");
    }

    sleep(1);
    CLEAR_TERMINAL
    LOCATION_NAME
    describe_location(PLAYER->current_location);
    write_line("\n\n");
    return can_exit_main_menu;
}

int execute_submenu_save(const int has_game_begun)
{
    int can_exit_main_menu = 0;
    FILE* save_file = NULL;

    if (!has_game_begun)
        write_line("\n\t[A game needs to be started for it to be saved.]\n");
    else
    {
        can_exit_main_menu = 1;
        save_file = fopen("save.txt", "w+");
        save_game(save_file);
        fclose(save_file);
        write_line("\n\t[Game saved!]\n");
        LOCATION_NAME
        describe_location(PLAYER->current_location);
        write_line("\n\n");
    }
    return can_exit_main_menu;
}

void execute_submenu_about(const int is_game_ongoing)
{
    write_line("\n\t[\"Treasure Venture\" is a text adventure. A text adventure game is a game that is interacted with through written commands, and which only displays written text. There is no graphical element.]\n");
    write_line("\n\t[This project differs from a classic text adventure in that \"Treasure Venture\" offers suggestions when the player is lost. Since this reveals the plot, it's usually considered as spoiling the player's enjoyment. Even so, I've allowed myself to make the handling of the game more accessible, which I hope will make for a bigger playerbase and therefore increase my chances of receiving critiques on my work.]\n");
    write_line("\n\t[\"Treasure Venture\" understands several commands, can save the ongoing game, and has events. An event example is to have the doors lock up behind the player when they cross the mansion's threshold for the first time. It also contains a mini-game entitled \"Twenty Squares\", that I leave you to discover as well as the game itself.]\n");
    write_line("\n\t[For more information, visit my channel:]\n\thttps://www.youtube.com/@thelycorisradiata/\n");

    if (is_game_ongoing)
    {
        LOCATION_NAME
        describe_location(PLAYER->current_location);
        write_line("\n\n");
    }
    return;
}

