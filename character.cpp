#include "character.h"
#include "constants.h"
#include "game.h"


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
        case PlayerAttribute::block: block = value; break;
    }
}
void Character::setPlayed(Card& c){played = c;}

//Changes chosen attribute by an amount delta.
void Character::changeAttribute(PlayerAttribute att, int Delta){
    switch(att){
        case PlayerAttribute::HP: 
            HP += Delta;
            cout<<name<<" has "<<((Delta>0)? "Gained ":"Lost ")<<abs(Delta)<<" HP!\n"; break; 
            if(HP>max_HP){
                cout<<"Can't have more HP than max HP!\n";
                setAttribute(PlayerAttribute::HP,max_HP);
            }
            break;
        case PlayerAttribute::max_HP: 
            max_HP += Delta; 
            cout<<name<<" has "<<((Delta>0)? "Gained ":"Lost ")<<abs(Delta)<<" max HP!\n"; break; 
        case PlayerAttribute::energy:
            energy += Delta; 
            cout<<name<<" has "<<((Delta>0)? "Gained ":"Lost ")<<abs(Delta)<<" energy!\n"; break;
        case PlayerAttribute::max_energy: 
            max_energy += Delta; 
            cout<<name<<" has "<<((Delta>0)? "Gained ":"Lost ")<<abs(Delta)<<" max energy!\n"; break;
        case PlayerAttribute::block: 
            block += Delta; 
            cout<<name<<" has "<<((Delta>0)? "Gained ":"Lost ")<<abs(Delta)<<" block!\n";
            if(block>MAX_BLOCK){
                cout<<"Reached maximum block!\n";
                setAttribute(PlayerAttribute::block,MAX_BLOCK);
            }
            break;
    }
}

//This method allows a Character to initiate combat.
void Character::StartCombat(Game& game){

    cout<<this->name<<" is initiating combat!\n";
    combat_deck.addPileToSelf(deck); //Create the combat deck (copy of master deck)
    game.rng.shuffle(combat_deck.cards); //Shuffle the deck
    combat_deck.movePileTo(draw); //Make the combat deck the new draw pile.
    
    //Reset energy and block.
    setAttribute(PlayerAttribute::energy, this->max_energy);
    setAttribute(PlayerAttribute::block,0);
    
    //Draw 5
    drawCards(5,game);
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
    //Switched responsibility from Game to Character.
    switch(type){
        case PileType::deck: 
            std::cout<<"Deck:\n";
			deck.displayPile();
			std::cout<<"Press any key to return...\n";
			system("pause>nul");
            break;

        case PileType::combat_deck: 
            std::cout<<"Combat Deck:\n";
			combat_deck.displayPile();
			std::cout<<"Press any key to return...\n";
			system("pause>nul");
            break;

        case PileType::hand: //Hand is combat only. Hand should be visible by default, so no need to wait for return key.
            std::cout<<"Hand:\n";
			hand.displayPile(); 
            break;

        case PileType::draw: 
            std::cout<<"Draw:\n";
			draw.displayPile();
			std::cout<<"Press any key to return...\n";
			system("pause>nul");
            break;
        
        case PileType::discard: 
            std::cout<<"Discard:\n";
			discard.displayPile();
			std::cout<<"Press any key to return...\n";
			system("pause>nul");
            break;

        case PileType::exhaust: 
            std::cout<<"Exhaust:\n";
			exhaust.displayPile();
			std::cout<<"Press any key to return...\n";
			system("pause>nul");
            break;
    }
}

void Character::drawCards(int amount, Game& game){

    cout<<"Drawing "<<amount<<" card(s)...\n"; Sleep(1000);

    if(draw.getSize()<amount){//If there are fewer cards in the draw pile than the amount we want to draw...
        //Draw the whole draw pile first
        amount -= draw.getSize(); //Amount of cards left to draw.
        hand.drawFrom(draw, draw.getSize());
        cout<<"Shuffling discard into draw pile...\n"; Sleep(1000);

        //Then shuffle the discard pile into the draw pile
        discard.movePileTo(draw); game.rng.shuffle(draw.cards);

        //Now, check if there are enough cards in the draw pile to finish drawing. If not, draw as many as possible, then stop drawing.
        if(draw.getSize()<amount){hand.drawFrom(draw, draw.getSize()); return;} //Draw as many as possible, then stop drawing.
        else{hand.drawFrom(draw, amount); return;} //Draw the rest of the cards needed to reach the full amount.

    }else{ //if there are enough cards in the draw pile to draw the full amount, just draw them.
        hand.drawFrom(draw, amount);    
    }

}
void Character::discardHand(){
    hand.movePileTo(discard);
}

void Character::displayStatus(){
    //STATUS BAR
    cout<<"-----------------------------\n";
    cout<<name<<'\n';
    cout<<"HP: "<<HP<<"/"<<max_HP<<'\n';
    cout<<"Energy : "<<energy<<"/"<<max_energy<<'\n';	
    cout<<"Block: "<<block<<'\n';
    cout<<"-----------------------------\n";

}

void Character::playCardFromHand(int pos, Game& game){
    
    played = getCardFromPile(PileType::hand,pos);

    int currentEnergy = getAttribute(PlayerAttribute::energy);

    if(currentEnergy >= played.getEnergyCost()){
        
        
        
        cout<<"Playing: "<<played.getName()<<"...\n";;

        //Remove card from hand and apply its effects. While the card is resolving, it is neither on the discard, exhaust nor draw pile, so it can't be affected by effects that target those piles. After resolution, the card is moved to the discard pile.        
        removeFromPlayerPile(PileType::hand, pos);
        
        played.applyEffects(*this,game);
        
        

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

bool Character::isAlive(){return (HP>0);}

void Character::endCombat(){
    combat_deck.deletePile();
    draw.deletePile();
    discard.deletePile();
    exhaust.deletePile();
    hand.deletePile();

}