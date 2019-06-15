#pragma once
#include <iostream>
#include <vector>

enum suit {Spades, Diamonds, Clubs, Hearts};
struct card
{
	int value;
	suit type;
};

class Deck
{
public:
	Deck(int numOfDecks);
	~Deck();
	void CreateCardDeck();
	void ShuffleDeck();
	void SetDisplayNormalDeck();
	void SetDisplayShuffledDeck();
	card ReturnCard();
	std::vector<card>& GetShuffledDeck();
	int ReturnSizeofDeck();
	void CheckEmpty();
	friend std::ostream& operator<<(std::ostream& os, const Deck& rhs);
private:
	const int numOfDecks_;
	bool check{};
	std::vector<card> shoe_{};
	std::vector<card> shuffledDeck_{};
	static void AssignSuit(enum suit &type, const int suit);
	//  card returnEmptyCard() const;
};

