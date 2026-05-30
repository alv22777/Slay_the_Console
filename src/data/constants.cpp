#include "data/constants.h"
#include "game_logic/effect.h"
#include "game_logic/power.h"
#include "card/card.h"
#include "card/pile.h"
#include "ui/colors.h"


const int ICL_STARTING_MAX_HP = 80;
const int SLT_STARTING_MAX_HP = 70;
const int DEF_STARTING_MAX_HP = 75;
const int WAT_STARTING_MAX_HP = 72;
const int STARTING_ENERGY = 3;
const int STARTING_BLOCK = 0;
const int STARTING_POTION_SLOTS = 3;
const int MAX_BLOCK = 999;
const int EVENT_LOG_SIZE = 8;
const int MAX_HAND_SIZE = 10;
const int VULNERABLE_PCENT = 50;
const int WEAK_PCENT = 25;
const int FRAIL_PCENT = 25;
const uint64_t SEED_MIN = 0;
const uint64_t SEED_MAX = UINT64_MAX;

Effect NO_EFFECT(EffectType::none, 0, TargetType::self);




////////////////////STARTER DECKS//////////////////

Card blank_card = {CID::blank_card,Color::colorless,"None",CardType::status,0,CardRarity::status,"None",{}, false};

////////////////////THE IRONCLAD//////////////////
Card ICL_Strike = {CID::ICL_Strike,Color::red, "Strike", CardType::attack, 1, CardRarity::starter,"Deal 6 damage.", {Effect(EffectType::damage, 6,TargetType::enemy)}, false};
Card ICL_Defend = {CID::ICL_Defend, Color::red, "Defend", CardType::skill, 1, CardRarity::starter, "Gain 5 block.", {Effect(EffectType::block,5,TargetType::self)}, false};
Card ICL_Bash = {CID::Bash, Color::red, "Bash", CardType::attack, 2,  CardRarity::starter, "Deal 8 damage. Apply 2 vulnerable.", 
    {
        Effect(EffectType::damage, 8, TargetType::enemy),
        Effect(EffectType::gain, 2, TargetType::enemy, PID::vulnerable),
    }, false};

////////////////////THE SILENT//////////////////
Card SLT_Strike = {CID::SLT_Strike, Color::green, "Strike", CardType::attack, 1, CardRarity::starter,"Deal 6 damage.", {Effect(EffectType::damage, 6,TargetType::enemy)},  false};
Card SLT_Defend = {CID::SLT_Defend, Color::green, "Defend", CardType::skill, 1, CardRarity::starter,"Gain 5 block.", {Effect(EffectType::block, 5, TargetType::self)}, false};
Card SLT_Neutralize = {CID::Neutralize, Color::green, "Neutralize", CardType::attack, 0, CardRarity::starter,"Deal 3 damage, apply 1 weak.", 
    {
        Effect(EffectType::damage, 3, TargetType::enemy),
        Effect(EffectType::gain, 1, TargetType::enemy, PID::weak),
    }, false};

Card SLT_Survivor = {CID::Survivor ,Color::green, "Survivor", CardType::skill, 1, CardRarity::starter,"Discard 1 hand. Gain 8 block.", 
    {
        Effect(EffectType::discard,1,TargetType::self),
        Effect(EffectType::block, 8, TargetType::self)
    }, false};
     
////////////////////THE DEFECT//////////////////

////////////////////THE WATCHER//////////////////

////////////////////THE REGENT//////////////////

////////////////////THE NECROBINDER//////////////////
    
////////////////////IRONCLAD CARD REWARDS//////////////////    
Card ICL_Sword_Boomerang = {CID::Sword_Boomerang, Color::red,"Sword Boomerang",CardType::attack, 1, CardRarity::common, "Deal 3 damage to a random enemy 3 times.",{
    Effect(EffectType::damage, 3, TargetType::random_enemy),
    Effect(EffectType::damage, 3, TargetType::random_enemy),
    Effect(EffectType::damage, 3, TargetType::random_enemy)
}, false};

Card ICL_Twin_Strike = {CID::Twin_Strike, Color::red,"Twin Strike", CardType::attack,1,CardRarity::common,"Deal 7 damage 2 times.",{
    Effect(EffectType::damage, 7, TargetType::enemy),
    Effect(EffectType::damage, 7, TargetType::enemy)
}, false};

Card ICL_Bloodletting={CID::Bloodletting, Color::red,"Bloodletting",CardType::skill,0,CardRarity::uncommon,"Lose 3 HP. Gain 2 energy",{
    Effect(EffectType::hp,-3, TargetType::self),
    Effect(EffectType::energy,2, TargetType::self)
}, false};

Card ICL_Headbutt={CID::Headbutt, Color::red, "Headbutt",CardType::attack, 1, CardRarity::common, "Deal 9 damage. Put 1 card from your discard pile on top of your draw pile.",
    {
        Effect(EffectType::damage, 9, TargetType::enemy),
        Effect(EffectType::headbutt, 1, TargetType::self)
    }, false};

Card ICL_True_Grit = {CID::True_Grit, Color::red, "True Grit", CardType::skill, 1, CardRarity::common, "Gain 7 block. Exhaust 1 random card from your hand.",
    {
        Effect(EffectType::block, 7, TargetType::self),
        Effect(EffectType::exhaust, 1, TargetType::self)
    }, false};

Card ICL_Exhume = {CID::Exhume, Color::red, "Exhume", CardType::skill, 1, CardRarity::rare, "Put 1 card from your exhaust pile into your hand.",
    {
        Effect(EffectType::exhume,1,TargetType::self)
    }, true};

Card ICL_Clash = {CID::Clash, Color::red, "Clash", CardType::attack, 0, CardRarity::common, "Deal 14 damage. Play: every card in your hand is an attack.",
{
    Effect(EffectType::damage, 14, TargetType::enemy),
}, false};
////////////////////SILENT CARD REWARDS//////////////////  
Card SLT_Prepared = {CID::Prepared, Color::green, "Prepared", CardType::skill, 0, CardRarity::common, "Draw 1 card. Discard 1 card.",
    {
        Effect(EffectType::draw, 1, TargetType::self),
        Effect(EffectType::discard, 1, TargetType::self)
    }, false};

Card SLT_Acrobatics ={CID::Acrobatics, Color::green, "Acrobatics", CardType::skill, 1, CardRarity::uncommon, "Draw 3 cards. Discard 1 card.",
    {
        Effect(EffectType::draw,3,TargetType::self),
        Effect(EffectType::discard, 1, TargetType::self)
    }, false};

Card SLT_Grand_Finale ={CID::Grand_Finale, Color::green, "Grand Finale", CardType::attack, 0, CardRarity::rare, "Deal 50 damage to all enemies. Play: your draw pile is empty.",
    {
        Effect(EffectType::damage,50,TargetType::enemy_all)
    }, false};

////////////////////DEFECT CARD REWARDS//////////////////
Card DEF_Skim = {CID::Skim, Color::blue, "Skim", CardType::skill, 1, CardRarity::uncommon, "Draw 3 cards.",
    {
        Effect(EffectType::draw, 3, TargetType::self)
    }, false};
Card DEF_Hologram = {CID::Hologram, Color:: blue, "Hologram", CardType::skill, 1, CardRarity::common, "Gain 3 block. Put 1 card from your discard pile into your hand.",
    {
        Effect(EffectType::block, 3, TargetType::self),
        Effect(EffectType::hologram, 1, TargetType::self)
    }, true};

Card DEF_Seek = {CID::Seek, Color::blue, "Seek", CardType::skill, 0, CardRarity::rare, "Put 2 cards from your draw pile into your hand.", 
    {
        Effect(EffectType::seek, 2, TargetType::self)
    }, true};

////////////////////WATCHER CARD REWARDS//////////////////

Card WAT_Scrawl = {CID::Scrawl, Color::purple, "Scrawl", CardType::skill, 1, CardRarity::rare, "Draw cards until your hand is full.",
    {
        Effect(EffectType::expertise, MAX_HAND_SIZE, TargetType::self)
    }, true};

////////////////////COLORLESS CARD REWARDS//////////////////  

Card CLS_Finesse = {CID::Finesse, Color::colorless, "Finesse", CardType::skill, 0, CardRarity::common, "Gain 4 block. Draw 1 card.",
    {
        Effect(EffectType::block, 4, TargetType::self),
        Effect(EffectType::draw, 1, TargetType::self)
    }, false};

Card CLS_Bite={CID::Bite, Color::colorless, "Bite", CardType::attack, 1, CardRarity::common, "Deal 7 damage. Heal 3 HP. ",
    {
        Effect(EffectType::damage,7,TargetType::enemy),
        Effect(EffectType::hp, 3, TargetType::self)
    }, false};
    
////////////////////CURSES//////////////////  
Card CUR_Injury={CID::Injury, Color::curse, "Injury", CardType::curse, -1, CardRarity::curse, "Unplayable.",{}, false};

////////////////////STATUS//////////////////  
Card STS_Wound={CID::Wound, Color::status, "Wound", CardType::status, -1, CardRarity::status, "Unplayable.",{}, false};


////////////////////STARTER DECKS//////////////////
Pile empty_deck = {};

Pile ICL_STARTER_DECK = createIroncladStarterDeck();
Pile SLT_STARTER_DECK = createSilentStarterDeck();



Pile createIroncladStarterDeck(){
    Pile deck;
    //for(int i =0; i<1;i++){deck.addCardTop(ICL_Strike);}
    //for(int i =0; i<1;i++){deck.addCardTop(ICL_Defend);}
    deck.addCardTop(ICL_Twin_Strike);
    deck.addCardTop(ICL_Bash);
    deck.addCardTop(SLT_Neutralize);

    return deck;
}


Pile createSilentStarterDeck(){
    Pile deck;
    for(int i = 0; i<5; i++){deck.addCardTop(SLT_Strike);}
    for(int i = 0;i<5;i++){deck.addCardTop(SLT_Defend);}
    deck.addCardTop(SLT_Neutralize);
    deck.addCardTop(SLT_Survivor);
    return deck;
}
