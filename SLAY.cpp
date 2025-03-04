#include <iostream>
#include <deque>
#include <algorithm>
#include <random>
#include <time.h>
#include <windows.h>
using namespace std;	


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
	int MaxEnergy;
	int energy; //Current energy. Combat only.
	int Block; //Current amount of BLK. Combat only.
	deque<Card> deck; //Your current deck of cards.
	// int Stance; //WAT, PSM (Prismatic): Current Stance. 0: Neutral NTL, 1: Calm CLM, 2: Wrath WRT, 3: Divinity DIV. Combat only.
	// int orbSlots; //How many orb slots you currently have. Defect starts with 3. On any other character, you start with 1 if you are Prismatic. Combat only.
	// deque <int> orbs; //Your channeled orbs. Combat only.
	
	// bool prismatic;
	deque<Card> Hand;
	deque<Card> draw_pile; //You draw cards from this pile
	deque<Card> discard_pile; //You discard cards in here from card effects and at the end of your turn.
	deque<Card> exhaust_pile; //Cards that have exhausted this combat.
	deque<Card> played; //The card you just played. Not in your hand, but also not in discard. Its effects are being resolved.
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
////////////////////CARD REWARDS//////////////////

Character Player;

void print_pile(deque<Card>);
void draw(Character&, int);
void play(Character&, Card, int);
deque<Card> Shuffle(deque<Card>);
bool change = 1;

int main(){ 
	std::srand(time(0));
	int choice = 0;
	while(choice>4||choice<1){cout<<"Please select your character: \n1. The Ironclad\n2. The Silent\n3. The Defect\n4. The Watcher\n"; cin>>choice;}
	
	switch(choice){
		case 1: Player.name = "The Ironclad"; Player.MaxHP = 80; Player.HP = 80; Player.Block = 0;
			for(int i = 0; i<5; i++){Player.deck.push_front (IC_Starter_Deck[0]);} 
			for(int i = 0; i<4; i++){Player.deck.push_front (IC_Starter_Deck[1]);} 
			Player.deck.push_front(IC_Starter_Deck[2]);
			Player.MaxEnergy = 3;
			Player.energy = 3;
			break;
		
		case 2: Player.name = "The Silent"; Player.MaxHP = 70; Player.HP = 70; break;
		default: break;
	}
	
	cout<<"COMBAT SIMULATION"<<endl;


	Player.draw_pile = Shuffle(Player.deck);
	draw(Player,10);

	while(1){

		if(change==1){

			system("cls");
			//STATUS BAR
			cout<<Player.name<<endl;
			cout<<"HP : "<<Player.HP<<"/"<<Player.MaxHP<<endl;
			cout<<"Energy : "<<Player.energy<<"/"<<Player.MaxEnergy<<endl;

			//STATUS BAR
			print_pile(Player.Hand);
		}

			change=0;
			
			do{
				cout<<"CARD TO PLAY?\n";
				cin>>choice;
				if(cin.fail()){cin.clear(); cin.ignore(1000, '\n');cout<<"NOT A NUMBER\n";choice=100;continue;}
				if(choice<Player.Hand.size()&&choice>=0){if(Player.Hand[choice].energy_cost>Player.energy){cout<<"NOT ENOUGH ENERGY.\n";}}

			}while((choice>Player.Hand.size()-1||choice<0)||(Player.Hand[choice].energy_cost>Player.energy)||cin.fail());
			
			Card Played = Player.Hand[choice];
			play(Player, Played, choice);
			Sleep(1000);

			change = 1;
	}
	
	return 0;
}

void print_pile(deque<Card> v){
	printf("%d cards: \n", v.size()); 	
	int j = 0;
	for(Card i: v)
		cout<<j++<<". "<<i.name<<" ("<<i.energy_cost<<" NRG,"<<i.type<<"): "<<i.card_text<<endl;
}

deque<Card> Shuffle(deque<Card> v){
	deque<Card> Shuffled = v;
	random_shuffle(Shuffled.begin(), Shuffled.end());
	cout<<"Shuffled "<< v.size() <<" cards.\n";
	return Shuffled;
}

void draw(Character &Player, int amount){
	for(int i =0; i<amount;i++){
		if(Player.draw_pile.size()>0){
		Player.Hand.push_front( Player.draw_pile.front());
		Player.draw_pile.pop_front();} 
	}	
}

void play(Character &Player, Card Played, int handpos){
	cout<<"Playing: "<<Played.name<<"...\n";
	Player.energy -= Played.energy_cost;
	//EFFECT foo();
	cout<<"\nYOU JUST PLAYED "<<Played.name<<"!"<<endl;
	Player.discard_pile.push_front(Player.played.front());
	Player.played.pop_front();
	Player.Hand.erase(Player.Hand.begin()+handpos);
}
