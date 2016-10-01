#ifndef _COMPUTER_PLAYER_
#define _COMPUTER_PLAYER_

#include <vector>
#include "Player.h"

class ComputerPlayer : public Player {
public:
    ComputerPlayer();
    ComputerPlayer(const Player&);
    Command turn(const std::vector<Card>&, Command);
};
#endif
