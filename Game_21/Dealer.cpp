#include "pch.h"
#include "Dealer.h"
#include "Random.h"
#include <iostream>


Dealer::Dealer()
{
}


Dealer::~Dealer()
{
}

bool Dealer::CheckHand() const
{
	if(total_ > 21)
	{
		std::cout << "The dealer has busted." << std::endl;
		return false;
	}
	else if(total_ == 21)
	{
		std::cout << "The dealer has a natural BlackJack!" << std::endl;
		return false;
	}

	return true;
}

void Dealer::ClearHand()
{
	hand_.clear();
	total_ = 0;
}

void Dealer::AssignHand(Deck& deck)
{
	card temp{};
	for(int i = 0; i < 2; i++)
	{
		deck.CheckEmpty();
		temp = deck.ReturnCard(RandomRange(0, deck.ReturnSizeofDeck()));
		hand_.push_back(temp);
		if(temp.value > 10)
		{
			total_ += 10;
		}
		else
		{
			total_ += temp.value;
		}
	}
}

void Dealer::DisplayHand()
{
	std::cout << "The Dealer's hand: " << std::endl;

	for(card temp : hand_)
	{
		switch(temp.value)
		{
		case 1:
			std::cout << "An ace of ";
			aceCheck_ = true;
			break;
		case 11:
			std::cout << "Jack of ";
			break;
		case 12:
			std::cout << "King of ";
			break;
		case 13:
			std::cout << "Queen of ";
			break;
		default:
			std::cout << temp.value << " of ";
			break;
		}

		switch(temp.type)
		{
		case 0:
			std::cout << "Spades" << std::endl;
			break;
		case 1:
			std::cout << "Diamonds" << std::endl;
			break;
		case 2:
			std::cout << "Clubs" << std::endl;
			break;
		case 3:
			std::cout << "Hearts" << std::endl;
			break;
		}
	}

	std::cout << "The Dealer's total is: ";
	
	if(aceCheck_ && total_ - 1 + 11 > 21)
	{
		std::cout << total_ << std::endl;
	}
	else if(aceCheck_ && total_ - 1 + 11 >= 17)
	{
		total_ += 10;
		std::cout << total_ << std::endl;
	}
	else if(aceCheck_)
	{
		std::cout << total_ << " or " << total_ - 1 + 11 << std::endl;
	}
	else
	{
		std::cout << total_ << std::endl;
	}
}

void Dealer::Hit(Deck& deck)
{
	deck.CheckEmpty();
	card temp{};
	temp = deck.ReturnCard(RandomRange(0, deck.ReturnSizeofDeck()));
	hand_.push_back(temp);
	if(temp.value > 10)
	{
		total_ += 10;
	}
	else
	{
		total_ += temp.value;
	}
}

void Dealer::DealerStart()
{
	if(!hand_.empty())
	{
		std::cout << "The Dealer has: " << std::endl;
 		card temp = hand_.at(0);

		switch(temp.value)
		{
		case 1:
			std::cout << "An ace of ";
			aceCheck_ = true;
			break;
		case 11:
			std::cout << "Jack of ";
			break;
		case 12:
			std::cout << "King of ";
			break;
		case 13:
			std::cout << "Queen of ";
			break;
		default:
			std::cout << temp.value << " of ";
			break;
		}

		switch(temp.type)
		{
		case 0:
			std::cout << "Spades";
			break;
		case 1:
			std::cout << "Diamonds";
			break;
		case 2:
			std::cout << "Clubs";
			break;
		case 3:
			std::cout << "Hearts";
			break;
		}

		std::cout << " face up and one unknown face down." << std::endl;
	}
	
}

int Dealer::GetTotal() const
{
	return total_;
}
