#include<iostream>
#include "pile.h"
#include "constants.h"
#include "character.h"
#include<windows.h>
using std::string; using std::cout;

Character::Character(string N, int MHP, int HP, int ME, int E, int B, Pile D, Card p)
    :name(N), max_HP(MHP), HP(HP), max_energy(ME), energy(E), block(B), deck(D), played(p){}

string Character::getName() {return name;}
int Character::getAttribute(PlayerAttribute att){
    switch(att){
        case PlayerAttribute::HP: return HP;
        case PlayerAttribute::max_HP: return max_HP;
        case PlayerAttribute::energy: return energy;
        case PlayerAttribute::max_energy: return max_energy;
        case PlayerAttribute::block: return block;
    }
}

Card& Character::getCardFromPile(PileType type, int position){
    switch(type){
        case PileType::deck: return deck.getCard(position);
        case PileType::combat_deck: return combat_deck.getCard(position);
        case PileType::hand: return hand.getCard(position);
        case PileType::draw: return draw.getCard(position);
        case PileType::discard: return discard.getCard(position);
        case PileType::exhaust: return exhaust.getCard(position);            
    }
}
Card& Character::getPlayed(){return played;}

int Character::getPlayerPileSize(PileType type){
    switch(type){
        case PileType::deck: return deck.getSize();
        case PileType::combat_deck: return combat_deck.getSize();
        case PileType::hand: return hand.getSize();
        case PileType::draw: return draw.getSize();
        case PileType::discard: return discard.getSize();
        case PileType::exhaust: return exhaust.getSize();
    }
}


void Character::setName(const string& n){name = n;}
void Character::setAttribute(PlayerAttribute att, int value){
    switch(att){
        case PlayerAttribute::HP: HP = value; break;
        case PlayerAttribute::max_HP: max_HP = value; break;
        case PlayerAttribute::energy: energy = value; break;
        case PlayerAttribute::max_energy: max_energy = value; break;
        case PlayerAttribute::block: block = value; break;
    }
}
void Character::setPlayed(Card& c){played = c;}

//Changes chosen attribute by an amount delta.
void Character::changeAttribute(PlayerAttribute att, int Delta){
    switch(att){
        case PlayerAttribute::HP: 
            HP += Delta;
            cout<<((Delta>0)? "Gained ":"Lost ")<<abs(Delta)<<" HP!\n"; break; 
            if(HP>max_HP){
                cout<<"Can't have more HP than max HP!\n";
                setAttribute(PlayerAttribute::HP,max_HP);
            }
            break;
        case PlayerAttribute::max_HP: 
            max_HP += Delta; 
            cout<<((Delta>0)? "Gained ":"Lost ")<<abs(Delta)<<" max HP!\n"; break; 
        case PlayerAttribute::energy:
            energy += Delta; 
            cout<<((Delta>0)? "Gained ":"Lost ")<<abs(Delta)<<" energy!\n"; break;
        case PlayerAttribute::max_energy: 
            max_energy += Delta; 
            cout<<((Delta>0)? "Gained ":"Lost ")<<abs(Delta)<<" max energy!\n"; break;
        case PlayerAttribute::block: 
            block += Delta; 
            cout<<((Delta>0)? "Gained ":"Lost ")<<abs(Delta)<<" block!\n";
            if(block>MAX_BLOCK){
                cout<<"Reached maximum block!\n";
                setAttribute(PlayerAttribute::block,MAX_BLOCK);
            }
            break;
    }
}
void Character::StartCombat(std::mt19937& seed){
    cout<<"Creating combat deck...\n"; combat_deck.addPileToSelf(deck);
    cout<<"Shuffling Combat deck...\n";	combat_deck.shufflePile(seed);
    cout<<"Creating Draw Pile...\n";
    combat_deck.movePileTo(draw); draw.displayPile();
    
    hand.drawFrom(draw,5);
    Sleep(1000);
}

void Character::addToPlayerPile(PileType type, Card& c){
    switch(type){
        case PileType::deck: deck.addCardToPile(c); break;
        case PileType::combat_deck: combat_deck.addCardToPile(c); break;
        case PileType::hand: hand.addCardToPile(c); break;
        case PileType::draw: draw.addCardToPile(c); break;
        case PileType::discard: discard.addCardToPile(c); break;
        case PileType::exhaust: exhaust.addCardToPile(c); break;
    }
}

void Character::removeFromPlayerPile(PileType type, int position){
    switch(type){
        case PileType::deck: deck.remove(position); break;
        case PileType::combat_deck: combat_deck.remove(position); break;
        case PileType::hand: hand.remove(position);break;
        case PileType::draw: draw.remove(position);break;
        case PileType::discard: discard.remove(position);break;
        case PileType::exhaust: exhaust.remove(position);break;
    }
}

void Character::deletePlayerPile(PileType type){
    switch(type){
        case PileType::deck: deck.deletePile(); break;
        case PileType::combat_deck: combat_deck.deletePile(); break;
        case PileType::hand: hand.deletePile(); break;
        case PileType::draw: draw.deletePile(); break;
        case PileType::discard: discard.deletePile(); break;
        case PileType::exhaust: exhaust.deletePile(); break;
    }
}

void Character::displayPlayerPile(PileType type){
    switch(type){
        case PileType::deck: deck.displayPile(); break;
        case PileType::combat_deck: combat_deck.displayPile(); break;
        case PileType::hand: hand.displayPile(); break;
        case PileType::draw: draw.displayPile(); break;
        case PileType::discard: discard.displayPile(); break;
        case PileType::exhaust: exhaust.displayPile(); break;
    }
}

void Character::displayStatus(){
    //STATUS BAR
    cout<<name<<'\n';
    cout<<"HP: "<<HP<<"/"<<max_HP<<'\n';
    cout<<"Energy : "<<energy<<"/"<<max_energy<<'\n';	
}

void Character::playCardFromHand(int pos){
    Card played = getCardFromPile(PileType::hand,pos);
    cout<<"Playing: "<<played.getName()<<"...";
    changeAttribute(PlayerAttribute::energy,-played.getEnergyCost());

    //EFFECT foo();

    cout<<"YOU JUST PLAYED "<<played.getName()<<"!"<<'\n';
    addToPlayerPile(PileType::discard, played);
    removeFromPlayerPile(PileType::hand, pos);
}

void Character::setupPlayer(int choice){
    switch(choice){
    case 1:
        setName("The Ironclad"); 
        setAttribute(PlayerAttribute::max_HP,ICL_STARTING_MAX_HP); setAttribute(PlayerAttribute::HP,ICL_STARTING_MAX_HP); 
        setAttribute(PlayerAttribute::max_energy,STARTING_ENERGY); setAttribute(PlayerAttribute::energy,STARTING_ENERGY);
        deck.addPileToSelf(ICL_STARTER_DECK);
        setPlayed(blank_card);
        break;
    case 2:
        setName("The Silent"); 
        setAttribute(PlayerAttribute::max_HP,SLT_STARTING_MAX_HP); setAttribute(PlayerAttribute::HP,SLT_STARTING_MAX_HP); 
        setAttribute(PlayerAttribute::max_energy,STARTING_ENERGY); setAttribute(PlayerAttribute::energy,STARTING_ENERGY);
        deck.addPileToSelf(SLT_STARTER_DECK);
        setPlayed(blank_card);
        break;
    }

}