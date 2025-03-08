#include<iostream>
#include "pile.h"
#include "character.h"
#include<windows.h>
using std::string; using std::cout;

Character::Character(string N, int MHP, int HP, int ME, int E, int B, Pile D, Card p)
    :name(N), max_HP(MHP), HP(HP), max_energy(ME), energy(E), block(B), deck(D), played(p){}

string Character::getName() {return name;}
int Character::getMaxHP() {return max_HP;}
int Character::getHP(){return HP;}
int Character::getMaxEnergy(){return max_energy;}
int Character::getBlock(){return block;}
int Character::getEnergy(){return energy;}

Card& Character::getCardFromDeck(int position){return deck.getCard(position);}
Card& Character::getCardFromCombatDeck(int position){return combat_deck.getCard(position);}	
Card& Character::getCardFromHand(int position){return hand.getCard(position);}
Card& Character::getCardFromDraw(int position) {return draw.getCard(position);}
Card& Character::getCardFromDiscard(int position){return discard.getCard(position);}
Card& Character::getCardFromExhaust(int position){return exhaust.getCard(position);}
Card& Character::getPlayed(){return played;}

int Character::getDeckSize() {return deck.getSize();}
int Character::getHandSize() {return hand.getSize();}
int Character::getDrawSize() {return draw.getSize();}
int Character::getDiscardSize() {return discard.getSize();}
int Character::getExhaustSize() {return exhaust.getSize();}

void Character::setName(string n){name = n;}
void Character::setMaxHP(int m){max_HP = m;}
void Character::setBlock(int b){block = b;}
void Character::setHP(int hp){HP = hp;}
void Character::setMaxEnergy(int mE){max_energy = mE;}
void Character::setEnergy(int e){energy=e;}
void Character::setPlayed(Card c){played = c;}

//Changes maxHP by an amount Delta (integer). To decrease MaxHP, Delta<0. Gives terminal feedback on the change.
void Character::changeMaxHP(int Delta){
    max_HP += Delta;
    if(HP>max_HP){HP=max_HP;}
    cout<<((Delta>0)? "Gained ":"Lost ")<<abs(Delta)<<" Max HP!\n";
    
}
void Character::changeMaxEnergy(int Delta){
    max_energy += Delta;
    cout<<((Delta>0)? "Gained ":"Lost ")<<abs(Delta)<<" Max HP!\n";
}
//Changes Block by an amount Delta(integer).
void Character::changeBlock(int Delta){
    block += Delta;
    cout<<((Delta>0)? "Gained ":"Lost ")<<abs(Delta)<<" Block!\n";
}
//Changes HP by an amount Delta(integer).
void Character::changeHP(int Delta){
    HP += Delta;
    cout<<((Delta>0)? "Gained ":"Lost ")<<abs(Delta)<<" HP!\n";		
}
//Changes energy by an amount Delta(integer).
void Character::changeEnergy(int Delta){
    energy += Delta;
    cout<<((Delta>0)? "Gained ":"Lost ")<<abs(Delta)<<" Energy!\n";
}


void Character::StartCombat(std::mt19937 seed){
    cout<<"Creating combat deck...\n"; combat_deck.addPileToSelf(deck);
    cout<<"Shuffling Combat deck...\n";	combat_deck.shufflePile(seed);
    cout<<"Creating Draw Pile...\n";
    combat_deck.movePileTo(draw); draw.displayPile(); system("pause");

    hand.drawFrom(draw,5);
}

//adds Card c to player master deck.
void Character::addToDeck(Card c){deck.addCardToPile(c);}
//Add Card c to player's draw pile
void Character::addToDraw(Card c){draw.addCardToPile(c);}
//Add Card c to Player's hand.
void Character::addToHand(Card c){hand.addCardToPile(c);}
//Add Card c to Player's discard pile.
void Character::addToDiscard(Card c){discard.addCardToPile(c);}
//Add Card c to Player's exhaust pile.
void Character::addToExhaust(Card c){exhaust.addCardToPile(c);}


//Removes a card with passed position from the player's deck.
void Character::removeFromDeck(int position){deck.remove(position);}
//Removes a card with passed position from the player's draw pile.
void Character::removeFromDraw(int position){draw.remove(position);}
//Removes a card with passed position from the player's discard pile.
void Character::removeFromHand(int position){hand.remove(position);}
//Removes a card with passed position from the player's discard pile.
void Character::removeFromDiscard(int position){discard.remove(position);}
//Removes a card with passed position from the player's Exhaust pile.
void Character::removeFromExhaust(int position){exhaust.remove(position);}

//Delete Player's Deck.
void Character::deleteDeck(){deck.deletePile();}
//Delete Player's Draw pile.
void Character::deleteDraw(){draw.deletePile();}
//Delete Player's Hand.
void Character::deleteHand(){hand.deletePile();}
//Delete Player's Discard Pile.
void Character::deleteDiscard(){discard.deletePile();}
//Delete Player's Exhaust pile.
void Character::deleteExhaust(){deck.deletePile();}

void Character::displayDeck(){deck.displayPile();}
void Character::displayCombatDeck(){combat_deck.displayPile();}
void Character::displayDraw(){draw.displayPile();}
void Character::displayHand(){hand.displayPile();}
void Character::displayDiscard(){discard.displayPile();}
void Character::displayExhaust(){exhaust.displayPile();}

void Character::displayStatus(){
    //STATUS BAR
    cout<<name<<'\n';
    cout<<"HP: "<<HP<<"/"<<max_HP<<'\n';
    cout<<"Energy : "<<energy<<"/"<<max_energy<<'\n';	
}

void Character::playCardFromHand(int pos){
    Card played = getCardFromHand(pos);
    cout<<"Playing: "<<played.getName()<<"...";
    changeEnergy(-played.getEnergyCost());

    //EFFECT foo();

    cout<<"YOU JUST PLAYED "<<played.getName()<<"!"<<'\n';
    addToDiscard(played);
    removeFromHand(pos);
}
