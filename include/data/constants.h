#ifndef CONSTANTS_H
#define CONSTANTS_H
#include"stdint.h"
#include<vector>
class Card;
class Pile;
class Effect;
enum class CID;

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
extern const int STARTING_POTION_SLOTS;
extern const int MAX_BLOCK;
extern const int EVENT_LOG_SIZE;
extern const int MAX_HAND_SIZE;
extern const int VULNERABLE_PCENT;
extern const int WEAK_PCENT;
extern const int FRAIL_PCENT;

extern const uint64_t SEED_MIN;
extern const uint64_t SEED_MAX;

extern Pile empty_deck;
extern Pile ICL_STARTER_DECK;
extern Pile SLT_STARTER_DECK;
extern Pile DEF_STARTER_DECK;
extern Pile WAT_STARTER_DECK;


//Card rewards
extern std::vector<CID> ICL_COMMON;
extern std::vector<CID> ICL_UNCOMMON;
extern std::vector<CID> ICL_RARE;

extern std::vector<CID> SLT_COMMON;
extern std::vector<CID> SLT_UNCOMMON;
extern std::vector<CID> SLT_RARE;

extern std::vector<CID> DEF_COMMON;
extern std::vector<CID> DEF_UNCOMMON;
extern std::vector<CID> DEF_RARE;

extern std::vector<CID> WAT_COMMON;
extern std::vector<CID> WAT_UNCOMMON;
extern std::vector<CID> WAT_RARE;

extern std::vector<CID> CLS_UNCOMMON;
extern std::vector<CID> CLS_RARE;

extern std::vector<CID> CURSES;


// Predefined Cards (Declared here, defined in `constants.cpp`)

extern Card blank_card;

//IRONCLAD
extern Card ICL_Strike;
extern Card ICL_Defend;
extern Card Bash; 

//COMMON//
extern Card Anger; 
extern Card Armaments; 
extern Card Body_Slam; 
extern Card Clash; 
extern Card Cleave; 
extern Card Clothesline; 
extern Card Flex; 
extern Card Havoc; 
extern Card Headbutt; 
extern Card Heavy_Blade; 
extern Card Iron_Wave; 
extern Card Perfected_Strike; 
extern Card Pommel_Strike; 
extern Card Shrug_It_Off; 
extern Card Sword_Boomerang; 
extern Card Thunderclap; 
extern Card True_Grit; 
extern Card Twin_Strike; 
extern Card Warcry; 
extern Card Wild_Strike; 

//UNCOMMON//
extern Card Battle_Trance; 
extern Card Blood_For_Blood; 
extern Card Bloodletting; 
extern Card Burning_Pact; 
extern Card Carnage; 
extern Card Combust; 
extern Card Dark_Embrace; 
extern Card Disarm; 
extern Card Dropkick; 
extern Card Dual_Wield; 
extern Card Entrench; 
extern Card Evolve; 
extern Card Feel_No_Pain; 
extern Card Fire_Breathing; 
extern Card Flame_Barrier; 
extern Card Ghostly_Armor; 
extern Card Hemokinesis; 
extern Card Infernal_Blade; 
extern Card Inflame; 
extern Card Intimidate; 
extern Card Metallicize; 
extern Card Power_Through; 
extern Card Pummel; 
extern Card Rage; 
extern Card Rampage; 
extern Card Reckless_Charge; 
extern Card Rupture; 
extern Card Searing_Blow; 
extern Card Second_Wind; 
extern Card Seeing_Red; 
extern Card Sentinel; 
extern Card Sever_Soul; 
extern Card Shockwave; 
extern Card Spot_Weakness; 
extern Card Uppercut; 
extern Card Whirlwind; 

//RARE//
extern Card Barricade; 
extern Card Berserk; 
extern Card Bludgeon; 
extern Card Brutality; 
extern Card Corruption; 
extern Card Demon_Form; 
extern Card Double_Tap; 
extern Card Exhume; 
extern Card Feed; 
extern Card Fiend_Fire; 
extern Card Immolate; 
extern Card Impervious; 
extern Card Juggernaut; 
extern Card Limit_Break; 
extern Card Offering; 
extern Card Reaper; 

//SILENT
extern Card SLT_Strike; 
extern Card SLT_Defend; 
extern Card Neutralize; 
extern Card Survivor; 

//COMMON//
extern Card Acrobatics; 
extern Card Backflip; 
extern Card Bane; 
extern Card Blade_Dance; 
extern Card Cloak_and_Dagger; 
extern Card Dagger_Spray; 
extern Card Dagger_Throw; 
extern Card Deadly_Poison; 
extern Card Dodge_and_Roll; 
extern Card Flying_Knee; 
extern Card Outmaneuver; 
extern Card Piercing_Wail; 
extern Card Poisoned_Stab; 
extern Card Prepared; 
extern Card Quick_Slash; 
extern Card Slice; 
extern Card Sneaky_Strike; 
extern Card Sucker_Punch; 

//UNCOMMON//
extern Card Accuracy; 
extern Card All_Out_Attack; 
extern Card Backstab; 
extern Card Blur; 
extern Card Bouncing_Flask; 
extern Card Calculated_Gamble; 
extern Card Caltrops; 
extern Card Catalyst; 
extern Card Choke; 
extern Card Concentrate; 
extern Card Crippling_Cloud; 
extern Card Dash; 
extern Card Distraction; 
extern Card Endless_Agony; 
extern Card Escape_Plan; 
extern Card Eviscerate; 
extern Card Expertise; 
extern Card Finisher; 
extern Card Flechettes; 
extern Card Footwork; 
extern Card Heel_Hook; 
extern Card Infinite_Blades; 
extern Card Leg_Sweep; 
extern Card Masterful_Stab; 
extern Card Noxious_Fumes; 
extern Card Predator; 
extern Card Reflex; 
extern Card Riddle_with_Holes; 
extern Card Setup; 
extern Card Skewer; 
extern Card Tactician; 
extern Card Terror; 
extern Card Well_Laid_Plans; 

//RARE//
extern Card A_Thousand_Cuts; 
extern Card Adrenaline; 
extern Card After_Image; 
extern Card Alchemize; 
extern Card Bullet_Time; 
extern Card Burst; 
extern Card Corpse_Explosion; 
extern Card Die_Die_Die; 
extern Card Doppelganger; 
extern Card Envenom; 
extern Card Glass_Knife; 
extern Card Grand_Finale; 
extern Card Malaise; 
extern Card Nightmare; 
extern Card Phantasmal_Killer; 
extern Card Storm_of_Steel; 
extern Card Tools_of_the_Trade; 
extern Card Unload; 
extern Card Wraith_Form; 

//DEFECT
extern Card DEF_Strike; 
extern Card DEF_Defend; 
extern Card Zap; 
extern Card Dualcast; 

//COMMON
extern Card Ball_Lightning; 
extern Card Barrage; 
extern Card Beam_Cell; 
extern Card Charge_Battery; 
extern Card Claw; 
extern Card Cold_Snap; 
extern Card Compile_Driver; 
extern Card Coolheaded; 
extern Card Go_for_the_Eyes; 
extern Card Hologram; 
extern Card Leap; 
extern Card Rebound; 
extern Card Recursion; 
extern Card Stack; 
extern Card Steam_Barrier; 
extern Card Streamline; 
extern Card Sweeping_Beam; 
extern Card Turbo; 

//UNCOMMON//
extern Card Aggregate; 
extern Card Auto_Shields; 
extern Card Blizzard; 
extern Card Boot_Sequence; 
extern Card Bullseye; 
extern Card Capacitor; 
extern Card Chaos; 
extern Card Chill; 
extern Card Consume; 
extern Card Darkness; 
extern Card Defragment; 
extern Card Doom_and_Gloom; 
extern Card Double_Energy; 
extern Card Equilibrium; 
extern Card FTL; 
extern Card Force_Field; 
extern Card Fusion; 
extern Card Genetic_Algorithm; 
extern Card Glacier; 
extern Card Heatsinks; 
extern Card Hello_World; 
extern Card Loop; 
extern Card Melter; 
extern Card Overclock; 
extern Card Recycle; 
extern Card Reinforced_Body; 
extern Card Reprogram; 
extern Card Rip_and_Tear; 
extern Card Scrape; 
extern Card Self_Repair; 
extern Card Skim; 
extern Card Static_Discharge; 
extern Card Storm; 
extern Card Sunder; 
extern Card Tempest; 
extern Card White_Noise; 

//RARE//
extern Card All_for_One; 
extern Card Amplify; 
extern Card Biased_Cognition; 
extern Card Buffer; 
extern Card Core_Surge; 
extern Card Creative_AI; 
extern Card Echo_Form; 
extern Card Electrodynamics; 
extern Card Fission; 
extern Card Hyperbeam; 
extern Card Machine_Learning; 
extern Card Meteor_Strike; 
extern Card Multi_Cast; 
extern Card Rainbow; 
extern Card Reboot; 
extern Card Seek; 
extern Card Thunder_Strike; 

//WATCHER
extern Card WAT_Strike; 
extern Card WAT_Defend; 
extern Card Vigilance; 
extern Card Eruption; 

//COMMON//
extern Card Bowling_Bash; 
extern Card Consecrate; 
extern Card Crescendo; 
extern Card Crush_Joints; 
extern Card Cut_Through_Fate; 
extern Card Empty_Body; 
extern Card Empty_Fist; 
extern Card Evaluate; 
extern Card Flurry_Of_Blows; 
extern Card Flying_Sleeves; 
extern Card Follow_Up; 
extern Card Halt; 
extern Card Just_Lucky; 
extern Card Pressure_Points; 
extern Card Prostrate; 
extern Card Protect; 
extern Card Sash_Whip; 
extern Card Third_Eye; 
extern Card Tranquility; 

//UNCOMMON//
extern Card Battle_Hymn; 
extern Card Carve_Reality; 
extern Card Collect; 
extern Card Conclude; 
extern Card Deceive_Reality; 
extern Card Empty_Mind; 
extern Card Fasting; 
extern Card Fear_No_Evil; 
extern Card Foreign_Influence; 
extern Card Foresight; 
extern Card Indignation; 
extern Card Inner_Peace; 
extern Card Like_Water; 
extern Card Meditate; 
extern Card Mental_Fortress; 
extern Card Nirvana; 
extern Card Perseverance; 
extern Card Pray; 
extern Card Reach_Heaven; 
extern Card Rushdown; 
extern Card Sanctity; 
extern Card Sands_of_Time; 
extern Card Signature_Move; 
extern Card Simmering_Fury; 
extern Card Study; 
extern Card Swivel; 
extern Card Talk_to_the_Hand; 
extern Card Tantrum; 
extern Card Wallop; 
extern Card Wave_of_the_Hand; 
extern Card Weave; 
extern Card Wheel_Kick; 
extern Card Windmill_Strike; 
extern Card Worship; 
extern Card Wreath_of_Flame; 

//RARE//
extern Card Alpha; 
extern Card Blasphemy; 
extern Card Brilliance; 
extern Card Conjure_Blade; 
extern Card Deus_Ex_Machina; 
extern Card Deva_Form; 
extern Card Devotion; 
extern Card Establishment; 
extern Card Judgment; 
extern Card Lesson_Learned; 
extern Card Master_Reality; 
extern Card Omniscience; 
extern Card Ragnarok; 
extern Card Scrawl; 
extern Card Spirit_Shield; 
extern Card Vault; 
extern Card Wish; 

//COLORLESS

//UNCOMMON//
extern Card Bandage_Up; 
extern Card Blind; 
extern Card Dark_Shackles; 
extern Card Deep_Breath; 
extern Card Discovery; 
extern Card Dramatic_Entrance; 
extern Card Enlightenment; 
extern Card Finesse; 
extern Card Flash_of_Steel; 
extern Card Forethought; 
extern Card Good_Instincts; 
extern Card Impatience; 
extern Card Jack_of_All_Trades; 
extern Card Madness; 
extern Card Mind_Blast; 
extern Card Panacea; 
extern Card Panic_Button; 
extern Card Purity; 
extern Card Swift_Strike; 
extern Card Trip; 

//RARE//
extern Card Apotheosis; 
extern Card Chrysalis; 
extern Card Hand_of_Greed; 
extern Card Magnetism; 
extern Card Master_of_Strategy; 
extern Card Mayhem; 
extern Card Metamorphosis; 
extern Card Panache; 
extern Card Sadistic_Nature; 
extern Card Secret_Technique; 
extern Card Secret_Weapon; 
extern Card The_Bomb; 
extern Card Thinking_Ahead; 
extern Card Transmutation; 
extern Card Violence; 


//SPECIAL
extern Card Apparition; 
extern Card Beta; 
extern Card Bite; 
extern Card Expunger; 
extern Card Insight; 
extern Card JAX; 
extern Card Omega; 
extern Card Ritual_Dagger; 
extern Card Safety; 
extern Card Shiv; 
extern Card Smite; 
extern Card Through_Violence; 


//STATUS
extern Card Burn; 
extern Card Dazed; 
extern Card Slimed; 
extern Card Void; 
extern Card Wound; 

//CURSE
extern Card Ascenders_Bane; 
extern Card Clumsy; 
extern Card Curse_of_the_Bell; 
extern Card Decay; 
extern Card Doubt; 
extern Card Injury; 
extern Card Necronomicurse; 
extern Card Normality; 
extern Card Pain; 
extern Card Parasite; 
extern Card Pride; 
extern Card Regret; 
extern Card Shame; 
extern Card Writhe; 

extern Effect NO_EFFECT;


////////////////////STARTER DECK//////////////////

Pile createIroncladStarterDeck();
Pile createSilentStarterDeck();
#endif
