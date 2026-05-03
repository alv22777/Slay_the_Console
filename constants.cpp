#include "constants.h"
#include "card.h"
#include "pile.h"
#include "effect.h"

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


Card ICL_Strike = {0, "Strike", CardType::attack, 1, CardRarity::starter,"Deal 6 damage.", {Effect(EffectType::damage, 6)}, targetType::enemy};
Card ICL_Defend = {0, "Defend", CardType::skill, 1, CardRarity::starter, "Gain 5 block", {Effect(EffectType::block, 5)}, targetType::ally};
Card ICL_Bash = {0, "Bash", CardType::attack, 2,  CardRarity::starter, "Deal 8 damage. Apply 2 vulnerable", {Effect(EffectType::damage, 8)}, targetType::enemy};
Card ICL_Sword_boomerang = {0,"Sword Boomerang",CardType::attack, 1, CardRarity::common, "Deal 10 damage to a random enemy 3 times.",{Effect(EffectType::damage, 10),Effect(EffectType::damage, 10),Effect(EffectType::damage, 10)}, targetType::random_enemy};
Card blank_card = {0,"None",CardType::status,0,CardRarity::status,"None",{}, targetType::none};


Pile empty_deck;

Card SLT_Strike = {1, "Strike", CardType::attack, 1, CardRarity::starter,"Deal 6 damage.", {Effect(EffectType::damage, 6)}, targetType::enemy};
Card SLT_Defend = {1, "Defend", CardType::skill, 1, CardRarity::starter,"Gain 5 block.", {Effect(EffectType::block, 5)}, targetType::ally};
Card SLT_Neutralize = {1, "Neutralize", CardType::attack, 0, CardRarity::starter,"Deal 3 damage, apply 1 weak.", {Effect(EffectType::damage, 3)}, targetType::enemy};
Card SLT_Survivor = {1, "Survivor", CardType::skill, 1, CardRarity::starter,"Discard 1 hand. Gain 8 block.", {Effect(EffectType::block, 8)}, targetType::ally};


Pile ICL_STARTER_DECK = createIroncladStarterDeck();
Pile SLT_STARTER_DECK = createSilentStarterDeck();

////////////////////CARD REWARDS//////////////////
Pile createIroncladStarterDeck(){
    Pile deck;
    for(int i =0; i<5;i++){deck.addCardToPile(ICL_Strike);}
    for(int i =0; i<4;i++){deck.addCardToPile(ICL_Defend);}
    deck.addCardToPile(ICL_Sword_boomerang);
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
