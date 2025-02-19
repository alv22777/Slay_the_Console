#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <time.h>

using namespace std;	


/*
	Glossary:
	ICL: The Ironclad
	SLT: The Silent
	DEF: The Defect
	WAT: The Watcher
	CLS: Colorless cards
	HP: Hit Points. If it becomes 0, you instantly die and lose the game.
	BLK: Block. If an enemy attacking would reduce your HP, lose that amount of block instead.
	ATK: An Attack. Deals damage to an/ALL enemies. Sometimes has other effects.
	SKL: Skill. Usually gives you block and/or other useful efects like card draw.
	POW: Power. Gives you a continuous (useful) effect throughout combat.
	CUR: Curse. Has negative effects. Obtained through events and certain relics.
	EXH: Exhaust. When this card is played, remove it from your deck until end of combat. 
*/

struct Card{
	int character; //0: ICL, 1: SLT, 2: DEF, 3: WAT, 4: CLS
	string name; //The card's name.
	string type; //ATK, SKL, POW, CUR, STS
	int energy_cost; //if energy_cost = -1, card is unplayable
	string card_Rarity;
	string card_text;
};


struct Character{
	string name; //Your character's name.
	int MaxHP; //Maximun number of Hit Points. Persistent through floors.
	int HP; //Current Hitpoints. Persistent through floors.
	int energy; //Current energy. Combat only.
	int Block; //Current amount of BLK. Combat only.
	vector<Card> deck; //Your current deck of cards.
	// int Stance; //WAT, PSM (Prismatic): Current Stance. 0: Neutral NTL, 1: Calm CLM, 2: Wrath WRT, 3: Divinity DIV. Combat only.
	// int orbSlots; //How many orb slots you currently have. Defect starts with 3. On any other character, you start with 1 if you are Prismatic. Combat only.
	// vector <int> orbs; //Your channeled orbs. Combat only.
	
	// bool prismatic;
	vector<Card> draw_pile; //You draw cards from this pile
	vector<Card> discard_pile; //You discard cards in here from card effects and at the end of your turn.
	vector<Card> exhaust_pile; //Cards that have exhausted this combat.
	vector<Card> played; //The card you just played. Not in your hand, but also not in discard. Its effects are being resolved.
};


////////////////////THE IRONCLAD//////////////////

////////////////////STARTER DECK//////////////////
Card IC_Starter_Deck[3]={
	{0, "Strike", "ATK", 1, "Starter","ENY: 6 DMG"},
	{0, "Defend", "SKL", 1, "Starter", "YOU: 5 BLK"},
	{0, "Bash", "ATK", 2,  "Starter", "ENY: 8 DMG, 2 VUL"}
};

////////////////////CARD REWARDS//////////////////
Card IC_Card_Rewards[4] ={
	{0, "Clothesline", "ATK", 2, "Common", "ENY: 12 DMG, 2 WKN"},
	{0, "Power Through", "SKL", 2, "Uncommon", "YOU: 15 BLK, HAND: 2 WND"},
	{0, "Reckless Charge", "ATK", 1, "Uncommon","ENY: 7 DMG DRW: 1 DZD"},
	{0, "Demon Form", "POW", 3, "Rare", "TURN: YOU: +3 STR"}
};


Character Player;

void print_pile(vector<Card>);
void draw_card(vector<Card>, Character);
vector<Card> Shuffle(vector<Card>);
int main(){ 
	std::srand(time(0));
	int choice = 0;
	while(choice>4||choice<1){cout<<"Please select your character: \n1. The Ironclad\n2. The Silent\n3. The Defect\n4. The Watcher\n"; cin>>choice;}
	
	switch(choice){
		case 1: Player.name = "The Ironclad"; Player.MaxHP = 80; Player.HP = 80; Player.Block = 0;
			for(int i = 0; i<5; i++){Player.deck.push_back (IC_Starter_Deck[0]);} 
			for(int i = 0; i<4; i++){Player.deck.push_back (IC_Starter_Deck[1]);} 
			Player.deck.push_back(IC_Starter_Deck[2]); break;
		case 2: Player.name = "The Silent"; Player.MaxHP = 70; Player.HP = 70; break;
		default: break;
	}
	

	//STATUS BAR
	cout<<Player.name<<endl;
	cout<<"HP : "<<Player.HP<<"/"<<Player.MaxHP<<endl;
	
	Player.deck.push_back(IC_Card_Rewards[3]);
	Player.deck.push_back(IC_Card_Rewards[0]);
	Player.deck.push_back(IC_Card_Rewards[2]);
	Player.deck.push_back(IC_Card_Rewards[1]);
	Player.deck.push_back(IC_Card_Rewards[2]);
	

	Player.draw_pile = Shuffle(Player.deck);
	print_pile(Player.draw_pile);
	
	return 0;
}

void print_pile(vector<Card> v){
	printf("Deck (%d cards): \n", v.size()); 	
	int j = 1;
	for(Card i: v)
		cout<<j++<<". "<<i.name<<" ("<<i.energy_cost<<","<<i.type<<"): "<<i.card_text<<endl;
}

vector<Card> Shuffle(vector<Card> v){
	vector<Card> Shuffled = v;
	random_shuffle(Shuffled.begin(), Shuffled.end());
	cout<<"Shuffled "<< v.size() <<" cards.\n";
	return Shuffled;
}