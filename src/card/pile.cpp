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


void Pile::addCardTop(Card& card){cards.push_front(card);}
void Pile::addCardBot(Card& card){cards.push_back(card);}
void Pile::remove(int position){cards.erase(cards.begin()+position);}
void Pile::addPileToSelf(Pile &p){ cards.insert(cards.end(), p.cards.begin(),p.cards.end()); }
void Pile::deletePile(){cards.erase(cards.begin(),cards.end());}
void Pile::movePileTo(Pile& p){ p.addPileToSelf(*this); deletePile(); } //Move this pile to pile p.

void Pile::drawFrom(Pile& p, int amount){    
    for(int i=0;i<amount;i++){
        if(!p.cards.empty()){addCardBot(p.cards.front()); p.remove(0);}
    } 
}

void Pile::displayPile(){ //Display all cards in pile p.
    int j=0;
    for (Card i: cards){std::cout<<"["<<j++<<"] "; i.display(); std::cout<<"\n";}
}

void Pile::displayFixed(size_t n){ //Display a fixed number of cards from the pile. If pile size < n, empty lines are printed.
    for(size_t i=0; i<n; i++){
        if(i<cards.size()){
            std::cout<<"["<<i<<"] ";
            cards[i].display();
        }
        std::cout<<'\n';
    }
}