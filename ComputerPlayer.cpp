#include "ComputerPlayer.h"
#include <iostream>

// default constructor
ComputerPlayer::ComputerPlayer() {}

// copy constructor
ComputerPlayer::ComputerPlayer(const Player& player) : Player(player) {};

// executes either a play or discard for the computer player depending on the state of the game
Command ComputerPlayer::turn(const std::vector<Card>& playedCards, Command action)
{
  if (legalPlays(playedCards).empty()) {
    discard(getHand().front(), playedCards);
    action.type = DISCARD;
  }
  else {
    action.card = legalPlays(playedCards).front();
    play(action.card, playedCards);
    action.type = PLAY;
  }
  return action;
}

