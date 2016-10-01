#ifndef STRAIGHTS_MODEL
#define STRAIGHTS_MODEL

#include "GamePlay.h"
#include <string>
#include <vector>
#include "Subject.h"
#include "Card.h"

//This class provides a simple interface for view and controller to talk to (Facade design pattern)
//to prevent direct communication between the GUI and the logic
//All the request are made to model which delegates to spcialized classes

class Model : public Subject {
public:
    Model();
    virtual ~Model();
    bool IsGameActive() const;
    int currentPlayerNumber() const;
    std::vector<int> getWinners() const;
    void setupNewGame(std::string seed);
    bool IsHumanPlayer(int playerNum) const;
    void quitCurrentGame();
    std::vector<int> getPlayerDiscardCounts() const;
    void playRound();
    std::vector<int> getPlayerScores() const;
    void setupNewRound();
    State CurrentRoundState() const;
    std::vector<int> getCurrentHandValues() const;
    void changeCurrentPlayerType(int currentPlayerIndex);
    void playOrDiscardCard(int cardIndex);
    bool validPlay();
    std::vector<int> getPlayedCardNumbers() const;
    std::string roundResults() const;
    void endCurrentGame();

    
private:
    GamePlay* m_gameScene;
    int m_seedVal;
    bool m_IsPlayValid;
    bool m_bIsGameActive;
    bool IslegalPlay(int cardNumber) const;
    std::vector<int> m_winners;
    std::vector<char> m_PlayerType;
    std::vector<int> convertCardsToInts(std::vector<Card>) const;
};

#endif
