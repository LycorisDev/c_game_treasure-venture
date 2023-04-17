#include "../headers/start.h"
#include "../headers/parser.h"
#include "../headers/commands.h"
#include "../headers/initialize.h"
#include "../headers/save.h"
#include "../headers/locations.h"

#define STATE_MENU 0
#define STATE_GAME 1
static int game_state = STATE_MENU;

static void execute_submenu_newgame(void);
static void execute_submenu_loadgame(void);
static void execute_submenu_save(void);
static void execute_submenu_about(void);

void interact(void)
{
    if (game_state == STATE_MENU)
    {
        if (!parser[0])
        {
            access_main_menu();
        }
        else if (!strcmp(parser[0], "new"))
        {
            execute_submenu_newgame();
        }
        else if (!strcmp(parser[0], "load"))
        {
            execute_submenu_loadgame();
        }
        else if (!strcmp(parser[0], "save"))
        {
            execute_submenu_save();
        }
        else if (!strcmp(parser[0], "about"))
        {
            execute_submenu_about();
        }
        else if (!strcmp(parser[0], "quit"))
        {
            close_window();
            return;
        }
        else
        {
            access_main_menu();
        }
    }
    else
    {
        if (!parser[0] || strcmp(parser[0], "menu"))
        {
            parse_game_command();
        }
        else
        {
            if (!parser[1])
            {
                access_main_menu();
            }
            else if (!strcmp(parser[1], "new"))
            {
                execute_submenu_newgame();
            }
            else if (!strcmp(parser[1], "load"))
            {
                execute_submenu_loadgame();
            }
            else if (!strcmp(parser[1], "save"))
            {
                execute_submenu_save();
            }
            else if (!strcmp(parser[1], "about"))
            {
                execute_submenu_about();
            }
            else if (!strcmp(parser[1], "quit"))
            {
                close_window();
                return;
            }
            else
            {
                access_main_menu();
            }
        }
    }

    return;
}

void access_main_menu(void)
{
    game_state = STATE_MENU;
    reset_output();
    add_output("\n\t[During the game, type 'Menu' to go back to the main menu.]\n");
    add_output("\n\t 'New Game'    'Load Game'    'Save'    'About'    'Quit'\n\n");
    return;
}

static void execute_submenu_newgame(void)
{
    FILE* save_file = NULL;
    initialize_game(save_file);
    reset_output();
    add_output("\n\t[A new game will start...]\n");

    if ((save_file = fopen("save.txt", "r")))
    {
        add_output("\t[The save file still exists.]\n");
        fclose(save_file);
    }

    sleep(1);
    reset_output();
    game_state = STATE_GAME;

    LOCATION_NAME
    describe_location(PLAYER->current_location);
    add_output("\n\n");
    return;
}

static void execute_submenu_loadgame(void)
{
    FILE* save_file = NULL;

    if ((save_file = fopen("save.txt", "r")))
    {
        initialize_game(save_file);
        fclose(save_file);
        add_output("\n\t[Your saved game will resume...]\n\n");
    }
    else
    {
        if (game_state != STATE_GAME)
            initialize_game(save_file);
        add_output("\n\t[No save could be found.]\n");
        game_state == STATE_GAME ? add_output("\t[The current game will resume...]\n\n") : add_output("\t[A new game will start...]\n\n");
    }

    sleep(1);
    reset_output();
    game_state = STATE_GAME;

    LOCATION_NAME
    describe_location(PLAYER->current_location);
    add_output("\n\n");
    return;
}

static void execute_submenu_save(void)
{
    FILE* save_file = NULL;

    if (game_state != STATE_GAME)
        add_output("\t[A game needs to be started for it to be saved.]\n");
    else
    {
        save_file = fopen("save.txt", "w+");
        save_game(save_file);
        fclose(save_file);
        add_output("\n\t[Game saved!]\n");

        LOCATION_NAME
        describe_location(PLAYER->current_location);
        add_output("\n\n");
    }
    return;
}

static void execute_submenu_about(void)
{
    add_output("\n\t[\"Treasure Venture\" is a text adventure. A text adventure game is a game that is interacted with through written commands, and which only displays written text. There is no graphical element.]\n");
    add_output("\n\t[This project differs from a classic text adventure in that \"Treasure Venture\" offers suggestions when the player is lost. Since this reveals the plot, it's usually considered as spoiling the player's enjoyment. Even so, I've allowed myself to make the handling of the game more accessible, which I hope will make for a bigger playerbase and therefore increase my chances of receiving critiques on my work.]\n");
    add_output("\n\t[\"Treasure Venture\" understands several commands, can save the ongoing game, and has events. An event example is to have the doors lock up behind the player when they cross the mansion's threshold for the first time. It also contains a mini-game entitled \"Twenty Squares\", that I leave you to discover as well as the game itself.]\n");
    add_output("\n\t[For more information, visit my channel:]\n\thttps://www.youtube.com/@thelycorisradiata/\n");

    if (game_state == STATE_GAME)
    {
        LOCATION_NAME
        describe_location(PLAYER->current_location);
        add_output("\n\n");
    }
    return;
}

