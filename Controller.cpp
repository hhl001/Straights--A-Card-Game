#include "Controller.h"

Controller::Controller(Model *model) : m_model(model) {}

void Controller::playerToggleButtonClicked(int playerNumber) const
{
	m_model->changeCurrentPlayerType(playerNumber);
}

void Controller::handSelectionButtonClicked(int cardNumber)  const
{
	m_model->playOrDiscardCard(cardNumber);
}

void Controller::quitGame() const
{
    m_model->quitCurrentGame();
}

void Controller::endGame() const
{
    m_model->endCurrentGame();
}

void Controller::playRound()  const
{
	m_model->playRound();
}

void Controller::newRound() const
{
	m_model->setupNewRound();
}

void Controller::newGame(std::string seed) const
{
	m_model->setupNewGame(seed);
}
