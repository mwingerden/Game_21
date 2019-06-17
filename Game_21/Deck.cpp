/******************************************************************************
filename    Deck.cpp
author      Matthew Wingerden
email		matthew.wingerden@gmail.com

Brief Description:
	This file contains member function implementations for the Deck class.

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

#include "pch.h"	 // needed in visual studio
#include "Deck.h"	 // function declarations
#include <iostream>  // cout
#include <algorithm> // random_shuffle

/*!****************************************************************************
    Function: Deck::Deck(int numOfDecks) : numOfDecks_(numOfDecks)
  
    Description: Constructor for class. Initializes numOfDecks.

	Inputs: numOfDecks - The number of decks to be created.
	
	Outputs: N/A
*/
/*****************************************************************************/
Deck::Deck(int numOfDecks) : numOfDecks_(numOfDecks)
{
}

/*!****************************************************************************
    Function: Deck::~Deck()
  
    Description: Destructor for class. Does not currently do anything.

	Inputs: N/A.
	
	Outputs: N/A
*/
/*****************************************************************************/
Deck::~Deck()
{
}

/*!****************************************************************************
    Function: Deck::CreateCardDeck()
  
    Description: Creates a multiple-deck of shoes.

	Inputs: N/A.
	
	Outputs: N/A
*/
/*****************************************************************************/
void Deck::CreateCardDeck()
{
	int value{1}; // tracks the value the current card being created will have
	int type{0};  // tracks the type of suite the card being created will have
	card temp{};  // a temporary card to be created and pushed back

	// a loop that creates a card and pushes back to the shoe vector
	for(int i = 0; i < 52 * numOfDecks_; i++)
	{
		// checks of the loop reached the max of one deck
		if(i % 52 == 0)
		{
			value = 1; // resets value to 1
			type = 0;  // resets type to 0
		}
		// checks if the value is over 13 to go to next suit
		else if(value > 13)
		{
			value = 1; // resets value to 1
			type++;    // increments type
		}

		temp.value = value++;				  // Assigns value then increments
		AssignSuit(temp.type, type); // Assigns a suit to the card
		shoe_.push_back(temp);			  // pushes the card to shoe
	}
}

/*!****************************************************************************
    Function: Deck::AssignSuit(suit& type, const int suit)
  
    Description: Assigns a suit to the cards type.

	Inputs: type - the cards type

			suit - the value of the suit
	
	Outputs: N/A
*/
/*****************************************************************************/
void Deck::AssignSuit(suit& type, const int suit)
{
	// switch statement that assigns the suit type
	switch(suit)
	{
	// in case of type 0 assign Spades to cards type
	case 0:
		type = Spades; // assigns Spades to type
		break;		   // breaks out of switch  

	// in case of type 1 assign Diamonds to cards type
	case 1:
		type = Diamonds; // assigns Diamonds to type
		break;			 // breaks out of switch  

	// in case of type 2 assign Clubs to cards type
	case 2:
		type = Clubs; // assigns Clubs to type
		break;		  // breaks out of switch  

	// in case of type 3 assign Hearts to cards type
	case 3:
		type = Hearts; // assigns Hearts to type
		break;		   // breaks out of switch 
		
	// if default case then nothing happens
	default:
		break; // breaks out of switch 
	}
}

/*!****************************************************************************
    Function: operator<<(std::ostream& os, const Deck& rhs)
  
    Description: Displays either the original shoe or the shuffled shoe.

	Inputs: os - The ostream to print out.

			rhs - The class to be printed out.
	
	Outputs: The the entire multi-deck
*/
/*****************************************************************************/
std::ostream& operator<<(std::ostream& os, const Deck& rhs)
{
	// the temp vector to hold shuffled shoe or the original shoe
	std::vector<card> temp{};

	// checks displayCheck to assign wither the shuffledShoe_ or the original shoe
	if(rhs.displayCheck)
		temp = rhs.shuffledShoe_; // assigns the shuffledShoe_ to temp 
	else
		temp = rhs.shoe_; // assigns shoe to temp

	// loops through the entirety of temp
	for(int i = 0; i < rhs.numOfDecks_; i++)
	{
		// checks if value is equivalent to 1
		if(temp.at(i).value == 1)
		{
			os << "An Ace of "; // prints out that the card is an ace
		}
		// checks of value is above 10
		else if(temp.at(i).value > 10)
		{
			// switch statement for printing out the right card
			switch(temp.at(i).value)
			{
			// in case of value 11 
			case 11:
				os << "Jack of "; // prints out that the card is a jack
				break;			  // breaks the out of statement

			// in case of value 12 
			case 12:
				os << "Queen of "; // prints out that the card is a queen
				break;			   // breaks the out of statement

			// in case of value 13
			case 13:
				os << "King of "; // prints out that the card is a king
				break;			  // breaks the out of statement

			// default case
			default:
				break; // breaks out of statement
			}
		}
		// else just prints out the value
		else
		{
			os << temp.at(i).value << " of "; // prints out the value
		}

		// checks for the suite type
		switch(temp.at(i).type)
		{
		// in case of type 0
		case 0:
			os << "Spades"; // prints out type spades
			break;			// breaks out of statement

		// in case of type 1
		case 1:
			os << "Diamonds"; // prints out type diamonds
			break;			  // breaks out of statement

		// in case of type 2
		case 2:
			os << "Clubs"; // prints out type clubs
			break;		   // breaks out of statement

		// in case of type 3
		case 3:
			os << "Hearts"; // prints out type hearts
			break;			// breaks out of statement

		// default case
		default:
			break; // breaks out o f statement
		}
		os << std::endl; // prints out a new line
	}
	return os; // returns the text
}

/*!****************************************************************************
    Function: Deck::ShuffleDeck()
  
    Description: Shuffles the shoe

	Inputs: N/A
	
	Outputs: N/A
*/
/*****************************************************************************/
void Deck::ShuffleDeck()
{
	shuffledShoe_ = shoe_; // assigns shoe_ to shuffledShoe_

	// shuffles shuffledShoe_
	std::random_shuffle(shuffledShoe_.begin(), shuffledShoe_.end());
}

/*!****************************************************************************
    Function: Deck::SetDisplayNormalDeck()
  
    Description: Sets displayCheck to false.

	Inputs: N/A
	
	Outputs: N/A
*/
/*****************************************************************************/
void Deck::SetDisplayNormalDeck()
{
	displayCheck = false;
}

/*!****************************************************************************
    Function: Deck::SetDisplayNormalDeck()
  
    Description: Sets displayCheck to true.

	Inputs: N/A
	
	Outputs: N/A
*/
/*****************************************************************************/
void Deck::SetDisplayShuffledDeck()
{
	displayCheck = true;
}

/*!****************************************************************************
    Function: Deck::GetShuffledDeck()
  
    Description: Returns the shuffledShoe_

	Inputs: N/A
	
	Outputs: returns the shuffledShoe_
*/
/*****************************************************************************/
std::vector<card>& Deck::GetShuffledDeck()
{
	return shuffledShoe_; // returns shuffledShoe_
}

/*!****************************************************************************
    Function: Deck::ReturnCard()
  
    Description: Returns the card from the back shuffledShoe_

	Inputs: N/A
	
	Outputs: returns a card from shuffledShoe_
*/
/*****************************************************************************/
card Deck::ReturnCard()
{
	card temp{}; // a temporary object type card

	// gets the last card of shuffledShoe_
	temp = shuffledShoe_.at(shuffledShoe_.size() - 1);

	shuffledShoe_.pop_back(); // pops the last card
	return temp;			  // returns the card
}

/*!****************************************************************************
    Function: Deck::ReturnSizeofDeck()
  
    Description: Returns the size of shuffledShoe_

	Inputs: N/A
	
	Outputs: returns the size
*/
/*****************************************************************************/
int Deck::ReturnSizeofDeck()
{
	return (int)shuffledShoe_.size(); // returns the size of the shoe
}

/*!****************************************************************************
    Function: Deck::CheckEmpty()
  
    Description: checks if shuffledShoe_ is empty. Reshuffles if true.

	Inputs: N/A
	
	Outputs: N/A
*/
/*****************************************************************************/
void Deck::CheckEmpty()
{
	// checks if empty
	if(shuffledShoe_.empty())
	{
		ShuffleDeck(); // shuffles the shoe again
	}
}
