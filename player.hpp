/************************************************************************************************
 * 
 * public functions used:
 * 
 *  from ComponentStatus Class:
 *    int getTotalHP() const;
 *    bool isSystemDestroyed() const;
 * 
 *    variables:
 *     system
 * 
 *  from Card Class:
 *    addCard()	     
 *    removeCard()
 * 
 *    variables:
 *      newcard
 *      removedcard
 *      cardIndex
 * 	 
 * public functions avalilable for use:
 *      getName()	      	Get the player's name.
 *      getHandSize()	    Check the number of cards in the hand.
 *      hasCards()	        Check whether the player has cards.
 *      isHandFull()	    Check whether the hand contains 5 cards.
 *      getHand()	        Access the cards in the hand.
 *      getSystem()	        Access the player's component system.
 * 
********************************************************************************************/

// ---------------------------------------------------------------------------------------------------

/*****************************************************************
 * Simon Fraser University
 * ENSC 251 - Software Design and Analysis for Engineers
 * Project - virus.exe
 *
 * player.hpp - header file for the Player class
 * 
 * function: manages player hand size and component status
 * 
 * Author: Vijeta Dhalla, 301644330
 * 
*******************************************************************/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "card.hpp"
#include "componentstatus.hpp"

class Player
{
private:
    std::string name;
    // for Game Class:
    //      Player player1("Player 1");
    //      Player player2("Player 2");

    // player's hand
    std::vector<Card> hand;

    // player's components
    ComponentStatus system;

    // hand size validation
    static constexpr std::size_t MAX_HAND_SIZE = 5;

public:
    // makes player object
    explicit Player(const std::string& playerName);

    // checks if player 1 or 2
    const std::string& getName() const;

    // gets hand size
    int getHandSize() const;

    // true if player has cards
    bool hasCards() const;

    // true if player has 5/5 cards
    bool isHandFull() const;

    // view player's hand
    const std::vector<Card>& getHand() const;

    // adds card if player's hand ≠ 5
    bool addCard(const Card& newCard);

    // plays card and removes from hand
    //    false = hand is empty
    //    false = cardIndex is invalid
    bool removeCard(int cardIndex, Card& removedCard);

    // Game class can modify player's components
    ComponentStatus& getSystem();

    // view player's components
    const ComponentStatus& getSystem() const;

    // view player's components' HP
    int getTotalHP() const;

    // true is player's componets are destroyed (HP = 0)
    bool isSystemDestroyed() const;
};

#endif
