OBJECTS = GamePlay.o Round.o Card.o Deck.o Player.o HumanPlayer.o ComputerPlayer.o Command.o Subject.o Model.o Controller.o DeckGUI.o View.o main.o
CXX = g++
CXXFLAGS = -Wall -O -g -std=c++0x `pkg-config gtkmm-2.4 --cflags`
LDFLAGS=`pkg-config gtkmm-2.4 --libs`
EXEC = straights

all: $(OBJECTS)
	$(CXX) $^ $(CXXFLAGS) $(LDFLAGS) -o $(EXEC);

clean:
	rm -rf ./straights $(OBJECTS)

DeckGUI.o: DeckGUI.h DeckGUI.cpp
Model.o: Subject.h Model.h Model.cpp
Subject.o: Subject.h Subject.cpp
Controller.o: Controller.h Model.h Controller.cpp
View.o: View.h View.cpp Observer.h Controller.h Model.h Subject.h DeckGUI.h
main.o: View.h Controller.h Model.h main.cpp
