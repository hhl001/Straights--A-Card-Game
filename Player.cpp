#include "Player.h"
#include "Command.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

// initializes the static player count to zero
int Player::playerNumber_ = 0;


// namespace for the player class
namespace PlayerHelper {
    int HANDSIZE_ = 13;
}

// constructor -- initializes the player's number 
Player::Player() : number_(++playerNumber_), score_(0), roundscore_(0) {}

// copy constructor -- creates a new player with the same data variables as the player passed in
Player::Player(const Player& player) : hand_(player.hand_), discards_(player.discards_), number_(player.number_), score_(player.score_), roundscore_(player.roundscore_) {};

// default constructor -- initializes the player, setting no values
Player::~Player() {
    playerNumber_ = 0; 
}

int Player::discardCount() {
    return discards_.size();
}

// accessor -- returns the cards in the player's hand
std::vector<Card> Player::getHand() const {
    return hand_;
}

// accessor -- returns the player's number in the game
int Player::getNumber() const {
    return number_;
}

// accessor -- returns the player's score in the round
int Player::getRoundScore() const {
    return roundscore_;
}

// accessor -- returns the player's total score
int Player::getTotalScore() const {
    return score_;
}

// member function -- plays the card for the player and removes it from the hand
void Player::play(const Card& card, const std::vector<Card>& playedCards) {
    std::cout << "Player " << number_ << " plays " << card << "." << std::endl;
    removeFromHand(card);
}

// member funcrion -- removes the card from the players hand
void Player::discard(const Card& card, const std::vector<Card>& playedCards) {
    std::cout << "Player " << number_ << " discards " << card << "." << std::endl;
    discards_.push_back(card);
    removeFromHand(card);
}

// member function -- prints the player's discarded cards in the round
std::string Player::printDiscards() const {
    std::stringstream ss;
    if (discards_.empty()) {
        ss << " ";
        return ss.str();
    }
    for (unsigned int x = 0; x < discards_.size(); x++) {
        ss << " " << discards_[x];
    }
    return ss.str();
}

// mutator -- sets the round and total score for the player
void Player::setScore() {
    int score = 0;
    for (unsigned int x = 0; x < discards_.size(); x++)
        score += (int)(discards_[x].getRank() + 1);
    score_ += score;
    roundscore_ = score;
}

// member function -- checks if a card is contained in the player's hand
bool Player::handContains(const Card& card) const {
    return ((std::find(hand_.begin(), hand_.end(), card)) != hand_.end());
}

// mutator -- sets the hand for the player at the beginning of the round
void Player::setHand(const std::vector<Card*>& deck) {
    int index = (number_ - 1) * PlayerHelper::HANDSIZE_;

    for (int x = index; x < index + PlayerHelper::HANDSIZE_; x++) {
        hand_.push_back(*deck[x]);
    }
}

// mutator -- resets the discards for the player at the beginning of each round
void Player::clearDiscards() {
    discards_.clear();
}

// mutator -- removes a card from the player's hand
void Player::removeFromHand(const Card& card) {
    std::vector<Card>::iterator position = std::find(hand_.begin(), hand_.end(), card);
    hand_.erase(position);
}

// member function -- returns all the legal cards the player can play
std::vector<Card> Player::legalPlays(const std::vector<Card>& playedCards) const {
    std::vector<Card> validCards;
    for (unsigned int x =  0; x < hand_.size(); x++) {
        if (legalPlay(hand_[x], playedCards))
            validCards.push_back(hand_[x]);
    }
    return validCards;
}

// member function -- determines whether a particular card can be played at that time in the round
bool Player::legalPlay(const Card& card, const std::vector<Card>& playedCards) const {
    if (playedCards.size() == 0 && !(card.getRank() == SEVEN && card.getSuit() == SPADE)) {
        return false;
    } else if (card.getRank() == SEVEN) {
        return true;
    } else {
        for (unsigned int x = 0; x < playedCards.size(); x++) {
            if (playedCards[x].getSuit() == card.getSuit()) {
                if (playedCards[x].getRank() == (Rank)((int)card.getRank() - 1) || playedCards[x].getRank() == (Rank)((int)card.getRank() + 1)) {
                    return true;
                }
            }
        }
    }
    return false;
}
