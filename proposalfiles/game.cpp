//Taya Mamenko
//301649208
//ENSC 251: Software Design and Analysis for Engineers
//virus.exe Game Class

#include "game.hpp" //include Game class
#include "gameui.hpp" //include GameUI class
#include <stdexcept> //for reporting errors

using namespace std;

Game::Game(
    const string& player1Name,
    const string& player2Name,
    GameUI& gameUI)
    : player1(player1Name), //create first player
      player2(player2Name), //create second player
      deck(), //create game deck
      ui(gameUI), //store interface reference
      currentPlayer(1), //first player starts
      gameOver(false), //game is not finished
      winner(""), //no winner yet
      turnsCompleted(0) //no turns completed
{
}

Player& Game::getCurrentPlayer() { //get current player
    if (currentPlayer == 1) { //check first player
        return player1; //return first player
    }
    else { //second player's turn
        return player2; //return second player
    }
}

Player& Game::getPlayer(int playerNumber) { //get selected player
    if (playerNumber == 1) { //check first player
        return player1; //return first player
    }
    else if (playerNumber == 2) { //check second player
        return player2; //return second player
    }

    throw out_of_range("Invalid player number"); //reject number
}

Deck& Game::getDeck() { //get game deck
    return deck; //return deck reference
}

bool Game::drawCard() { //draw one card
    if (gameOver) { //check if game ended
        return false; //cannot draw after game ends
    }

    if (getCurrentPlayer().isHandFull()) { //check hand limit
        return false; //maximum 5 cards in hand
    }

    if (deck.isEmpty()) { //check remaining cards
        return false; //deck has no cards
    }

    Card card = deck.drawTopCard(); //take top card

    return getCurrentPlayer().addCard(card); //add card to hand
}

bool Game::isValidMove(int cardIndex) { //check selected card
    if (gameOver) { //check game status
        return false; //game already ended
    }

    Player& player = getCurrentPlayer(); //get current player

    if (cardIndex < 0) { //check negative index
        return false; //invalid card index
    }

    if (cardIndex >= player.getHandSize()) { //check hand size
        return false; //card is not in hand
    }

    const Card& card = player.getHand().at(cardIndex); //get card

    //TODO: find component matching card suit
    //TODO: identify attack, healing, or shield card
    //TODO: check if the target component is destroyed
    //TODO: reject a move when its target is invalid

    //requires Card and System component interfaces
    (void)card; //avoid unused variable warning

    return true; //card index is valid
}

void Game::applyCardEffect(const Card& card) { //apply card effect

    //TODO: find component matching card suit
    //TODO: use opponent component for attack cards
    //TODO: use current player component for healing and shields

    //cards 2-10 deal damage equal to card rank
    //Jack restores 2 HP to own component
    //Queen restores 4 HP to own component
    //King restores 6 HP to own component
    //Ace activates shield for one turn

    //TODO: use actual Card, System, and Component methods
    (void)card; //avoid unused variable warning

    throw logic_error(
        "Card effects are not integrated yet"
    ); //prevent playing a card without applying its effect
}

bool Game::playCard(int cardIndex) { //play selected card
    if (!isValidMove(cardIndex)) { //check selected move
        return false; //reject invalid move
    }

    Player& player = getCurrentPlayer(); //get current player

    Card card = player.getHand().at(cardIndex); //copy card

    applyCardEffect(card); //apply card effect before removal

    Card removedCard = card; //store removed card

    if (!player.removeCard(cardIndex, removedCard)) { //remove card
        return false; //card removal failed
    }

    deck.discardCard(removedCard); //move card to discard pile

    return true; //card played successfully
}

void Game::removeExpiredShields() { //remove expired shields

    //TODO: check current player's components
    //TODO: find shields activated during previous turn
    //TODO: remove expired shields at start of owner's turn

    //requires System and Component interfaces
}

void Game::checkWinner() { //check if game ended

    bool player1Destroyed =
        player1.isSystemDestroyed(); //check first system

    bool player2Destroyed =
        player2.isSystemDestroyed(); //check second system

    if (player1Destroyed && player2Destroyed) { //both destroyed
        winner = "Draw"; //game ends in draw
        gameOver = true; //finish game
        return; //stop checking
    }

    if (player1Destroyed) { //first system destroyed
        winner = player2.getName(); //second player wins
        gameOver = true; //finish game
        return; //stop checking
    }

    if (player2Destroyed) { //second system destroyed
        winner = player1.getName(); //first player wins
        gameOver = true; //finish game
        return; //stop checking
    }

    if (deck.isEmpty()) { //check empty deck
        int hp1 = player1.getTotalHP(); //first player HP
        int hp2 = player2.getTotalHP(); //second player HP

        if (hp1 > hp2) { //first player has more HP
            winner = player1.getName(); //first player wins
        }
        else if (hp2 > hp1) { //second player has more HP
            winner = player2.getName(); //second player wins
        }
        else { //equal remaining HP
            winner = "Draw"; //game ends in draw
        }

        gameOver = true; //finish game
    }
}

void Game::nextTurn() { //switch to next player
    if (gameOver) { //check if game finished
        return; //stop turn switching
    }

    turnsCompleted++; //record completed turn

    if (currentPlayer == 1) { //first player's turn ended
        currentPlayer = 2; //switch to second player
    }
    else { //second player's turn ended
        checkWinner(); //check winner after full round

        if (gameOver) { //check if game ended
            return; //stop switching players
        }

        currentPlayer = 1; //switch to first player
    }

    removeExpiredShields(); //update shield status
}

void Game::playTurn() { //handle current player's turn

    Player& player = getCurrentPlayer(); //get current player

    ui.displayTurn(player.getName()); //show current player

    ui.displayComponents(
        player1.getName(), //first player's name
        player1.getTotalHP() //first player's HP
    );

    ui.displayComponents(
        player2.getName(), //second player's name
        player2.getTotalHP() //second player's HP
    );

    ui.displayHand(player.getHandSize()); //show player hand

    bool canDraw =
        !player.isHandFull() && !deck.isEmpty(); //check draw action

    bool canPlay = player.hasCards(); //check play action

    ui.displayTurnMenu(canDraw, canPlay); //show actions

    int choice =
        ui.getTurnChoice(canDraw, canPlay); //read action

    if (choice == 0) { //no action available
        ui.displayMessage("No actions available."); //show message
        nextTurn(); //skip turn
        return; //finish action
    }

    if (choice == 1) { //player chooses to draw
        if (drawCard()) { //attempt to draw
            ui.displayMessage("Card drawn successfully."); //confirm
            nextTurn(); //finish turn
        }
        else { //draw failed
            ui.displayMessage("Cannot draw card."); //show error
        }

        return; //finish action
    }

    if (choice == 2) { //player chooses to play
        int cardIndex =
            ui.getCardChoice(player.getHandSize()); //select card

        if (playCard(cardIndex)) { //attempt to play card
            ui.displayMessage("Card played successfully."); //confirm
            nextTurn(); //finish turn
        }
        else { //invalid card
            ui.displayMessage("Invalid move. Try again."); //show error
        }

        return; //finish action
    }
}

GameResult Game::getResult() const { //get final game result
    if (!gameOver) { //check game status
        throw logic_error("Game is not finished"); //reject request
    }

    if (winner == "Draw") { //check draw
        return GameResult::Draw; //return draw result
    }

    if (winner == player1.getName()) { //check first player
        return GameResult::Player1Win; //return first player win
    }

    if (winner == player2.getName()) { //check second player
        return GameResult::Player2Win; //return second player win
    }

    throw logic_error("Unknown game result"); //reject unknown result
}

GameResult Game::startGame() { //start a new game

    currentPlayer = 1; //first player starts
    gameOver = false; //reset game status
    winner = ""; //clear previous winner
    turnsCompleted = 0; //reset turn counter

    deck = Deck(); //create fresh deck
    deck.shuffle(); //shuffle cards

    for (int i = 0; i < 5; i++) { //deal starting hands

        if (!deck.isEmpty()) { //check remaining cards
            Card card = deck.drawTopCard(); //draw first card
            player1.addCard(card); //give card to first player
        }

        if (!deck.isEmpty()) { //check remaining cards
            Card card = deck.drawTopCard(); //draw second card
            player2.addCard(card); //give card to second player
        }
    }

    while (!gameOver) { //continue until game ends
        playTurn(); //handle current player's action
    }

    return getResult(); //return final result to main
}

bool Game::isGameOver() const { //check game status
    return gameOver; //return true if game finished
}

string Game::getWinner() const { //get winning player
    return winner; //return winner name or draw
}
