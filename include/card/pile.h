#ifndef PILE_H
#define PILE_H

class Card;
#include<deque>

class Pile{
    

    public:
	std::deque <Card> cards;
	
	size_t getSize() const; 
	Card& getCard(int position);
	//PILE MANIPULATION METHODS//

	//Use this to add a card to the pile
	void addCardTop(Card& card);
	void addCardBot(Card& card);
	
	//Use this to remove given position from this pile of cards.
	void remove(int position);
	

	
	//Add all the elements from pile p into self. Generally, it should be used in tandem with deletePile(). 
	void addPileToSelf(Pile &p);

	//Remove all elements from the pile of cards
	void deletePile();

	//Move all the elements from this pile to a target pile p, then delete this pile. 
	void movePileTo(Pile& p);

	//This function allows to draw a certain amount of cards (amount) from another pile (&p) into self.
	//It also removes the drawn Cards from the origin pile.
	void drawFrom(Pile& p, int amount);

	//This function displays the pile of cards as a simple list.
	void displayPile();

	void displayFixed(size_t n); //Displays a set number of elements from the pile.
};

#endif