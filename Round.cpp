#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <list>
#include <cstdlib>
#include "Round.h"
#include "Command.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"


// constructor -- sets the data members for the round including the deck, initiating the turn number to 1 of 4 in the cycle and setting the state of the round to starting
Round::Round(std::vector<Player*> players, Deck* deck) : state_(BEGIN), deck_(deck), players_(players) {}

// destructor
Round::~Round() {}

// accessor -- gets the players present in the round
const std::vector<Player*> Round::getPlayers() const {
    return players_;
}

// accessor -- returns the hand of the current player
const std::vector<Card> Round::currentHand() const {
    return currentPlayer_->getHand();
}

// accessor -- returns the number of the current player
int Round::currentPlayerNumber() const {
    return currentPlayer_->getNumber();
}

// accessor -- returns the current state of the round
const State Round::getState() const {
    return state_;
}

// accessor -- returns the played cards in the round
const std::vector<Card> Round::getPlayedCards() const {
    return playedCards_;
}

// accessor -- returns the legal plays for the current player
const std::vector<Card> Round::legalPlays() const {
    return currentPlayer_->legalPlays(playedCards_);
}

// accessor -- returns the number of discards for the current players
const std::vector<int> Round::playerDiscardCounts() const {
    std::vector<int> discardCounts;
    for (unsigned int x = 0; x < players_.size(); x++) {
        discardCounts.push_back(players_[x]->discardCount());
    }
    return discardCounts;
}

// member function -- resets discards, shuffles the deck, sets the hands for the players that round 
// and begins the cycle of turns, determining who should go first
void Round::setup() {
    for (unsigned int x = 0; x < players_.size(); x++) {
        players_[x]->clearDiscards();
    }
    deck_->shuffle();
    setHands();
    Player* first = firstPlayer();
    currentPlayer_ = first;
    std::cout << "A new round begins. It's player " << first->getNumber() << "'s turn to play." << std::endl;
}

// member function -- initiates a ragequit and then begins the next turn for the computer player taking over
void Round::changePlayerType() {
    int number = currentPlayer_->getNumber() -1;
    Player* newPlayer = new ComputerPlayer(*currentPlayer_);
    delete currentPlayer_;
    players_[number] = newPlayer;
    currentPlayer_ = newPlayer;
    std::cout << "Player " << players_[number]->getNumber() << " ragequits. A computer will now take over.\n";
    takeTurn();
}

// member function -- begins the turn for a player
void Round::takeTurn(Command action) {
    inputCommand(currentPlayer_, action);
}

// member function -- determines the player to go first based on who has the seven of spades
Player* Round::firstPlayer() const {
    Card firstPlay = Card((Suit)(SPADE), (Rank)(SEVEN));
    for (unsigned int x = 0; x < players_.size(); x++) {
        if (players_[x]->handContains(firstPlay))
            return players_[x];
    }
}

// member function -- determines the player that should go next in the round based on the previous player
Player* Round::nextPlayer(const Player* player) const {
    int number = player->getNumber();
    if (number + 1 > 4)
        return players_[0];
    else
        return players_[number];
}

void Round::inputCommand(Player* player, Command action) {
    state_ = ACTIVE;
    if (player->getHand().empty()) {
        for (unsigned int x = 0; x < players_.size(); x++) {
            players_[x]->setScore();
        }
        state_ = OVER;
        return;
    }

    currentPlayer_ = player;
    Player* next = nextPlayer(player);
    action = currentPlayer_->turn(playedCards_, action);
     switch(action.type) {
        case PLAY:  {
            playedCards_.push_back(action.card);
            inputCommand(next);
        }
            break;
        case DECK: {
            deck_->print();
            inputCommand(currentPlayer_);
        }
            break;
        case QUIT: {};
            break;
        case RAGEQUIT: {
            changePlayerType();
        }
            break;
        case BAD_COMMAND: { 
            state_ = HOLD;
        };
            break;
        default: { inputCommand(next); }
    }
}

// mutator -- sets the hands for the players in the round
void Round::setHands() {
    for (unsigned int x = 0; x < players_.size(); x++) {
        players_[x]->setHand(deck_->getCards());
    }
}
