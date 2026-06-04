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

Effect NO_EFFECT(EID::none, 0, TID::self);


Card blank_card = {CID::blank_card,Color::colorless,"None",CardType::status,0,CardRarity::status,"None",{}, false};

//THE IRONCLAD
Card ICL_Strike = {CID::ICL_Strike,Color::red, "Strike", CardType::attack, 1, CardRarity::starter,"Deal 6 damage.", {Effect(EID::damage, 6,TID::enemy)}, false};
Card ICL_Defend = {CID::ICL_Defend, Color::red, "Defend", CardType::skill, 1, CardRarity::starter, "Gain 5 block.", {Effect(EID::block,5,TID::self)}, false};
Card Bash = {CID::Bash, Color::red, "Bash", CardType::attack, 2,  CardRarity::starter, "Deal 8 damage. Apply 2 vulnerable.", 
    {
        Effect(EID::damage, 8, TID::enemy),
        Effect(EID::gain, 2, TID::enemy, PID::vulnerable),
    }, false};

//COMMON
Card Anger = blank_card; 
Card Armaments = blank_card; 
Card Body_Slam = blank_card; 
Card Clash = {CID::Clash, Color::red, "Clash", CardType::attack, 0, CardRarity::common, "Deal 14 damage. Play: every card in your hand is an attack.",
{
    Effect(EID::damage, 14, TID::enemy),
}, false};
Card Cleave = {CID::Cleave, Color::red, "Cleave", CardType::attack, 1, CardRarity::common, "Deal 8 damage to ALL enemies.",{
    Effect(EID::damage, 8, TID::enemy_all)
}, false};
Card Clothesline = {CID::Clothesline, Color::red, "Clothesline", CardType::attack, 2, CardRarity::common, "Deal 12 damage. Apply 2 weak",{
    Effect(EID::damage, 12, TID::enemy),
    Effect(EID::gain, 2, TID::enemy, PID::weak)
}, false};
Card Flex = blank_card; 
Card Havoc = blank_card; 
Card Headbutt={CID::Headbutt, Color::red, "Headbutt",CardType::attack, 1, CardRarity::common, "Deal 9 damage. Put 1 card from your discard pile on top of your draw pile.",
    {
        Effect(EID::damage, 9, TID::enemy),
        Effect(EID::cards_top, 1, PileID::discard, PileID::draw)
    }, false}; 
Card Heavy_Blade = blank_card; 
Card Iron_Wave={CID::Iron_Wave, Color::red, "Iron Wave", CardType::attack, 1, CardRarity::common, "Gain 5 block. Deal 5 damage",{
    Effect(EID::block, 5, TID::self),
    Effect(EID::damage, 5, TID::enemy)
}, false};
Card Perfected_Strike = blank_card; 
Card Pommel_Strike={CID::Pommel_Strike, Color::red, "Pommel Strike", CardType::attack, 1, CardRarity::common, "Deal 9 damage. Draw 1 card.",{
    Effect(EID::damage, 9, TID::enemy),
    Effect(EID::draw, 1, TID::self)
}, false}; 
Card Shrug_It_Off={CID::Shrug_It_Off, Color::red, "Shrug It Off", CardType::skill, 1, CardRarity::common, "Gain 8 block. Draw 1 card.",{
    Effect(EID::block, 8, TID::self),
    Effect(EID::draw, 1, TID::self)
}, false}; 
Card Sword_Boomerang = {CID::Sword_Boomerang, Color::red,"Sword Boomerang",CardType::attack, 1, CardRarity::common, "Deal 3 damage to a random enemy 3 times.",{
    Effect(EID::damage, 3, TID::random_enemy),
    Effect(EID::damage, 3, TID::random_enemy),
    Effect(EID::damage, 3, TID::random_enemy)
}, false};
Card Thunderclap={CID::Thunderclap, Color::red, "Thunderclap", CardType::attack, 1, CardRarity::common, "Deal 4 damage to ALL enemies. Apply 1 vulnerable to ALL enemies.",{
    Effect(EID::damage, 4, TID::enemy_all),
    Effect(EID::gain, 1, TID::enemy_all, PID::vulnerable)
}, false}; 
Card True_Grit = {CID::True_Grit, Color::red, "True Grit", CardType::skill, 1, CardRarity::common, "Gain 7 block. Exhaust 1 random card from your hand.",
    {
        Effect(EID::block, 7, TID::self),
        Effect(EID::exhaust, 1, TID::self)
    }, false};
Card Twin_Strike = {CID::Twin_Strike, Color::red,"Twin Strike", CardType::attack,1,CardRarity::common,"Deal 7 damage 2 times.",{
    Effect(EID::damage, 7, TID::enemy),
    Effect(EID::damage, 7, TID::enemy)
}, false};
Card Warcry={CID::Warcry, Color::red, "Warcry", CardType::skill, 0, CardRarity::common, "Draw 1 card. Put 1 card from your hand on top of your draw pile.",{
    Effect(EID::draw, 1, TID::self),
    Effect(EID::cards_top, 1, PileID::hand, PileID::draw)
}, false}; 
Card Wild_Strike = blank_card; 

//UNCOMMON
Card Battle_Trance = blank_card; 
Card Blood_For_Blood={CID::Blood_For_Blood, Color::red, "Blood For Blood", CardType::attack, 4, CardRarity::uncommon, "Deal 18 damage. Costs 1 less energy for each time you lost HP this combat.",{
    Effect(EID::damage, 18, TID::enemy),
}, false}; 
Card Bloodletting={CID::Bloodletting, Color::red,"Bloodletting",CardType::skill,0,CardRarity::uncommon,"Lose 3 HP. Gain 2 energy",{
    Effect(EID::hp,-3, TID::self),
    Effect(EID::energy,2, TID::self)
}, false};
Card Burning_Pact={CID::Burning_Pact, Color::red, "Burning Pact", CardType::skill, 1, CardRarity::uncommon, "Exhaust 1 card from your hand. Draw 2 cards.",{
    Effect(EID::exhaust, 1, TID::self),
    Effect(EID::draw, 2, TID::self)
}, false}; 
Card Carnage = blank_card; 
Card Combust = blank_card; 
Card Dark_Embrace = blank_card; 
Card Disarm = {CID::Disarm, Color::red, "Disarm", CardType::skill, 1, CardRarity::uncommon, "Enemy loses 2 strength.",{
    Effect(EID::gain, -2, TID::enemy, PID::strength)
}, true}; 
Card Dropkick = blank_card; 
Card Dual_Wield = blank_card; 
Card Entrench = blank_card; 
Card Evolve = blank_card; 
Card Feel_No_Pain = blank_card; 
Card Fire_Breathing = blank_card; 
Card Flame_Barrier = blank_card; 
Card Ghostly_Armor = blank_card; 
Card Hemokinesis = {CID::Hemokinesis, Color::red, "Hemokinesis", CardType::attack, 1, CardRarity::uncommon, "Lose 2 HP. Deal 14 damage.",{
    Effect(EID::hp, -2, TID::self),
    Effect(EID::damage, 14, TID::enemy)
}, false}; 
Card Infernal_Blade = blank_card; 
Card Inflame = {CID::Inflame, Color::red, "Inflame", CardType::power, 1, CardRarity::uncommon, "Gain 2 strength.",{
    Effect(EID::gain, 2, TID::self, PID::strength)
}, false}; 
Card Intimidate = {CID::Intimidate, Color::red, "Intimidate", CardType::skill, 0, CardRarity::uncommon, "Apply 1 weak to ALL enemies.",{
    Effect(EID::gain, 1, TID::enemy_all, PID::weak)
}, true}; 
Card Metallicize = blank_card; 
Card Power_Through = blank_card; 
Card Pummel = {CID::Pummel, Color::red, "Pummel", CardType::attack, 1, CardRarity::uncommon, "Deal 2 damage 4 times.",{
    Effect(EID::damage, 2, TID::enemy),
    Effect(EID::damage, 2, TID::enemy),
    Effect(EID::damage, 2, TID::enemy),
    Effect(EID::damage, 2, TID::enemy),
}, false};
Card Rage = blank_card; 
Card Rampage = blank_card; 
Card Reckless_Charge = blank_card; 
Card Rupture = blank_card; 
Card Searing_Blow = {CID::Searing_Blow, Color::red, "Searing Blow", CardType::attack, 2, CardRarity::uncommon, "Deal 12 damage. Can be upgraded any number of times.",{
    Effect(EID::damage, 12, TID::enemy)
}, false}; 
Card Second_Wind = blank_card; 
Card Seeing_Red = {CID::Seeing_Red, Color::red, "Seeing Red", CardType::skill, 1, CardRarity::uncommon, "Gain 2 energy.",{
    Effect(EID::energy, 2, TID::self)
}, false}; 
Card Sentinel = blank_card; 
Card Sever_Soul = blank_card; 
Card Shockwave = {CID::Shockwave, Color::red, "Shockwave", CardType::attack, 2, CardRarity::uncommon, "Apply 3 vulnerable and 3 weak to ALL enemies.",{
    Effect(EID::gain, 3, TID::enemy_all, PID::vulnerable),
    Effect(EID::gain, 3, TID::enemy_all, PID::weak)
}, false}; 
Card Spot_Weakness = blank_card; 
Card Uppercut = {CID::Uppercut, Color::red, "Uppercut", CardType::attack, 2, CardRarity::uncommon, "Deal 13 damage. Apply 1 weak. Apply 1 vulnerable.",{
    Effect(EID::damage, 13, TID::enemy),
    Effect(EID::gain, 1, TID::enemy, PID::weak),
    Effect(EID::gain, 1, TID::enemy, PID::vulnerable)
}, false}; 
Card Whirlwind = blank_card; 

//RARE
Card Barricade = {CID::Barricade, Color::red, "Barricade", CardType::power, 1, CardRarity::rare, "Block is not removed at the start of your turn.",{
    Effect(EID::gain, 0, TID::self, PID::barricade)
}, false}; 
Card Berserk = blank_card; 
Card Bludgeon = blank_card; 
Card Brutality = blank_card; 
Card Corruption = blank_card; 
Card Demon_Form = {CID::Demon_Form, Color::red, "Demon Form", CardType::power, 3, CardRarity::rare, "At the start of your turn, gain 2 strength.",{
    Effect(EID::gain, 2, TID::self, PID::demon)
}, false}; 
Card Double_Tap = blank_card; 
Card Exhume = {CID::Exhume, Color::red, "Exhume", CardType::skill, 1, CardRarity::rare, "Put 1 card from your exhaust pile into your hand.",
    {
        Effect(EID::cards_bottom,1,PileID::exhaust, PileID::hand)
    }, true};
Card Feed = blank_card; 
Card Fiend_Fire = blank_card; 
Card Immolate = blank_card; 
Card Impervious = {CID::Impervious, Color::red, "Impervious", CardType::skill, 2, CardRarity::rare, "Gain 30 block.",{
    Effect(EID::block, 30, TID::self)
}, true}; 
Card Juggernaut = blank_card; 
Card Limit_Break = blank_card; 
Card Offering = {CID::Offering, Color::red, "Offering", CardType::skill, 0, CardRarity::rare, "Lose 6 HP. Gain 2 energy. Draw 3 cards.",{
    Effect(EID::hp, -6, TID::self),
    Effect(EID::energy, 2, TID::self),
    Effect(EID::draw, 3, TID::self),
}, false}; 
Card Reaper = blank_card; 

//THE SILENT
Card SLT_Strike = {CID::SLT_Strike, Color::green, "Strike", CardType::attack, 1, CardRarity::starter,"Deal 6 damage.", {Effect(EID::damage, 6,TID::enemy)},  false};
Card SLT_Defend = {CID::SLT_Defend, Color::green, "Defend", CardType::skill, 1, CardRarity::starter,"Gain 5 block.", {Effect(EID::block, 5, TID::self)}, false};
Card Neutralize = {CID::Neutralize, Color::green, "Neutralize", CardType::attack, 0, CardRarity::starter,"Deal 3 damage, apply 1 weak.", 
    {
        Effect(EID::damage, 3, TID::enemy),
        Effect(EID::gain, 1, TID::enemy, PID::weak),
    }, false};
Card Survivor = {CID::Survivor ,Color::green, "Survivor", CardType::skill, 1, CardRarity::starter,"Discard 1 hand. Gain 8 block.", 
    {
        Effect(EID::discard,1,TID::self),
        Effect(EID::block, 8, TID::self)
    }, false};

//COMMON
Card Acrobatics ={CID::Acrobatics, Color::green, "Acrobatics", CardType::skill, 1, CardRarity::uncommon, "Draw 3 cards. Discard 1 card.",
    {
        Effect(EID::draw,3,TID::self),
        Effect(EID::discard, 1, TID::self)
    }, false};
Card Backflip = {CID::Backflip, Color::green, "Backflip", CardType::skill, 1, CardRarity::common, "Gain 5 block. Draw 2 cards.",{
    Effect(EID::block, 5, TID::self),
    Effect(EID::draw, 2, TID::self)
}, false}; 
Card Bane = blank_card; 
Card Blade_Dance = {CID::Blade_Dance, Color::green, "Blade Dance", CardType::skill, 1, CardRarity::common, "Add 3 Shivs to your hand.",{
    Effect(EID::addCard, 3, CID::Shiv, PileID::hand)
}, false}; 
Card Cloak_and_Dagger = blank_card; 
Card Dagger_Spray = {CID::Dagger_Spray, Color::green, "Dagger Spray", CardType::attack, 1, CardRarity::common, "Deal 4 damage to ALL enemies twice.",{
    Effect(EID::damage, 4, TID::enemy_all),
    Effect(EID::damage, 4, TID::enemy_all),
}, false}; 
Card Dagger_Throw = {CID::Dagger_Throw, Color::green, "Dagger Throw", CardType::attack, 1, CardRarity::common, "Deal 9 damage. Draw 1 card. Discard 1 card.",
    {
        Effect(EID::damage, 9, TID::enemy),
        Effect(EID::draw, 1, TID::self),
        Effect(EID::discard, 1, TID::self),
    }, false}; 
Card Deadly_Poison = {CID::Deadly_Poison, Color::green, "Deadly Poison", CardType::skill, 1, CardRarity::common, "Apply 5 poison",
    {
        Effect(EID::gain, 5, TID::enemy, PID::poison)
    },false}; 
Card Dodge_and_Roll = blank_card; 
Card Flying_Knee = {CID::Flying_Knee, Color::green, "Flying Knee", CardType::attack, 1, CardRarity::common, "Deal 9 damage. Next turn, gain 1 energy.",{
    Effect(EID::damage, 9, TID::enemy),
    Effect(EID::gain, 1, TID::self, PID::energized)
}, false}; 
Card Outmaneuver = {CID::Outmaneuver, Color::green, "Outmaneuver", CardType::skill, 1, CardRarity::common, "Next turn, gain 2 energy.",{
    Effect(EID::gain, 2, TID::self, PID::energized)
}, false}; 
Card Piercing_Wail = blank_card; 
Card Poisoned_Stab = {CID::Poisoned_Stab, Color::green, "Poisoned Stab", CardType::attack, 1, CardRarity::common, "Deal 6 damage. Apply 3 poison.",{
    Effect(EID::damage, 6, TID::enemy),
    Effect(EID::gain, 3, TID::enemy, PID::poison)
}, false}; 
Card Prepared = {CID::Prepared, Color::green, "Prepared", CardType::skill, 0, CardRarity::common, "Draw 1 card. Discard 1 card.",
    {
        Effect(EID::draw, 1, TID::self),
        Effect(EID::discard, 1, TID::self)
    }, false};
Card Quick_Slash = {CID::Quick_Slash, Color::green, "Quick Slash", CardType::attack, 1, CardRarity::common, "Deal 5 damage. Draw 1 card.",{
    Effect(EID::damage, 5, TID::enemy),
    Effect(EID::draw, 1, TID::self)
}, false}; 
Card Slice = {CID::Slice, Color::green, "Slice", CardType::attack, 0, CardRarity::common, "Deal 6 damage.",{
    Effect(EID::damage, 6, TID::enemy)
}, false}; 
Card Sneaky_Strike = blank_card; 
Card Sucker_Punch = {CID::Sucker_Punch, Color::green, "Sucker Punch", CardType::attack, 1, CardRarity::common, "Deal 8 damage. Apply 1 weak.",{
    Effect(EID::damage, 8, TID::enemy),
    Effect(EID::gain, 1, TID::enemy, PID::weak)
}, false}; 

//UNCOMMON
Card Accuracy = {CID::Accuracy, Color::green, "Accuracy", CardType::skill, 1, CardRarity::uncommon, "Shivs deal 4 additional damage.",{
    Effect(EID::gain, 4, TID::self, PID::accuracy)
}, false}; 
Card All_Out_Attack = blank_card; 
Card Backstab = blank_card; 
Card Blur = blank_card; 
Card Bouncing_Flask = {CID::Bouncing_Flask, Color::green, "Bouncing Flask", CardType::skill, 1, CardRarity::uncommon, "Apply 3 poison to a random enemy 3 times.",{
    Effect(EID::gain, 3, TID::random_enemy, PID::poison),
    Effect(EID::gain, 3, TID::random_enemy, PID::poison),
    Effect(EID::gain, 3, TID::random_enemy, PID::poison)
}, false}; 
Card Calculated_Gamble = blank_card; 
Card Caltrops = blank_card; 
Card Catalyst = blank_card; 
Card Choke = blank_card; 
Card Concentrate = {CID::Concentrate, Color::green, "Concentrate", CardType::skill, 1, CardRarity::uncommon, "Discard 3 cards. Gain 2 energy.",
    {
        Effect(EID::discard, 3, TID::self),
        Effect(EID::energy, 2, TID::self)
    }, false}; 
Card Crippling_Cloud = {CID::Crippling_Cloud, Color::green, "Crippling Cloud", CardType::skill, 2, CardRarity::uncommon, "Apply 4 poison and 2 weak to ALL enemies",
    {
        Effect(EID::gain, 4, TID::enemy_all, PID::poison),
        Effect(EID::gain, 2, TID::enemy_all, PID::weak)
    }, true};
Card Dash ={CID::Dash, Color::green, "Dash", CardType::attack, 2, CardRarity::uncommon, "Gain 10 block. Deal 10 damage.",
    {
    Effect(EID::block, 10, TID::self),
    Effect(EID::damage, 10, TID::enemy)
    }, false}; 
Card Distraction = blank_card; 
Card Endless_Agony = blank_card; 
Card Escape_Plan = blank_card; 
Card Eviscerate = blank_card; 
Card Expertise = {CID::Expertise, Color::green, "Expertise", CardType::skill, 1, CardRarity::uncommon, "Draw cards until you have 6 cards in your hand.",
    {
        Effect(EID::expertise, 6, TID::self)
    }, false}; 
Card Finisher = blank_card; 
Card Flechettes = blank_card; 
Card Footwork = {CID::Footwork, Color::green, "Footwork", CardType::power, 1, CardRarity::uncommon, "Gain 2 dexterity.",{
    Effect(EID::gain, 2, TID::self, PID::dexterity)
}, false}; 
Card Heel_Hook = blank_card; 
Card Infinite_Blades = blank_card; 
Card Leg_Sweep = blank_card; 
Card Masterful_Stab = blank_card; 
Card Noxious_Fumes = blank_card; 
Card Predator = blank_card; 
Card Reflex = blank_card; 
Card Riddle_with_Holes = blank_card; 
Card Setup = blank_card; 
Card Skewer = blank_card; 
Card Tactician = blank_card; 
Card Terror = blank_card; 
Card Well_Laid_Plans = blank_card; 

//RARE
Card A_Thousand_Cuts = blank_card; 
Card Adrenaline = {CID::Adrenaline, Color::green, "Adrenaline", CardType::skill, 0, CardRarity::rare, "Gain 1 energy. Draw 2 cards",
    {
        Effect(EID::energy, 1, TID::self),
        Effect(EID::draw, 2, TID::self)
    }, true}; 
Card After_Image = blank_card; 
Card Alchemize = blank_card; 
Card Bullet_Time = blank_card; 
Card Burst = blank_card; 
Card Corpse_Explosion = blank_card; 
Card Die_Die_Die = {CID::Die_Die_Die, Color::green, "Die Die Die", CardType::attack, 1, CardRarity::rare, "Deal 13 damage to ALL enemies.",
    {
        Effect(EID::damage, 13, TID::enemy_all)
    }, true }; 
Card Doppelganger = blank_card; 
Card Envenom = blank_card; 
Card Glass_Knife = blank_card; 
Card Grand_Finale ={CID::Grand_Finale, Color::green, "Grand Finale", CardType::attack, 0, CardRarity::rare, "Deal 50 damage to all enemies. Play: your draw pile is empty.",
    {
        Effect(EID::damage,50,TID::enemy_all)
    }, false};
Card Malaise = blank_card; 
Card Nightmare = blank_card; 
Card Phantasmal_Killer = blank_card; 
Card Storm_of_Steel = blank_card; 
Card Tools_of_the_Trade = blank_card; 
Card Unload = blank_card; 
Card Wraith_Form = blank_card; 

//DEFECT
Card DEF_Strike = {CID::DEF_Strike, Color::blue, "Strike", CardType::attack, 1, CardRarity::starter,"Deal 6 damage.", {Effect(EID::damage, 6,TID::enemy)}, false}; 
Card DEF_Defend = {CID::DEF_Defend, Color::blue, "Defend", CardType::skill, 1, CardRarity::starter,"Gain 5 block.", {Effect(EID::block, 5,TID::self)}, false}; 
Card Zap = blank_card; 
Card Dualcast = blank_card;

//COMMON
Card Ball_Lightning = blank_card; 
Card Barrage = blank_card; 
Card Beam_Cell = {CID::Beam_Cell, Color::blue, "Beam Cell", CardType::attack, 0, CardRarity::common, "Deal 3 damage. Apply 1 vulnerable.",
    {
        Effect(EID::damage, 3, TID::self),
        Effect(EID::gain, 1, TID::enemy, PID::vulnerable)
    }, false}; 
Card Charge_Battery = {CID::Charge_Battery, Color::blue, "Charge Battery", CardType::skill, 1, CardRarity::common, "Gain 8 block. Next turn, gain 1 energy.",{
    Effect(EID::block, 8, TID::self),
    Effect(EID::gain, 1, TID::self, PID::energized)
}, false}; 
Card Claw = blank_card; 
Card Cold_Snap = blank_card; 
Card Compile_Driver = blank_card; 
Card Coolheaded = blank_card; 
Card Go_for_the_Eyes = blank_card; 
Card Hologram = {CID::Hologram, Color:: blue, "Hologram", CardType::skill, 1, CardRarity::common, "Gain 3 block. Put 1 card from your discard pile into your hand.",
    {
        Effect(EID::block, 3, TID::self),
        Effect(EID::cards_bottom, 1, PileID::discard, PileID::hand)
    }, true}; 
Card Leap = {CID::Leap, Color::blue, "Leap", CardType::skill, 1, CardRarity::common, "Gain 9 block.",
    {
        Effect(EID::block, 9, TID::self)
    }, false}; 
Card Rebound = blank_card; 
Card Recursion = blank_card; 
Card Stack = blank_card; 
Card Steam_Barrier = blank_card; 
Card Streamline = blank_card; 
Card Sweeping_Beam = {CID::Sweeping_Beam, Color::blue, "Sweeping Beam",CardType::attack, 1, CardRarity::common, "Deal 5 damage to ALL enemies. Draw 1 card.",
    {
        Effect(EID::damage, 5, TID::enemy_all),
        Effect(EID::draw, 1, TID::self)
    }, false}; 
Card Turbo = blank_card; 

//UNCOMMON
Card Aggregate = blank_card; 
Card Auto_Shields = blank_card; 
Card Blizzard = blank_card; 
Card Boot_Sequence = blank_card; 
Card Bullseye = blank_card; 
Card Capacitor = blank_card; 
Card Chaos = blank_card; 
Card Chill = blank_card; 
Card Consume = blank_card; 
Card Darkness = blank_card; 
Card Defragment = blank_card; 
Card Doom_and_Gloom = blank_card; 
Card Double_Energy = blank_card; 
Card Equilibrium = blank_card; 
Card FTL = blank_card; 
Card Force_Field = blank_card; 
Card Fusion = blank_card; 
Card Genetic_Algorithm = blank_card; 
Card Glacier = blank_card; 
Card Heatsinks = blank_card; 
Card Hello_World = blank_card; 
Card Loop = blank_card; 
Card Melter = blank_card; 
Card Overclock = blank_card; 
Card Recycle = blank_card; 
Card Reinforced_Body = blank_card; 
Card Reprogram = {CID::Reprogram, Color::blue, "Reprogram", CardType::skill, 1, CardRarity::uncommon, "Lose 1 focus. Gain 1 strength. Gain 1 dexterity.",{
    Effect(EID::gain, -1, TID::self, PID::focus),
    Effect(EID::gain, 1, TID::self, PID::strength),
    Effect(EID::gain, 1, TID::self, PID::dexterity),
},false}; 
Card Rip_and_Tear = {CID::Rip_and_Tear, Color::blue, "Rip and Tear", CardType::attack, 1, CardRarity::uncommon, "Deal 7 damage to a random enemy twice.",{
    Effect(EID::damage, 7, TID::enemy),
    Effect(EID::damage, 7, TID::enemy)
}, false}; 
Card Scrape = blank_card; 
Card Self_Repair = blank_card; 
Card Skim = {CID::Skim, Color::blue, "Skim", CardType::skill, 1, CardRarity::uncommon, "Draw 3 cards.",
    {
        Effect(EID::draw, 3, TID::self)
    }, false};
Card Static_Discharge = blank_card; 
Card Storm = blank_card; 
Card Sunder = blank_card; 
Card Tempest = blank_card; 
Card White_Noise = blank_card; 

//RARE
Card All_for_One = blank_card; 
Card Amplify = blank_card; 
Card Biased_Cognition = blank_card; 
Card Buffer = {CID::Buffer, Color::blue, "Buffer", CardType::power, 1, CardRarity::rare, "Negate the next time you would lose HP.",{
    Effect(EID::gain, 1, TID::self, PID::buffer)
}, false}; 
Card Core_Surge = blank_card; 
Card Creative_AI = blank_card; 
Card Echo_Form = blank_card; 
Card Electrodynamics = blank_card; 
Card Fission = blank_card; 
Card Hyperbeam = {CID::Hyperbeam, Color::blue, "Hyperbeam", CardType::attack, 3, CardRarity::rare, "Deal 26 damage to all enemies. Lose 3 focus.",{
    Effect(EID::damage, 26, TID::enemy_all),
    Effect(EID::gain, -3, TID::self, PID::focus)
}, false}; 
Card Machine_Learning = blank_card; 
Card Meteor_Strike = blank_card; 
Card Multi_Cast = blank_card; 
Card Rainbow = blank_card; 
Card Reboot = blank_card; 
Card Seek = {CID::Seek, Color::blue, "Seek", CardType::skill, 0, CardRarity::rare, "Put 1 card from your draw pile into your hand.", 
    {
        Effect(EID::cards_bottom, 1, PileID::draw, PileID::hand)
    }, true}; 
Card Thunder_Strike = blank_card; 

//WATCHER
Card WAT_Strike = {CID::WAT_Strike,Color::purple, "Strike", CardType::attack, 1, CardRarity::starter,"Deal 6 damage.", {Effect(EID::damage, 6,TID::enemy)}, false};
Card WAT_Defend = {CID::WAT_Defend,Color::purple, "Defend", CardType::attack, 1, CardRarity::starter,"Gain 5 block." , {Effect(EID::block, 5,TID::self)}, false};
Card Vigilance = blank_card; 
Card Eruption = blank_card; 

//COMMON
Card Bowling_Bash = blank_card;  
Card Consecrate = {CID::Consecrate, Color::purple, "Consecrate", CardType::attack, 0, CardRarity::common, "Deal 5 damage to ALL enemies.", {
    Effect(EID::damage, 5, TID::enemy_all)
}, false}; 
Card Crescendo = blank_card; 
Card Crush_Joints = blank_card; 
Card Cut_Through_Fate = blank_card; 
Card Empty_Body = blank_card; 
Card Empty_Fist = blank_card; 
Card Evaluate = blank_card; 
Card Flurry_Of_Blows = blank_card; 
Card Flying_Sleeves = blank_card; 
Card Follow_Up = blank_card; 
Card Halt = blank_card; 
Card Just_Lucky = blank_card; 
Card Pressure_Points = blank_card; 
Card Prostrate = blank_card; 
Card Protect = blank_card; 
Card Sash_Whip = blank_card; 
Card Third_Eye = blank_card; 
Card Tranquility = blank_card; 

//UNCOMMON
Card Battle_Hymn = blank_card; 
Card Carve_Reality = blank_card; 
Card Collect = blank_card; 
Card Conclude = blank_card; 
Card Deceive_Reality = blank_card; 
Card Empty_Mind = blank_card; 
Card Fasting = blank_card; 
Card Fear_No_Evil = blank_card; 
Card Foreign_Influence = blank_card; 
Card Foresight = blank_card; 
Card Indignation = blank_card; 
Card Inner_Peace = blank_card; 
Card Like_Water = blank_card; 
Card Meditate = blank_card; 
Card Mental_Fortress = blank_card; 
Card Nirvana = blank_card; 
Card Perseverance = blank_card; 
Card Pray = blank_card; 
Card Reach_Heaven = blank_card; 
Card Rushdown = blank_card; 
Card Sanctity = blank_card; 
Card Sands_of_Time = blank_card; 
Card Signature_Move = blank_card; 
Card Simmering_Fury = blank_card; 
Card Study = blank_card; 
Card Swivel = blank_card; 
Card Talk_to_the_Hand = blank_card; 
Card Tantrum = blank_card; 
Card Wallop = blank_card; 
Card Wave_of_the_Hand = blank_card; 
Card Weave = blank_card; 
Card Wheel_Kick = blank_card; 
Card Windmill_Strike = blank_card; 
Card Worship = blank_card; 
Card Wreath_of_Flame = blank_card; 

//RARE
Card Alpha = blank_card; 
Card Blasphemy = blank_card; 
Card Brilliance = blank_card; 
Card Conjure_Blade = blank_card; 
Card Deus_Ex_Machina = blank_card; 
Card Deva_Form = blank_card; 
Card Devotion = blank_card; 
Card Establishment = blank_card; 
Card Judgment = blank_card; 
Card Lesson_Learned = blank_card; 
Card Master_Reality = blank_card; 
Card Omniscience = blank_card; 
Card Ragnarok = {CID::Ragnarok, Color::purple, "Ragnarok", CardType::attack, 3, CardRarity::rare, "Deal 5 damage to a random enemy 5 times.",
    {
        Effect(EID::damage, 5, TID::random_enemy),
        Effect(EID::damage, 5, TID::random_enemy),
        Effect(EID::damage, 5, TID::random_enemy),
        Effect(EID::damage, 5, TID::random_enemy),
        Effect(EID::damage, 5, TID::random_enemy),
    }, false}; 
Card Scrawl = {CID::Scrawl, Color::purple, "Scrawl", CardType::skill, 1, CardRarity::rare, "Draw cards until your hand is full.",
    {
        Effect(EID::expertise, MAX_HAND_SIZE, TID::self)
    }, true}; 
Card Spirit_Shield = blank_card; 
Card Vault = blank_card; 
Card Wish = blank_card; 

//COLORLESS

//UNCOMMON
Card Bandage_Up = {CID::Bandage_Up, Color::colorless, "Bandage Up", CardType::skill, 0, CardRarity::uncommon, "Heal 4 hp.",
    {
        Effect(EID::hp, 4, TID::self),
    }, true};
Card Blind = {CID::Blind, Color::colorless, "Blind", CardType::skill, 0, CardRarity::uncommon, "Apply 2 weak",
    {
        Effect(EID::gain, 2, TID::enemy, PID::weak)
    }, false}; 
Card Dark_Shackles = blank_card;  
Card Deep_Breath = blank_card; 
Card Discovery = blank_card; 
Card Dramatic_Entrance = blank_card; 
Card Enlightenment = blank_card; 
Card Finesse = {CID::Finesse, Color::colorless, "Finesse", CardType::skill, 0, CardRarity::uncommon, "Gain 4 block. Draw 1 card.",
    {
        Effect(EID::block, 4, TID::self),
        Effect(EID::draw, 1, TID::self)
    }, false};
Card Flash_of_Steel = {CID::Flash_of_Steel, Color::colorless, "Flash of Steel", CardType::attack, 0, CardRarity::uncommon, "Deal 3 damage. Draw 1 card.",
    {
        Effect(EID::damage, 3, TID::self),
        Effect(EID::draw, 1, TID::self)
    }, false};
Card Forethought = blank_card; 
Card Good_Instincts = blank_card; 
Card Impatience = blank_card; 
Card Jack_of_All_Trades = blank_card; 
Card Madness = blank_card; 
Card Mind_Blast = blank_card; 
Card Panacea = blank_card; 
Card Panic_Button = blank_card; 
Card Purity = blank_card; 
Card Swift_Strike = blank_card; 
Card Trip = blank_card; 

//RARE
Card Apotheosis = blank_card; 
Card Chrysalis = blank_card; 
Card Hand_of_Greed = blank_card; 
Card Magnetism = blank_card; 
Card Master_of_Strategy = blank_card; 
Card Mayhem = blank_card; 
Card Metamorphosis = blank_card; 
Card Panache = blank_card; 
Card Sadistic_Nature = blank_card; 
Card Secret_Technique = blank_card; 
Card Secret_Weapon = blank_card; 
Card The_Bomb = blank_card; 
Card Thinking_Ahead = blank_card; 
Card Transmutation = blank_card; 
Card Violence = blank_card; 

//SPECIAL
Card Apparition = blank_card;
Card Beta = blank_card;
Card Bite={CID::Bite, Color::colorless, "Bite", CardType::attack, 1, CardRarity::common, "Deal 7 damage. Heal 3 HP. ",
    {
        Effect(EID::damage,7,TID::enemy),
        Effect(EID::hp, 3, TID::self)
    }, false}; 
Card Expunger = blank_card; 
Card Insight = blank_card; 
Card JAX = {CID::JAX, Color::colorless, "J.A.X.", CardType::skill, 0, CardRarity::common, "Lose 3 HP. Gain 2 strength.",
    {
        Effect(EID::hp, -3, TID::self),
        Effect(EID::gain, 2, TID::self, PID::strength)
    }, false}; 
Card Omega = blank_card; 
Card Ritual_Dagger = blank_card; 
Card Safety = blank_card; 
Card Shiv = {CID::Shiv, Color::colorless, "Shiv", CardType::attack, 0, CardRarity::common, "Deal 4 damage.",{
    Effect(EID::damage,4,TID::enemy)
}, true};
Card Smite = blank_card; 
Card Through_Violence = blank_card; 

//STATUS
Card Burn = blank_card; 
Card Dazed = blank_card; 
Card Slimed = blank_card; 
Card Void = blank_card; 
Card Wound={CID::Wound, Color::status, "Wound", CardType::status, -1, CardRarity::status, "Unplayable.",{}, false};

//CURSE
Card Ascenders_Bane = blank_card; 
Card Clumsy = blank_card; 
Card Curse_of_the_Bell = blank_card; 
Card Decay = blank_card; 
Card Doubt = blank_card; 
Card Injury={CID::Injury, Color::curse, "Injury", CardType::curse, -1, CardRarity::curse, "Unplayable.",{}, false};
Card Necronomicurse = blank_card; 
Card Normality = blank_card; 
Card Pain = blank_card; 
Card Parasite = blank_card; 
Card Pride = blank_card; 
Card Regret = blank_card; 
Card Shame = blank_card; 
Card Writhe = blank_card; 

Pile empty_deck = {};

Pile ICL_STARTER_DECK = createIroncladStarterDeck();
Pile SLT_STARTER_DECK = createSilentStarterDeck();

Pile createIroncladStarterDeck(){
    Pile deck;
    // for(int i =0; i<5;i++){deck.addCardTop(ICL_Strike);}
    // for(int i =0; i<5;i++){deck.addCardTop(ICL_Defend);}
    deck.addCardTop(Thunderclap);
    deck.addCardTop(Cleave);
    deck.addCardTop(Consecrate);

    return deck;
}

Pile createSilentStarterDeck(){
    Pile deck;
    for(int i = 0; i<5; i++){deck.addCardTop(SLT_Strike);}
    for(int i = 0;i<5;i++){deck.addCardTop(SLT_Defend);}
    deck.addCardTop(Neutralize);
    deck.addCardTop(Survivor);
    return deck;
}
