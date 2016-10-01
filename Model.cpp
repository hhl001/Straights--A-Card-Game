#include "Model.h"
#include <iostream>
#include <sstream>

Model::Model()
{
    //initialize all the data members
    m_IsPlayValid = true;
    m_seedVal = 0;
    m_bIsGameActive = false;
    //set humans to be the default for all 4 player
    for(int playerNum = 0; playerNum < 4; playerNum++)
    {
        m_PlayerType.push_back('h');
    }
}

Model::~Model()
{
    if (m_bIsGameActive)
    {
        delete m_gameScene;
    }
}

// accessor -- determines whether the player corresponding to the number provided is a human or a computer
bool Model::IsHumanPlayer(int playerIndex) const
{
    if(m_PlayerType[playerIndex] == 'h')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Model::IsGameActive() const
{
    return m_bIsGameActive;
}

State Model::CurrentRoundState() const
{
    return m_gameScene->getRoundState();
}

int Model::currentPlayerNumber() const
{
    return m_gameScene->currentPlayerNumber();
}

std::vector<int> Model::getPlayerDiscardCounts() const
{
    return m_gameScene->getPlayerDiscardCounts();
}

std::vector<int> Model::getPlayerScores() const
{
    return m_gameScene->getPlayerScores();
}

std::vector<int> Model::getCurrentHandValues() const {
    
    return convertCardsToInts(m_gameScene->getCurrentHand());
}

std::vector<int> Model::getWinners() const
{
    return m_winners;
}

void Model::setupNewGame(std::string seed)
{
    if (m_bIsGameActive)
    {
        quitCurrentGame();
    }
    std::stringstream ss;
    ss << seed;
    ss >> m_seedVal;
    m_bIsGameActive = true;
    GamePlay* newGame = new GamePlay(m_PlayerType, m_seedVal);
    m_gameScene = newGame;
    setupNewRound();
}

void Model::endCurrentGame()
{
    delete m_gameScene;
    m_winners.clear();
}

void Model::quitCurrentGame()
{
    if (m_bIsGameActive)
    {
        endCurrentGame();
        m_bIsGameActive = false;
        notify();
    }
}

void Model::playRound()
{
    m_gameScene->playRound();
    notify();
}

void Model::setupNewRound()
{
    std::vector<Player*> gameWinners = m_gameScene->getWinners();
    //if theere are no winners this means the game is not yet over hence we setup a new reound
    if (gameWinners.empty())
    {
        m_gameScene->beginNewRound();
    }
    else
    {
        m_bIsGameActive = false;
        for (unsigned int x = 0; x < gameWinners.size(); x++)
        {
            m_winners.push_back(gameWinners[x]->getNumber());
        }
    }
    notify();
}

void Model::changeCurrentPlayerType(int playerNumber)
{
    if(m_PlayerType[playerNumber] == 'h')
    {
        m_PlayerType[playerNumber] = 'c';
    }
    else
    {
        m_PlayerType[playerNumber] = 'h';
    }
    if (m_bIsGameActive)
    {
        m_gameScene->changeCurrentPlayerType();
    }
    notify();
}

void Model::playOrDiscardCard(int cardNumber)
{
    if (IslegalPlay(cardNumber))
    {
        Command actionToTake;
        actionToTake.card = m_gameScene->getCurrentHand()[cardNumber];
        if (m_gameScene->getLegalPlaysForPlayer().empty())
        {
            actionToTake.type = DISCARD;
        }
        else
        {
            actionToTake.type = PLAY;
        }
        m_gameScene->continueRound(actionToTake);
        m_IsPlayValid = true;
    }
    else
    {
        m_IsPlayValid = false;
    }
    //notify the view, so it can update since the state of the model is changed
    notify();
}

bool Model::validPlay()
{
    bool currentMoveValidityState = m_IsPlayValid;
    if (!m_IsPlayValid)
    {
        m_IsPlayValid = !m_IsPlayValid;
    }
    return currentMoveValidityState;
}

std::vector<int> Model::getPlayedCardNumbers() const
{
    return convertCardsToInts(m_gameScene->getCardsPlayedInRound());
}

std::string Model::roundResults() const
{
    return m_gameScene->roundResults();
}

bool Model::IslegalPlay(int cardNumber) const
{
    std::vector<Card> legalPlays = m_gameScene->getLegalPlaysForPlayer();
    Card card = m_gameScene->getCurrentHand()[cardNumber];
    
    if (legalPlays.empty())
    {
        return true;
    }
    
    for (unsigned int x = 0; x < legalPlays.size(); x++)
    {
        if (card == legalPlays[x])
        {
              return true;
        }
    }
    return false;
}

std::vector<int> Model::convertCardsToInts(std::vector<Card> cards) const
{
    std::vector<int> cardValues;
    
    for (int x = 0; x < (int)cards.size(); x++) {
        cardValues.push_back(13 * cards[x].getSuit() + cards[x].getRank());
    }
    
    return cardValues;
}



