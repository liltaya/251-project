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
#include "system.hpp"

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
    System system;

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
    System& getSystem();

    // view player's components
    const System& getSystem() const;

    // view player's components' HP
    int getTotalHP() const;

    // true is player's componets are destroyed (HP = 0)
    bool isSystemDestroyed() const;
};

#endif
