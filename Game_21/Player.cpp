/******************************************************************************
filename    Player.cpp
author      Matthew Wingerden
email		matthew.wingerden@gmail.com

Brief Description:
	This file contains member function implementations for the Player class.

	- Player
	Constructor for the class.

	- ~Player
	Destructor for class. Does not do anything.

	- SetBet
	Sets the bet of the player.

	- AddToMoney
	Adds money to initial pot.

	- SubtractFromMoney
	Subtracts from initial pot.

	- CheckMoney
	Checks if money is not 0.

	- GetMoney
	Return the amount of money in the player's pot.


	- operator<<
	Overloads << to print out the amount of money of the player.

	- AssignHand
	Gives the hand to the player.

	- Hit
	Gives a card to the player's hand.

	- HitSecond
	Hit for the second hand for the split. 


	- DisplayHand
	Displays the hand of the player. 

	- DisplaySecondHand
	Displays the seconds hand for a split.


	- CheckHand
	Checks the hand of player for a natural or a bust.

	- CheckSecondHand
	Checks the second hand on a split for natural or bust.


	- ClearHand
	Empties the hand and sets everything to null.

	- ModifyTotal
	Modifies the total if there is an ace in the hand. 

	- GetTotal
	Returns the total of the player. 

	- GetSecondTotal
	Returns the second total of the player when in a split. 


	- CheckNatural
	Checks for the natural blackjack.

	- DoubleDown
	Handles double down implementation.

	- Insurance
	Handles insurance implementation.

	- GetInsurance
	Returns if Player asked for insurance. 

	- GetSplit
	Returns if player asked for a split.


	- Split
	Handles the split implementation. 

	- GetHand
	Returns the hand of the player. 

	- GetSecondHand
	Returns the second hand of the player for a split. 
	
******************************************************************************/

#include "pch.h"	 // required by visual studio
#include "Player.h"  // member function declarations
#include <iostream>  // std, cout, endl
#include "Dealer.h"  // Dealer implementation
#include <algorithm> // transform

/*!****************************************************************************
    Function: Player(double money)
  
    Description: Constructor for class. Assigns the amount of money.

	Inputs: The amount of money the player's starts with.
	
	Outputs: N/A
*/
/*****************************************************************************/
Player::Player(double money)
{
	originalMoney_ = money; // assigns money to originalMoney_ 
	money_ = money;			// assigns money to money_ to keep track
	bet_ = 0;				// sets bet_ to 0
	total = 0;				// sets total to 0
	aceCheck = false;		// sets aceCheck to false
}

/*!****************************************************************************
    Function: ~Player()
  
    Description: Destructor for the class. 

	Inputs: N/A
	
	Outputs: N/A
*/
/*****************************************************************************/
Player::~Player()
{
}

/*!****************************************************************************
    Function: SetBet(double bet)
  
    Description: Sets the bet for the player.

	Inputs: The current bet for the round.
	
	Outputs: N/A
*/
/*****************************************************************************/
void Player::SetBet(double bet)
{
	bet_ = bet; // sets bet to bet_ to keep track
}

/*!****************************************************************************
    Function: Player::AddToMoney(double amount)
  
    Description: Adds money earned from the round to money_.

	Inputs: The amount won from the round.
	
	Outputs: N/A
*/
/*****************************************************************************/
void Player::AddToMoney(double amount)
{
	money_ += amount; // Adds amount to money_
}

/*!****************************************************************************
    Function: Player::SubtractFromMoney(double amount) 
  
    Description: Takes away money from the lost round. 

	Inputs: The amount lost from the round.
	
	Outputs: N/A
*/
/*****************************************************************************/
void Player::SubtractFromMoney(double amount) 
{
	money_ -= amount; // subtracts amount from money_
}

/*!****************************************************************************
    Function: Player::CheckMoney()
  
    Description: Checks if player's money is empty.

	Inputs: N/A
	
	Outputs: Returns if the if the money does not equal 0
*/
/*****************************************************************************/
bool Player::CheckMoney() const
{ 
	// checks if money_ is greater than 0
	if(money_ > 0.0)
	{
		return true; // returns true
	}

	return false; // returns false
}

/*!****************************************************************************
    Function: Player::GetMoney()
  
    Description: Returns the current amount of money.

	Inputs: N/A
	
	Outputs: Returns the money_
*/
/*****************************************************************************/
double Player::GetMoney() const
{
	return money_; // returns money_
}

/*!****************************************************************************
    Function: std::ostream& operator<<(std::ostream& os, const Player& rhs)
  
    Description: Prints out the original amount of money the player started
				 with and how much the player lost/gained.

	Inputs: - os
			The ostream to send the output to the screen.

			- rhs
			The player class with data to print out. 
	
	Outputs: Returns the text to print out.
*/
/*****************************************************************************/
std::ostream& operator<<(std::ostream& os, const Player& rhs)
{
	// prints out the original amount
	os << "With the original amount of money of: $" << rhs.originalMoney_ << std::endl;

	// gets the difference of original money and current money
	double difference = rhs.money_ - rhs.originalMoney_; 

	// checks if the difference is greater than 0
	if(difference > 0)
	{
		// prints out the difference gained and the current amount
		os << "You have gained $" << difference << "." << std::endl;
		os <<"Your current amount is: $" << rhs.money_;
	}
	// checks if difference is less than 0
	else if(difference < 0)
	{
		// prints out the difference lost and the current amount
		os << "You have lost $" << difference * -1 << "." << std::endl;
		os << "Your current amount is: $" << rhs.money_;
	}
	else
	{
		// prints out that the difference is 0
		os << "You have neither lost nor gain any money." << std::endl;
	}

	return os; // returns the istream of text
}

/*!****************************************************************************
    Function: Player::AssignHand(Deck& deck)
  
    Description: Gives a hand of cards to the player.

	Inputs: - deck
			The deck of cards
	
	Outputs: N/A
*/
/*****************************************************************************/
void Player::AssignHand(Deck& deck)
{
	card temp{}; // temp object with card qualities

	// loops through the desired amount of cards
	for(int i = 0; i < 2; i++)
	{
		deck.CheckEmpty();			// check if deck is empty
		temp = deck.ReturnCard();   // returns the card from the deck
		hand_.push_back(temp); // pushes the card in the player's hand

		// checks if value is greater than 10
		if(temp.value > 10)
		{
			total += 10; // adds 10 to total
		}
		else
		{
			total += temp.value; // adds value to total
		}
	}
}

/*!****************************************************************************
    Function: Player::Hit(Deck& deck)
  
    Description: Gives a card to the players hand.

	Inputs: - deck
			The deck of cards
	
	Outputs: N/A
*/
/*****************************************************************************/
void Player::Hit(Deck& deck)
{
	deck.CheckEmpty();			// checks if deck is empty
	card temp{};				// card object 
	temp = deck.ReturnCard();   // returns card from deck
	hand_.push_back(temp); // pushes card to the hand of player

	// checks if value is greater than 10
	if(temp.value > 10)
	{
		total += 10; // adds 10 to total
	}
	// checks if double down is in affect and not busted
	else if(doubleDown_ && temp.value == 1 && total + 11 < 21)
	{
		total += 11; // adds 11 to total
	}
	else
	{
		total += temp.value; // adds value to total
	}
}

/*!****************************************************************************
    Function: Player::HitSecond(Deck& deck)
  
    Description: Gives a card to the players hand when split in affect.

	Inputs: - deck
			The deck of cards
	
	Outputs: N/A
*/
/*****************************************************************************/
void Player::HitSecond(Deck& deck)
{
	deck.CheckEmpty();				  // checks if deck is empty
	card temp{};					  // card object 
	temp = deck.ReturnCard();		  // returns card from deck
	secondHand_.push_back(temp); // pushes card to the hand of player

	// checks if value is greater than 10
	if(temp.value > 10)
	{
		total += 10; // adds 10 to total
	}
	else
	{
		secondTotal += temp.value; // adds value to secondTotal
	}
}

/*!****************************************************************************
    Function: Player::DisplayHand()
  
    Description: Displays the hand of the player.

	Inputs: N/A
	
	Outputs: N/A
*/
/*****************************************************************************/
void Player::DisplayHand()
{
	// establishes that the player's hand is to be printed
	std::cout << "Your hand: " << std::endl;

	// loops through the entire hand
	for(card temp : hand_)
	{
		// checks the value of the card
		switch(temp.value)
		{
		// in case of 1 print that the card is an ace
		case 1:
			std::cout << "An ace of "; // prints card is an ace
			aceCheck = true;		   // make aceCheck_ as true
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
	}

	// establish the player's total to be printed
	std::cout << "Your total is: ";

	// checks for ace in hand and if 11 is a bust
	if(aceCheck && total - 1 + 11 > 21)
	{
		std::cout << total << std::endl; // prints out total with ace as 1
	}
	// checks if ace in hand
	else if(aceCheck)
	{
		// prints out total with ace as 1 and 11
		std::cout << total << " or " << total - 1 + 11 << std::endl;
	}
	else
	{
		std::cout << total << std::endl; // prints out total
	}
}

/*!****************************************************************************
    Function: Player::DisplaySecondHand()
  
    Description: Displays the hand of the player when split occurs.

	Inputs: N/A
	
	Outputs: N/A
*/
/*****************************************************************************/
void Player::DisplaySecondHand()
{
	// Sets up the second hand to be printed
	std::cout << "Your second hand: " << std::endl;

	// loops through the entire hand
	for(card temp : secondHand_)
	{
		// checks the value of the card
		switch(temp.value)
		{
		// in case of 1 print that the card is an ace
		case 1:
			std::cout << "An ace of "; // prints card is an ace
			aceCheck = true;		   // make aceCheck_ as true
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
	}

	// sets up the total to be printed
	std::cout << "Your total is: ";

	// checks if ace n hand and is a bust with 11
	if(aceCheck && secondTotal - 1 + 11 > 21)
	{
		std::cout << secondTotal << std::endl; // prints out total with ace = 1
	}
	else if(aceCheck)
	{
		// prints out total with ace value = 1 and 11
		std::cout << secondTotal << " or " << secondTotal - 1 + 11 << std::endl;
	}
	else
	{
		std::cout << secondTotal << std::endl; // prints out second total
	}
}

/*!****************************************************************************
    Function: Player::CheckHand()
  
    Description: Checks player's hand for bust.

	Inputs: N/A
	
	Outputs: Returns true if total isn't a bust.
*/
/*****************************************************************************/
bool Player::CheckHand() const
{
	// checks if total is greater than 21
	if(total > 21)
	{
		return false; // returns false
	}

	return true; // returns true
}

/*!****************************************************************************
    Function: Player::CheckSecondHand()
  
    Description: Checks player's hand for bust if split.

	Inputs: N/A
	
	Outputs: Returns true if total isn't a bust.
*/
/*****************************************************************************/
bool Player::CheckSecondHand() const
{
	// checks if total is greater than 21
	if(secondTotal > 21)
	{
		return false; // returns false
	}

	return true; // returns true
}

/*!****************************************************************************
    Function: Player::ClearHand()
  
    Description: Clears the players hand.

	Inputs: N/A
	
	Outputs: N/A
*/
/*****************************************************************************/
void Player::ClearHand()
{
	hand_.clear();		 // clears hand
	secondHand_.clear(); // clears second hand
	total = 0;			 // sets total to 0
	secondTotal = 0;	 // sets second total to 0
	aceCheck = false;    // sets aceCheck to false
	insurance = false;   // sets insurance to false
	split = false;		 // sets split to false
	doubleDown_ = false; // sets doubleDown to false
}

/*!****************************************************************************
    Function: Player::ModifyTotal(int num)
  
    Description: Changes total if player stands with an ace that does not bust.

	Inputs: The amount the total to be manipulated.
	
	Outputs: N/A
*/
/*****************************************************************************/
void Player::ModifyTotal(int num)
{
	// checks for the ace and secondTotal does not bust
	if(aceCheck && secondTotal + num < 21)
	{
		secondTotal += num; // adds total to secondTotal
	}
	// checks for the ace and total does not bust
	else if(aceCheck && total + num < 21)
	{
		total += num; // adds total to total
	}
}

/*!****************************************************************************
    Function: Player::GetTotal()
  
    Description: Returns the total of the player's hand.

	Inputs: N/A
	
	Outputs: Returns the total.
*/
/*****************************************************************************/
int Player::GetTotal() const
{
	return total; // returns total
}

/*!****************************************************************************
    Function: Player::GetTotal()
  
    Description: Returns the secondTotal of the player's hand .

	Inputs: N/A
	
	Outputs: Returns the total.
*/
/*****************************************************************************/
int Player::GetSecondTotal() const
{
	return secondTotal; // returns secondTotal
}

/*!****************************************************************************
    Function: Player::CheckNatural(double bet, Dealer &dealer)
  
    Description: Checks if player has a natural blackjack against the dealer

	Inputs: - dealer
			Compares total to player's total.
	
	Outputs: Returns true if player has a natural.
*/
/*****************************************************************************/
bool Player::CheckNatural(Dealer &dealer)
{
	// checks for ace and natural against the dealer
	if(aceCheck && total + 10 == 21 && dealer.GetTotal() + 10 != 21)
	{
		std::cout << std::endl; // creates the new line

		// tells user that player has a natural
		std::cout << "You have a Natural BlackJack!" << std::endl;

		dealer.DisplayHand(); // displays dealers hand

		// tell user dealer does not have a natural
		std::cout << "The Dealer doesn't have a Natural." << std::endl;
		std::cout << "You have earned: $" << bet_ * 1.5 << std::endl;

		AddToMoney(bet_ * 1.5); // adds money 1.5 times the amount
		return true;				  // returns true
	}
	// checks for ace and natural for dealer
	else if(aceCheck && total + 10 == 21 && dealer.GetTotal() + 10 == 21)
	{
		std::cout << std::endl; // creates new line

		// tell user that player and dealer have a natural
		std::cout << "You have a Natural BlackJack!" << std::endl;
		std::cout << "The Dealer has a Natural." << std::endl;
		std::cout << "It's a push." << std::endl;

		return true; // returns true
	}

	return false; // returns false
}

/*!****************************************************************************
    Function: Player::DoubleDown()
  
    Description: Asks player to double down.

	Inputs: N/A
	
	Outputs: Returns true if player wants a double down.
*/
/*****************************************************************************/
bool Player::DoubleDown()
{
	std::string choice{}; // a string to hold the choice of player

	// checks if total is between 9 and 11
	if(total >= 9 && total <= 11)
	{
		// loops until user types yes or no
		do
		{  
			// prompts user
			std::cout << "Do you want to double down?(Yes or No): ";
			// assigns player choice to choice
			std::cin >> choice;
			// transforms choice to lower case
			std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
		}while(choice != "yes" && choice != "no");

		// checks if choice is yes
		if(choice == "yes")
		{
			doubleDown_ = true; // assigns double down is true
			return true; // returns true
		}
	}
	return false; // returns false
}

/*!****************************************************************************
    Function: Player::Insurance(Dealer& dealer)
  
    Description: Asks player for insurance.

	Inputs: - dealer
			To check if the dealer's first card is an ace.
	
	Outputs: Returns true if player asked for insurance.
*/
/*****************************************************************************/
bool Player::Insurance(Dealer& dealer)
{
	card temp = dealer.ReturnHand(); // assigns temp to first card of dealer

	// checks if dealers card is 1 and player hasn't asked for insurance yet
	if(temp.value == 1 && !insurance)
	{
		// tell user that dealer has an ace showing
		std::cout << "The Dealer has an ace showing." << std::endl;

		std::string choice{}; // choice is to hold the response of player

		// loops until user types yes or no 
		do
		{
			// prompts user if insurance is wanted
			std::cout << "Do you want Insurance?(Yes or No)";

			std::cin >> choice; // assign input to choice

			// transform choice to lower case
			std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
		}while(choice != "yes" && choice != "no");

		// checks if choice is yes
		if(choice == "yes")
		{
			insurance = true;       // assigns true to insurance
			std::cout << std::endl; // creates new line
			return true;			// returns true
		}
	}
	return false; // returns false
}

/*!****************************************************************************
    Function: Player::GetInsurance()
  
    Description: Returns insurance.

	Inputs: N/A
	
	Outputs: Returns whether insurance is true or not.
*/
/*****************************************************************************/
bool Player::GetInsurance()
{
	return insurance; // returns insurance
}

/*!****************************************************************************
    Function: Player::GetSplit()
  
    Description: Returns split.

	Inputs: N/A
	
	Outputs: Returns whether split is true or not.
*/
/*****************************************************************************/
bool Player::GetSplit()
{
	return split;
}

/*!****************************************************************************
    Function: Player::Split()
  
    Description: Handles split implementation.

	Inputs: N/A
	
	Outputs: Returns true if player wants to split
*/
/*****************************************************************************/
bool Player::Split()
{
	// checks if hand value are the same
	if(hand_.at(0).value == hand_.at(1).value)
	{
		std::string choice{}; // choice to hold player's input
		do
		{
			// prompts user 
			std::cout << "Do you want to split?(Yes or No)";

			std::cin >> choice; // assigns choice to user input

			// transforms choice to lower case
			std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
		}while(choice != "yes" && choice != "no");

		// checks choice equals yes
		if(choice == "yes")
		{
			split = true; // assign split to true

			// pushes second card to second hand
			secondHand_.push_back(hand_.at(1));

			// checks second card value is greater than ten
			if(secondHand_.at(0).value > 10)
			{
				secondTotal += 10; // add 10 to secondTotal
			}
			else
			{
				// add value to secondTotal
				secondTotal = secondHand_.at(0).value;
			}

			total -= secondTotal; // subtracts total taken away
			hand_.pop_back();	  // removes second card from first hand

			// create two new lines
			std::cout << std::endl << std::endl;

			return true; // return true
		}
	}

	return false; // return false
}

/*!****************************************************************************
    Function: Player::GetHand()
  
    Description: Returns players hand.

	Inputs: N/A
	
	Outputs: Returns vector.
*/
/*****************************************************************************/
std::vector<card>& Player::GetHand()
{
	return hand_; // returns hand
}

/*!****************************************************************************
    Function: Player::GetSecondHand()
  
    Description: Returns players second hand.

	Inputs: N/A
	
	Outputs: Returns vector.
*/
/*****************************************************************************/
std::vector<card>& Player::GetSecondHand()
{
	return secondHand_; // returns second hand
}

