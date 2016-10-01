/*
 * MVC example of GTKmm program
 *
 * View class.  Is responsible for buttons (that user clicks) and for displaying
 * the top card of the deck.
 *
 *  Created by Jo Atlee on 06/07/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */


#ifndef MVC_VIEW_H
#define MVC_VIEW_H

#include <gtkmm.h>
#include "DeckGUI.h"
#include "Observer.h"

class Controller;
class Model;


class View : public Gtk::Window, public Observer {
public:
    View( Controller*, Model* );
	virtual ~View();
	virtual void update();	// Observer Pattern: concrete update() method

private:
	// Observer Pattern: to access Model accessors without having to downcast subject
	Model *model_;
	
	// Strategy Pattern member (plus signal handlers)
	Controller *controller_;

	// Card Images
	DeckGUI deck;

	// Add fields and private methods in here
	Gtk::VBox    panels;      // Main window divided into four vertical panels
	Gtk::HBox    butBox;      // Vertical boxes for start, set seed and end

	Gtk::Button  start_button;
	Gtk::Entry   seed_field;      // Contains the seed number
	Gtk::Button  end_button;

	// All table contents
	Gtk::Frame   frame;            // Create a nice framed border for the box.
	Gtk::Frame   cardFrame[52];        // Create a nice framed border for cards.
	Gtk::VBox    table;
	Gtk::HBox    tableRows[4];
	Gtk::Image   card[52];          // Images to display.

	// Player types and information
	Gtk::HBox    playerBox;
	Gtk::VBox    playerInfoBox[4];
	Gtk::Frame   playerFrame[4];            // Create a nice framed border for players.
	Gtk::Button  type_button[4];
	Gtk::Label   pointLabel[4];
	Gtk::Label   discardLabel[4];

	// Cards in your hand
	Gtk::Frame   cardsInHandFrame;
	Gtk::HBox    cardsInHandBox;
	Gtk::Button  cardInHandButton[13];        // Create a nice framed border for cards.
	Gtk::Image   cardInHandImage[13];          // Images to display.

	// Functions
	void clickStartButton();
	void clickEndButton();
	void startNewRound();
	void roundUpdate();
	void roundEnd();
	void newGame();
	void clickPlayerButton(int index);				// forwards the clicking of the player button to the controller
	void clickHandButton(int index);				// forwards the clicking of a card in the player's hand to the controller
	void showWinner();



}; // View

#endif
