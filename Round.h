#ifndef _ROUND_
#define _ROUND_

#include <vector>
#include "Deck.h"
#include "Player.h"

//for view update
enum State { BEGIN, ACTIVE, OVER, HOLD };

class Round {
public:
    Round(std::vector<Player*> players, Deck* deck_);               // constructor -- takes the players and deck
    virtual ~Round();                                               // destructor
    void setup();                                                   // member function -- runs the setup required to begin a new round
    void changePlayerType();                                        // member function -- ragequits the player and then begins the turn for the computer replacement
    void takeTurn(Command action = Command());                      // member function -- begins the turn for a player
    const std::vector<Player*> getPlayers() const;                  // accessor -- returns the players in the round
    const std::vector<Card> currentHand() const;                    // accessor -- returns the current player's hand
    int currentPlayerNumber() const;                                // accessor -- returns the current player's number
    const std::vector<Card> getPlayedCards() const;                 // accessor -- returns the cards played so far in the round
    const State getState() const;                                   // accessor -- returns the state of the round
    const std::vector<Card> legalPlays() const;                     // accessor -- returns the legal plays for the current player
    const std::vector<int> playerDiscardCounts() const;             // accessor -- returns the number of discards for each player in the round

private:
    Player* firstPlayer() const;                                    // determines the player to go first in the round
    void setHands();                                                // sets all hands for the players at the beginning of the round
    void inputCommand(Player* player, Command action = Command());  // takes in an action and executes the required command
    Player* nextPlayer(const Player*) const;                        // returns the player to go next based on the player who went previously
    
    State state_;                                                   // current state of the round
    Deck* deck_;                                                    // current deck of the round
    Player* currentPlayer_;                                         // player whose current turn it is
    std::vector<Player*> players_;                                  // current players in the round
    std::vector<Card> playedCards_;                                 // cards already played in the round
};
#endif
