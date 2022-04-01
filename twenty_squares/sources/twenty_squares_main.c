#include "../headers/twenty_squares_main.h"
#include "../headers/twenty_squares_turn.h"
#include "../../headers/input.h"

int execute_twenty_squares(const char* character)
{
    char input[INPUT_SIZE];

    char prompt_player_wants_to_play[150] = "\n\t[Do you want to play Twenty Squares with the ";
    strcat(prompt_player_wants_to_play, character);
    get_string_input(input, "yes_no", prompt_player_wants_to_play, "? Yes/No]");
    if (strcmp(input, "no") == 0)
        return EXIT_SUCCESS;

    clear_terminal();
    printf("TWENTY SQUARES\n\n");
    printf("This mini-game is based upon the oldest game known to mankind: a five millenia old mesopotamian board game, known today as the Game of Twenty Squares or the Royal Game of Ur.\n");
    printf("Its purpose is to provide a \"classic\" version of the game, as well as a new take on it, that exploits possibilities brought by a computer.\n");
    printf("On these notes, I reserve special thanks to Irving Finkel of the British Museum and Tom Scott, who was his guest in the Museum's introductory video on the Royal Game of Ur. This video is how I came to learn of the game, and I've used the simple rules described in it to make the first level.\n\n");

    get_string_input(input, "yes_no", "Do you know the rules of the game?", "Yes/No");
    if (strcmp(input, "no") == 0)
    {
        clear_terminal();
        printf("GUIDE - PAGE 1/3\n\n");
        printf("The Twenty Squares is a board game where two players face each other using, well... A board, and also stones and a dice from 0 to 4. The goal is to bring each of our seven stones beyond the finish line.\n");

        printf("                                                       \n");
        printf("             ___ ___ ___               ___ ___ ___     \n");
        printf("            |▒▒▒|   |▒▒▒|             | 4 | 5 |   |    \n");
        printf("            |▒▒▒|___|▒▒▒|             |___|___|___|    \n");
        printf("            |   |   |   |             | 3 | 6 |   |    \n");
        printf("            |___|___|___|             |___|___|___|    \n");
        printf("            |   |   |   |             | 2 | 7 |   |    \n");
        printf("            |___|___|___|             |___|___|___|    \n");
        printf("            |   |▒▒▒|   |             | 1 | 8 |   |    \n");
        printf("            |___|▒▒▒|___|             |___|___|___|    \n");
        printf("        ooooooo |   | ooooooo     ooooooo | 9 | ooooooo\n");
        printf("                |___|                     |___|        \n");
        printf("              x |   | x                 x |10 | x      \n");
        printf("             ___|___|___               ___|___|___     \n");
        printf("            |▒▒▒|   |▒▒▒|             |14 |11 |   |    \n");
        printf("            |▒▒▒|___|▒▒▒|             |___|___|___|    \n");
        printf("            |   |   |   |             |13 |12 |   |    \n");
        printf("            |___|___|___|             |___|___|___|    \n\n\n");

        printf("Let's take a look at the drawing on the left. The players begin and end the race on their own side of the board. Left for Player One, right for Player Two. On the drawing above, the stones are placed before their respective first cells. The 'x' marks the objective. The middle road is where the players meet and fight. On the right drawing, Player One's path has been detailed. Each turn, the dice is thrown and the result is the number of board cells forwards a stone can go, for one stone per cell. The turn");
        /* printf(): Virtually cut in half because of the ANSI length requirement of a maximum of 509 characters */
        printf(" passes if the dice lands on 0 or if no stone can move. Stepping onto a cell occupied by an enemy stone makes you capture it, unless... See the gray cells on the left drawing? They are Special Cells and deliver abilities to the stones standing on them. The abilities are named after the four elements.\n\n");
        printf("What do these abilities do, and can the stones move less than the dice throw? To find out, let's see the different levels!\n\n");
        press_enter_to_continue();

        clear_terminal();
        printf("GUIDE - PAGE 2/3\n\n");
        printf("Level 1: Classic Infinite.\n");
        printf("Level 2: Classic Dispatch.\n");
        printf("Level 3: Deadly Sins Infinite.\n");
        printf("Level 4: Deadly Sins Dispatch.\n\n");
        printf("The words 'Infinite' and 'Dispatch' are the first thing to pay attention to. In Infinite levels, captured stones return to their player's homebase, while in Dispatch ones they get straight up killed. This difference changes the way a game is won. While in Infinite levels the winner is whoever first runs out of stones, in Dispatch levels we experience a system a points. A stone beyond the finish line is +1 point, and a stone killed is -1. Once a player gets rid of all their stones, the game ends, the poin");
        /* printf(): Virtually cut in half because of the ANSI length requirement of a maximum of 509 characters */
        printf("ts are counted, and the winner is determined.\n\n");
        printf("'Classic' and 'Deadly Sins,' on the other hand, refer to the stones' movements and the abilities. In Classic levels, the stones can only move up to the dice throw, and the abilities are automatically used upon receiving. Classic levels have two abilities, always given together: Air and Earth. Air gives the player a free turn, while Earth protects the stone as long as it stands still or as long as Water is not used against it.\n\n");
        printf("In Deadly Sins levels, the four abilities are available, but only one at a time, and the stone is responsible for whether they are used, discarded, or the decision let to the player. Lust, Pride, Envy and Greed leave the decision to the player, while Gluttony uses it, Sloth discards, and as for Wrath, it discards or uses it depending on which ability it is.\n\n");
    printf("As for the effect of the last two abilities, Water and Fire: from 1 to the dice throw result, Water lets you select stones to bring back to their respective homebases. Fire, however, kills the enemy stone of our choice. Of course, in Infinite this means the stone goes back to homebase.\n\n");
            printf("When it comes to the Deadly Sins stones movements, the dice throw is a range, not a finality. How does each stone pick their cell?\n\n");
        press_enter_to_continue();

        clear_terminal();
        printf("GUIDE - PAGE 3/3\n\n");
        printf("Lust has eyes only for you. It listens to everything you say and will go to the cell you pick.\n\n");
        printf("Pride doesn't do well with orders. It rejects what you picked and goes where it wants. It can also refuse to move just to be a bother.\n\n");
        printf("Gluttony doesn't think. It just goes the farthest it can.\n\n");
        printf("Sloth would rather be asleep. But since it doesn't have Pride's force of will, it can't remain immobile, and so picks the closest cell allowed.\n\n");
        printf("Envy lacks a personality of its own. It goes all over the place, not able to settle for a pattern. The cell is picked at random.\n\n");
        printf("Wrath is a slave to bloodlust. When it notices an enemy stone on the board, it targets it with an unyielding focus, ready to step upon allies to see the enemy perish. The rest of the time, it moves to the closest available cell as to stick around longer: this way, it has more chance of meeting the other team.\n\n");
        printf("Greed follows a set of priorities: the closest Special Cell, then the closest enemy, and finally the finish line. The reason it lets you decide what to do with the ability, is because it doesn't know how to use what it gathered. There's no personal purpose to its hoarding, but hopefully it'll help you win.\n\n");
        press_enter_to_continue();
    }

    start_game(input);

    clear_terminal();
    return EXIT_SUCCESS;
}

