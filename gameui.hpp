//Taya Mamenko
//301649208
//ENSC 251: Software Design and Analysis for Engineers
//virus.exe GameUI Class Header

#ifndef GAMEUI_HPP
#define GAMEUI_HPP

#include <string> //for player names and messages

using namespace std;

class Player; //forward declaration of Player class
enum class GameResult; //forward declaration of game result

class GameUI { //manage game interface

private:
    int getValidInput(int min, int max); //validate user input

public:
    GameUI(); //create game interface

    void displayTitleScreen(); //show main menu
    int getMenuChoice(); //read main menu choice
    string getPlayerName(int playerNumber); //read player name
    void displayRules(); //show game rules
    void displayGameResult(GameResult result); //show winner
    void displayGameEndMenu(); //show replay menu
    int getGameEndChoice(); //read replay choice
    void displayInvalidInput(); //show input error
    void displayGoodbye(); //show exit message

    void displayTurn(const string& playerName); //show current turn

    void displayComponents(
        const string& playerName,
        int totalHP
    ); //show player health

    void displayHand(int handSize); //show hand size

    void displayTurnMenu(
        bool canDraw,
        bool canPlay
    ); //show available actions

    int getTurnChoice(
        bool canDraw,
        bool canPlay
    ); //read player action

    int getCardChoice(int handSize); //read selected card

    void displayMessage(
        const string& message
    ); //show game message

    void displaySystem(const Player& player); //show components
    void displayCards(const Player& player); //show hand cards
};

#endif
