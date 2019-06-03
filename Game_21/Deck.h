#pragma once
#include <vector>

enum suits {Spades, Diamonds, Clubs, Hearts};
struct card
{
	int value;
	suits type;
};

class Deck
{
public:
	Deck(int deck);
	~Deck();
	void CreateCardDeck();
	void ShuffleDeck();
	void SetDisplayNormalDeck();
	void SetDisplayShuffledDeck();
	card ReturnCard(int pos);
	std::vector<card>& GetShuffledDeck();
	size_t ReturnSizeofDeck();
	void CheckEmpty();
	friend std::ostream& operator<<(std::ostream& os, const Deck& rhs);
private:
	const int MaxDeck_;
	bool check{};
	std::vector<card> deck_{};
	std::vector<card> shuffledDeck_{};
	static void AssignSuit(enum suits &type, const int suit);
	card returnEmptyCard() const;
};

