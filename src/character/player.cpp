#include "character/player.h"
#include "data/constants.h"
#include "game_logic/game.h"
#include "ui/colors.h"
#include "ui/formatting.h"
#include "ui/input.h"
#include "card/pile.h"
#include "card/card.h"
#include <algorithm>
#include <windows.h>
#include <iomanip>


Player::Player(std::string n,int mHP, int e, Color c): Character(n,mHP,c), max_energy(e), energy(e), played(blank_card){}


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
        case Attribute::energy: energy += Delta; break;
        case Attribute::max_energy: max_energy += Delta; break;
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
    

    combat_deck.addPileToSelf(deck); //Create the combat deck (copy of master deck)
    combat_deck.movePileTo(draw); //Make the combat deck the new draw pile.
    game.rng.shuffle(draw.cards); //Shuffle the draw pile
    
    //Reset energy and block.
    setAttribute(Attribute::energy, this->max_energy);
    setAttribute(Attribute::block,0);
    
    //Draw 5 cards.
    drawCards(5,game);
}

void Player::drawCards(int amount, Game& game){

    if(draw.getSize()<amount){//Draw pile is smaller than cards left to draw.
        
        amount -= draw.getSize(); 
        hand.drawFrom(draw, draw.getSize());
            
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
    Card& tried = getCardFromPile(PileType::hand,pos);
    if(!tried.canPlay(*this, game)){std::cout<<"You can not play this card!\n"; return;}
    if(getAttribute(Attribute::energy) < tried.getEnergyCost()){std::cout<<"Not enough energy!\n"; return;}
     
    tried.display(); std::cout<<'\n';
    setPlayed(tried);
    played.applyEffects(*this,game, pos);
}

Player Player::createPlayer(int choice){
    switch(choice){
        case 1:{
            Player p(color(Color::red, "The Ironclad"), ICL_STARTING_MAX_HP, STARTING_ENERGY, Color::red);
            p.deck.addPileToSelf(ICL_STARTER_DECK);
            return p;
            }
        case 2:{
            Player p(color(Color::green, "The Silent"), SLT_STARTING_MAX_HP, STARTING_ENERGY, Color::green);
            p.deck.addPileToSelf(SLT_STARTER_DECK);
            return p;
            }
        default:{return Player("NOPLAYER",0,0,Color::colorless);}
    }
}

void Player::addToPile(PileType type, Card& c, bool bottom){
    if(bottom){
        switch(type){
            case PileType::deck: deck.addCardBot(c); break;
            case PileType::combat_deck: combat_deck.addCardBot(c); break;
            case PileType::hand: hand.addCardBot(c); break;
            case PileType::draw: draw.addCardBot(c); break;
            case PileType::discard: discard.addCardBot(c); break;
            case PileType::exhaust: exhaust.addCardBot(c); break;
        }
    }else{
        switch(type){
            case PileType::deck: deck.addCardTop(c); break;
            case PileType::combat_deck: combat_deck.addCardTop(c); break;
            case PileType::hand: hand.addCardTop(c); break;
            case PileType::draw: draw.addCardTop(c); break;
            case PileType::discard: discard.addCardTop(c); break;
            case PileType::exhaust: exhaust.addCardTop(c); break;
        }
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

void Player::displayPlayerPile(PileType type, bool fixed, int n){
    Pile choice;
    //Switched responsibility from Game to Character.
    switch(type){
        case PileType::deck: 
        std::cout<<"Deck:\n"; choice = deck;
        break;

        case PileType::combat_deck: 
        std::cout<<"Combat Deck:\n"; choice = combat_deck;
        break;
            
        case PileType::hand: //Hand is combat only. Hand should be visible by default, so no need to wait for return key.
        std::cout<<"Hand:\n"; choice = hand;
        break;
        
        case PileType::draw: 
        std::cout<<"Draw:\n"; choice = draw;
        break;
        
        case PileType::discard: 
        std::cout<<"Discard:\n"; choice = discard;
        break;
        
        case PileType::exhaust: 
        std::cout<<"Exhaust:\n"; choice = exhaust;
        break;
        
       
    }
    
    if(fixed){choice.displayFixed(n);}
    else{choice.displayPile();}

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
    std::cout<<color(col, padRight(getName(),15))<<
    color(Color::hp, " HP "+std::to_string(HP)+'/'+std::to_string(max_HP))<<
    color(col, " Energy "+std::to_string(energy)+'/'+std::to_string(max_energy))<<
    color(Color::block, " Block "+std::to_string(block)+'\n');
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

//Transfer {amount} cards manually chosen from source Pile to target Pile.
void Player::transferCardsManual(PileType source, PileType target, int amount, bool bottom){
    std::deque<int> choices = chooseCards(source, amount); 
    
    if(bottom){//cards go on bottom of the pile
        for(int pos: choices){
            addToPile(target,getCardFromPile(source,pos), true);
            removeFromPlayerPile(source, pos);
        }       
    }
    else{ //Cards go on top of the pile
        for(int pos: choices){
            addToPile(target, getCardFromPile(source, pos), false);
            removeFromPlayerPile(source, pos);
        }
    }   
}

//Transfer the selected cards (choices) from source Pile to target Pile
void Player::transferCardsAuto(PileType source, PileType target, std::deque<int> choices, bool bottom){
    //Go from latest index to earliest, this prevents index invalidation due to container mutation
    std::sort(choices.begin(),choices.end(), std::greater<int>()); 
    for(int pos: choices){
        addToPile(target,getCardFromPile(source,pos), bottom);
        removeFromPlayerPile(source, pos);
    }
}



//Manually choose n cards from Pile source, it returs the choices sorted in descending order.
std::deque<int> Player::chooseCards(PileType source, int amount){
    std::deque<int> choices;

    std::cout<<"Choose "<<amount<<" card"<<((amount>1)? "s.":".")<<'\n';
    displayPlayerPile(source, false, 0);

    if(amount>=getPlayerPileSize(source)){ //We can't get 3 cards if source's pile size is 2, so just default to the whole pile!
        for(int i = 0; i<getPlayerPileSize(source);i++){
            choices.push_back(i);
        }
    }
    else{
        while(choices.size()<amount){
            int input = inputInt(0,getPlayerPileSize(source)-1);

            if( std::find(choices.begin(), choices.end(), input) == choices.end() ){
                choices.push_back(input);
                std::cout<<amount-choices.size()<<" card"<<((amount-choices.size()>1)? "s ":" ")<< "remaining.\n";
            }else{
                std::cout<<"Card already selected.\n";
            }
        }
    }

    //Go from latest index to earliest, this prevents index invalidation due to container mutation
    std::sort(choices.begin(),choices.end(), std::greater<int>()); 
    return choices;
}

std::deque<int> Player::findIndexes(PileType p, CardType c, bool matching){
    if(matching){
        switch(p){
            case PileType::deck: return deck.findMatchingIndexes(c);
            case PileType::combat_deck: return combat_deck.findMatchingIndexes(c);
            case PileType::hand: return hand.findMatchingIndexes(c);
            case PileType::draw: return draw.findMatchingIndexes(c);
            case PileType::discard: return discard.findMatchingIndexes(c);
            case PileType::exhaust: return exhaust.findMatchingIndexes(c);
            default: return {};
        }
    }
    else{
        switch(p){
            case PileType::deck: return deck.findNonMatchingIndexes(c);
            case PileType::combat_deck: return combat_deck.findNonMatchingIndexes(c);
            case PileType::hand: return hand.findNonMatchingIndexes(c);
            case PileType::draw: return draw.findNonMatchingIndexes(c);
            case PileType::discard: return discard.findNonMatchingIndexes(c);
            case PileType::exhaust: return exhaust.findNonMatchingIndexes(c);
            default: return {};
        }
    }
    
}