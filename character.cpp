#include "character.h"
#include "constants.h"

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
        default : return 0;
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
        default : return blank_card;            
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
        default : return 0;
    }
}


void Character::setName(const string& n){name = n;}
void Character::setAttribute(PlayerAttribute att, int value){
    switch(att){
        case PlayerAttribute::HP: HP = value; cout<<"HP set to "<<value<<".\n"; break;
        case PlayerAttribute::max_HP: max_HP = value; cout<<"Max HP set to "<<value<<".\n"; break;
        case PlayerAttribute::energy: energy = value; cout<<"Energy set to "<<value<<".\n"; break;
        case PlayerAttribute::max_energy: max_energy = value; cout<<"Max Energy set to "<<value<<".\n"; break;
        case PlayerAttribute::block: block = value; cout<<"Block set to "<<value<<".\n"; break;
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

void Character::drawCards(int amount, std::mt19937& seed){

    hand.drawFrom(draw, amount);
    if(hand.getSize()<amount){ //If we couldn't draw the full amount of cards, try shuffling discard into draw and drawing the rest.
        cout<<"Shuffling discard into draw pile...\n";
        discard.movePileTo(draw); draw.shufflePile(seed);
        hand.drawFrom(draw, amount-hand.getSize());
    }
}
void Character::discardHand(){
    hand.movePileTo(discard);
}

void Character::displayStatus(){
    //STATUS BAR
    cout<<name<<'\n';
    cout<<"HP: "<<HP<<"/"<<max_HP<<'\n';
    cout<<"Energy : "<<energy<<"/"<<max_energy<<'\n';	
    cout<<"Block: "<<block<<'\n';
}

void Character::playCardFromHand(int pos){
    
    Card played = getCardFromPile(PileType::hand,pos);
    int currentEnergy = getAttribute(PlayerAttribute::energy);

    if(currentEnergy >= played.getEnergyCost()){
        
        changeAttribute(PlayerAttribute::energy,-played.getEnergyCost());
        
        cout<<"Playing: "<<played.getName()<<"...";;
        //Remove card from hand and apply its effects. While the card is resolving, it is neither on the discard, exhaust nor draw pile, so it can't be affected by effects that target those piles. After resolution, the card is moved to the discard pile.        
        removeFromPlayerPile(PileType::hand, pos);

        //Look for the vector of effects in the card and apply them one by one. Allows for multiple effects to be applied in the order they are listed on the card.
        played.applyEffects(*this);

        //Card is discarded.
        addToPlayerPile(PileType::discard, played);
        
        

    }
    else{cout<<"Not enough energy!\n";} //Player can't play the card if they don't have enough energy to pay for it.

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