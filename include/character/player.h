#ifndef PLAYER_H
#define PLAYER_H
#include"character/character.h"
#include <memory>
#include "card/pile.h"
#include "card/card.h"
#include "item/potion.h"


enum class Color;


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
    
    uint8_t potion_slots;
	std::vector<Potion> potions;
    
    bool drawCard(Game& game);
    public:
    Player(std::string name, int maxHP, int maxEnergy, Color c);

    void StartCombat(Game& game);
    void setAttribute(Attribute a, int magnitude);

    void changeAttribute(Attribute a, int Delta);
    
    int getAttribute(Attribute a);

    //Add Card c to player Pile type (deck, hand, discard...). 
    void addToPile(PileID type, Card &c, bool bottom);

    int getPlayerPileSize(PileID type);
	//Removes Card with position pos from the player's Pile type (deck, hand, discard...).
	void removeFromPlayerPile(PileID type, int pos);


	//Display player Pile type (deck, hand, discard...).
	void displayPlayerPile(PileID type, bool fixed, int n, bool indexed);
    

	//Draw x cards from player's draw pile into hand. If draw is empty, shuffle discard into draw and continue drawing. If both draw and discard are empty, stop drawing.
	uint32_t drawCards(int amount, Game& game);
	//Discard the player's hand at the end of the turn.
	void discardHand();

	//Display a simple status bar for the current state of the player.
	void displayStatus();

    Card &getCardFromPile(PileID type, int position);

    void setPlayed(Card &c);

    //Play card from chosen position in player's hand.
	void playCardFromHand(int pos, Game& game);

	static std::unique_ptr<Player> createPlayer(int choice);
    bool isHandFull();
    void endCombat();
    Card& getPlayed();



    uint32_t transferCardsManual(PileID source, PileID target, int amount, bool bottom, Game& game);

    uint32_t transferCardsAuto(PileID source, PileID target, std::deque<int> selected, bool bottom);

    std::deque<int> chooseCards(PileID source, int amount, Game& game);
    std::deque<int> findIndexes(PileID p, CardType c, bool matching); 
    
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    Player(Player&&) noexcept = default;
    Player& operator=(Player&&) noexcept = default;
    
    ~Player() noexcept override = default;
};

#endif
