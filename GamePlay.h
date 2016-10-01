#ifndef _GAMEPLAY_
#define _GAMEPLAY_

#include <vector>
#include "Round.h"
#include "Player.h"

class GamePlay {
public:
    GamePlay(const std::vector<char>& playerTypes, const int seedVal);
    virtual ~GamePlay();
    void changeCurrentPlayerType();
    void playRound();
    void beginNewRound();
    const State getRoundState() const;
    void continueRound(Command);
    const std::vector<int> getPlayerScores() const;
    const std::vector<Card> getCurrentHand() const;
    int currentPlayerNumber() const;
    std::string roundResults() const;
    const std::vector<Card> getLegalPlaysForPlayer() const;
    const std::vector<Player*> getWinners() const;
    const std::vector<Card> getCardsPlayedInRound() const;
    const std::vector<int> getPlayerDiscardCounts() const;
    
private:
    std::vector<Player*> m_players;
    Deck m_deck;
    Round* m_round;
    int m_UpperScoreBoundForGame;
    
};

#endif
