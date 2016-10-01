#include "HumanPlayer.h"
#include <iostream>


HumanPlayer::HumanPlayer() {}

Command HumanPlayer::turn(const std::vector<Card>& playedCards, Command action) {
    print(playedCards);
    try {
        switch(action.type) {
            case PLAY: { play(action.card, playedCards); }
                break;
            case DISCARD: { discard(action.card, playedCards); }
                break;
            case BAD_COMMAND:;
                break;
            default: {}
        }
    }
    catch(const char* &s) {
        action.type = BAD_COMMAND;
    }
    return action;
}

void HumanPlayer::play(const Card& card, const std::vector<Card>& playedCards) {
    if (legalPlay(card, playedCards) && handContains(card))
        Player::play(card, playedCards);
    else
        throw "This is not a legal play.\n>";
}

void HumanPlayer::discard(const Card& card, const std::vector<Card>& playedCards) {
    if (legalPlays(playedCards).empty() && handContains(card))
    {
        Player::discard(card, playedCards);
    }
    else
    {
        throw "You have a legal play. You may not discard.\n>";
    }
}

void HumanPlayer::printHand() const {
    std::cout << "\nYour hand:";
    for (unsigned int x = 0; x < getHand().size(); x++)
        std::cout << " " << getHand()[x];
}

void HumanPlayer::printSuit(const Suit& s, const std::vector<Card>& playedCards) const {
    std::string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
        "7", "8", "9", "10", "J", "Q", "K"};
    for (unsigned int x = 0; x < playedCards.size(); x++) {
        if (playedCards[x].getSuit() == s)
            std::cout << " " << ranks[playedCards[x].getRank()];
    }
    if (playedCards.empty())
        std::cout << " ";
}

void HumanPlayer::print(const std::vector<Card>& playedCards) const {
    std::cout << "Cards on the table:\n";
    std::cout << "Clubs:";
    printSuit(CLUB, playedCards);
    std::cout << "\nDiamonds:";
    printSuit(DIAMOND, playedCards);
    std::cout << "\nHearts:";
    printSuit(HEART, playedCards);
    std::cout << "\nSpades:";
    printSuit(SPADE, playedCards);
    printHand();
    printLegalPlays(playedCards);
    std::cout << std::endl;
}

void HumanPlayer::printLegalPlays(const std::vector<Card>& playedCards) const {
    std::cout << "\nLegal plays:";
    for (unsigned int x = 0; x < getHand().size(); x++) {
        if (legalPlay(getHand()[x], playedCards))
            std::cout << " " << getHand()[x];
    }
}

