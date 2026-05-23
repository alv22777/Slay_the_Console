#include "card/pile.h"
#include "card/card.h"
#include <iostream>
#include <algorithm>

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

bool Pile::empty(){return cards.empty();}

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

std::deque<int> Pile::findMatchingIndexes(CardType c){
    int pile_size = static_cast<int>(getSize());

    if(pile_size == 0){return {};}

    std::deque<int> result;
    for(int i = pile_size-1; i>=0;i--){
        if(cards[i].getCardType() == c){
            result.push_back(i);
        }
    }

    return result;
}

std::deque<int> Pile::findNonMatchingIndexes(CardType c){
    int pile_size = static_cast<int>(getSize());

    if(pile_size == 0){return {};}

    std::deque<int> result;
    for(int i = pile_size-1; i>=0;i--){
        if(cards[i].getCardType() != c){
            result.push_back(i);
        }
    }

    return result;
}

// 0: ID, 1: Cost, 2: Type, 3: Name, default: 0.
void Pile::sortBy(int category, bool asc){
    
    if(asc){

        switch(category){
            case 0: //By card ID    
               std::sort(cards.begin(),cards.end(), [](Card& a, Card& b){
                    return a.getID()<b.getID();
               });
            break;
    
            case 1: //By cost
               std::sort(cards.begin(),cards.end(), [](Card& a, Card& b){
                    return a.getEnergyCost()<b.getEnergyCost();
               });
            break;
            case 2: //By card type
                std::sort(cards.begin(),cards.end(), [](Card& a, Card& b){
                        return a.getCardType()<b.getCardType();   
                });
            break;
            case 3: //By name
                std::sort(cards.begin(),cards.end(), [](Card& a, Card& b){
                    return a.getName()<b.getName();
               });
            break;
    
            default: //Default to card ID
                std::sort(cards.begin(),cards.end(), [](Card& a, Card& b){
                    return a.getID()<b.getID();
               });
            break;
        }
    }
    else{
        switch(category){
            case 0: //By card ID    
               std::sort(cards.begin(),cards.end(), [](Card& a, Card& b){
                    return a.getID()>b.getID();
               });
            break;
    
            case 1: //By cost
               std::sort(cards.begin(),cards.end(), [](Card& a, Card& b){
                    return a.getEnergyCost()>b.getEnergyCost();
               });
            break;
            case 2: //By card type
                std::sort(cards.begin(),cards.end(), [](Card& a, Card& b){
                        return a.getCardType()>b.getCardType();   
                });
            break;
            case 3: //By name
                std::sort(cards.begin(),cards.end(), [](Card& a, Card& b){
                    return a.getName()>b.getName();
               });
            break;
    
            default: //Default to card ID
                std::sort(cards.begin(),cards.end(), [](Card& a, Card& b){
                    return a.getID()>b.getID();
               });
            break;
        }

    }
}

std::deque<IndexedCard> Pile::indexed()
{
    std::deque<IndexedCard> indexed_cards;

    for(int i = 0; i<getSize(); i++){
        IndexedCard iCard = {&getCard(i),i};
        indexed_cards.push_back(iCard);
    }

    std::sort(indexed_cards.begin(), indexed_cards.end(), [](IndexedCard a, IndexedCard b){
        return (a.c)->getID() < (b.c)->getID();
    });

    return indexed_cards;
}

// 0: ID, 1: Cost, 2: Type, 3: Name, default: 0.
void Pile::displaySortedBy(int category, bool asc){
    Pile copy = *this;
    copy.sortBy(category,asc);
    copy.displayPile();
}