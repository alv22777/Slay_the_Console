#include "card/pile.h"
#include "card/card.h"
#include <iostream>

//Returns a card in the pile in the given position.
Card& Pile::getCard(int position){
    if(position<0||position>=getSize()){
        throw std::out_of_range("Pile::getCard() - Index out of range.");
    }
    return cards[position];
}

size_t  Pile::getSize()const {return cards.size();}

//PILE MANIPULATION METHODS//


void Pile::addCardToPile(Card& card){cards.push_back(card);}

void Pile::remove(int position){cards.erase(cards.begin()+position);}




void Pile::addPileToSelf(Pile &p){ cards.insert(cards.end(), p.cards.begin(),p.cards.end()); }
void Pile::deletePile(){cards.erase(cards.begin(),cards.end());}

void Pile::movePileTo(Pile& p){ p.addPileToSelf(*this); deletePile(); } //Move this pile to pile p.

//This function allows to draw a certain amount of cards (amount) from another pile (&p) into self.
//It also removes the drawn Cards from the origin pile.
void Pile::drawFrom(Pile& p, int amount){
    for(int i=0;i<amount;i++){
        if(p.cards.empty()){std::cerr<<"This pile is empty! No cards left to draw...\n";break;}
        else{addCardToPile(p.cards.front()); p.remove(0);}
        
    } 
}


void Pile::displayPile(){
    if (cards.empty()){std::cout<<"This pile is empty!\n"; return;}
    int j=0;
    for (Card i: cards){std::cout<<"["<<j++<<"] "; i.display();}
}

void Pile::displayFixed(size_t n){
    for(size_t i=0; i<n; i++){
        
        if(i<cards.size()){
            std::cout<<"["<<i<<"] ";
            cards[i].display();
        }

        std::cout<<'\n';

    }
}