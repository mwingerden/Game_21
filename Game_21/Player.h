/******************************************************************************
filename    Player.h
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
#pragma once
#include <string>
#include "Deck.h"
#include "Dealer.h"

class Player
{
public:
	Player(double money = 0);
	~Player();
	void SetBet(double bet);
	void AddToMoney(double amount);
	void SubtractFromMoney(double amount);
	void ModifyTotal(int num);
	double GetMoney() const;
	int GetTotal() const;
	int GetSecondTotal() const;
	bool CheckMoney() const;
	bool CheckHand() const;
	bool CheckSecondHand() const;
	bool CheckNatural(Dealer &dealer);
	bool Insurance(Dealer &dealer);
	bool Split();
	bool DoubleDown();
	bool GetInsurance();
	bool GetSplit();
	std::vector<card>& GetHand();
	std::vector<card>& GetSecondHand();
	void ClearHand();
	void AssignHand(Deck &deck);
	void DisplayHand();
	void DisplaySecondHand();
	void Hit(Deck &deck);
	void HitSecond(Deck &deck);
	friend std::ostream & operator<<(std::ostream &os, const Player &rhs);
private:
	std::vector<card> hand_{};		 // vector for hand
	std::vector<card> secondHand_{}; // vector for second hand for split
	bool aceCheck;					 // keeps track for ace in hand
	bool insurance{};				 // keeps track for insurance
	bool split{};					 // keeps track for split
	bool doubleDown_{};				 // keeps track for double down
	int total;						 // keeps track of total 
	int secondTotal{};				 // keeps track for second total
	double originalMoney_;			 // holds for original amount
	double money_;					 // keeps track of money lost/gained
	double bet_;					 // keeps track for the bet
};

