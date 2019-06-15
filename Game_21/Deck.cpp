#include "pch.h"
#include "Deck.h"
#include <iostream>
#include <algorithm>


Deck::Deck(int numOfDecks) : numOfDecks_(numOfDecks)
{
}


Deck::~Deck()
{
}

void Deck::CreateCardDeck()
{
	int value{1};
	int type{0};
	card temp{};
	for(int i = 0; i < numOfDecks_; i++)
	{
		if(value > 13)
		{
			value = 1;
			type++;
		}
		temp.value = value++;
		AssignSuit(temp.type, type);
		
		shoe_.push_back(temp);
	}
}

void Deck::AssignSuit(suit& type, const int suit)
{
	switch(suit)
	{
	case 0:
		type = Spades;
		break;
	case 1:
		type = Diamonds;
		break;
	case 2:
		type = Clubs;
		break;
	case 3:
		type = Hearts;
		break;
	default:
		break;
	}
}

std::ostream& operator<<(std::ostream& os, const Deck& rhs)
{
	std::vector<card> temp{};
	if(rhs.check)
		temp = rhs.shuffledDeck_;
	else
		temp = rhs.shoe_;

	for(int i = 0; i < rhs.numOfDecks_; i++)
	{
		if(temp.at(i).value == 1)
		{
			os << "An Ace of ";
		}
		else if(temp.at(i).value > 10)
		{
			switch(temp.at(i).value)
			{
			case 11:
				os << "Jack of ";
				break;
			case 12:
				os << "Queen of ";
				break;
			case 13:
				os << "King of ";
				break;
			default:
				break;
			}
		}
		else
		{
			os << temp.at(i).value << " of ";
		}
		 
		switch(temp.at(i).type)
		{
		case 0:
			os << "Spades";
			break;
		case 1:
			os << "Diamonds";
			break;
		case 2:
			os << "Clubs";
			break;
		case 3:
			os << "Hearts";
			break;
		default:
			break;

		
		}
		os << std::endl;
	}
	return os;
}


void Deck::ShuffleDeck()
{
	shuffledDeck_ = shoe_;

	std::random_shuffle(shuffledDeck_.begin(), shuffledDeck_.end());
}

void Deck::SetDisplayNormalDeck()
{
	check = false;
}

void Deck::SetDisplayShuffledDeck()
{
	check = true;
}

std::vector<card>& Deck::GetShuffledDeck()
{
	return shuffledDeck_;
}

card Deck::ReturnCard()
{
	card temp{};
	temp = shuffledDeck_.at(shuffledDeck_.size() - 1);
	shuffledDeck_.pop_back();;
	return temp;
}
int Deck::ReturnSizeofDeck()
{
	return (int)shuffledDeck_.size();
}

void Deck::CheckEmpty()
{
	if(shuffledDeck_.empty())
	{
		ShuffleDeck();
	}
}
