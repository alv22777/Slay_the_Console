#ifndef PILE_H
#define PILE_H

class Card; enum class CardType;
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
	std::deque<IndexedCard> indexed(bool display);
};

#endif