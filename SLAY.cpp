#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

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
	SKL: A Skill. Usually gives you block and/or other useful efects like card draw.
	POW: A Power. Gives you a continuous (useful) effect throughout combat.
	CUR: Curse. Has negative effects. Obtained through events and certain relics.
	EXH: Exhaust. When this card is played, remove it from your deck until end of combat. 
	
*/
struct Card{
	
	int character; //0: ICL, 1: SLT, 2: DEF, 3: WAT, 4: CLS
	string name;
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
	int Stance; //WAT, PSM (Prismatic): Current Stance. 0: Neutral NTL, 1: Calm CLM, 2: Wrath WRT, 3: Divinity DIV. Combat only.
	vector<Card> deck; //Your current deck of cards.
};


////////////////////THE IRONCLAD//////////////////

////////////////////STARTER DECK//////////////////
Card IC_Starter_Deck[3]={
	{0, "Strike", "ATK", 1, "Basic","ENY: 6 DMG"},
	{0, "Defend", "SKL", 1, "Basic", "YOU: 5 BLK"},
	{0, "Bash", "ATK", 2,  "Basic", "ENY: 8 DMG, 2 VUL"}
};

////////////////////CARD REWARDS//////////////////
Card IC_Card_Rewards[4] ={
	{0, "Clothesline", "ATK", 2, "Common", "ENY: 12 DMG, 2 WKN"},
	{0, "Power Through", "SKL", 2, "Uncommon", "YOU: 15 BLK, HAND: 2 WND"},
	{0, "Reckless Charge", "ATK", 1, "Uncommon","ENY: DRW: 1 DZD"},
	{0, "Demon Form", "POW", 3, "Rare", "TURN: YOU: +3 STR"}
};

Character C;

void print_deck(vector<Card>, Character);
int main(){ 
	int choice = 0;
	while(choice>4||choice<1){cout<<"Please select your character: \n1. The Ironclad\n2. The Silent\n3. The Defect\n4. The Watcher\n"; cin>>choice;}
	
	switch(choice){
		case 1: C.name = "The Ironclad"; C.MaxHP = 80; C.HP = 80; C.Block = 0; 
			for(int i = 0; i<5; i++){C.deck.push_back (IC_Starter_Deck[0]);} 
			for(int i = 5; i<9; i++){C.deck.push_back (IC_Starter_Deck[1]);} 
			C.deck.push_back(IC_Starter_Deck[2]); C.deck.push_back(IC_Card_Rewards[3]); break;
		case 2: C.name = "The Silent"; C.MaxHP = 70; C.HP = 70; break;
		default: break;
	}
	

	//STATUS BAR
	cout<<C.name<<endl;
	cout<<"HP : "<<C.HP<<"/"<<C.MaxHP<<endl;
	print_deck(C.deck, C);	
	
	
	return 0;
}

void print_deck(vector<Card> v, Character C){
	printf("Deck (%d cards): \n", C.deck.size()); 
	
	int j = 1;
	for(Card i: v)
		cout<<j++<<". "<<i.name<<" ("<<i.energy_cost<<","<<i.type<<"): "<<i.card_text<<endl;
}