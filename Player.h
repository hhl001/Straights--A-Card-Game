#ifndef _PLAYER_
#define _PLAYER_

#include <vector>
#include <string>
#include "Card.h"
#include "Command.h"

class Player {
public:
    Player();
    Player(const Player&);
    virtual ~Player();
    virtual Command turn(const std::vector<Card>&, Command = Command()) = 0;
    std::vector<Card> getHand() const;
    void setHand(const std::vector<Card*>&);
    int getNumber() const;
    int getRoundScore() const;
    int getTotalScore() const;
    void setScore();
    bool handContains(const Card&) const;
    bool legalPlay(const Card&, const std::vector<Card>&) const;
    std::vector<Card> legalPlays(const std::vector<Card>&) const;
    void clearDiscards();
    std::string printDiscards() const;
    virtual void play(const Card&, const std::vector<Card>&);
    virtual void discard(const Card&, const std::vector<Card>&);
    int discardCount();
private:
    static int playerNumber_;
    std::vector<Card> hand_;
    std::vector<Card> discards_;
    const int number_;
    int score_;
    int roundscore_;

    void removeFromHand(const Card&);                                      
};
    
#endif
