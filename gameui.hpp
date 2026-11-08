//Taya Mamenko
//301649208
//ENSC 251: Software Design and Analysis for Engineers
//virus.exe Game Class
#ifndef GAMEUI_HPP
#define GAMEUI_HPP

#include <iostream> //for input and output
#include "game.hpp" //include Game class

using namespace std;

class GameUI {
private:
    Game game; //store game object

    int getValidInput(int min, int max); //validate user input
    void showTurnMenu(); //show player actions

public:
    GameUI(); //default constructor

    void showMenu(); //show main menu
    void showRules(); //show game rules
    void showGame(); //show game status
    void showHand(); //show player cards
    void showComponents(); //show component HP

    int getMenuChoice(); //read menu choice
    int getCardChoice(); //read card choice

    void showWinner(); //show winner
    void run(); //run game interface
};

#endif
