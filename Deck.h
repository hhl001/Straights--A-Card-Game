#ifndef _DECK_
#define _DECK_

#include <vector>
#include "Card.h"
#include <random>

class Deck {
public:
    Deck();
    virtual ~Deck();
    std::vector<Card*> getCards() const;
    void print() const;
    void shuffle();
    void initializeRNG(int seed);
    
private:
    std::vector<Card*> cards_;
    int m_seed;
};
#endif
