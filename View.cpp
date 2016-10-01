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

#include "Observer.h"
#include "View.h"
#include "Controller.h"
#include "Model.h"
#include "Subject.h"
#include "DeckGUI.h"
#include <iostream>
using namespace std;

// Creates buttons with labels. Sets butBox elements to have the same size, 
// with 10 pixels between widgets
View::View(Controller *c, Model *m) : model_(m), controller_(c), start_button("Start new game with seed:"), end_button("End current game") {

	// Sets some properties of the window.
    set_title( "Straights UI" );
	set_border_width( 10 );
	
	// Do stuff in here
	// Add panels to the window
	add(panels);

	// Add button box and card image to the panels
	panels.add( butBox );
	panels.add( frame );
	panels.add( playerBox );
	panels.add( cardsInHandFrame );
	

	// Vertical boxes for start, set seed and end
	butBox.add( start_button );
	start_button.signal_clicked().connect( sigc::mem_fun( *this, &View::clickStartButton ) );
	seed_field.set_text("0");
	seed_field.set_alignment(Gtk::ALIGN_CENTER);
	butBox.add( seed_field );
	butBox.add( end_button );
	end_button.signal_clicked().connect( sigc::mem_fun( *this, &View::clickEndButton ) );

	// Set the look of the table
	frame.set_label( "Cards on the table" );
	frame.add(table);

	for (int i=0; i<4; i++){
		for (int j=0; j<13; j++){
			card[i*13+j].set( deck.null() );
			cardFrame[i*13+j].add(card[i*13+j]);
			tableRows[i].add( cardFrame[i*13+j] );
		}
		table.add(tableRows[i]);
	}

	// Set the look player types 
	for (int i=0; i<4; i++){
		stringstream s;
		s << (i+1);
		playerFrame[i].set_label( "Player " + s.str() );

		playerInfoBox[i].add( type_button[i] );
		playerInfoBox[i].add( pointLabel[i] );
		playerInfoBox[i].add( discardLabel[i] );
		playerFrame[i].add(playerInfoBox[i]);

		type_button[i].set_label( "Human" );
		// -------------------
		type_button[i].signal_clicked().connect( sigc::bind<int>( sigc::mem_fun(*this, &View::clickPlayerButton), i));
		//type_button[i].set_sensitive(false);
		pointLabel[i].set_text("0 points");
		discardLabel[i].set_text("0 discards");

		playerBox.add(playerFrame[i]);
	}

	// Set the look of cards in hand
	cardsInHandFrame.set_label( "Your Hand" );
	for (int i=0; i<13; i++){
		cardInHandImage[i].set( deck.null() ); 
		cardInHandButton[i].set_image(cardInHandImage[i]);
		cardInHandButton[i].signal_clicked().connect( sigc::bind<int>( sigc::mem_fun(*this, &View::clickHandButton), i));
		cardsInHandBox.add(cardInHandButton[i]);
	}
	cardsInHandFrame.add(cardsInHandBox);

	
	// The final step is to display the buttons (they display themselves)
	show_all();

	// Register view as observer of model
	model_->subscribe(this);

} // View::View

View::~View() {}

void View::update() {
	
	if (!model_->IsGameActive()) {
		newGame();
		showWinner();
	}
	else {
		if (model_->CurrentRoundState() == HOLD) {
			roundUpdate();
		}

		else if (model_->CurrentRoundState() == BEGIN) {
			startNewRound();
		}

		else if (model_->CurrentRoundState() == OVER) {
			roundEnd();
		}
	}
	
}

void View::roundUpdate() {
	if (model_->validPlay()) {
		std::vector<int> discardsInts = model_->getPlayerDiscardCounts();

		for (int i = 0; i < 4; i++) {
			std::stringstream ss;
			ss << discardsInts[i] << " discards";
			discardLabel[i].set_text(ss.str());
		}
		
		for (int i = 0; i < 4; i++) {
			if (i == model_->currentPlayerNumber() - 1)
			type_button[i].set_sensitive(true);
			else
			type_button[i].set_sensitive(false);
		}	

		// replaceHand
		std::vector<int> handValues = model_->getCurrentHandValues();
		for (int i = 0; i < 13; i++) {
			if (i < handValues.size()) {
				int row = handValues[i] / 13;
				int column = handValues[i] % 13;
				cardInHandImage[i].set(deck.getCardImage((Rank)column, (Suit)row));
			}
			else {
				cardInHandImage[i].set(deck.null());
			}
		}

		// add cards to the table
		const std::vector<int>& tableValues = model_->getPlayedCardNumbers();
		for (int i = 0; i < tableValues.size(); i++) {
			int row = tableValues[i] / 13;
			int column = tableValues[i] % 13;
			card[ tableValues[i] ].set(deck.getCardImage((Rank)column, (Suit)row));
		}

	}
	else {
		Gtk::MessageDialog dialog( *this, "Not a legal play");
		dialog.run();
		dialog.hide();
	}
}

void View::roundEnd() {
	Gtk::MessageDialog dialog( *this, model_->roundResults());
	dialog.run();
	dialog.hide();

	controller_->newRound();
}

// Implement private methods in here
void View::clickStartButton() {
	controller_->newGame(seed_field.get_text());
}

void View::clickEndButton() {
	controller_->quitGame();
}

void View::startNewRound() {
	vector<int> scores = model_->getPlayerScores();
	vector<int> discards = model_->getPlayerDiscardCounts();

	// empty the table
	for (int i = 0; i < 52; i++) {
		card[i].set( deck.null() );
	}
	// empty player hands
	for (int i = 0; i < 13; i++) {
		cardInHandImage[i].set( deck.null() );
	}

	for (int i=0; i<4; i++){
		type_button[i].set_label("Rage!");
	}

	// update points and number of discard cards to table 
	for (int i = 0; i < 4; i++) {
		std::stringstream tempStream;
		//std::stringstream discardsStream;
		tempStream << scores[i] << " points";
		pointLabel[i].set_label(tempStream.str());
		tempStream.str("");
		tempStream << discards[i] << " discards";
		discardLabel[i].set_text(tempStream.str());
		type_button[i].set_sensitive(true);
	}

	stringstream startText;
	startText << "A new round begins. It's player " << model_->currentPlayerNumber() << "'s turn to play.";
    Gtk::MessageDialog dialog( *this, startText.str() );

    dialog.run();
    dialog.hide();

    controller_->playRound();
}

// reset points and cards for players
void View::newGame() {
	// empty the table
	for (int i = 0; i < 52; i++) {
		card[i].set( deck.null() );
	}

	// empty player hands
	for (int i = 0; i < 13; i++) {
		cardInHandImage[i].set( deck.null() );
	}

	for (int i=0; i<4; i++){
		discardLabel[i].set_label("0 discards");
		
		if ( model_->IsHumanPlayer(i)) {
			type_button[i].set_label("Human");
		}
		else {
			type_button[i].set_label("Computer");
		}
		
	}

}

void View::clickPlayerButton(int playerIndex) {
	controller_->playerToggleButtonClicked(playerIndex);
}

void View::clickHandButton(int cardIndexInHand) {
	controller_->handSelectionButtonClicked(cardIndexInHand);
}

void View::showWinner() {
	std::vector<int> winnerList = model_->getWinners();
	if (!winnerList.empty()) {
		stringstream ss;
		for (int i = 0; i <  winnerList.size(); i++) {
			ss << "Player " << winnerList[i] <<  " wins\n";
		}
		Gtk::MessageDialog dialog(*this, ss.str());
		dialog.run();
		dialog.hide();

		// End the game
		controller_->endGame();
	}
}