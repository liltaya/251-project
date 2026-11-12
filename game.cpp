//Taya Mamenko
//301649208
//ENSC 251: Software Design and Analysis for Engineers
//virus.exe Game Class

#include "game.hpp" //include Game class
#include "gameui.hpp" //include GameUI class
#include "computersystem.hpp" //include ComputerSystem class
#include "component.hpp" //include Component class
#include <stdexcept> //for reporting errors
#include <string> //for messages

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
      turnsCompleted(0), //no turns completed
      finalResult(GameResult::Draw) //default result
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

bool Game::addCard() { //draw one card
    if (gameOver) { //check game status
        return false; //cannot draw after game ends
    }

    Player& player = getCurrentPlayer(); //get current player

    if (player.isHandFull()) { //check hand limit
        return false; //maximum 5 cards
    }

    if (deck.isEmpty()) { //check remaining cards
        return false; //deck has no cards
    }

    return deck.drawCard(player); //draw card into hand
}

bool Game::isValidMove(int cardIndex) { //check selected card
    if (gameOver) { //check game status
        return false; //game already ended
    }

    Player& player = getCurrentPlayer(); //get current player

    if (cardIndex < 0) { //check negative index
        return false; //invalid card index
    }

    if (static_cast<size_t>(cardIndex) >=
        player.getHandSize()) { //check hand size
        return false; //card is not in hand
    }

    const Card& card =
        player.getHand().at(cardIndex); //get selected card

    if (card.getSuit() < 0 ||
        card.getSuit() > 3) { //check card suit
        return false; //invalid suit
    }

    int rank = card.getRank(); //get card rank

    if (rank < 1 || rank > 14) { //check valid rank range
        return false; //invalid rank
    }

    return true; //selected card is valid
}

void Game::applyCardEffect(const Card& card) { //apply card effect

    int suit = card.getSuit(); //get target component
    int rank = card.getRank(); //get card rank

    Player& current = getCurrentPlayer(); //get active player

    Player& opponent =
        currentPlayer == 1 ? player2 : player1; //get opponent

    if (rank >= 2 && rank <= 10) { //check attack card

        Component& target =
            opponent.getSystem().getComponent(suit); //opponent component

        if (target.isDestroyed()) { //check destroyed component
            ui.displayMessage(
                "Component already destroyed. Card discarded."
            ); //show no effect
            return; //finish effect
        }

        if (target.isShielded()) { //check active shield
            ui.displayMessage(
                "Firewall blocked the attack."
            ); //show blocked attack
            return; //no damage
        }

        int damage = target.takeDamage(rank); //apply damage

        ui.displayMessage(
            opponent.getName() + "'s " +
            target.getName() + " takes " +
            to_string(damage) + " damage."
        ); //show attack result

        if (target.isDestroyed()) { //check component HP
            ui.displayMessage(
                target.getName() + " has been destroyed."
            ); //show destruction
        }

        return; //finish attack
    }

    if (rank >= 11 && rank <= 13) { //check healing card

        Component& target =
            current.getSystem().getComponent(suit); //own component

        int healing = 0; //healing amount

        if (rank == 11) { //Jack card
            healing = 2; //restore 2 HP
        }
        else if (rank == 12) { //Queen card
            healing = 4; //restore 4 HP
        }
        else { //King card
            healing = 6; //restore 6 HP
        }

        if (target.isDestroyed()) { //check destroyed component
            ui.displayMessage(
                "Destroyed components cannot be healed."
            ); //show no effect
            return; //finish effect
        }

        int restored = target.heal(healing); //restore health

        ui.displayMessage(
            current.getName() + "'s " +
            target.getName() + " recovers " +
            to_string(restored) + " HP."
        ); //show healing result

        return; //finish healing
    }

    if (rank == 1 || rank == 14) { //check Ace card

        Component& target =
            current.getSystem().getComponent(suit); //own component

        if (target.isDestroyed()) { //check destroyed component
            ui.displayMessage(
                "Destroyed components cannot be shielded."
            ); //show no effect
            return; //finish effect
        }

        if (target.isShielded()) { //check existing shield
            ui.displayMessage(
                "Firewall already active."
            ); //shield does not stack
            return; //finish effect
        }

        target.activateShield(); //activate firewall

        ui.displayMessage(
            "Firewall activated on " +
            target.getName() + "."
        ); //show shield result

        return; //finish shield effect
    }

    throw logic_error("Invalid card rank"); //reject invalid card
}

bool Game::removeCard(int cardIndex) { //play selected card

    if (!isValidMove(cardIndex)) { //check selected move
        return false; //reject invalid move
    }

    Player& player = getCurrentPlayer(); //get active player

    Card card =
        player.getHand().at(cardIndex); //copy selected card

    Card removedCard = card; //store card to discard

    if (!player.removeCard(cardIndex, removedCard)) { //remove from hand
        return false; //card removal failed
    }

    deck.discardCard(removedCard); //move card to discard pile

    applyCardEffect(card); //apply selected card effect

    return true; //card played successfully
}

void Game::removeExpiredShields() { //remove expired shields

    getCurrentPlayer().getSystem().removeAllShields(); //clear own shields
}

void Game::checkWinner() { //check if game ended

    if (turnsCompleted % 2 != 0) { //check complete round
        return; //wait until both players finish
    }

    bool player1Destroyed =
        player1.isSystemDestroyed(); //check first system

    bool player2Destroyed =
        player2.isSystemDestroyed(); //check second system

    if (player1Destroyed && player2Destroyed) { //both destroyed
        winner = "Draw"; //game ends in draw
        finalResult = GameResult::Draw; //store result
        gameOver = true; //finish game
        return; //stop checking
    }

    if (player1Destroyed) { //first system destroyed
        winner = player2.getName(); //second player wins
        finalResult = GameResult::Player2Win; //store result
        gameOver = true; //finish game
        return; //stop checking
    }

    if (player2Destroyed) { //second system destroyed
        winner = player1.getName(); //first player wins
        finalResult = GameResult::Player1Win; //store result
        gameOver = true; //finish game
        return; //stop checking
    }

    bool noCardsRemaining =
        deck.isEmpty() && //check empty deck
        !player1.hasCards() && //check first hand
        !player2.hasCards(); //check second hand

    if (noCardsRemaining) { //all cards have been used

        int hp1 = player1.getTotalHP(); //first player HP
        int hp2 = player2.getTotalHP(); //second player HP

        if (hp1 > hp2) { //first player has more HP
            winner = player1.getName(); //first player wins
            finalResult = GameResult::Player1Win; //store result
        }
        else if (hp2 > hp1) { //second player has more HP
            winner = player2.getName(); //second player wins
            finalResult = GameResult::Player2Win; //store result
        }
        else { //equal remaining HP
            winner = "Draw"; //game ends in draw
            finalResult = GameResult::Draw; //store result
        }

        gameOver = true; //finish game
    }
}

void Game::nextTurn() { //switch to next player

    if (gameOver) { //check game status
        return; //game already finished
    }

    turnsCompleted++; //record completed turn

    if (currentPlayer == 1) { //first player's turn ended
        currentPlayer = 2; //switch to second player
    }
    else { //second player's turn ended

        checkWinner(); //check result after full round

        if (gameOver) { //check game status
            return; //stop switching players
        }

        currentPlayer = 1; //switch to first player
    }
}

void Game::playTurn() { //handle current player's turn

    removeExpiredShields(); //remove expired own shields

    Player& player = getCurrentPlayer(); //get current player

    ui.displayTurn(player.getName()); //show current turn

    ui.displaySystem(player1); //show first player's components
    ui.displaySystem(player2); //show second player's components

    ui.displayCards(player); //show current player's cards

    ui.displayMessage(
        "Cards remaining in deck: " +
        to_string(deck.cardsRemaining())
    ); //show remaining cards

    while (!gameOver) { //continue until valid action

        bool canDraw =
            !player.isHandFull() &&
            !deck.isEmpty(); //check draw availability

        bool canPlay = player.hasCards(); //check play availability

        if (!canDraw && !canPlay) { //check unavailable actions
            ui.displayMessage(
                "No actions available. Turn skipped."
            ); //show message

            nextTurn(); //finish turn
            return; //stop current turn
        }

        int choice =
            ui.getTurnChoice(canDraw, canPlay); //read action

        if (choice == 1) { //player chooses to draw

            if (addCard()) { //attempt to draw
                ui.displayMessage(
                    "Card drawn successfully."
                ); //confirm draw

                nextTurn(); //finish turn
                return; //stop current turn
            }

            ui.displayMessage(
                "Cannot draw a card. Try again."
            ); //show error
        }
        else if (choice == 2) { //player chooses to play

            int cardIndex =
                ui.getCardChoice(
                    static_cast<int>(player.getHandSize())
                ); //select card

            if (removeCard(cardIndex)) { //attempt to play card

                ui.displayMessage(
                    "Card played successfully."
                ); //confirm play

                nextTurn(); //finish turn
                return; //stop current turn
            }

            ui.displayMessage(
                "Invalid card. Try again."
            ); //show error
        }
    }
}

GameResult Game::getResult() const { //get final game result

    if (!gameOver) { //check game status
        throw logic_error("Game is not finished"); //reject request
    }

    return finalResult; //return stored result
}

GameResult Game::startGame() { //start a new game

    currentPlayer = 1; //first player starts
    gameOver = false; //reset game status
    winner = ""; //clear previous winner
    turnsCompleted = 0; //reset turn counter
    finalResult = GameResult::Draw; //reset result

    deck = Deck(); //create fresh deck
    deck.shuffle(); //shuffle cards

    for (int i = 0; i < 5; i++) { //deal starting hands

        if (!deck.drawCard(player1)) { //deal first player
            throw logic_error(
                "Cannot deal first player's hand"
            ); //report dealing error
        }

        if (!deck.drawCard(player2)) { //deal second player
            throw logic_error(
                "Cannot deal second player's hand"
            ); //report dealing error
        }
    }

    while (!gameOver) { //continue until game ends
        playTurn(); //handle current player's turn
    }

    return getResult(); //return result to main
}

bool Game::isGameOver() const { //check game status
    return gameOver; //return game status
}

string Game::getWinner() const { //get winning player
    return winner; //return winner name or draw
}
