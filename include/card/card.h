#ifndef CARD_H
#define CARD_H

#include<iostream>
#include<vector>
#include"game_logic/effect.h"
#include "ui/colors.h"


class Player;


//Certain cards can only have certain targets. which are the following:
enum class CID{
    blank_card, 
    // IRONCLAD //
    ICL_Strike, ICL_Defend, Bash, 
    //Common//
    Anger, Armaments, Body_Slam, Clash, Cleave, Clothesline, Flex, Havoc, Headbutt, Heavy_Blade, Iron_Wave, 
    Perfected_Strike, Pommel_Strike, Shrug_It_Off, Sword_Boomerang, Thunderclap, True_Grit, Twin_Strike,  Warcry,
    Wild_Strike, 
    
    //Uncommon//
    Battle_Trance, Blood_For_Blood, Bloodletting, Burning_Pact, Carnage, Combust, Dark_Embrace, Disarm, Dropkick,
    Dual_Wield, Entrench, Evolve, Feel_No_Pain, Fire_Breathing, Flame_Barrier, Ghostly_Armor, Hemokinesis, Infernal_Blade,
    Inflame, Intimidate, Metallicize, Power_Through, Pummel, Rage, Rampage, Reckless_Charge, Rupture, Searing_Blow, 
    Second_Wind, Seeing_Red, Sentinel, Sever_Soul, Shockwave, Spot_Weakness, Uppercut, Whirlwind,
    
    //Rare//
    Barricade, Berserk, Bludgeon, Brutality, Corruption, Demon_Form, Double_Tap, Exhume, Feed, Fiend_Fire, Immolate, 
    Impervious, Juggernaut, Limit_Break, Offering, Reaper, 
    
    
    // SILENT //
    SLT_Strike, SLT_Defend, Neutralize, Survivor, 
    //Common//
    Acrobatics, Backflip, Bane, Blade_Dance, Cloak_and_Dagger, Dagger_Spray, Dagger_Throw, Deadly_Poison, Dodge_and_Roll,
    Flying_Knee, Outmaneuver, Piercing_Wail, Poisoned_Stab, Prepared, Quick_Slash, Slice, Sneaky_Strike, Sucker_Punch,
    
    //Uncommon//
    Accuracy, All_Out_Attack, Backstab, Blur, Bouncing_Flask, Calculated_Gamble, Caltrops, Catalyst, Choke, Concentrate,
    Crippling_Cloud, Dash, Distraction, Endless_Agony, Escape_Plan, Eviscerate, Expertise, Finisher, Flechettes, Footwork,
    Heel_Hook, Infinite_Blades, Leg_Sweep, Masterful_Stab, Noxious_Fumes, Predator, Reflex, Riddle_with_Holes, Setup, Skewer, 
    Tactician, Terror, Well_Laid_PLans,
    
    //RARE//
    A_Thousand_Cuts, Adrenaline, After_Image, Alchemize, Bullet_Time, Burst, Corpse_Explosion, Die_Die_Die, Doppelganger,
    Envenom, Glass_Knife, Grand_Finale, Malaise, Nightmare, Phantasmal_Killer, Storm_of_Steel, Tools_of_the_Trade, Unload,
    Wraith_Form,
    
    // DEFECT //
    DEF_Strike, DEF_Defend, Zap, Dualcast, 
    //Common
    Ball_Lightning, Barrage, Beam_Cell, Charge_Battery, Claw, Cold_Snap, Compile_Driver, Coolheaded, Go_for_the_Eyes, Hologram,
    Leap,Rebound, Recursion, Stack, Steam_Barrier, Streamline, Sweeping_Beam, Turbo, 
    
    //Uncommon//
    Aggregate, Auto_Shields, Blizzard, Boot_Sequence, Bullseye, Capacitor, Chaos, Chill, Consume, Darkness, Defragment, Doom_and_Gloom,
    Double_Energy, Equilibrium, FTL, Force_Field, Fusion, Genetic_Algorithm, Glacier, Heatsinks, Hello_World, Loop, Melter, Overclock,
    Recycle, Reinforced_Body, Reprogram, Rip_and_Tear, Scrape, Self_Repair, Skim, Static_Discharge, Storm, Sunder, Tempest, White_Noise, 
    
    //Rare//
    All_for_One, Amplify, Biased_Cognition, Buffer, Core_Surge, Creative_AI, Echo_Form, Electrodynamics, Fission, Hyperbeam, Machine_Learning,
    Meteor_Strike, Multi_Cast, Rainbow, Reboot, Seek, Thunder_Strike,
    
    
    // WATCHER //
    WAT_Strike, WAT_Defend, Vigilance, Eruption,
    //Common//
    Bowling_Bash, Consecrate, Crescendo, Crush_Joints, Cut_Through_Fate, Empty_Body, Empty_Fist, Evaluate, Flurry_Of_Blows, Flying_Sleeves,
    Follow_Up, Halt, Just_Lucky, Pressure_Points, Prostrate, Protect, Sash_Whip, Third_Eye, Tranquility,
    
    //Uncommon//
    Battle_Hymn, Carve_Reality, Collect, Conclude, Deceive_Reality, Empty_Mind, Fasting, Fear_No_Evil, Foreign_Influence, Foresight,
    Indignation, Inner_Peace, Like_Water, Meditate, Mental_Fortress, Nirvana, Perseverance, Pray, Reach_Heaven, Rushdown, Sanctity,
    Sands_of_Time, Signature_Move, Simmering_Fury, Study, Swivel, Talk_to_the_Hand, Tantrum, Wallop, Wave_of_the_Hand, Weave, Wheel_Kick,
    Windmill_Strike, Worship, Wreath_of_Flame,
    
    //Rare//
    Alpha, Blasphemy, Brilliance, Conjure_Blade, Deus_Ex_Machina, Deva_Form, Devotion, Establishment, Judgment, Lesson_Learned,
    Master_Reality, Omniscience, Ragnarok, Scrawl, Spirit_Shield, Vault, Wish,
    
    // COLORLESS //
    //Uncommon//
    Bandage_Up, Blind, Dark_Shackles, Deep_Breath, Discovery, Dramatic_Entrance, Enlightenment, Finesse, Flash_of_Steel, Forethought,
    Good_Instincts, Impatience, Jack_of_All_Trades, Madness, Mind_Blast, Panacea, Panic_Button, Purity, Swift_Strike, Trip,
    
    //Rare//
    Apotheosis, Chrysalis, Hand_of_Greed, Magnetism, Master_of_Strategy, Mayhem, Metamorphosis, Panache, Sadistic_Nature, Secret_Technique,
    Secret_Weapon, The_Bomb, Thinking_Ahead, Transmutation, Violence, 
    
    //Special//
    Apparition, Beta, Bite, Expunger, Insight, JAX, Miracle, Omega, Ritual_Dagger, Safety, Shiv, Smite, Through_Violence, 
    
    // STATUS //
    Burn, Dazed, Slimed, Void, Wound,
    
    // CURSE //
    Ascenders_Bane, Clumsy, Curse_of_the_Bell, Decay, Doubt, Injury, Necronomicurse, Normality, Pain, Parasite, Pride, Regret, Shame, Writhe,
};
enum class CardType {attack, skill, power, status, curse};
enum class CardRarity {starter, common, uncommon, rare, status, curse};

//This class defines a Card object. It is the unit that forms piles.
class Card{
    CID id;
    Color character; 
	std::string name;
	CardType type;
	int energy_cost; // -2: X cost, -1: unplayable
	CardRarity rarity;
	std::string card_text;
    std::vector<Effect> effects;  
    bool exhaust;
public:
    Card(CID i, Color c, std::string n, CardType t, int cost, CardRarity r, std::string text, std::vector<Effect> e, bool ex);
    void display();    
    int getEnergyCost();
    CID getID();
    std::string getName();
    Color rarityColor();
    CardType getCardType();
    std::string getCardTypeText();
    std::string getCardRarity();
    void applyEffects(Player& source, Game& game, int pos);
    bool canPlay(Player& source, Game& game);
};

Card createCard(CID id);

#endif
