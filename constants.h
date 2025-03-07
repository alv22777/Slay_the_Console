#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "card.h"
#include "pile.h"

const int ICL_STARTING_MAX_HP = 80;
const int SLT_STARTING_MAX_HP = 70;
const int DEF_STARTING_MAX_HP = 75;
const int WAT_STARTING_MAX_HP = 72;
const int STARTING_ENERGY = 3;
const int STARTING_BLOCK = 0;

////////////////////THE IRONCLAD//////////////////
extern Pile ICL_STARTER_DECK;
extern Pile SLT_STARTER_DECK;
extern Pile DEF_STARTER_DECK;
extern Pile WAT_STARTER_DECK;

// Predefined Cards (Declared here, defined in `constants.cpp`)
extern Card ICL_Strike;
extern Card ICL_Defend;
extern Card ICL_Bash;

extern Card SLT_Strike;
extern Card SLT_Defend;
extern Card SLT_Neutralize;
extern Card SLT_Survivor;
////////////////////STARTER DECK//////////////////

extern Card blank_card;

extern Pile empty_deck;


void initializeDecks();
#endif