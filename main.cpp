/******************************************************************
 * 
 * public functions used:
 * 
 *  from GameUI Class:
 *     void displayTitleScreen();
 *     int getMenuChoice();
 *     string getPlayerName(int playerNumber);
 *     void displayRules();
 *     void displayGameResult(GameResult result);
 *     void displayGameEndMenu();
 *     int getGameEndChoice();
 *     void displayInvalidInput();
 *     void displayGoodbye();
 * 
 *  from Game Class:
 *    Game(string player1Name, string player2Name, GameUI& ui);
 *    GameResult startGame();
 * 
*******************************************************************/

/***********************************************************************************
 * 
 * class dependencies flow chart:
 * 
 * 
 *             GameUI
 *  
 *  main()
 *                          Player(2) ---->   Card
 *             Game ---->   Deck              System ---->  Component(4)
 *                  b       Card
 *                          GameUI
 * 
*************************************************************************************/

// ---------------------------------------------------------------------------------------------------

/*****************************************************************
 * Simon Fraser University
 * ENSC 251 - Software Design and Analysis for Engineers
 * Project - virus.exe
 *
 * main.cpp - houses the main() function
 * 
 * Author: Vijeta Dhalla, 301644330
 * 
*******************************************************************/

#include <iostream>
#include "game.hpp"
#include "gameui.hpp"

int main()
{
    // creates GameUI
    GameUI ui;

    bool running = true;

    // game loop that continues until the user chooses to quit
    while (running == true)
    {
        // display title screen w start, rules, and quit options
        ui.displayTitleScreen();

        // user's menu selection
        int choice = ui.getMenuChoice();

        // 2 = game rules
        if (choice == 2)
        {
            ui.displayRules();

            // back to title
            continue;
        }

        // 1 = start game
        else if (choice == 1)
        {

            // creates Game object
            // do we want player names? currently just "Player 1" and "Player 2"
            Game game("Player 1", "Player 2", ui);

            // starts game
            GameResult result = game.startGame();

            // displays end condtion (win, lose, draw, etc.)
            ui.displayGameResult(result);

            // prompts replay or quit
            ui.displayGameEndMenu();

            int endChoice = ui.getGameEndChoice();

            // 1 = replay
            if (endChoice == 1)
            {
                // return to start of loop
                continue;
            }

            // 2 = quit
            else if (endChoice == 2)
            {
                running = false;
            }
        }

        // 3 = quit
        else if (choice == 3)
        {
            running = false;
        }

        // invalid inputs
        else
        {
            ui.displayInvalidInput();
        }
    }

    // end / quitting program screen
    ui.displayGoodbye();

    return 0;
}