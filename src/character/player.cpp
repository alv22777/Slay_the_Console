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


Player::Player(std::string n,int mHP, int e, Color c): 
Character(n,mHP,c), max_energy(e), energy(e), played(blank_card), potion_slots(STARTING_POTION_SLOTS){}


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

int Player::getPlayerPileSize(PileID type){
    switch(type){
        case PileID::deck: return deck.getSize();
        case PileID::combat_deck: return combat_deck.getSize();
        case PileID::hand: return hand.getSize();
        case PileID::draw: return draw.getSize();
        case PileID::discard: return discard.getSize();
        case PileID::exhaust: return exhaust.getSize();
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
    setPlayed(blank_card);
    //Draw 5 cards.
    drawCards(5,game);
}

bool Player::drawCard(Game& game){
    
    if(draw.empty()){ game.rng.shuffle(discard.cards); discard.movePileTo(draw); }

    if(draw.empty()){return false;}

    hand.drawFrom(draw,1);
    return true;
}

uint32_t Player::drawCards(int amount, Game& game){
    
    int drawn = 0;

    for(int i = 0; i<amount; i++){
       
        if(isHandFull()){game.pushLog("My hand is full!",2); return drawn;}
       
        bool success = drawCard(game);
       
        if(success){drawn++;}
    }

    return drawn;
}

bool Player::isHandFull(){return hand.getSize()==MAX_HAND_SIZE;}

void Player::discardHand(){hand.movePileTo(discard);}

void Player::playCardFromHand(int pos, Game& game){
    Card& tried = getCardFromPile(PileID::hand,pos);
    if(!tried.canPlay(*this, game)){std::cout<<"You can not play this card!\n"; return;}
    if(getAttribute(Attribute::energy) < tried.getEnergyCost()){std::cout<<"Not enough energy!\n"; return;}
     
    tried.display(); std::cout<<'\n';
    setPlayed(tried);
    game.pushLog(color(col, name) + " played " + color(tried.rarityColor(), tried.getName()), 0);
    played.applyEffects(*this,game, pos);
}

std::unique_ptr<Player> Player::createPlayer(int choice){
    switch(choice){
        case 1:{
                std::unique_ptr<Player> p = std::make_unique<Player>(color(Color::red, "The Ironclad"), ICL_STARTING_MAX_HP, STARTING_ENERGY,  Color::red);
                p->deck.addPileToSelf(ICL_STARTER_DECK);
                return p;
            }
        case 2:{
                std::unique_ptr<Player> p = std::make_unique<Player>(
                    color(Color::green,"The Silent"), 
                    SLT_STARTING_MAX_HP, 
                    STARTING_ENERGY, 
                    Color::green); 
                p->deck.addPileToSelf(SLT_STARTER_DECK);
                return p;
            }
            
        default:{return std::make_unique<Player>("NOPLAYER",0,0,Color::colorless);}
    }
}

void Player::addToPile(PileID type, Card& c, bool bottom){
    if(bottom){
        switch(type){
            case PileID::deck: deck.addCardBot(c); break;
            case PileID::combat_deck: combat_deck.addCardBot(c); break;
            case PileID::hand: hand.addCardBot(c); break;
            case PileID::draw: draw.addCardBot(c); break;
            case PileID::discard: discard.addCardBot(c); break;
            case PileID::exhaust: exhaust.addCardBot(c); break;
        }
    }else{
        switch(type){
            case PileID::deck: deck.addCardTop(c); break;
            case PileID::combat_deck: combat_deck.addCardTop(c); break;
            case PileID::hand: hand.addCardTop(c); break;
            case PileID::draw: draw.addCardTop(c); break;
            case PileID::discard: discard.addCardTop(c); break;
            case PileID::exhaust: exhaust.addCardTop(c); break;
        }
    }
}

void Player::removeFromPlayerPile(PileID type, int position){
    switch(type){
        case PileID::deck: deck.remove(position); break;
        case PileID::combat_deck: combat_deck.remove(position); break;
        case PileID::hand: hand.remove(position);break;
        case PileID::draw: draw.remove(position);break;
        case PileID::discard: discard.remove(position);break;
        case PileID::exhaust: exhaust.remove(position);break;
    }
}

void Player::displayPlayerPile(PileID type, bool fixed, int n, bool sorted = false){
    Pile choice;
    
    switch(type){
        case PileID::deck: 
        std::cout<<"Deck:\n"; choice = deck;
        break;

        case PileID::combat_deck: 
        std::cout<<"Combat Deck:\n"; choice = combat_deck;
        break;
            
        case PileID::hand: //Hand is combat only. Hand should be visible by default, so no need to wait for return key.
        std::cout<<"Hand:\n"; choice = hand;
        break;
        
        case PileID::draw: 
        std::cout<<"Draw:\n"; choice = draw;
        break;
        
        case PileID::discard: 
        std::cout<<"Discard:\n"; choice = discard;
        break;
        
        case PileID::exhaust: 
        std::cout<<"Exhaust:\n"; choice = exhaust;
        break;
        
       
    }
    
    if(fixed){choice.displayFixed(n);}
    else if(sorted){choice.displaySortedBy(0,true);}
    else{choice.displayPile();}
}
    
void Player::endCombat(){
    combat_deck.deletePile();
    draw.deletePile();
    discard.deletePile();
    exhaust.deletePile();
    hand.deletePile();
    removeAllPowers();
}

void Player::displayStatus(){
    Character::displayStatus();
    std::cout<<color(col, " ● "+std::to_string(energy)+'/'+std::to_string(max_energy))<<"\n";
    Character::displayPowers();
    std::cout<<'\n';
}

Card& Player::getCardFromPile(PileID type, int position){
    switch(type){
        case PileID::deck: return deck.getCard(position);
        case PileID::combat_deck: return combat_deck.getCard(position);
        case PileID::hand: return hand.getCard(position);
        case PileID::draw: return draw.getCard(position);
        case PileID::discard: return discard.getCard(position);
        case PileID::exhaust: return exhaust.getCard(position);
        default : return blank_card;            
    }
}

void Player::setPlayed(Card& c){played = c;}

//Transfer {amount} cards manually chosen from source Pile to target Pile.
//If cards go into hand, and the amount would take the player over maximum hand size
//only enough cards to fill hand are transferred, and remaining cards go into discard.
uint32_t Player::transferCardsManual(PileID source, PileID target, int amount, bool bottom, Game& game){
    std::deque<int> selected = chooseCards(source, amount, game); 

    int slots = MAX_HAND_SIZE-hand.getSize();
    bool will_fill = slots < selected.size();

    if(will_fill && target == PileID::hand){
        for(int i = 0; i<selected.size();i++){
            if(i<slots){ addToPile(target,getCardFromPile(source,selected[i]),true); }  //if slot available, add to hand
            else{ addToPile(PileID::discard,getCardFromPile(source,selected[i]),true); } //otherwise, add to discard.
        }
    }    
    else{ 
        for(int pos: selected){ addToPile(target,getCardFromPile(source,pos), bottom); }       
    }


    //Go from latest index to earliest, this prevents index invalidation due to container mutation
    std::sort(selected.begin(),selected.end(), std::greater<int>()); 
    for(int pos: selected){ removeFromPlayerPile(source,pos); }

    return selected.size();
}

//Transfer the selected cards (choices) from source Pile to target Pile
uint32_t Player::transferCardsAuto(PileID source, PileID target, std::deque<int> selected, bool bottom){
  
  if(target == PileID::hand){ //If cards go into hand, order matters
        bool over_hand_size = (hand.getSize()+selected.size())> MAX_HAND_SIZE;
        int slots = MAX_HAND_SIZE-hand.getSize();

        if(over_hand_size){
            for(int i = 0; i<selected.size();i++){
                if(i<slots){ addToPile(target,getCardFromPile(source,selected[i]),true); }  //if slot available, add to hand
                else{ addToPile(PileID::discard,getCardFromPile(source,selected[i]),true); } //otherwise, add to discard.
            }
        }
    }
    else{
        for(int pos: selected){
            addToPile(target, getCardFromPile(source,pos),bottom);
        }
    }
    
    //Go from latest index to earliest, this prevents index invalidation due to container mutation
    std::sort(selected.begin(),selected.end(), std::greater<int>()); 
    for(int pos: selected)  {
        removeFromPlayerPile(source, pos);
    }

    return selected.size();
}



//Manually choose n cards from Pile source, it returs the choices sorted in descending order.
std::deque<int> Player::chooseCards(PileID source, int amount, Game& game){
    std::deque<int> selected;
    
    if(amount>=getPlayerPileSize(source)){ //We can't get more cards if source's pile size is smaller, so just default to the whole pile
        for(int i = 0; i<getPlayerPileSize(source);i++){ selected.push_back(i); }
        return selected;
    }
    
    std::cout<<"Choose "<<amount<<" card"<<((amount>1)? "s > ":" > ");

    std::deque<IndexedCard> IndexedCards;
    if(source == PileID::draw){
        std::cout<<"\n";
        IndexedCards = draw.indexed();
        draw.displaySortedBy(0,true);
    }
    else if(source != PileID::hand){displayPlayerPile(source, false, 0);}
    
    while(selected.size()<amount){

        game.displayGameState();
        
        std::cout<<"Selected: { ";
        for(int pos: selected){
            std::cout<<pos<<" ";
        }
        std::cout<<" }\n";
        
        if(source == PileID::draw){draw.displaySortedBy(0,true);}
        else if (source != PileID::hand){displayPlayerPile(source, false, 0);}

        std::cout<<"Choose "<<amount-selected.size()<<" card"<<((amount-selected.size()>1)? "s > ":" > ");
        
        int input = inputInt(0,getPlayerPileSize(source)-1,true);
        
        if(auto it = std::find(selected.begin(), selected.end(), input) == selected.end() ){
            selected.push_back(input);    
        }else{
            selected.erase(selected.begin()+it);
            std::cout<< "Card deselected.\n";
        }

    }
    
    //Finally, if we were selecting from draw, remap to correct indices
    if(source == PileID::draw){
        for(int i = 0; i<selected.size();i++){
            selected[i] = IndexedCards[selected[i]].index;
        }
    }

    return selected;
}

std::deque<int> Player::findIndexes(PileID p, CardType c, bool matching){
    if(matching){
        switch(p){
            case PileID::deck: return deck.findMatchingIndexes(c);
            case PileID::combat_deck: return combat_deck.findMatchingIndexes(c);
            case PileID::hand: return hand.findMatchingIndexes(c);
            case PileID::draw: return draw.findMatchingIndexes(c);
            case PileID::discard: return discard.findMatchingIndexes(c);
            case PileID::exhaust: return exhaust.findMatchingIndexes(c);
            default: return {};
        }
    }
    else{
        switch(p){
            case PileID::deck: return deck.findNonMatchingIndexes(c);
            case PileID::combat_deck: return combat_deck.findNonMatchingIndexes(c);
            case PileID::hand: return hand.findNonMatchingIndexes(c);
            case PileID::draw: return draw.findNonMatchingIndexes(c);
            case PileID::discard: return discard.findNonMatchingIndexes(c);
            case PileID::exhaust: return exhaust.findNonMatchingIndexes(c);
            default: return {};
        }
    }
    
}