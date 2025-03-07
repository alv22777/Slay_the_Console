#include <iostream>
#include <deque>
#include <algorithm>
#include <random>
#include <ctime>
#include <windows.h>
using std::string; using std::cout; using std::deque; using std::cin; using std::random_shuffle;	


const int ICL_STARTING_MAX_HP = 80;
const int SLT_STARTING_MAX_HP = 70;
const int DEF_STARTING_MAX_HP = 75;
const int WAT_STARTING_MAX_HP = 72;
const int STARTING_ENERGY = 3;
const int STARTING_BLOCK = 0;
/*
	Glossary:
	ICL: The Ironclad
	SLT: The Silent
	DEF: The Defect
	WAT: The Watcher
	CLS: Colorless cards
	HP: Hit Points. If it becomes 0, you instantly die and lose the game.
	NRG: Energy. It's used to play cards.
	BLK: Block. If an enemy attacking would reduce your HP, lose that amount of block instead.
	ATK: An Attack. Deals damage to an/ALL enemies. Sometimes has other effects.
	SKL: Skill. Usually gives you block and/or other useful efects like card draw.
	POW: Power. Gives you a continuous (useful) effect throughout combat.
	CUR: Curse. Has negative effects. Obtained through events and certain relics.
	EXH: Exhaust. When this card is played, remove it from your deck until end of combat. 
*/
std::mt19937 rng;

class Card{
	int character; //0: ICL, 1: SLT, 2: DEF, 3: WAT, 4: CLS
	string name; //The card's name.
	string type; //ATK, SKL, POW, CUR, STS
	int energy_cost; //if energy_cost = -1, card is unplayable
	string rarity;
	string card_text;
	public:
	//Creates a Card and initializes it's values with the given arguments.
	Card(int c, string n, string t, int cost, string r, string text)//Character, name, type, energy cost, rarity, card text
		:character(c), name(n), type(t), energy_cost(cost), rarity(r), card_text(text){}

	//Display this card on the terminal.	
	void display(){cout<<name<<"("<<energy_cost<<" NRG, "<<type<<"):"<<card_text<<'\n';}
	int getEnergyCost(){return energy_cost;}
	string getName(){return name;}

	
};

class Pile{
	deque <Card> cards;

	public:
	//returns the deque containing the cards in the pile.
	deque<Card>& getCards(){return cards;}

	//PILE MANIPULATION METHODS//

	//Use this to add a card to the pile
	void addCardToPile(Card& card){cards.push_back(card);}
	//Use this to remove given position from this pile of cards.
	void remove(int position){cards.erase(cards.begin()+position);}
	
	//Use this to randomize the order of the cards in the deck.
	void shuffle(){
		std::shuffle(cards.begin(),cards.end(),rng);
		cout<<"Successfully shuffled "<<getCards().size()<<" cards.\n";
	}
	
	//Add all the elements from pile p into self. Generally, it should be used in tandem with deletePile(). 
	void addPileToSelf(Pile &p){
		for(Card card: p.getCards()){addCardToPile(card);}
	}
	//Remove all elements from the pile of cards
	void deletePile(){cards.erase(cards.begin(),cards.end());}

	//Move all the elements from this pile to a target pile P, then delete this pile. 
	void movePileTo(Pile& p){
		addPileToSelf(p);
		deletePile();
	}

	//This function allows to draw a certain amount of cards (amount) from another pile (&p) into self.
	//It also removes the drawn Cards from the origin pile.
	void drawFrom(Pile& p, int amount){
		for(int i=0;i<amount;i++){
			if(p.cards.empty()){std::cerr<<"This pile is empty! No cards left to draw...\n";}
			else{addCardToPile(p.cards.front()); p.remove(0);}
		} 
	}
	//This function displays the pile of cards as a simple list.
	void displayPile(){
		if (cards.empty()){cout<<"This pile is empty! Nothing to show!\n"; return;}
		int j=0;
		for (Card i: cards){cout<<j++<<". "; i.display();}
	}
};

class Character{
	string name; //Your character's name.
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
	Character(string N, int MHP, int HP, int ME, int E, int B, Pile D, Card p)
		:name(N), max_HP(MHP), HP(HP), max_energy(ME), energy(E), block(B), deck(D), played(p){}

	string getName() {return name;}
	int getMaxHP() {return max_HP;}
	int getHP(){return HP;}
	int getMaxEnergy(){return max_energy;}
	int getBlock(){return block;}
	int getEnergy(){return energy;}
	Pile getDeck(){return deck;}
	Pile getCombatDeck(){return combat_deck;}	
	Pile getHand(){return hand;}
	Pile getDraw() {return draw;}
	Pile getDiscard(){return discard;}
	Pile getExhaust(){return exhaust;}
	Card getPlayed(){return played;}

	int getDeckSize() {return deck.getCards().size();}
	int getHandSize() {return hand.getCards().size();}
	int getDrawSize() {return draw.getCards().size();}
	int getDiscardSize() {return discard.getCards().size();}
	int getExhaustSize() {return exhaust.getCards().size();}
	void setName(string n){name = n;}
	void setMaxHP(int m){max_HP = m;}
	void setBlock(int b){block = b;}
	void setHP(int hp){HP = hp;}
	void setPlayed(Card p){played = p;}
	//Changes maxHP by an amount Delta (integer). To decrease MaxHP, Delta<0. Gives terminal feedback on the change.
	void changeMaxHP(int Delta){
		max_HP += Delta;
		cout<<((Delta>0)? "Gained ":"Lost ")<<abs(Delta)<<" Max HP!\n";
	}
	void changeMaxEnergy(int Delta){
		max_energy += Delta;
		cout<<((Delta>0)? "Gained ":"Lost ")<<abs(Delta)<<" Max HP!\n";
	}
	//Changes Block by an amount Delta(integer).
	void changeBlock(int Delta){
		block += Delta;
		cout<<((Delta>0)? "Gained ":"Lost ")<<abs(Delta)<<" Block!\n";
	}
	//Changes HP by an amount Delta(integer).
	void changeHP(int Delta){
		HP += Delta;
		cout<<((Delta>0)? "Gained ":"Lost ")<<abs(Delta)<<" HP!\n";		
	}
	//Changes energy by an amount Delta(integer).
	void changeEnergy(int Delta){
		energy += Delta;
		cout<<((Delta>0)? "Gained ":"Lost ")<<abs(Delta)<<" Energy!\n";
	}
	

	void StartCombat(){
		cout<<"Creating combat deck...\n"; combat_deck.addPileToSelf(deck);
		cout<<"Combat deck: "; combat_deck.displayPile();
		cout<<"Shuffling Combat deck";	combat_deck.shuffle(); combat_deck.displayPile();
		cout<<"Creating Draw Pile...\n";
		draw.addPileToSelf(combat_deck);
		draw.displayPile();
		hand.drawFrom(draw,5);
	}
	
	//adds Card c to player master deck.
	void addToDeck(Card c){deck.addCardToPile(c);}
	//Add Card c to player's draw pile
	void addToDraw(Card c){draw.addCardToPile(c);}
	//Add Card c to Player's hand.
	void addToHand(Card c){hand.addCardToPile(c);}
	//Add Card c to Player's discard pile.
	void addToDiscard(Card c){discard.addCardToPile(c);}
	//Add Card c to Player's exhaust pile.
	void addToExhaust(Card c){exhaust.addCardToPile(c);}

	//Removes a card with passed position from the player's deck.
	void removeFromDeck(int position){deck.remove(position);}
	//Removes a card with passed position from the player's draw pile.
	void removeFromDraw(int position){draw.remove(position);}
	//Removes a card with passed position from the player's discard pile.
	void removeFromHand(int position){hand.remove(position);}
	//Removes a card with passed position from the player's discard pile.
	void removeFromDiscard(int position){discard.remove(position);}
	//Removes a card with passed position from the player's Exhaust pile.
	void removeFromExhaust(int position){exhaust.remove(position);}
	
	//Delete Player's Deck.
	void deleteDeck(){deck.deletePile();}
	//Delete Player's Draw pile.
	void deleteDraw(){draw.deletePile();}
	//Delete Player's Hand.
	void deleteHand(){hand.deletePile();}
	//Delete Player's Discard Pile.
	void deleteDiscard(){discard.deletePile();}
	//Delete Player's Exhaust pile.
	void deleteExhaust(){deck.deletePile();}


	void displayStatus(){
		//STATUS BAR
		cout<<name<<'\n';
		cout<<"HP : "<<HP<<"/"<<max_HP<<'\n';
		cout<<"Energy : "<<energy<<"/"<<max_energy<<'\n';	
	}
	void playCardFromHand(int pos){
		Card played = getHand().getCards()[pos];
		cout<<"Playing: "<<played.getName()<<"...";
		changeEnergy(-played.getEnergyCost());

		//EFFECT foo();

		cout<<"YOU JUST PLAYED "<<played.getName()<<"!"<<'\n';
		addToDiscard(played);
		removeFromHand(pos);
	}
};


////////////////////THE IRONCLAD//////////////////

////////////////////STARTER DECK//////////////////
Card ICL_Strike = {0, "Strike", "ATK", 1, "Starter","ENY: 6 DMG"};
Card ICL_Defend = {0, "Defend", "SKL", 1, "Starter", "YOU: 5 BLK"};
Card ICL_Bash = {0, "Bash", "ATK", 2,  "Starter", "ENY: 8 DMG, 2 VUL"};
Card blank_card = {0,"None","None",0,"None","None"};
Pile ICL_STARTER_DECK;
Pile empty_deck;


////////////////////CARD REWARDS//////////////////
Card IC_Card_Rewards[] ={
	{0, "Clothesline", "ATK", 2, "Common", "ENY: 12 DMG, 2 WKN"},
	{0, "Power Through", "SKL", 2, "Uncommon", "YOU: 15 BLK, HAND: 2 WND"},
	{0, "Reckless Charge", "ATK", 1, "Uncommon","ENY: 7 DMG DRW: 1 DZD"},
	{0, "Demon Form", "POW", 3, "Rare", "TURN: YOU: +3 STR"}
};

////////////////////CARD REWARDS//////////////////


bool change = 1;
Character player = Character("NOPLAYER", 0, 0, 0, 0, 0, empty_deck, blank_card);

int main(){ 
	for(int i =0; i<9;i++){
		(i<5)? ICL_STARTER_DECK.addCardToPile(ICL_Strike):ICL_STARTER_DECK.addCardToPile(ICL_Defend);
	}
	ICL_STARTER_DECK.addCardToPile(ICL_Bash);
	
	
	// set seed
	//std::mt19937 g(12314);
	std::mt19937 g(time(nullptr)); //RNG

	int choice = 0;
	while(choice>4||choice<1){cout<<"Please select your character: \n1. The Ironclad\n2. The Silent\n3. The Defect\n4. The Watcher\n"; cin>>choice;}
	
	switch(choice){
		case 1: 
			player = Character("The Ironclad", ICL_STARTING_MAX_HP, ICL_STARTING_MAX_HP, STARTING_ENERGY, STARTING_ENERGY, STARTING_BLOCK, ICL_STARTER_DECK, blank_card);
			cout<<"YOU SELECTED "<<player.getName()<<"\nStarting max HP: "<<player.getMaxHP()<<"\nHP: "<<player.getHP()<<"\nMax Energy: "<<player.getMaxEnergy()<<"\nEnergy: "<<player.getEnergy()<<"\nSTARTER DECK:\n";
			player.getDeck().displayPile();
			break;
		
		case 2:break;
	}
	
	cout<<"COMBAT SIMULATION"<<'\n';
	
	player.StartCombat();


	while(1){

		if(change==1){
			//system("cls");
		}

			change=0;			
			player.displayStatus();
			player.getHand().displayPile();
			//STATUS BAR


			do{
				cout<<"CARD TO PLAY?\n";
				cin>>choice;
				if(cin.fail()){cin.clear(); cin.ignore(1000, '\n');cout<<"NOT A NUMBER\n";choice=100;continue;}
				if(choice<player.getHand().getCards().size()&&choice>=0){if(player.getHand().getCards()[choice].getEnergyCost()>player.getEnergy()){cout<<"NOT ENOUGH ENERGY.\n";}}

			}while((choice>player.getHand().getCards().size()-1||choice<0)||(player.getHand().getCards()[choice].getEnergyCost()>player.getEnergy())||cin.fail());
			
			Card Played = player.getHand().getCards()[choice];
			player.playCardFromHand(choice);

			Sleep(1000);

			change = 1;
	}
	
	return 0;
}

