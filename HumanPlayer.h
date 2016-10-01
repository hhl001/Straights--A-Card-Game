#ifndef _HUMAN_PLAYER_
#define _HUMAN_PLAYER_

#include "Player.h"

class HumanPlayer : public Player {
public:
    HumanPlayer();
    Command turn(const std::vector<Card>&, Command);
private:
    void print(const std::vector<Card>&) const;
    void discard(const Card&, const std::vector<Card>&);
    void printHand() const;
    void play(const Card&, const std::vector<Card>&);
    void printSuit(const Suit& s, const std::vector<Card>& playedCards) const;
    void printLegalPlays(const std::vector<Card>&) const;
    void setCommand(const Command&);
};
#endif
