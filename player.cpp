// ---------------------------------------------------------------------------------------------------

/*****************************************************************
 * Simon Fraser University
 * ENSC 251 - Software Design and Analysis for Engineers
 * Project - virus.exe
 *
 * player.cpp - implements the Player class
 * 
 * Author: Vijeta Dhalla, 301644330
 * 
*******************************************************************/

#include "player.hpp"

// hand starts empty
// assumes Deck class deals 5 starting cards
// assumes ComponentStatus initializes 4 components
Player::Player(const std::string& playerName) : name(playerName) {}

// name is either "Player 1" or "Player 2"
const std::string& Player::getName() const
{
    return name;
}

// checks hand size to verify draw or play options
int Player::getHandSize() const
{
    return static_cast<int>(hand.size());
}

bool Player::hasCards() const
{
    return !hand.empty();
}

bool Player::isHandFull() const
{
    return hand.size() >= MAX_HAND_SIZE;
}

// const reference to look at hand
const std::vector<Card>& Player::getHand() const
{
    return hand;
}

bool Player::addCard(const Card& newCard)
{
    // restricts "add' option if 5/5 hand size
    if (isHandFull())
    {
        return false;
    }

    hand.push_back(newCard);
    return true;
}

bool Player::removeCard(int cardIndex, Card& removedCard)
{
    // restricts "play" option if 0/5 hand size or invalid
    if (cardIndex < 0 || static_cast<std::size_t>(cardIndex) >= hand.size())
    {
        return false;
    }

    // safe to remove card at cardIndex and copy it into removedCard
    removedCard = hand[static_cast<std::size_t>(cardIndex)];
    hand.erase(hand.begin() + cardIndex);

    return true;
}

ComponentStatus& Player::getSystem()
{
    return system;
}

const ComponentStatus& Player::getSystem() const
{
    return system;
}

int Player::getTotalHP() const
{
    // checks component HP
    return system.getTotalHP();
}

bool Player::isSystemDestroyed() const
{
    // checks if component is destroyed (HP = 0)
    return system.isSystemDestroyed();
}
