#include <iostream>
#include <string>
#include "stdlib.h"
#include "Deck.h"

int CARD_COUNT = 52;

// constructor -- adds all cards to deck
Deck::Deck() {
    for (int suit = CLUB; suit < SUIT_COUNT; suit++) {
        for (int rank = ACE; rank < RANK_COUNT; rank++) {
            cards_.push_back(new Card((Suit)suit,(Rank)rank));
        }
    }
}

// destructor -- deletes all created cards
Deck::~Deck() {
    for (unsigned int x = 0; x < cards_.size(); x++) {
        delete cards_[x];
    }
}

// member function -- shuffles the deck's cards
void Deck::shuffle(){
    static std::mt19937 rng(m_seed);
    
    int n = CARD_COUNT;
    
    while (n > 1) {
        int k = (int)(rng() % n);
        --n;
        Card *c = cards_[n];
        cards_[n] = cards_[k];
        cards_[k] = c;
    }
}

void Deck::initializeRNG(int seed)
{
    m_seed = seed;
}

// member function -- prints the shuffled deck of the current round
void Deck::print() const {
    for (unsigned int x = 0; x < cards_.size(); x++) {
        std::cout << *cards_[x] << " ";
        if (x == 12 || x == 25 || x == 38 || x == 51)
            std::cout << std::endl;
    }
    std::cout << "\n>";
}


// accessor -- returns the cards maintained by the deck
std::vector<Card*> Deck::getCards() const {
    return cards_;
}
