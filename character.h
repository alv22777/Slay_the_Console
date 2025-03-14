#ifndef CHARACTER
#define CHARACTER
#include "card.h"
#include "pile.h"
#include <deque>
#include <algorithm>
#include <random>
#include <ctime>
#include <windows.h>

//The player can have 6 Piles, 
enum class PileType{deck, combat_deck, hand, draw, discard, exhaust};
enum class PlayerAttribute{HP, max_HP, energy, max_energy, block};

//This is a Slay The Spire Character, it has several core attributes like HP, energy and block.
//It also has several Piles, which track the player's deck out of combat an during combat.
class Character{
	std::string name; //Your character's name.
	int max_HP; //Maximun number of Hit Points. Persistent through floors.
	int HP; //Current Hitpoints. Persistent through floors.
	int max_energy; //You get this amount of energy each turn. Persistent.
	int energy; //Current energy. Combat only.
	int block; //Current amount of BLK. Combat only.
	Pile deck; //Your current deck of cards.
	Pile combat_deck; //Deck used for combat.

	Pile hand; //Your current hand
	Pile draw; //You draw cards from this pile
	Pile discard; //You discard cards in here from card effects and at the end of your turn.
	Pile exhaust; //Cards that have exhausted this combat.

	Card played;

	public:
	Character(std::string N, int MHP, int HP, int ME, int E, int B, Pile D, Card p);

	std::string getName();
	int getAttribute(PlayerAttribute att);

	Card& getCardFromPile(PileType type, int position);
	Card& getPlayed();
	
	int getPlayerPileSize(PileType type);
		
	void setName(const std::string& n);
	void setAttribute(PlayerAttribute att, int value);
	void setPlayed(Card& c);

	void changeAttribute(PlayerAttribute att, int Delta);
    
	void StartCombat(std::mt19937& seed);

	//Add Card c to player Pile type (deck, hand, discard...). 
	void addToPlayerPile(PileType type, Card& c);
	
	//Removes Card with position pos from the player's Pile type (deck, hand, discard...).
	void removeFromPlayerPile(PileType type, int pos);

	//Delete player's pile type(deck, hand, discard...).
	void deletePlayerPile(PileType type);

	//Display player Pile type (deck, hand, discard...).
	void displayPlayerPile(PileType type);

	//Display a simple status bar for the current state of the player.
	void displayStatus();

	//Play card from chosen position in player's hand.
	void playCardFromHand(int pos);

	void setupPlayer(int choice);
};
// int Stance; //WAT, PSM (Prismatic): Current Stance. 0: Neutral NTL, 1: Calm CLM, 2: Wrath WRT, 3: Divinity DIV. Combat only.
// int orbSlots; //How many orb slots you currently have. Defect starts with 3. On any other character, you start with 1 if you are Prismatic. Combat only.
// deque <int> orbs; //Your channeled orbs. Combat only.
// bool prismatic;
#endif