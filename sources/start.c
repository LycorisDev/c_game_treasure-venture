#include "../headers/start.h"
#include "../headers/parser.h"
#include "../headers/commands.h"
#include "../headers/initialize.h"
#include "../headers/save.h"
#include "../headers/locations.h"

#include "../headers/output.h"

#define STATE_MENU 0
#define STATE_GAME 1
static int game_state = STATE_MENU;
static int is_game_ongoing = 0;

static void execute_menu_command(const char* command);
static void execute_submenu_new(void);
static void execute_submenu_load(void);
static void execute_submenu_save(void);
static void execute_submenu_about(void);
static void execute_submenu_quit(void);

static const KeyFunc command_list[] = 
{
    {"about", &execute_submenu_about},
    {"load", &execute_submenu_load},
    {"new", &execute_submenu_new},
    {"quit", &execute_submenu_quit},
    {"save", &execute_submenu_save},
    {NULL, &access_main_menu}
};

void interact(void)
{
    if (yes_no_callback != NULL)
    {
        parse_yes_no();
    }
    else if (game_state == STATE_MENU)
    {
        execute_menu_command(parser[0]);
    }
    else
    {
        if (!parser[0])
            display_game_commands();
        else if (strcmp(parser[0], "menu"))
            execute_game_command();
        else
            execute_menu_command(parser[1]);
    }
    return;
}

static void execute_menu_command(const char* command)
{
    int i = 0;

    if (!*command)
    {
        access_main_menu();
        return;
    }

    while (command_list[i].key != NULL)
    {
        if (!strcmp(command, command_list[i].key))
        {
            command_list[i].func();
            return;
        }
        ++i;
    }

    command_list[i].func();
    return;
}

void access_main_menu(void)
{
    game_state = STATE_MENU;
    reset_output();
    add_output("\t-[ TREASURE VENTURE ]-\n\n");
    add_output("\t[During the game, type 'Menu' to go back to the main menu.]\n\n");
    add_output("\t 'New Game'    'Load Game'    'Save'    'About'    'Quit'\n\n");
    return;
}

static void execute_submenu_new(void)
{
    FILE* save_file = NULL;

    initialize_game(save_file);
    reset_output();
    add_output("\t[A new game will start...]\n");
    if ((save_file = fopen("save.txt", "r")))
    {
        add_output("\t[The save file still exists.]\n");
        fclose(save_file);
    }
    add_output("\n");

    game_state = STATE_GAME;
    is_game_ongoing = 1;
    describe_location(PLAYER->current_location);
    return;
}

static void execute_submenu_load(void)
{
    FILE* save_file = NULL;

    reset_output();

    if ((save_file = fopen("save.txt", "r")))
    {
        initialize_game(save_file);
        fclose(save_file);
        add_output("\t[Your saved game will resume...]\n\n");
    }
    else
    {
        add_output("\t[No save could be found.]\n");
        if (is_game_ongoing)
            add_output("\t[The current game will resume...]\n\n");
        else
        {
            add_output("\t[A new game will start...]\n\n");
            initialize_game(save_file);
        }
    }

    game_state = STATE_GAME;
    is_game_ongoing = 1;
    describe_location(PLAYER->current_location);
    return;
}

static void execute_submenu_save(void)
{
    FILE* save_file = NULL;

    if (!is_game_ongoing)
    {
        add_output("\t[A game needs to be started for it to be saved.]\n\n");
        return;
    }

    save_file = fopen("save.txt", "w+");
    save_game(save_file);
    fclose(save_file);
    add_output("\t[Game saved!]\n\n");

    if (game_state == STATE_GAME)
        describe_location(PLAYER->current_location);
    return;
}

static void execute_submenu_about(void)
{
    add_output("\t[\"Treasure Venture\" is a text adventure. A text adventure game is a game that is interacted with through written commands, and which only displays written text. There is no graphical element.]\n\n");
    add_output("\t[This project differs from a classic text adventure in that \"Treasure Venture\" offers suggestions when the player is lost. Since this reveals the plot, it's usually considered as spoiling the player's enjoyment. Even so, I've allowed myself to make the handling of the game more accessible, which I hope will make for a bigger playerbase and therefore increase my chances of receiving critiques on my work.]\n\n");
    add_output("\t[\"Treasure Venture\" understands several commands, can save the ongoing game, and has events. An event example is to have the doors lock up behind the player when they cross the mansion's threshold for the first time. It also contains a mini-game entitled \"Twenty Squares\", that I leave you to discover as well as the game itself.]\n\n");
    add_output("\t[For more information, visit my channel:]\n\thttps://www.youtube.com/@thelycorisradiata/\n\n");

    if (game_state == STATE_GAME)
        describe_location(PLAYER->current_location);
    return;
}

static void execute_submenu_quit(void)
{
    close_window();
    return;
}

