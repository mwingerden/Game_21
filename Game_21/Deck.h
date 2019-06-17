/******************************************************************************
filename    Deck.cpp
author      Matthew Wingerden
email		matthew.wingerden@gmail.com

Brief Description:
	This file contains the declarations fo the class and its member functions.

	The Functions Include:
	- Deck 
	This is the constructor for the class that takes the number of decks the 
	player wants ot play with.

	- ~Deck
	The destructor for the Deck class. Currently does nothing.

	- CreateCardDeck
	This function creates a shoe of cards depending on the player's preference 
	of number of decks

	- AssignSuit
	Assigns the suit of to an individual card.

	- operator<<
	Prints out either the shuffled shoe or the original shoe. Mostly for 
	testing purposes.

	- ShuffleDeck
	Shuffles the original shoe and assigns it to the shuffled shoe.

	- SetDisplayNormalDeck
	Sets the operator<< to display the original shoe. For testing purpose.

	- SetDisplayShuffledDeck
	Sets the operator<< to display the shuffled shoe. For testing purpose.

	- GetShuffledDeck
	Returns the shuffled shoe.

	- ReturnCard
	Returns a card from the shuffled shoe.

	- ReturnSizeofDeck
	Returns the size of the shoe.

	- CheckEmpty
	Checks of the shuffled shoe is empty.
	
******************************************************************************/

#pragma once
#include <iostream> // std
#include <vector>   // vector<>

// the suit types
enum suit {Spades, Diamonds, Clubs, Hearts};

// the struct for the card
struct card
{
	int value; // holds the value of card
	suit type; // holds the type of suit for card
};

class Deck
{
public:
	// class constructor
	Deck(int numOfDecks);

	// class destructor
	~Deck();

	// creates a shoe for the game
	void CreateCardDeck();

	// overload operator to display the deck
	friend std::ostream& operator<<(std::ostream& os, const Deck& rhs);

	// shuffles the shoe
	void ShuffleDeck();

	// set the display method to display original shoe
	void SetDisplayNormalDeck();

	// set the display method to display shuffled shoe
	void SetDisplayShuffledDeck();

	// returns the shuffled shoe
	std::vector<card>& GetShuffledDeck();

	// returns a card from the shoe
	card ReturnCard();

	// returns the size of the deck
	int ReturnSizeofDeck();

	// checks if the deck is empty 
	void CheckEmpty();

	
private:
	const int numOfDecks_;			   // holds number of decks
	std::vector<card> shoe_{};		   // vector holding a set of cards
	std::vector<card> shuffledShoe_{}; // vector holding the shuffled shoe

	bool displayCheck{}; // changes to display shoe_ or shuffledShoe_

	// private member function that assigns suit type to card
	static void AssignSuit(enum suit &type, const int suit);
};

