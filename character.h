#ifndef CHARACTER
#define CHARACTER
#include "card.h"
#include "pile.h"
#include <deque>
#include <algorithm>
#include <random>
#include <ctime>
#include <windows.h>
class Character{
	std::string name; //Your character's name.
	int max_HP; //Maximun number of Hit Points. Persistent through floors.
	int HP; //Current Hitpoints. Persistent through floors.
	int max_energy; //You get this amount of energy each turn. Persistent.
	int energy; //Current energy. Combat only.
	int block; //Current amount of BLK. Combat only.
	Pile deck; //Your current deck of cards.
	Pile combat_deck;
	// int Stance; //WAT, PSM (Prismatic): Current Stance. 0: Neutral NTL, 1: Calm CLM, 2: Wrath WRT, 3: Divinity DIV. Combat only.
	// int orbSlots; //How many orb slots you currently have. Defect starts with 3. On any other character, you start with 1 if you are Prismatic. Combat only.
	// deque <int> orbs; //Your channeled orbs. Combat only.
	// bool prismatic;
	Pile hand; //Your current hand
	Pile draw; //You draw cards from this pile
	Pile discard; //You discard cards in here from card effects and at the end of your turn.
	Pile exhaust; //Cards that have exhausted this combat.

	Card played;

	public:
	Character(std::string N, int MHP, int HP, int ME, int E, int B, Pile D, Card p);

	std::string getName();
	int getMaxHP();
	int getHP();
	int getMaxEnergy();
	int getBlock();
	int getEnergy();
	Pile getDeck();
	Pile getCombatDeck();
	Pile getHand();
	Pile getDraw();
	Pile getDiscard();
	Pile getExhaust();
	Card getPlayed();

	int getDeckSize();
	int getHandSize();
	int getDrawSize();
	int getDiscardSize();
	int getExhaustSize();
	void setName(std::string n);
	void setMaxHP(int m);
	void setBlock(int b);
	void setHP(int hp);
	void setPlayed(Card p);

	//Changes maxHP by an amount Delta (integer). To decrease MaxHP, Delta<0. Gives terminal feedback on the change.
	void changeMaxHP(int Delta);
    ////Changes max_energy by an amount Delta (integer).
	void changeMaxEnergy(int Delta);
	//Changes Block by an amount Delta(integer).
	void changeBlock(int Delta);
	//Changes HP by an amount Delta(integer).
	void changeHP(int Delta);
	//Changes energy by an amount Delta(integer).
	void changeEnergy(int Delta);
	

	void StartCombat(std::mt19937 seed);
	
	//adds Card c to player master deck.
	void addToDeck(Card c);
	//Add Card c to player's draw pile
	void addToDraw(Card c);
	//Add Card c to Player's hand.
	void addToHand(Card c);
	//Add Card c to Player's discard pile.
	void addToDiscard(Card c);
	//Add Card c to Player's exhaust pile.
	void addToExhaust(Card c);

	//Removes a card with passed position from the player's deck.
	void removeFromDeck(int position);
	//Removes a card with passed position from the player's draw pile.
	void removeFromDraw(int position);
	//Removes a card with passed position from the player's discard pile.
	void removeFromHand(int position);
	//Removes a card with passed position from the player's discard pile.
	void removeFromDiscard(int position);
	//Removes a card with passed position from the player's Exhaust pile.
	void removeFromExhaust(int position);
	
	//Delete Player's Deck.
	void deleteDeck();
	//Delete Player's Draw pile.
	void deleteDraw();
	//Delete Player's Hand.
	void deleteHand();
	//Delete Player's Discard Pile.
	void deleteDiscard();
	//Delete Player's Exhaust pile.
	void deleteExhaust();


	void displayStatus();
	void playCardFromHand(int pos);
};

#endif