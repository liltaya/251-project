
//Taya Mamenko
//301649208
//ENSC 251: Software Design and Analysis for Engineers
//virus.exe Game Class

#include "game.hpp" //include Game class

using namespace std;

Game::Game() { //default constructor starts new game
    currentPlayer = 1; //first player starts
    gameOver = false; //game is not finished
    winner = ""; //no winner yet
}

void Game::startGame() { //start a new game
    reset both players; //restore component HP
    reset deck; //create 52 cards
    deck.shuffle(); //shuffle the deck

    deal 5 cards to player1; //first player hand
    deal 5 cards to player2; //second player hand

    currentPlayer = 1; //first player starts
    gameOver = false; //reset game status
    winner = ""; //clear previous winner
}

Player& Game::getCurrentPlayer() { //get current player
    if (currentPlayer == 1) {
        return player1; //return first player
    }
    else {
        return player2; //return second player
    }
}

Player& Game::getPlayer(int playerNumber) { //get selected player
    if (playerNumber == 1) {
        return player1; //return first player
    }
    else {
        return player2; //return second player
    }
}

Deck& Game::getDeck() { //get game deck
    return deck; //return deck
}

bool Game::drawCard() { //draw one card
    if (gameOver) {
        return false; //cannot draw after game ends
    }

    if (getCurrentPlayer().getHandSize() >= 5) {
        return false; //maximum 5 cards in hand
    }

    if (deck.isEmpty()) {
        return false; //deck has no cards
    }

    Card card = deck.drawTopCard(); //take top card
    getCurrentPlayer().addCard(card); //add card to hand

    return true; //card drawn successfully
}

bool Game::isValidMove(int cardIndex) { //check if card can be played
    if (gameOver) {
        return false; //game already ended
    }

    if (cardIndex < 0) {
        return false; //invalid card index
    }

    if (cardIndex >= getCurrentPlayer().getHandSize()) {
        return false; //card is not in hand
    }

    Card card = getCurrentPlayer().getCard(cardIndex); //get card

    find component matching card suit; //select component

    if (card is an attack card) { //check attack card
        check opponent component; //find target

        if (component is destroyed) {
            return false; //cannot attack destroyed component
        }
    }
    else { //check healing or shield card
        check current player component; //find own component

        if (component is destroyed) {
            return false; //cannot restore destroyed component
        }
    }

    return true; //move is valid
}

void Game::applyCardEffect(Card card) { //apply card effect
    find component matching card suit; //select component

    if (card rank >= 2 && card rank <= 10) {
        int damage = card rank; //number cards deal damage

        find opponent component; //get attack target

        if (component has shield) {
            block damage; //shield protects component
        }
        else {
            decrease component HP by damage; //apply damage
        }
    }
    else if (card rank == 11) { //Jack card
        find current player component; //get own component
        increase component HP by 2; //heal 2 HP
    }
    else if (card rank == 12) { //Queen card
        find current player component; //get own component
        increase component HP by 4; //heal 4 HP
    }
    else if (card rank == 13) { //King card
        find current player component; //get own component
        increase component HP by 6; //heal 6 HP
    }
    else if (card rank == 1) { //Ace card
        find current player component; //get own component
        activate component shield; //protect for one turn
    }
}

bool Game::playCard(int cardIndex) { //play selected card
    if (!isValidMove(cardIndex)) {
        return false; //invalid move
    }

    Card card = getCurrentPlayer().getCard(cardIndex); //get card
    applyCardEffect(card); //apply card effect

    getCurrentPlayer().removeCard(cardIndex); //remove from hand
    deck.discardCard(card); //move card to discard pile

    return true; //card played successfully
}

void Game::removeExpiredShields() { //remove expired shields
    check current player components; //find active shields
    remove shields from previous turn; //end protection
}

void Game::nextTurn() { //switch to next player
    if (gameOver) {
        return; //game already ended
    }

    if (currentPlayer == 1) {
        currentPlayer = 2; //switch to second player
    }
    else {
        checkWinner(); //check game after full round

        if (gameOver) {
            return; //stop if game ended
        }

        currentPlayer = 1; //switch to first player
    }

    removeExpiredShields(); //update shield status
}

void Game::checkWinner() { //check if game ended
    bool player1Destroyed = check all player1 components; //first system
    bool player2Destroyed = check all player2 components; //second system

    if (player1Destroyed && player2Destroyed) {
        winner = "Draw"; //both systems destroyed
        gameOver = true; //end game
        return;
    }

    if (player1Destroyed) {
        winner = player2.getName(); //second player wins
        gameOver = true; //end game
        return;
    }

    if (player2Destroyed) {
        winner = player1.getName(); //first player wins
        gameOver = true; //end game
        return;
    }

    if (deck.isEmpty()) {
        int hp1 = get total player1 HP; //first player HP
        int hp2 = get total player2 HP; //second player HP

        if (hp1 > hp2) {
            winner = player1.getName(); //first player wins
        }
        else if (hp2 > hp1) {
            winner = player2.getName(); //second player wins
        }
        else {
            winner = "Draw"; //equal total HP
        }

        gameOver = true; //end game
    }
}

bool Game::isGameOver() const { //check game status
    return gameOver; //return true if game ended
}

string Game::getWinner() const { //get winning player
    return winner; //return winner name or draw
}
