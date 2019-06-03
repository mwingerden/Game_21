#pragma once
#include <string>
#include "Deck.h"

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
	bool CheckMoney() const;
	bool CheckHand() const;
	void ClearHand();
	void AssignHand(Deck &deck);
	void DisplayHand();
	void Hit(Deck &deck);
	friend std::ostream & operator<<(std::ostream &os, const Player &rhs);
private:
	std::vector<card> hand_{};
	bool aceCheck;
	int total;
	double originalMoney_;
	double money_;
	double bet_;
};

