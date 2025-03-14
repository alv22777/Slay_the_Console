#include "pile.h"
#include <iostream>
#include "card.h"
#include <random>
#include <algorithm>

//Returns a card in the pile in the given position.
Card& Pile::getCard(int position){
    if(position<0||position>=getSize()){
        throw std::out_of_range("Pile::getCard() - Index out of range.");
    }
    return cards[position];
}

size_t  Pile::getSize()const {return cards.size();}

//PILE MANIPULATION METHODS//

//Use this to add a card to the pile
void Pile::addCardToPile(Card& card){cards.push_back(card);}
//Use this to remove given position from this pile of cards.
void Pile::remove(int position){cards.erase(cards.begin()+position);}

//Use this to randomize the order of the cards in the pile.
void Pile::shufflePile(std::mt19937& seed){
    std::shuffle(cards.begin(),cards.end(),seed);
   std::cout<<"Successfully shuffled "<<getSize()<<" cards.\n";
}

//Add all the elements from pile p into self. Generally, it should be used in tandem with deletePile(). 
void Pile::addPileToSelf(Pile &p){
    cards.insert(cards.end(), p.cards.begin(),p.cards.end());
}

//Remove all elements from the pile of cards
void Pile::deletePile(){cards.erase(cards.begin(),cards.end());}

//Move all the elements from this pile to a target pile p, then delete this pile. 
void Pile::movePileTo(Pile& p){
    p.addPileToSelf(*this);
    deletePile();
}

//This function allows to draw a certain amount of cards (amount) from another pile (&p) into self.
//It also removes the drawn Cards from the origin pile.
void Pile::drawFrom(Pile& p, int amount){
    for(int i=0;i<amount;i++){
        if(p.cards.empty()){std::cerr<<"This pile is empty! No cards left to draw...\n";break;}
        else{addCardToPile(p.cards.front()); p.remove(0);}
    } 
}
//This function displays the pile of cards as a simple list.
void Pile::displayPile(){
    if (cards.empty()){std::cout<<"This pile is empty! Nothing to show!\n"; return;}
    int j=0;
    for (Card i: cards){std::cout<<j++<<". "; i.display();}
}