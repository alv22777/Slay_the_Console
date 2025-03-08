#include "constants.h"
#include "card.h"
#include "pile.h"


////////////////////THE IRONCLAD//////////////////

////////////////////STARTER DECK//////////////////
Card ICL_Strike = {0, "Strike", "ATK", 1, "Starter","ENY: 6 DMG"};
Card ICL_Defend = {0, "Defend", "SKL", 1, "Starter", "YOU: 5 BLK"};
Card ICL_Bash = {0, "Bash", "ATK", 2,  "Starter", "ENY: 8 DMG, 2 VUL"};

Card blank_card = {0,"None","None",0,"None","None"};

Pile ICL_STARTER_DECK;
Pile SLT_STARTER_DECK;
Pile empty_deck;

Card SLT_Strike = {1, "Strike", "ATK", 1, "Starter","ENY: 6 DMG"};
Card SLT_Defend = {1, "Defend", "SKL", 1, "Starter","YOU: 5 BLK"};
Card SLT_Neutralize = {1, "Neutralize", "ATK", 0, "Starter","ENY: 3 DMG, 2 WKN"};
Card SLT_Survivor = {1, "Survivor", "SKL", 1, "Starter","DISCARD: FROM HAND, YOU: 8 BLK"};


////////////////////CARD REWARDS//////////////////
void initializeDecks(){
    for (int i = 0; i < 5; i++) ICL_STARTER_DECK.addCardToPile(ICL_Strike);
    for (int i = 0; i < 4; i++) ICL_STARTER_DECK.addCardToPile(ICL_Defend);
    ICL_STARTER_DECK.addCardToPile(ICL_Bash);

    for (int i = 0; i < 5; i++) SLT_STARTER_DECK.addCardToPile(SLT_Strike);
    for (int i = 0; i < 5; i++) SLT_STARTER_DECK.addCardToPile(SLT_Defend);
    SLT_STARTER_DECK.addCardToPile(SLT_Neutralize);
    SLT_STARTER_DECK.addCardToPile(SLT_Survivor);

}
