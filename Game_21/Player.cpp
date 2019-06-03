#include "pch.h"
#include "Player.h"
#include "Random.h"
#include <iostream>


Player::Player(double money)
{
	originalMoney_ = money;
	money_ = money;
	bet_ = 0;
	total = 0;
	aceCheck = false;
}


Player::~Player()
{
}

void Player::SetBet(double bet)
{
	bet_ = bet;
}

void Player::AddToMoney(double amount)
{
	money_ += amount;
}

void Player::SubtractFromMoney(double amount) 
{
	money_ -= amount;
}

bool Player::CheckMoney() const
{
	if(money_ > 0.0)
	{
		return 1;
	}

	return 0;
}

double Player::GetMoney() const
{
	return money_;
}


std::ostream& operator<<(std::ostream& os, const Player& rhs)
{
	os << "With the original amount of money of: $" << rhs.originalMoney_ << std::endl;

	double difference = rhs.money_ - rhs.originalMoney_;

	if(difference > 0)
	{
		os << "You have gained $" << difference << "." << std::endl;
		os <<"Your current amount is: $" << rhs.money_;
	}
	else if(difference < 0)
	{
		os << "You have lost $" << difference * -1 << "." << std::endl;
		os << "Your current amount is: $" << rhs.money_;
	}
	else
	{
		os << " has remained the same." << std::endl;
	}

	return os;
}

void Player::AssignHand(Deck& deck)
{
	card temp{};
	for(int i = 0; i < 2; i++)
	{
		deck.CheckEmpty();
		temp = deck.ReturnCard(RandomRange(0, deck.ReturnSizeofDeck()));
		hand_.push_back(temp);
		if(temp.value > 10)
		{
			total += 10;
		}
		else
		{
			total += temp.value;
		}
	}
}

void Player::Hit(Deck& deck)
{
	deck.CheckEmpty();
	card temp{};
	temp = deck.ReturnCard(RandomRange(0, deck.ReturnSizeofDeck()));
	hand_.push_back(temp);
	if(temp.value > 10)
	{
		total += 10;
	}
	else
	{
		total += temp.value;
	}
}


void Player::DisplayHand()
{
	std::cout << "Your hand: " << std::endl;

	for(card temp : hand_)
	{
		switch(temp.value)
		{
		case 1:
			std::cout << "An ace of ";
			aceCheck = true;
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

	std::cout << "Your total is: ";
	
	if(aceCheck && total - 1 + 11 > 21)
	{
		std::cout << total << std::endl;
	}
	else if(aceCheck)
	{
		std::cout << total << " or " << total - 1 + 11 << std::endl;
	}
	else
	{
		std::cout << total << std::endl;
	}
}

bool Player::CheckHand() const
{
	if(total > 21)
	{
		std::cout << "You have busted." << std::endl;
		return false;
	}

	return true;
}


void Player::ClearHand()
{
	hand_.clear();
	total = 0;
}

void Player::ModifyTotal(int num)
{
	if(aceCheck)
	{
		total += num;
	}
}

int Player::GetTotal() const
{
	return total;
}
