#ifndef PILE_H
#define PILE_H

class Card; enum class CardType;

//There can be 6 types of piles, although the pile itself does not require knowledge of which type it is. 
//The player class will have 6 piles, and the pile manipulation methods will be used by the player class to manipulate the piles. 
//The game class will also use the pile manipulation methods to manipulate the piles during combat.

enum class PileID{deck, combat_deck, hand, draw, discard, exhaust};

#include<deque>
struct IndexedCard{ Card* c; int index; };

class Pile{
    

    public:
	std::deque <Card> cards;
	
	size_t getSize() const; 
	Card& getCard(int position);
	
	//PILE MANIPULATION METHODS//

	void addCardTop(Card& card);
	void addCardBot(Card& card);
	
	void remove(int position);
	
	void addPileToSelf(Pile &p);

	void deletePile();

	void movePileTo(Pile& p);

	void drawFrom(Pile& p, int amount);
	bool empty();
	
	//UI

	void displayPile();
	void displayFixed(size_t n); //Displays a set number of elements from the pile.

	//LOGIC
	
	std::deque<int> findMatchingIndexes(CardType c);
	std::deque<int> findNonMatchingIndexes(CardType c);

	void sortBy(int category, bool asc); 
	void displaySortedBy(int category, bool asc);

	std::deque<IndexedCard> indexed();
};

#endif