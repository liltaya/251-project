
 //Taya Mamenko
 //301649208
 //ENSC 251: Software Design and Analysis for Engineers
 //virus.exe Game Class

#ifndef GAME_HPP
#define GAME_HPP

#include <string> //for storing player names and game result
#include "player.hpp" //include Player class
#include "deck.hpp" //include Deck class
#include "card.hpp" //include Card class

using namespace std;

class GameUI; //forward declare GameUI class

enum class GameResult { //store possible game results
    Player1Win, //first player wins
    Player2Win, //second player wins
    Draw //game ends in a draw
};

class Game {
private:
    Player player1; //stores first player
    Player player2; //store second player
    Deck deck; //store game deck
    GameUI& ui; //store reference to game interface
    int currentPlayer; //track current player
    bool gameOver; //check if game ended
    string winner; //store winner name
    int turnsCompleted; //track completed turns

    bool isValidMove(int cardIndex); //check selected card
    void applyCardEffect(const Card& card); //apply card effect
    void checkWinner(); //check game result
    void removeExpiredShields(); //remove old shields
    void playTurn(); //handle current player's action
    GameResult getResult() const; //convert winner to result

public:
    Game(const string& player1Name,
         const string& player2Name,
         GameUI& gameUI); //create game with two players

    GameResult startGame(); //start game and return result
    Player& getCurrentPlayer(); //get current player
    Player& getPlayer(int playerNumber); //get selected player
    Deck& getDeck(); //get game deck

    bool addCard(); //draw card from deck
    bool removeCard(int cardIndex); //play selected card
    void nextTurn(); //switch players

    bool isGameOver() const; //check if game ended
    string getWinner() const; //get game winner
};

#endif
