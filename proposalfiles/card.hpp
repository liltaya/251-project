// ENSC 251, alina beg 301593470
#ifndef CARD_H
#define CARD_H

#include <string>
using namespace std;

class Card {
private:
    int suit; 
    int rank; 

public:
    Card();
    Card(int s, int r);

    int getSuit() const; 
    int getRank() const;
    int getEffectValue() const; // get number for effect value ex. jack (11) returns 2
    string getDescription() const; // get description of card in readable form ex. jack of hearts
};

#endif
