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
	bool CheckNatural(double bet, Dealer &dealer);
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
	std::vector<card> hand_{};
	std::vector<card> secondHand_{};
	bool aceCheck;
	bool insurance{};
	bool split{};
	bool doubleDown_{};
	int total;
	int secondTotal{};
	double originalMoney_;
	double money_;
	double bet_;
};

