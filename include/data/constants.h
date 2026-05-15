#ifndef CONSTANTS_H
#define CONSTANTS_H
#include"stdint.h"

class Card;
class Pile;


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
extern const int ICL_STARTING_MAX_HP;
extern const int SLT_STARTING_MAX_HP;
extern const int DEF_STARTING_MAX_HP;
extern const int WAT_STARTING_MAX_HP;
extern const int STARTING_ENERGY;
extern const int STARTING_BLOCK;
extern const int MAX_BLOCK;
extern const int EVENT_LOG_SIZE;
extern const int MAX_HAND_SIZE;
extern const uint64_t SEED_MIN;
extern const uint64_t SEED_MAX;

extern Pile empty_deck;
extern Pile ICL_STARTER_DECK;
extern Pile SLT_STARTER_DECK;
extern Pile DEF_STARTER_DECK;
extern Pile WAT_STARTER_DECK;

// Predefined Cards (Declared here, defined in `constants.cpp`)

extern Card blank_card;

extern Card ICL_Strike;
extern Card ICL_Defend;
extern Card ICL_Bash;

extern Card SLT_Strike;
extern Card SLT_Defend;
extern Card SLT_Neutralize;
extern Card SLT_Survivor;

extern Card ICL_Sword_boomerang;
extern Card ICL_Twin_Strike;
extern Card ICL_Bloodletting;
extern Card ICL_Headbutt;
extern Card ICL_True_Grit;
extern Card ICL_Exhume;
extern Card ICL_Clash;

extern Card SLT_Prepared;
extern Card SLT_Acrobatics;

extern Card DEF_Skim;
extern Card DEF_Hologram;

extern Card CLS_Finesse;
extern Card CLS_Bite;

extern Card CUR_Injury;

extern Card STS_Wound;




////////////////////STARTER DECK//////////////////

Pile createIroncladStarterDeck();
Pile createSilentStarterDeck();
#endif
