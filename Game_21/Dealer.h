#pragma once
#include "Deck.h"

class Dealer
{
public:
	Dealer();
	~Dealer();

	bool CheckHand() const;
	void ClearHand();
	void AssignHand(Deck &deck);
	void DealerStart();
	void DisplayHand();
	void Hit(Deck &deck);
	int GetTotal() const;
private:
	std::vector<card> hand_{};
	bool aceCheck_{};
	int total_{};
};

