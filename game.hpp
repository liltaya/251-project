//Taya Mamenko
//301649208
//ENSC 251: Software Design and Analysis for Engineers
//virus.exe Game Class Header

#ifndef GAME_HPP
#define GAME_HPP

#include <string> //for player names
#include "player.hpp" //include Player class
#include "deck.hpp" //include Deck class
#include "card.hpp" //include Card class

using namespace std;

class GameUI; //forward declaration of GameUI class

enum class GameResult { //possible game results
    Player1Win, //first player wins
    Player2Win, //second player wins
    Draw //game ends in draw
};

class Game { //manage game rules and turns

private:
    Player player1; //first player
    Player player2; //second player
    Deck deck; //game deck
    GameUI& ui; //game interface
    int currentPlayer; //current player number
    bool gameOver; //game status
    string winner; //winning player name
    int turnsCompleted; //completed turns
    GameResult finalResult; //final result

    bool isValidMove(int cardIndex); //check selected card
    void applyCardEffect(const Card& card); //apply card effect
    void removeExpiredShields(); //remove old shields
    void checkWinner(); //check game result
    void playTurn(); //handle player turn
    GameResult getResult() const; //return final result

public:
    Game(
        const string& player1Name,
        const string& player2Name,
        GameUI& gameUI
    ); //create game

    GameResult startGame(); //start game
    Player& getCurrentPlayer(); //get active player
    Player& getPlayer(int playerNumber); //get selected player
    Deck& getDeck(); //get game deck
    bool addCard(); //draw one card
    bool removeCard(int cardIndex); //play selected card
    void nextTurn(); //switch players
    bool isGameOver() const; //check game status
    string getWinner() const; //get winner name
};

#endif
