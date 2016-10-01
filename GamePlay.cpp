#include "stdlib.h"
#include "GamePlay.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <random>

GamePlay::GamePlay(const std::vector<char>& playerTypes, const int seedVal = 0) : m_UpperScoreBoundForGame(80)
{
    m_deck.initializeRNG(seedVal);
    for (int playerNum = 0; playerNum < 4; playerNum++)
    {
        if (playerTypes[playerNum] == 'h')
        {
            m_players.push_back(new HumanPlayer());

        }
        else
        {
            m_players.push_back(new ComputerPlayer());
        }
    }
}

GamePlay::~GamePlay() {
    for (int playerNum = 0; playerNum < (int)m_players.size(); playerNum++)
    {
        delete m_players[playerNum];
    }
}

void GamePlay::changeCurrentPlayerType()
{
    m_round->changePlayerType();
    m_players = m_round->getPlayers();
}

void GamePlay::beginNewRound()
{
    Round* newRound = new Round(m_players, &m_deck);
    newRound->setup();
    m_round = newRound;
}

void GamePlay::playRound()
{
    std::vector<Player*> gameWinners = getWinners();
    m_round->takeTurn();
    gameWinners = getWinners();
}

void GamePlay::continueRound(Command command)
{
    m_round->takeTurn(command);
}

const std::vector<int> GamePlay::getPlayerDiscardCounts() const
{
    return m_round->playerDiscardCounts();
}

const std::vector<Card> GamePlay::getCurrentHand() const
{
    return m_round->currentHand();
}

const std::vector<Card> GamePlay::getCardsPlayedInRound() const
{
    return m_round->getPlayedCards();
}

int GamePlay::currentPlayerNumber() const
{
    return m_round->currentPlayerNumber();
}

const State GamePlay::getRoundState() const
{
    return m_round->getState();
}

const std::vector<Card> GamePlay::getLegalPlaysForPlayer() const
{
    return m_round->legalPlays();
}

const std::vector<int> GamePlay::getPlayerScores() const
{
    std::vector<int> scores;
    for (int x = 0; x < 4; x++) {
        scores.push_back(m_players[x]->getTotalScore());
    }
    return scores;
}

std::string GamePlay::roundResults() const
{
    std::stringstream ss;
    for (int playerNum = 0; playerNum < (int)m_players.size(); playerNum++)
    {
        ss << "Player " << m_players[playerNum]->getNumber() << "'s discards:";
        ss << m_players[playerNum]->printDiscards();

        ss << "\nPlayer " << m_players[playerNum]->getNumber() << "'s score: "
            << (m_players[playerNum]->getTotalScore() - m_players[playerNum]->getRoundScore()) << " + " << (m_players[playerNum]->getRoundScore())
            << " = " << m_players[playerNum]->getTotalScore() << std::endl;
    }
    return ss.str();
}

const std::vector<Player*> GamePlay::getWinners() const
{
    std::vector<Player*> gameWinners;
    for (int playerNum = 0; playerNum < (int)m_players.size(); playerNum++)
    {
        if (m_players[playerNum]->getTotalScore() >= m_UpperScoreBoundForGame)
        {
            //check if the criteria of ending game has been satified
            for (int playerIter = 0; playerIter < m_players.size(); playerIter++)
            {
                if (gameWinners.empty() || m_players[playerIter]->getTotalScore() == gameWinners[0]->getTotalScore())
                {
                    gameWinners.push_back(m_players[playerIter]);
                }
                else if (m_players[playerIter]->getTotalScore() < gameWinners[0]->getTotalScore())
                {
                    gameWinners.clear();
                    gameWinners.push_back(m_players[playerIter]);
                }
            }
            break;
        }
    }
    return gameWinners;
}

