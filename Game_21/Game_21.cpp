// Game_21.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Deck.h"
#include "Random.h"
#include "Player.h"
#include "Dealer.h"
#include <algorithm>

void EndOfRound(Player &player, const Dealer &dealer, const double bet)
{
	if(player.GetTotal() > dealer.GetTotal() || dealer.GetTotal() > 21)
	{
		std::cout << "You've won this round!" << std::endl;
		std::cout << "Money Gained: $" << bet * 2 << std::endl;
		player.AddToMoney(bet * 2);
	}
	else if(player.GetTotal() == dealer.GetTotal())
	{
		std::cout << "It's a push." << std::endl;
		player.AddToMoney(bet);
	}
	else
	{
		std::cout << "You've lost this round." << std::endl;
		std::cout << "Money lost: $" << bet << std::endl;
	}

	std::cout << "Your total is: $" << player.GetMoney() << std::endl;
}

bool CheckPlayerAmount(double amount)
{
	if(amount < 200 || amount > 1000)
	{
		throw amount;
	}
	return true;
}

int main()
{
	std::string choice{};
	std::string HitStand{};
	bool check{};
	double amount{};
	long double bet{};
	std::cout << "Welcome to the game of BlackJack!" << std::endl;

	do
	{
		std::cout << "Please type the amount of money you want to play with between $200 and $1000: $";
		std::cin >> amount;
		std::cout << std::endl;
		try
		{
			check = CheckPlayerAmount(amount);
		}
		catch(...)
		{
			std::cout << "Please type an amount between $200 and $1000" << std::endl << std::endl;
		}
	} while(!check);

	Player player(amount);

	Dealer dealer;

	Deck deck(52);

	RandomInit();

	deck.CreateCardDeck();

	deck.ShuffleDeck();

	do
	{
		std::cout << "Do you want to play?(Yes or No) ";
		std::cin >> choice;
		std::cout << std::endl;
		std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
		if(!player.CheckMoney())
		{
			std::cout << "You are out of money." << std::endl;
			break;
		}
		if(choice == "yes")
		{
			do
			{
				std::cout << "Type your bet($1 - $" << player.GetMoney() << "): $";
				std::cin >> bet;
				std::cout << std::endl;
				if(bet > player.GetMoney())
				{
					std::cout << "You are betting over you amount of $" << player.GetMoney() << std::endl <<
						std::endl;
				}
				else if(bet < 1)
				{
					std::cout << "Bet is to low" << std::endl;
				}

			}while(!(bet >= 1 && bet <= player.GetMoney()));

			player.SubtractFromMoney(bet);

			player.AssignHand(deck);

			dealer.AssignHand(deck);

			dealer.DealerStart();

			std::cout << std::endl;

			player.DisplayHand();

			do
			{
				do
				{
					std::cout << "Hit or Stand? ";
					std::cin >> HitStand;
					std::transform(HitStand.begin(), HitStand.end(), HitStand.begin(), ::tolower);
				}while(!(HitStand == "hit" || HitStand == "stand"));
			
				if(HitStand == "hit")
				{
					player.Hit(deck);
				}
				else if(HitStand == "stand")
				{
					player.ModifyTotal(10);
				}
				std::cout << std::endl;
				player.DisplayHand();
				std::cout << std::endl;

				if(!player.CheckHand())
				{
					std::cout << "You lost $" << bet << std::endl << std::endl;
					break;
				}

			}while(HitStand != "stand");

			if(player.CheckHand())
			{
				dealer.DisplayHand();

				while(dealer.GetTotal() < 17)
				{
					std::cout << std::endl;
					dealer.Hit(deck);
					std::cout << "The Dealer hitting..." << std::endl;
				}
				std::cout << std::endl;
				
				dealer.DisplayHand();

				std::cout << std::endl << std::endl;

				EndOfRound(player, dealer, bet);
				
				std::cout << std::endl << std::endl;
			}
			

			player.ClearHand();
			dealer.ClearHand();
		}
		

	}while(choice != "no");


	if(!player.CheckMoney())
	{
		std::cout << "Please Try Again Next Time." << std::endl;
	}

	std::cout << std::endl << player << std::endl;

    return 0;
}
