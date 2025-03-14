#include "constants.h"
#include "card.h"
#include "pile.h"

const int ICL_STARTING_MAX_HP = 80;
const int SLT_STARTING_MAX_HP = 70;
const int DEF_STARTING_MAX_HP = 75;
const int WAT_STARTING_MAX_HP = 72;
const int STARTING_ENERGY = 3;
const int STARTING_BLOCK = 0;
const int MAX_BLOCK = 999;
////
////////////////////THE IRONCLAD//////////////////

////////////////////STARTER DECK//////////////////
Card ICL_Strike = {0, "Strike", "ATK", 1, "Starter","ENY: 6 DMG"};
Card ICL_Defend = {0, "Defend", "SKL", 1, "Starter", "YOU: 5 BLK"};
Card ICL_Bash = {0, "Bash", "ATK", 2,  "Starter", "ENY: 8 DMG, 2 VUL"};

Card blank_card = {0,"None","None",0,"None","None"};


Pile empty_deck;

Card SLT_Strike = {1, "Strike", "ATK", 1, "Starter","ENY: 6 DMG"};
Card SLT_Defend = {1, "Defend", "SKL", 1, "Starter","YOU: 5 BLK"};
Card SLT_Neutralize = {1, "Neutralize", "ATK", 0, "Starter","ENY: 3 DMG, 2 WKN"};
Card SLT_Survivor = {1, "Survivor", "SKL", 1, "Starter","DISCARD: FROM HAND, YOU: 8 BLK"};


Pile ICL_STARTER_DECK = createIroncladStarterDeck();
Pile SLT_STARTER_DECK = createSilentStarterDeck();

////////////////////CARD REWARDS//////////////////
Pile createIroncladStarterDeck(){
    Pile deck;
    for(int i =0; i<5;i++){deck.addCardToPile(ICL_Strike);}
    for(int i =0; i<4;i++){deck.addCardToPile(ICL_Defend);}
    deck.addCardToPile(ICL_Bash);
    return deck;
}
Pile createSilentStarterDeck(){
    Pile deck;
    for(int i = 0; i<5; i++){deck.addCardToPile(SLT_Strike);}
    for(int i = 0;i<5;i++){deck.addCardToPile(SLT_Defend);}
    deck.addCardToPile(SLT_Neutralize);
    deck.addCardToPile(SLT_Survivor);
    return deck;
}
