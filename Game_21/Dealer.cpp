/******************************************************************************
filename    Dealer.cpp
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

#include "pch.h"	// visual studio required
#include "Dealer.h" // Holds functions declarations
#include <iostream> // std, cout, endl

/*!****************************************************************************
    Function: Dealer::Dealer()
  
    Description: Constructor for class.

	Inputs: N/A
	
	Outputs: N/A
*/
/*****************************************************************************/
Dealer::Dealer()
{
}

/*!****************************************************************************
    Function: Dealer::~Dealer()
  
    Description: Destructor for class.

	Inputs: N/A
	
	Outputs: N/A
*/
/*****************************************************************************/
Dealer::~Dealer()
{
}

/*!****************************************************************************
    Function: Dealer::CheckHand()
  
    Description: Checks the dealer's hand for natural blackjack or a bust.

	Inputs: N/A
	
	Outputs: Returns true if dealer has natural or bust.
*/
/*****************************************************************************/
bool Dealer::CheckHand()
{
	// checks if total is above 21
	if(total_ > 21)
	{
		// prints out the dealer has busted
		std::cout << "The dealer has busted." << std::endl; 
		return true; // return true
	}
	// checks if dealer's total is 21
	else if(total_ == 21)
	{
		// prints out that dealer has blackjack
		std::cout << "The dealer has a natural BlackJack!" << std::endl;
		return true; // return true
	}
	// checks when dealer has an ace that it equals 21
	else if(aceCheck_ && total_ + 10 == 21)
	{
		total_ += 10; // adds to total
		return false; // returns false
	}

	return false; // return false
}

/*!****************************************************************************
    Function: Dealer::ClearHand()
  
    Description: Checks the dealer's hand for natural blackjack or a bust.

	Inputs: N/A
	
	Outputs: N/A
*/
/*****************************************************************************/
void Dealer::ClearHand()
{
	hand_.clear();     // clears the hand vector
	total_ = 0;        // sets total to 0
	aceCheck_ = false; // sets aceCheck_ to false
}

/*!****************************************************************************
    Function: Dealer::AssignHand(Deck& deck)
  
    Description: Gives the Dealer a hand of cards from the deck.

	Inputs: The Deck of cards.
	
	Outputs: N/A
*/
/*****************************************************************************/
void Dealer::AssignHand(Deck& deck)
{
	card temp{}; // creates a temp card to give to dealer

	// loops through the limit of cards
	for(int i = 0; i < 2; i++)
	{
		deck.CheckEmpty();			// checks if deck is empty
		temp = deck.ReturnCard();   // returns a card from the deck
		hand_.push_back(temp); // pushes the card to the dealer's hand

		// checks if value is greater than 10
		if(temp.value > 10)
		{
			total_ += 10; // adds ten to total
		}
		// else just add value to total
		else
		{
			total_ += temp.value; // adds card value to total
		}
	}
}

/*!****************************************************************************
    Function: Dealer::DisplayHand()
  
    Description: Displays the entire hand of the dealer.

	Inputs: N/A
	
	Outputs: N/A
*/
/*****************************************************************************/
void Dealer::DisplayHand()
{
	// titles the hand being printed
	std::cout << "The Dealer's hand: " << std::endl; 

	// loops through the entire hand
	for(card temp : hand_)
	{
		// checks the value of the card
		switch(temp.value)
		{
		// in case of 1 print that the card is an ace
		case 1:
			std::cout << "An ace of "; // prints card is an ace
			aceCheck_ = true;		   // make aceCheck_ as true
			break;					   // breaks out of statement

		// in case of 11 print that the card is an ace
		case 11:
			std::cout << "Jack of "; // prints card is a Jack
			break;				     // breaks out of statement

		// in case of 12 print that the card is an ace
		case 12:
			std::cout << "King of "; // prints card is a King
			break;					 // breaks out of statement

		// in case of 11 print that the card is an ace
		case 13:
			std::cout << "Queen of "; // prints card is a Queen
			break;					  // breaks out of statement

		// default case
		default:
			std::cout << temp.value << " of "; // prints out value of card
			break;							   // breaks out of statement
		}

		// checks the type of suit 
		switch(temp.type)
		{
		// in case of type 0
		case 0:
			std::cout << "Spades" << std::endl; // print out spades
			break;								// break out of statement

		// in case of type 1
		case 1:
			std::cout << "Diamonds" << std::endl; // print out spades
			break;								  // break out of statement

		// in case of type 2
		case 2:
			std::cout << "Clubs" << std::endl; // print out spades
			break;							   // break out of statement

		// in case of type 3
		case 3:
			std::cout << "Hearts" << std::endl; // print out spades
			break;								// break out of statement

		// default case
		default:
			break; // break out of statement
		}
		
	}

	// establishes what the dealers total is going to be
	std::cout << "The Dealer's total is: ";

	// checks if there is an ace in hand and total plus 11 is over 21
	// if over 21 then assume ace's value is one
	if(aceCheck_ && total_ - 1 + 11 > 21)
	{
		std::cout << total_ << std::endl; // print out total
	}
	// checks if there is an ace in hand and total plus 11 is over 17
	// if in range then ace is assumed value is 11
	else if(aceCheck_ && total_ - 1 + 11 >= 17)
	{
		total_ += 10;					  // adds remaining total 
		std::cout << total_ << std::endl; // prints out total 
	}
	// checks if there is an ace
	// if ace shows different totals with ace being value of 1 and 11
	else if(aceCheck_)
	{
		// prints out total
		std::cout << total_ << " or " << total_ - 1 + 11 << std::endl;
	}
	else
	{
		std::cout << total_ << std::endl; // prints the total
	}
}

/*!****************************************************************************
    Function: Dealer::Hit(Deck& deck)
  
    Description: Gives the dealer another card.

	Inputs: The deck of cards.
	
	Outputs: N/A
*/
/*****************************************************************************/
void Dealer::Hit(Deck& deck)
{
	deck.CheckEmpty();		    // checks if the deck is empty
	card temp{};				// creates an empty card
	temp = deck.ReturnCard();   // assigns temp a card
	hand_.push_back(temp); // pushes temp to the hand of the dealer

	// checks if value is 10
	if(temp.value > 10)
	{
		total_ += 10; // adds ten to total 
	}
	else
	{
		total_ += temp.value; // adds value to total
	}
}

/*!****************************************************************************
    Function: Dealer::DealerStart()
  
    Description: Prints out the first card of the dealer with the unknown.

	Inputs: N/A
	
	Outputs: N/A
*/
/*****************************************************************************/
void Dealer::DealerStart()
{
	// checks if hand is empty
	if(!hand_.empty())
	{
		// establishes the dealer's hand
		std::cout << "The Dealer has: " << std::endl;

		// assigns the temp card
 		card temp = hand_.at(0);

		// checks the value of the card
		switch(temp.value)
		{
		// in case of 1 print that the card is an ace
		case 1:
			std::cout << "An ace of "; // prints card is an ace
			aceCheck_ = true;		   // make aceCheck_ as true
			break;					   // breaks out of statement

		// in case of 11 print that the card is an ace
		case 11:
			std::cout << "Jack of "; // prints card is a Jack
			break;				     // breaks out of statement

		// in case of 12 print that the card is an ace
		case 12:
			std::cout << "King of "; // prints card is a King
			break;					 // breaks out of statement

		// in case of 11 print that the card is an ace
		case 13:
			std::cout << "Queen of "; // prints card is a Queen
			break;					  // breaks out of statement

		// default case
		default:
			std::cout << temp.value << " of "; // prints out value of card
			break;							   // breaks out of statement
		}

		switch(temp.type)
		{
		// in case of type 0
		case 0:
			std::cout << "Spades" << std::endl; // print out spades
			break;								// break out of statement

		// in case of type 1
		case 1:
			std::cout << "Diamonds" << std::endl; // print out spades
			break;								  // break out of statement

		// in case of type 2
		case 2:
			std::cout << "Clubs" << std::endl; // print out spades
			break;							   // break out of statement

		// in case of type 3
		case 3:
			std::cout << "Hearts" << std::endl; // print out spades
			break;								// break out of statement

		// default case
		default:
			break; // break out of statement
		}

		// establishes the unknown of the second card
		std::cout << " face up and one unknown face down." << std::endl;
	}
	
}

/*!****************************************************************************
    Function: Dealer::GetTotal() const
  
    Description: Returns the dealer's total.

	Inputs: N/A
	
	Outputs: Returns the total.
*/
/*****************************************************************************/
int Dealer::GetTotal() const
{
	return total_; // returns total
}

/*!****************************************************************************
    Function: Dealer::ReturnHand() const
  
    Description: Returns the first card of the dealer's hand.

	Inputs: N/A
	
	Outputs: Returns the card.
*/
/*****************************************************************************/
card Dealer::ReturnHand() const
{
	return hand_.at(0); // returns the first card
}
