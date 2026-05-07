#include "character/player.h"
#include "data/constants.h"
#include "game_logic/game.h"
#include "ui/colors.h"
#include "card/pile.h"
#include "card/card.h"
#include <windows.h>

Player::Player(std::string n,int mHP, int e): Character(n,mHP), max_energy(e), energy(e), played(blank_card){}


Card& Player::getPlayed(){return played;}

void Player::setAttribute(Attribute a, int magnitude){
    switch(a){
        case Attribute::max_energy: max_energy = magnitude; break;
        case Attribute::energy: energy = magnitude; break;
        default: Character::setAttribute(a,magnitude); break;
    }
}

int Player::getAttribute(Attribute a){
    switch(a){
        case Attribute::energy: return energy; break;
        case Attribute::max_energy: return max_energy; break;
        default : return Character::getAttribute(a);
    }
}

void Player::changeAttribute(Attribute a, int Delta){
    switch(a){
         case Attribute::energy: 
            energy += Delta; 
            std::cout<<name<<" has "<<((Delta>0)? "Gained ":"Lost ")<<abs(Delta)<<" energy!\n"; break;
        case Attribute::max_energy:
            max_energy += Delta; 
            std::cout<<name<<" has "<<((Delta>0)? "Gained ":"Lost ")<<abs(Delta)<<" max energy!\n"; break;
        default: Character::changeAttribute(a,Delta); break;
    }
}

int Player::getPlayerPileSize(PileType type){
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

//This method allows a Character to initiate combat.
void Player::StartCombat(Game& game){
    setPlayed(blank_card);
    std::cout<<this->getName()<<" is initiating combat!\n";
    combat_deck.addPileToSelf(deck); //Create the combat deck (copy of master deck)
    game.rng.shuffle(combat_deck.cards); //Shuffle the deck
    combat_deck.movePileTo(draw); //Make the combat deck the new draw pile.
    
    //Reset energy and block.
    setAttribute(Attribute::energy, this->max_energy);
    setAttribute(Attribute::block,0);
    
    //Draw 5 cards.
    drawCards(5,game);
    Sleep(1000);
}

void Player::drawCards(int amount, Game& game){

    std::cout<<"Drawing "<<amount<<" card(s)...\n"; Sleep(1000);

    if(draw.getSize()<amount){//Draw pile is smaller than cards left to draw.
        
        amount -= draw.getSize(); 
        hand.drawFrom(draw, draw.getSize());
        
        std::cout<<"Shuffling discard into draw pile...\n"; Sleep(1000);        
        discard.movePileTo(draw); game.rng.shuffle(draw.cards);

        //Now, check if there are enough cards in the draw pile to finish drawing. If not, draw as many as possible, then stop drawing.
        if(draw.getSize()<amount){hand.drawFrom(draw, draw.getSize()); return;} //Draw as many as possible, then stop drawing.
        else{hand.drawFrom(draw, amount); return;} //Draw the rest of the cards needed to reach the full amount.

    }else{ //draw normally.
        hand.drawFrom(draw, amount);    
    }

}


void Player::discardHand(){hand.movePileTo(discard);}


void Player::playCardFromHand(int pos, Game& game){
    
    played = getCardFromPile(PileType::hand,pos);

    if(getAttribute(Attribute::energy) >= played.getEnergyCost()){
        std::cout<<"Playing: "<<played.getName()<<"...\n";
        removeFromPlayerPile(PileType::hand, pos); //Card is now "hovering" (not on any player pile).
        played.applyEffects(*this,game);
    }
    else{std::cout<<"Not enough energy!\n";}
}

void Player::setupPlayer(int choice){
    switch(choice){
    case 1:
        setName(color(Color::red, "The Ironclad")); 
        setAttribute(Attribute::max_hp, ICL_STARTING_MAX_HP); setAttribute(Attribute::hp,ICL_STARTING_MAX_HP); 
        setAttribute(Attribute::max_energy,STARTING_ENERGY); setAttribute(Attribute::energy,STARTING_ENERGY);
        deck.addPileToSelf(ICL_STARTER_DECK);
        setPlayed(blank_card);
        break;
    case 2:
        setName("The Silent"); 
        setAttribute(Attribute::max_hp,SLT_STARTING_MAX_HP); setAttribute(Attribute::hp,SLT_STARTING_MAX_HP); 
        setAttribute(Attribute::max_energy,STARTING_ENERGY); setAttribute(Attribute::energy,STARTING_ENERGY);
        deck.addPileToSelf(SLT_STARTER_DECK);
        setPlayed(blank_card);
        break;
    }

}

void Player::addToPlayerPile(PileType type, Card& c){
    switch(type){
        case PileType::deck: deck.addCardToPile(c); break;
        case PileType::combat_deck: combat_deck.addCardToPile(c); break;
        case PileType::hand: hand.addCardToPile(c); break;
        case PileType::draw: draw.addCardToPile(c); break;
        case PileType::discard: discard.addCardToPile(c); break;
        case PileType::exhaust: exhaust.addCardToPile(c); break;
    }
}

void Player::removeFromPlayerPile(PileType type, int position){
    switch(type){
        case PileType::deck: deck.remove(position); break;
        case PileType::combat_deck: combat_deck.remove(position); break;
        case PileType::hand: hand.remove(position);break;
        case PileType::draw: draw.remove(position);break;
        case PileType::discard: discard.remove(position);break;
        case PileType::exhaust: exhaust.remove(position);break;
    }
}

void Player::deletePlayerPile(PileType type){
    switch(type){
        case PileType::deck: deck.deletePile(); break;
        case PileType::combat_deck: combat_deck.deletePile(); break;
        case PileType::hand: hand.deletePile(); break;
        case PileType::draw: draw.deletePile(); break;
        case PileType::discard: discard.deletePile(); break;
        case PileType::exhaust: exhaust.deletePile(); break;
    }
}

void Player::displayPlayerPile(PileType type){
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

void Player::endCombat(){
    combat_deck.deletePile();
    draw.deletePile();
    discard.deletePile();
    exhaust.deletePile();
    hand.deletePile();
}

void Player::displayStatus(){
    //STATUS BAR
    std::cout<<getName()<<" HP "<<HP<<"/"<<max_HP<<" Energy "<<energy<<"/"<<max_energy<<" Block "<<block<<'\n';
}

Card& Player::getCardFromPile(PileType type, int position){
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

void Player::setPlayed(Card& c){played = c;}