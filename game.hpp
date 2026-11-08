
//Taya Mamenko
//301649208
//ENSC 251: Software Design and Analysis for Engineers
//virus.exe Game Class
#ifndef GAME_HPP
#define GAME_HPP

#include <string> //for storing game result
#include "player.hpp" //include Player class
#include "deck.hpp" //include Deck class
#include "card.hpp" //include Card class

using namespace std;

class Game {
private:
    Player player1; //store first player
    Player player2; //store second player
    Deck deck; //store game deck
    int currentPlayer; //track current player
    bool gameOver; //check if game ended
    string winner; //store winner name

    bool isValidMove(int cardIndex); //check selected card
    void applyCardEffect(Card card); //apply card effect
    void checkWinner(); //check game result
    void removeExpiredShields(); //remove old shields

public:
    Game(); //default constructor

    void startGame(); //start new game
    Player& getCurrentPlayer(); //get current player
    Player& getPlayer(int playerNumber); //get selected player
    Deck& getDeck(); //get game deck

    bool drawCard(); //draw card from deck
    bool playCard(int cardIndex); //play selected card
    void nextTurn(); //switch players

    bool isGameOver() const; //check if game ended
    string getWinner() const; //get game winner
};

#endif
