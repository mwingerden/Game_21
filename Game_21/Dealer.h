/******************************************************************************
filename    Dealer.h
author      Matthew Wingerden
email		matthew.wingerden@gmail.com

Brief Description:
	This file contains member function implementations for the Dealer class.

	The Functions Include:
	- Dealer 
	This is the constructor for the class that currently does nothing.

	- ~Dealer
	The destructor for the Deck class. Currently does nothing.

	- CheckHand
	Checks Dealers hand for natural blackjack or bust.

	- ClearHand
	Clears the dealers hand variable and other checks.

	- AssignHand
	Assigns a hand of random cards to the dealer.

	- DisplayHand
	Prints out the hand of the dealer.

	- Hit
	This functions adds a card to the dealers hand until his total is above 17
	or busted.

	- DealerStart
	Displays the dealers first card and the unknown.

	- GetTotal
	Returns the dealers total.

	- ReturnHand
	Returns the dealers hand.
	
******************************************************************************/

#pragma once
#include "Deck.h" // for deck object

class Dealer
{
public:
	// the classes constructor
	Dealer();

	// the classes constructor
	~Dealer();

	// checks the hand of the dealer
	bool CheckHand();

	// clears the dealer's hand
	void ClearHand();

	// assigns a hand to the dealer
	void AssignHand(Deck &deck);

	// displays the dealers hand
	void DisplayHand();

	// gives the dealer another card
	void Hit(Deck &deck);

	// starts the game with the first card shown and the second unknown
	void DealerStart();

	// returns the dealer's total
	int GetTotal() const;

	// returns the dealer's hand
	card ReturnHand() const;
private:
	std::vector<card> hand_{}; // the vector to holds the dealer's hand
	bool aceCheck_{};		   // a check for an ace in the hand
	int total_{};			   // hold the dealer's total
};

