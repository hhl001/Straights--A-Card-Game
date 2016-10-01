#ifndef MVC_CONTROLLER
#define MVC_CONTROLLER

#include <gtkmm.h>
#include "Model.h"
#include <iostream>

class Model;

class Controller
{
public:
   Controller( Model* );
   void playerToggleButtonClicked(int playerNumber) const;
   void handSelectionButtonClicked(int cardNumber) const;
   void playRound() const;
   void newRound() const;
   void newGame(std::string seed) const;
   void endGame() const;
   void quitGame() const;
    
private:
   Model *m_model;
};
#endif

