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
	if(player.GetSplit())
	{
		if(player.GetTotal() > dealer.GetTotal() || dealer.GetTotal() > 21)
		{
			std::cout << "You've won the first hand!" << std::endl;
			std::cout << "Money Gained: $" << bet << std::endl;
			player.AddToMoney(bet);
		}
		else if(player.GetTotal() > 21)
		{
			std::cout << "You busted your first hand." << std::endl << std::endl;
		}
		else
		{
			std::cout << "You've lost your first hand this round." << std::endl;
			std::cout << "Money lost: $" << bet << std::endl;
			player.SubtractFromMoney(bet);
		}

		if(player.GetSecondTotal() > dealer.GetTotal() || dealer.GetTotal() > 21)
		{
			std::cout << "You've won the second hand!" << std::endl;
			std::cout << "Money Gained: $" << bet << std::endl;
			player.AddToMoney(bet);
		}
		else if(player.GetSecondTotal() > 21)
		{
			std::cout << "You busted your second hand." << std::endl << std::endl;
		}
		else
		{
			std::cout << "You've lost your second hand this round." << std::endl;
			std::cout << "Money lost: $" << bet << std::endl;
			player.SubtractFromMoney(bet);
		}
	}
	else if(player.GetTotal() > dealer.GetTotal() || dealer.GetTotal() > 21)
	{
		std::cout << "You've won this round!" << std::endl;
		std::cout << "Money Gained: $" << bet << std::endl;
		player.AddToMoney(bet);
	}
	else if(player.GetTotal() == dealer.GetTotal())
	{
		std::cout << "It's a push." << std::endl;
	}
	else if(dealer.GetTotal() == 21)
	{
		std::cout << "The Dealer has a Natural BlackJack." << std::endl;
		std::cout << "You've lost this round." << std::endl;
		std::cout << "Money lost: $" << bet << std::endl;
		player.SubtractFromMoney(bet);
		if(player.GetInsurance())
		{
			std::cout << "But you have insurance." << std::endl;
			std::cout << "Money Gained: $" << (bet * 1.5) * 2 << std::endl;
			player.AddToMoney((bet * 1.5) * 2);
		}
	}
	else
	{
		std::cout << "You've lost this round." << std::endl;
		std::cout << "Money lost: $" << bet << std::endl;
		player.SubtractFromMoney(bet);
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

void PlayerPlay(Player &player, Deck &deck, Dealer &dealer, double bet)
{
	std::string HitStand{};

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
			std::cout << "You Have Busted!" << std::endl;
			std::cout << "You lost $" << bet << std::endl << std::endl;
			player.SubtractFromMoney(bet);
			break;
		}

	}while(HitStand != "stand");

	if(player.Insurance(dealer))
	{
		std::cout << "You have an insurance of: $" << bet * 1.5 << std::endl << std::endl;
	}
}

void DealerPlay(Dealer &dealer, Deck &deck)
{
	std::cout << "The Dealer revealed the unknown card" << std::endl;
	dealer.DisplayHand();

	while(dealer.GetTotal() < 17)
	{
		std::cout << std::endl;
		dealer.Hit(deck);
		std::cout << "The Dealer hitting..." << std::endl;
		if(dealer.CheckHand())
		{
			break;
		}
	}
	std::cout << std::endl;

	std::cout << "The Dealer's final hand:" << std::endl;
	dealer.DisplayHand();

	if(dealer.GetTotal() > 21)
	{
		std::cout << "The Dealer busted!" << std::endl;
	}

}

int main()
{
	int amountOfDecks{};
	std::string choice{};
	bool check{};
	double playerMoney{};
	double bet{};
	std::cout << "Welcome to the game of BlackJack!" << std::endl;

	do
	{
		std::cout << "Please type the amount of money you want to play with between $200 and $1000: $";
		std::cin >> playerMoney;
		std::cout << std::endl;
		if(std::cin.fail())
		{	
			std::cout << "You didn't type an amount." << std::endl << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
		}
		else
		{
			try
			{
				check = CheckPlayerAmount(playerMoney);
			}
			catch(...)
			{
				std::cout << "Please type an amount between $200 and $1000" << std::endl << std::endl;
			}
		}
		
	} while(!check);


	do
	{
		std::cout << "How many decks of cards do you want to play with?: ";
		std::cin >> amountOfDecks;
		std::cout << std::endl;
	}while(!(amountOfDecks >= 1));

	Player player(playerMoney);

	Dealer dealer;

	Deck deck(amountOfDecks);

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

				if(std::cin.fail())
				{
					std::cout << "You didn't type in a value." << std::endl << std::endl;
					std::cin.clear();
					std::cin.ignore(256, '\n');
				}
				else
				{
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
				}
			}while(!(bet >= 1 && bet <= player.GetMoney()));

			player.AssignHand(deck);

			dealer.AssignHand(deck);

			dealer.DealerStart();

			std::cout << std::endl;

			player.DisplayHand();

			if(player.CheckNatural(dealer))
			{
				std::cout << "Your total: $" << player.GetMoney() << std::endl << std::endl << std::endl;
			}
			else
			{
				if(player.DoubleDown())
				{
					player.Hit(deck);
					std::cout << std::endl;
					player.DisplayHand();
					std::cout << std::endl << std::endl;
					bet *= 2;
				}
				else if(player.Split())
				{
					player.DisplayHand();
					do
					{
						do
						{
							std::cout << "Hit or Stand? ";
							std::cin >> choice;
							std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
						}while(!(choice == "hit" || choice == "stand"));
					
						if(choice == "hit")
						{
							player.Hit(deck);
						}
						else if(choice == "stand")
						{
							player.ModifyTotal(10);
						}

						std::cout << std::endl;
						player.DisplayHand();
						std::cout << std::endl;
				
						if(!player.CheckHand())
						{
							std::cout << "You Have Busted!" << std::endl;
							std::cout << "You lost $" << bet << std::endl << std::endl;
							player.SubtractFromMoney(bet);
							break;
						}
				
					}while(choice != "stand");

					player.DisplaySecondHand();

					do
					{
						do
						{
							std::cout << "Hit or Stand? ";
							std::cin >> choice;
							std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
						}while(!(choice == "hit" || choice == "stand"));
					
						if(choice == "hit")
						{
							player.HitSecond(deck);
						}
						else if(choice == "stand")
						{
							player.ModifyTotal(10);
						}

						std::cout << std::endl;
						player.DisplaySecondHand();
						std::cout << std::endl;
				
						if(!player.CheckSecondHand())
						{
							std::cout << "You Have Busted!" << std::endl;
							std::cout << "You lost $" << bet << std::endl << std::endl;
							player.SubtractFromMoney(bet);
							break;
						}
				
					}while(choice != "stand");
				}
				else
				{
					PlayerPlay(player, deck, dealer, bet);
				}

				if(player.CheckHand())
				{
					DealerPlay(dealer, deck);

					std::cout << std::endl << std::endl;

					EndOfRound(player, dealer, bet);
					
					std::cout << std::endl << std::endl;
				}
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
