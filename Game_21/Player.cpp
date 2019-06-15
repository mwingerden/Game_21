#include "pch.h"
#include "Player.h"
#include "Random.h"
#include <iostream>
#include "Dealer.h"
#include <algorithm>


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
		os << "You have neither lost nor gain any money." << std::endl;
	}

	return os;
}

void Player::AssignHand(Deck& deck)
{
	card temp{};
	for(int i = 0; i < 2; i++)
	{
		deck.CheckEmpty();
		temp = deck.ReturnCard();
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
	temp = deck.ReturnCard();
	hand_.push_back(temp);
	if(temp.value > 10)
	{
		total += 10;
	}
	else if(doubleDown_ && temp.value == 1 && total + 11 < 21)
	{
		total += 11;
	}
	else
	{
		total += temp.value;
	}
}

void Player::HitSecond(Deck& deck)
{
	deck.CheckEmpty();
	card temp{};
	temp = deck.ReturnCard();
	secondHand_.push_back(temp);
	if(temp.value > 10)
	{
		secondTotal += 10;
	}
	else
	{
		secondTotal += temp.value;
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

void Player::DisplaySecondHand()
{
	std::cout << "Your second hand: " << std::endl;

	for(card temp : secondHand_)
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
	
	if(aceCheck && secondTotal - 1 + 11 > 21)
	{
		std::cout << secondTotal << std::endl;
	}
	else if(aceCheck)
	{
		std::cout << secondTotal << " or " << secondTotal - 1 + 11 << std::endl;
	}
	else
	{
		std::cout << secondTotal << std::endl;
	}
}

bool Player::CheckHand() const
{
	if(total > 21)
	{
		return false;
	}

	return true;
}

bool Player::CheckSecondHand() const
{
	if(secondTotal > 21)
	{
		return false;
	}

	return true;
}


void Player::ClearHand()
{
	hand_.clear();
	secondHand_.clear();
	total = 0;
	secondTotal = 0;
	aceCheck = false;
	insurance = false;
	split = false;
	doubleDown_ = false;
}

void Player::ModifyTotal(int num)
{
	if(aceCheck && secondTotal + num < 21)
	{
		secondTotal += num;
	}
	else if(aceCheck && total + num < 21)
	{
		total += num;
	}
}

int Player::GetTotal() const
{
	return total;
}

int Player::GetSecondTotal() const
{
	return secondTotal;
}


bool Player::CheckNatural(double bet, Dealer &dealer)
{
	if(aceCheck && total + 10 == 21 && dealer.GetTotal() + 10 != 21)
	{
		std::cout << std::endl;
		std::cout << "You have a Natural BlackJack!" << std::endl;
		dealer.DisplayHand();
		std::cout << "The Dealer doesn't have a Natural." << std::endl;
		std::cout << "You have earned: $" << bet * 1.5 << std::endl;
		AddToMoney(bet * 1.5);
		return true;
	}
	else if(aceCheck && total + 10 == 21 && dealer.GetTotal() + 10 == 21)
	{
		std::cout << std::endl;
		std::cout << "You have a Natural BlackJack!" << std::endl;
		std::cout << "The Dealer has a Natural." << std::endl;
		std::cout << "It's a push." << std::endl;
		return true;
	}

	return false;
}

bool Player::DoubleDown()
{
	std::string choice{};
	if(total >= 9 && total <= 11)
	{
		do
		{
			std::cout << "Do you want to double down?(Yes or No): ";
			std::cin >> choice;
			std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
		}while(choice != "yes" && choice != "no");
		
		if(choice == "yes")
		{
			doubleDown_ = true;
			return true;
		}
	}
	return false;
}

bool Player::Insurance(Dealer& dealer)
{
	card temp = dealer.ReturnHand();
	if(temp.value == 1 && !insurance)
	{
		std::cout << "The Dealer has an ace showing." << std::endl;
		std::string choice{};
		do
		{
			std::cout << "Do you want Insurance?(Yes or No)";
			std::cin >> choice;
			std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
		}while(choice != "yes" && choice != "no");
		
		if(choice == "yes")
		{
			insurance = true;
			std::cout << std::endl;
			return true;
		}
	}
	return false;
}

bool Player::GetInsurance()
{
	return insurance;
}

bool Player::GetSplit()
{
	return split;
}


bool Player::Split()
{
	if(hand_.at(0).value == hand_.at(1).value)
	{
		std::string choice{};
		do
		{
			std::cout << "Do you want to split?(Yes or No)";
			std::cin >> choice;
			std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
		}while(choice != "yes" && choice != "no");

		if(choice == "yes")
		{
			split = true;
			secondHand_.push_back(hand_.at(1));
			if(secondHand_.at(0).value >= 11)
			{
				secondTotal += 10;
			}
			else
			{
				secondTotal = secondHand_.at(0).value;
			}
			total -= secondTotal;
			hand_.pop_back();
			std::cout << std::endl << std::endl;
			return true;
		}
	}

	return false;
}

std::vector<card>& Player::GetHand()
{
	return hand_;
}

std::vector<card>& Player::GetSecondHand()
{
	return secondHand_;
}

