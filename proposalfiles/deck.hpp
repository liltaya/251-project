// ENSC 251 Alina Beg 301593470
#ifndef DECK_H
#define DECK_H

#include "card.hpp"

class Player;

class Deck {
private:
    Card cards[52]; // array of 52 cards
    Card discardPile[52]; // where all the used cards go
    int deckCount; // how many cards in deck
    int discardedCount; // how many cards were played

public:
    Deck();

    void shuffle(); // randomize order of cards in deck
    bool isEmpty() const; // checks if deck is empty
    int cardsRemaining() const; // how many cards are left
    bool drawCard(Player& player); // draws a card from deck
    void discardCard(const Card& card); // puts a card in the discard pile (ex. after a play)
};

#endif

