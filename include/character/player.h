#ifndef PLAYER_H
#define PLAYER_H
#include"character/character.h"
#include"card/pile.h"
#include"card/card.h"
#include"ui/colors.h"

//The player can have 6 Piles, 
enum class PileType{deck, combat_deck, hand, draw, discard, exhaust};
class Player: public Character{
    int max_energy;
    int energy;
    //std::deque<Relic> relics;

    Pile deck; //Your current deck of cards.
	Pile combat_deck; //Deck used for combat.
	Pile hand; //Your current hand
	Pile draw; //You draw cards from this pile
	Pile discard; //You discard cards into here from card effects and at the end of your turn.
	Pile exhaust; //Cards that have exhausted this combat.

	Card played; //player's last played card.

    public:
    Player(std::string name, int maxHP, int maxEnergy, Color c);

    void StartCombat(Game& game);
    void setAttribute(Attribute a, int magnitude);

    void changeAttribute(Attribute a, int Delta);
    
    int getAttribute(Attribute a);

    //Add Card c to player Pile type (deck, hand, discard...). 
    void addToPile(PileType type, Card &c, bool bottom);

    int getPlayerPileSize(PileType type);
	//Removes Card with position pos from the player's Pile type (deck, hand, discard...).
	void removeFromPlayerPile(PileType type, int pos);


	//Display player Pile type (deck, hand, discard...).
	void displayPlayerPile(PileType type, bool fixed, int n);
	
	//Draw x cards from player's draw pile into hand. If draw is empty, shuffle discard into draw and continue drawing. If both draw and discard are empty, stop drawing.
	void drawCards(int amount, Game& game);
	//Discard the player's hand at the end of the turn.
	void discardHand();

	//Display a simple status bar for the current state of the player.
	void displayStatus();

    Card &getCardFromPile(PileType type, int position);

    void setPlayed(Card &c);

    //Play card from chosen position in player's hand.
	void playCardFromHand(int pos, Game& game);

	void setupPlayer(int choice);
    void endCombat();
    Card& getPlayed();



    void transferCardsManual(PileType source, PileType target, int amount, bool bottom);

    void transferCardsAuto(PileType source, PileType target, std::deque<int> choices, bool bottom);

    std::deque<int> chooseCards(PileType source, int amount);

    ~Player() noexcept override = default;

};

#endif