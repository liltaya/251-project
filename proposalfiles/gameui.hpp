//Taya Mamenko
//301649208
//ENSC 251: Software Design and Analysis for Engineers
//virus.exe GameUI Class

#ifndef GAMEUI_HPP
#define GAMEUI_HPP

#include <string> //for storing player names and messages

using namespace std;

enum class GameResult; //forward declare game result

class GameUI {
private:
    int getValidInput(int min, int max); //validate user input

public:
    GameUI(); //default constructor

    void displayTitleScreen(); //show main menu
    int getMenuChoice(); //read main menu choice
    string getPlayerName(int playerNumber); //read player name
    void displayRules(); //show game rules

    void displayGameResult(GameResult result); //show winner
    void displayGameEndMenu(); //show replay and quit options
    int getGameEndChoice(); //read replay choice
    void displayInvalidInput(); //show invalid input message
    void displayGoodbye(); //show program ending

    void displayTurn(const string& playerName); //show current turn
    void displayComponents(
        const string& playerName,
        int totalHP); //show player HP
    void displayHand(int handSize); //show number of cards
    void displayTurnMenu(
        bool canDraw,
        bool canPlay); //show available actions

    int getTurnChoice(
        bool canDraw,
        bool canPlay); //read turn action

    int getCardChoice(int handSize); //read selected card
    void displayMessage(const string& message); //show message
};

#endif
