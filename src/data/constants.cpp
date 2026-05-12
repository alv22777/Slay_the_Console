#include "data/constants.h"
#include "game_logic/effect.h"
#include "card/card.h"
#include "card/pile.h"
#include "ui/colors.h"

const int ICL_STARTING_MAX_HP = 80;
const int SLT_STARTING_MAX_HP = 70;
const int DEF_STARTING_MAX_HP = 75;
const int WAT_STARTING_MAX_HP = 72;
const int STARTING_ENERGY = 3;
const int STARTING_BLOCK = 0;
const int MAX_BLOCK = 999;
const int EVENT_LOG_SIZE = 5;


////////////////////THE IRONCLAD//////////////////

////////////////////STARTER DECK//////////////////

Card blank_card = {Color::colorless,"None",CardType::status,0,CardRarity::status,"None",{}, false};

Card ICL_Strike = {Color::red, "Strike", CardType::attack, 1, CardRarity::starter,"Deal 6 damage.", {Effect(EffectType::damage, 6,TargetType::enemy)}, false};

Card ICL_Defend = {Color::red, "Defend", CardType::skill, 1, CardRarity::starter, "Gain 5 block.", {Effect(EffectType::block,5,TargetType::self)}, false};

Card ICL_Bash = {Color::red, "Bash", CardType::attack, 2,  CardRarity::starter, "Deal 8 damage. Apply 2 vulnerable.", {Effect(EffectType::damage, 8, TargetType::enemy)}, false};


Card SLT_Strike = {Color::green, "Strike", CardType::attack, 1, CardRarity::starter,"Deal 6 damage.", {Effect(EffectType::damage, 6,TargetType::enemy)},  false};
Card SLT_Defend = {Color::green, "Defend", CardType::skill, 1, CardRarity::starter,"Gain 5 block.", {Effect(EffectType::block, 5, TargetType::ally)}, false};
Card SLT_Neutralize = {Color::green, "Neutralize", CardType::attack, 0, CardRarity::starter,"Deal 3 damage, apply 1 weak.", {Effect(EffectType::damage, 3, TargetType::enemy)}, false};
Card SLT_Survivor = {Color::green, "Survivor", CardType::skill, 1, CardRarity::starter,"Discard 1 hand. Gain 8 block.", {Effect(EffectType::block, 8, TargetType::ally)}, false};

////////////////////CARD REWARDS//////////////////

Card ICL_Sword_Boomerang = {Color::red,"Sword Boomerang",CardType::attack, 1, CardRarity::common, "Deal 3 damage to a random enemy 3 times.",{
    Effect(EffectType::damage, 3, TargetType::random_enemy),
    Effect(EffectType::damage, 3, TargetType::random_enemy),
    Effect(EffectType::damage, 3, TargetType::random_enemy)
}, false};

Card ICL_Twin_Strike = {Color::red,"Twin Strike", CardType::attack,1,CardRarity::common,"Deal 7 damage 2 times.",{
    Effect(EffectType::damage, 7, TargetType::enemy),
    Effect(EffectType::damage, 7, TargetType::enemy)
}, false};

Card ICL_Bloodletting={Color::red,"Bloodletting",CardType::skill,0,CardRarity::common,"Lose 3 HP. Gain 2 energy",{
    Effect(EffectType::hp,-3, TargetType::self),
    Effect(EffectType::energy,2, TargetType::self)
}, false};

Card CLS_Bite={Color::colorless, "Bite", CardType::attack, 1, CardRarity::common, "Deal 7 damage. Heal 3 HP. ",
    {
        Effect(EffectType::damage,7,TargetType::enemy),
        Effect(EffectType::hp, 3, TargetType::self)
    }, false
};

Card STS_Wound={Color::status, "Wound", CardType::status, -1, CardRarity::status, "Unplayable.",{}, false};
Card CUR_Injury={Color::curse, "Injury", CardType::curse, -1, CardRarity::curse, "Unplayable.",{}, false};



////////////////////STARTER DECKS//////////////////
Pile empty_deck = {};

Pile ICL_STARTER_DECK = createIroncladStarterDeck();
Pile SLT_STARTER_DECK = createSilentStarterDeck();



Pile createIroncladStarterDeck(){
    Pile deck;
    for(int i =0; i<1;i++){deck.addCardToPile(ICL_Strike);}
    for(int i =0; i<1;i++){deck.addCardToPile(ICL_Defend);}
    
    deck.addCardToPile(ICL_Bash);
    deck.addCardToPile(ICL_Sword_Boomerang);
    deck.addCardToPile(ICL_Twin_Strike);
    deck.addCardToPile(CLS_Bite);

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
