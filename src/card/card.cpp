#include "card/card.h"
#include "game_logic/game.h"
#include "character/player.h"
#include "game_logic/effect.h"
#include "ui/colors.h"
#include "ui/formatting.h"
#include "data/constants.h"
#include<iostream>
#include<vector>



//Creates a Card and initializes it's values with the given arguments.
Card::Card(CID i, Color c, std::string n, CardType t, int cost, CardRarity r, std::string text, std::vector<Effect> e, bool ex)//Character, name, type, energy cost, rarity, card text
    :character(c), name(n), type(t), energy_cost(cost), rarity(r), card_text(text), effects(e), exhaust(ex), id(i){}   
    
//Display this card
void Card::display(){
    std::string cost = color(Color::keyword, to_energy(energy_cost));
    std::string card_type;
    switch(type){
        case CardType::attack: card_type = color(character, u8" ▲ "); break;
        case CardType::skill: card_type = color(character, u8" ■ "); break;
        case CardType::power: card_type = color(character, u8" ● "); break;
        case CardType::status: card_type = color(Color::status,u8"  ꩜ "); break;
        case CardType::curse: card_type = color(Color::curse,u8"  ⛦ "); break;
        default: card_type="none"; break; 
    }
    std::cout<<cost<<card_type<<color(rarityColor(), name)<<": "<<card_text;
    if(exhaust){std::cout<<color(Color::exhaust," Exhaust.");}
}

int Card::getEnergyCost(){return energy_cost;}
CID Card::getID(){return id;}
std::string Card::getName(){return name;}

Color Card::rarityColor(){
    switch(rarity){
        case CardRarity::common: return Color::common;
        case CardRarity::uncommon: return Color::uncommon;
        case CardRarity::rare: return Color::rare;
        case CardRarity::status: return Color::status;
        case CardRarity::starter: return Color::common;
        case CardRarity::curse: return Color::curse;
        default: return Color::common;
    }
}

std::string Card::getCardTypeText(){
    switch(type){
        case CardType::attack: return "Attack";
        case CardType::skill: return "Skill";
        case CardType::power: return "Power";
        case CardType::status: return "Status";
        case CardType::curse: return "Curse";
        default: return "none";
    }
}

CardType Card::getCardType(){return type;}
std::string Card::getCardRarity(){
        switch(rarity){
        case CardRarity::starter: return "Starter"; break;
        case CardRarity::common: return "Common"; break;
        case CardRarity::uncommon: return "Uncommon"; break;
        case CardRarity::rare: return "Rare"; break;
        case CardRarity::status: return "Status"; break;
        case CardRarity::curse: return "Curse"; break;
        default: return "none"; break;
    }
}

void Card::applyEffects(Player& source, Game& game, int pos){

    if((!effects[0].isSingleTarget())||game.hasValidTargets(effects[0].getTarget(),  source)){

        source.removeFromPlayerPile(PileID::hand, pos); //Card is now "hovering" (not on any player pile).
        source.changeAttribute(Attribute::energy,-source.getPlayed().getEnergyCost()); //Pay energy cost.

        game.resolveEffects(source,effects);

        if(exhaust){source.addToPile(PileID::exhaust, source.getPlayed(), false);}
        else{source.addToPile(PileID::discard, source.getPlayed(), false);}
    }
}

//Determines if a card can be played. Defaults to true, overrides
//for special cases depending on player/gamestate parameters.
bool Card::canPlay(Player& source, Game& game){
    bool able = true;
    if(name == "Clash"){ 
        able = source.findIndexes(PileID::hand, CardType::attack, false).size() == 0;
    }
    else if (name == "Grand Finale"){
        able = source.getPlayerPileSize(PileID::draw) == 0;
    }
    return able;
}

Card createCard(CID id){
    Card c = blank_card; 
    switch(id){

        //IRONCLAD
        case CID::ICL_Strike: c = ICL_Strike; break;
        case CID::ICL_Defend: c = ICL_Defend; break;
        case CID::Bash: c = Bash; break;

        //COMMON//
        case CID::Anger: c = Anger; break;
        case CID::Armaments: c = Armaments; break;
        case CID::Body_Slam: c = Body_Slam; break;
        case CID::Clash: c = Clash; break;
        case CID::Cleave: c = Cleave; break;
        case CID::Clothesline: c = Clothesline; break;
        case CID::Flex: c = Flex; break;
        case CID::Havoc: c = Havoc; break;
        case CID::Headbutt: c = Headbutt; break;
        case CID::Heavy_Blade: c = Heavy_Blade; break;
        case CID::Iron_Wave: c = Iron_Wave; break;
        case CID::Perfected_Strike: c = Perfected_Strike; break;
        case CID::Pommel_Strike: c = Pommel_Strike; break;
        case CID::Shrug_It_Off: c = Shrug_It_Off; break;
        case CID::Sword_Boomerang: c = Sword_Boomerang; break;
        case CID::Thunderclap: c = Thunderclap; break;
        case CID::True_Grit: c = True_Grit; break;
        case CID::Twin_Strike: c = Twin_Strike; break;
        case CID::Warcry: c = Warcry; break;
        case CID::Wild_Strike: c = Wild_Strike; break;

        //UNCOMMON//
        case CID::Battle_Trance: c = Battle_Trance; break;
        case CID::Blood_For_Blood: c = Blood_For_Blood; break;
        case CID::Bloodletting: c = Bloodletting; break;
        case CID::Burning_Pact: c = Burning_Pact; break;
        case CID::Carnage: c = Carnage; break;   
        case CID::Combust: c = Combust; break;
        case CID::Dark_Embrace: c = Dark_Embrace; break;
        case CID::Disarm: c = Disarm; break;
        case CID::Dropkick: c = Dropkick; break;
        case CID::Dual_Wield: c = Dual_Wield; break;
        case CID::Entrench: c = Entrench; break; 
        case CID::Evolve: c = Evolve; break;
        case CID::Feel_No_Pain: c = Feel_No_Pain; break;
        case CID::Fire_Breathing: c = Fire_Breathing; break;
        case CID::Flame_Barrier: c = Flame_Barrier; break;
        case CID::Ghostly_Armor: c = Ghostly_Armor; break;
        case CID::Hemokinesis: c = Hemokinesis; break;
        case CID::Infernal_Blade: c = Infernal_Blade; break;
        case CID::Inflame: c = Inflame; break;
        case CID::Intimidate: c = Intimidate; break;
        case CID::Metallicize: c = Metallicize; break;
        case CID::Power_Through: c = Power_Through; break;
        case CID::Pummel: c = Pummel; break;
        case CID::Rage: c = Rage; break;
        case CID::Rampage: c = Rampage; break;
        case CID::Reckless_Charge: c = Reckless_Charge; break;
        case CID::Rupture: c = Rupture; break;
        case CID::Searing_Blow: c = Searing_Blow; break;
        case CID::Second_Wind: c = Second_Wind; break;
        case CID::Seeing_Red: c = Seeing_Red; break;
        case CID::Sentinel: c = Sentinel; break;
        case CID::Sever_Soul: c = Sever_Soul; break;
        case CID::Shockwave: c = Shockwave; break;
        case CID::Spot_Weakness: c = Spot_Weakness; break;
        case CID::Uppercut: c = Uppercut; break;
        case CID::Whirlwind: c = Whirlwind; break;

        //RARE//
        case CID::Barricade: c = Barricade; break;
        case CID::Berserk: c = Berserk; break;
        case CID::Bludgeon: c = Bludgeon; break;
        case CID::Brutality: c = Brutality; break;
        case CID::Corruption: c = Corruption; break;
        case CID::Demon_Form: c = Demon_Form; break;
        case CID::Double_Tap: c = Double_Tap; break;
        case CID::Exhume: c = Exhume; break;
        case CID::Feed: c = Feed; break;
        case CID::Fiend_Fire: c = Fiend_Fire; break;
        case CID::Immolate: c = Immolate; break;
        case CID::Impervious: c = Impervious; break;
        case CID::Juggernaut: c = Juggernaut; break;
        case CID::Limit_Break: c = Limit_Break; break;
        case CID::Offering: c = Offering; break;
        case CID::Reaper: c = Reaper; break;

        //SILENT
        case CID::SLT_Strike: c = SLT_Strike; break;
        case CID::SLT_Defend: c = SLT_Defend; break;
        case CID::Neutralize: c = Neutralize; break;
        case CID::Survivor: c = Survivor; break;

        //COMMON//
        case CID::Acrobatics: c = Acrobatics; break;
        case CID::Backflip: c = Backflip; break;
        case CID::Bane: c = Bane; break;
        case CID::Blade_Dance: c = Blade_Dance; break;
        case CID::Cloak_and_Dagger: c = Cloak_and_Dagger; break;
        case CID::Dagger_Spray: c = Dagger_Spray; break;
        case CID::Dagger_Throw: c = Dagger_Throw; break;
        case CID::Deadly_Poison: c = Deadly_Poison; break;
        case CID::Dodge_and_Roll: c = Dodge_and_Roll; break;
        case CID::Flying_Knee: c = Flying_Knee; break;
        case CID::Outmaneuver: c = Outmaneuver; break;
        case CID::Piercing_Wail: c = Piercing_Wail; break;
        case CID::Poisoned_Stab: c = Poisoned_Stab; break;
        case CID::Prepared: c = Prepared; break;
        case CID::Quick_Slash: c = Quick_Slash; break;
        case CID::Slice: c = Slice; break;
        case CID::Sneaky_Strike: c = Sneaky_Strike; break;
        case CID::Sucker_Punch: c = Sucker_Punch; break;

        //UNCOMMON//
        case CID::Accuracy: c = Accuracy; break;
        case CID::All_Out_Attack: c = All_Out_Attack; break;
        case CID::Backstab: c = Backstab; break;
        case CID::Blur: c = Blur; break;
        case CID::Bouncing_Flask: c = Bouncing_Flask; break;
        case CID::Calculated_Gamble: c = Calculated_Gamble; break;
        case CID::Caltrops: c = Caltrops; break;
        case CID::Catalyst: c = Catalyst; break;
        case CID::Choke: c = Choke; break;
        case CID::Concentrate: c = Concentrate; break;
        case CID::Crippling_Cloud: c = Crippling_Cloud; break;
        case CID::Dash: c = Dash; break;
        case CID::Distraction: c = Distraction; break;
        case CID::Endless_Agony: c = Endless_Agony; break;
        case CID::Escape_Plan: c = Escape_Plan; break;
        case CID::Eviscerate: c = Eviscerate; break;
        case CID::Expertise: c = Expertise; break;
        case CID::Finisher: c = Finisher; break;
        case CID::Flechettes: c = Flechettes; break;
        case CID::Footwork: c = Footwork; break;
        case CID::Heel_Hook: c = Heel_Hook; break;
        case CID::Infinite_Blades: c = Infinite_Blades; break;
        case CID::Leg_Sweep: c = Leg_Sweep; break;
        case CID::Masterful_Stab: c = Masterful_Stab; break;
        case CID::Noxious_Fumes: c = Noxious_Fumes; break;
        case CID::Predator: c = Predator; break;
        case CID::Reflex: c = Reflex; break;
        case CID::Riddle_with_Holes: c = Riddle_with_Holes; break;
        case CID::Setup: c = Setup; break;
        case CID::Skewer: c = Skewer; break;
        case CID::Tactician: c = Tactician; break;
        case CID::Terror: c = Terror; break;
        case CID::Well_Laid_PLans: c = Well_Laid_Plans; break;

        //RARE//
        case CID::A_Thousand_Cuts: c = A_Thousand_Cuts; break;
        case CID::Adrenaline: c = Adrenaline; break;
        case CID::After_Image: c = After_Image; break;
        case CID::Alchemize: c = Alchemize; break;
        case CID::Bullet_Time: c = Bullet_Time; break;
        case CID::Burst: c = Burst; break;
        case CID::Corpse_Explosion: c = Corpse_Explosion; break;
        case CID::Die_Die_Die: c = Die_Die_Die; break;
        case CID::Doppelganger: c = Doppelganger; break;
        case CID::Envenom: c = Envenom; break;
        case CID::Glass_Knife: c = Glass_Knife; break;
        case CID::Grand_Finale: c = Grand_Finale; break;
        case CID::Malaise: c = Malaise; break;
        case CID::Nightmare: c = Nightmare; break;
        case CID::Phantasmal_Killer: c = Phantasmal_Killer; break;
        case CID::Storm_of_Steel: c = Storm_of_Steel; break;
        case CID::Tools_of_the_Trade: c = Tools_of_the_Trade; break;
        case CID::Unload: c = Unload; break;
        case CID::Wraith_Form: c = Wraith_Form; break;

        //DEFECT
        case CID::DEF_Strike: c = DEF_Strike; break;
        case CID::DEF_Defend: c = DEF_Defend; break;
        case CID::Zap: c = Zap; break;
        case CID::Dualcast: c = Dualcast; break;

        //COMMON
        case CID::Ball_Lightning: c = Ball_Lightning; break;
        case CID::Barrage: c = Barrage; break;
        case CID::Beam_Cell: c = Beam_Cell; break;
        case CID::Charge_Battery: c = Charge_Battery; break;
        case CID::Claw: c = Claw; break;
        case CID::Cold_Snap: c = Cold_Snap; break;
        case CID::Compile_Driver: c = Compile_Driver; break;
        case CID::Coolheaded: c = Coolheaded; break;
        case CID::Go_for_the_Eyes: c = Go_for_the_Eyes; break;
        case CID::Hologram: c = Hologram; break;
        case CID::Leap: c = Leap; break;
        case CID::Rebound: c = Rebound; break;
        case CID::Recursion: c = Recursion; break;
        case CID::Stack: c = Stack; break;
        case CID::Steam_Barrier: c = Steam_Barrier; break;
        case CID::Streamline: c = Streamline; break;
        case CID::Sweeping_Beam: c = Sweeping_Beam; break;
        case CID::Turbo: c = Turbo; break;

        //UNCOMMON//
        case CID::Aggregate: c = Aggregate; break;
        case CID::Auto_Shields: c = Auto_Shields; break;
        case CID::Blizzard: c = Blizzard; break;
        case CID::Boot_Sequence: c = Boot_Sequence; break;
        case CID::Bullseye: c = Bullseye; break;
        case CID::Capacitor: c = Capacitor; break;
        case CID::Chaos: c = Chaos; break;
        case CID::Chill: c = Chill; break;
        case CID::Consume: c = Consume; break;
        case CID::Darkness: c = Darkness; break;
        case CID::Defragment: c = Defragment; break;
        case CID::Doom_and_Gloom: c = Doom_and_Gloom; break;
        case CID::Double_Energy: c = Double_Energy; break;
        case CID::Equilibrium: c = Equilibrium; break;
        case CID::FTL: c = FTL; break;
        case CID::Force_Field: c = Force_Field; break;
        case CID::Fusion: c = Fusion; break;
        case CID::Genetic_Algorithm: c = Genetic_Algorithm; break;
        case CID::Glacier: c = Glacier; break;
        case CID::Heatsinks: c = Heatsinks; break;
        case CID::Hello_World: c = Hello_World; break;
        case CID::Loop: c = Loop; break;
        case CID::Melter: c = Melter; break;
        case CID::Overclock: c = Overclock; break;
        case CID::Recycle: c = Recycle; break;
        case CID::Reinforced_Body: c = Reinforced_Body; break;
        case CID::Reprogram: c = Reprogram; break;
        case CID::Rip_and_Tear: c = Rip_and_Tear; break;
        case CID::Scrape: c = Scrape; break;
        case CID::Self_Repair: c = Self_Repair; break;
        case CID::Skim: c = Skim; break;
        case CID::Static_Discharge: c = Static_Discharge; break;
        case CID::Storm: c = Storm; break;
        case CID::Sunder: c = Sunder; break;
        case CID::Tempest: c = Tempest; break;
        case CID::White_Noise: c = White_Noise; break;

        //RARE//
        case CID::All_for_One: c = All_for_One; break;
        case CID::Amplify: c = Amplify; break;
        case CID::Biased_Cognition: c = Biased_Cognition; break;
        case CID::Buffer: c = Buffer; break;
        case CID::Core_Surge: c = Core_Surge; break;
        case CID::Creative_AI: c = Creative_AI; break;
        case CID::Echo_Form: c = Echo_Form; break;
        case CID::Electrodynamics: c = Electrodynamics; break;
        case CID::Fission: c = Fission; break;
        case CID::Hyperbeam: c = Hyperbeam; break;
        case CID::Machine_Learning: c = Machine_Learning; break;
        case CID::Meteor_Strike: c = Meteor_Strike; break;
        case CID::Multi_Cast: c = Multi_Cast; break;
        case CID::Rainbow: c = Rainbow; break;
        case CID::Reboot: c = Reboot; break;
        case CID::Seek: c = Seek; break;
        case CID::Thunder_Strike: c = Thunder_Strike; break;

        //WATCHER
        case CID::WAT_Strike: c = WAT_Strike; break;
        case CID::WAT_Defend: c = WAT_Defend; break;
        case CID::Vigilance: c = Vigilance; break;
        case CID::Eruption: c = Eruption; break;

        //COMMON//
        case CID::Bowling_Bash: c = Bowling_Bash; break;
        case CID::Consecrate: c = Consecrate; break;
        case CID::Crescendo: c = Crescendo; break;
        case CID::Crush_Joints: c = Crush_Joints; break;
        case CID::Cut_Through_Fate: c = Cut_Through_Fate; break;
        case CID::Empty_Body: c = Empty_Body; break;
        case CID::Empty_Fist: c = Empty_Fist; break;
        case CID::Evaluate: c = Evaluate; break;
        case CID::Flurry_Of_Blows: c = Flurry_Of_Blows; break;
        case CID::Flying_Sleeves: c = Flying_Sleeves; break;
        case CID::Follow_Up: c = Follow_Up; break;
        case CID::Halt: c = Halt; break;
        case CID::Just_Lucky: c = Just_Lucky; break;
        case CID::Pressure_Points: c = Pressure_Points; break;
        case CID::Prostrate: c = Prostrate; break;
        case CID::Protect: c = Protect; break;
        case CID::Sash_Whip: c = Sash_Whip; break;
        case CID::Third_Eye: c = Third_Eye; break;
        case CID::Tranquility: c = Tranquility; break;

        //UNCOMMON//
        case CID::Battle_Hymn: c = Battle_Hymn; break;
        case CID::Carve_Reality: c = Carve_Reality; break;
        case CID::Collect: c = Collect; break;
        case CID::Conclude: c = Conclude; break;
        case CID::Deceive_Reality: c = Deceive_Reality; break;
        case CID::Empty_Mind: c = Empty_Mind; break;
        case CID::Fasting: c = Fasting; break;
        case CID::Fear_No_Evil: c = Fear_No_Evil; break;
        case CID::Foreign_Influence: c = Foreign_Influence; break;
        case CID::Foresight: c = Foresight; break;
        case CID::Indignation: c = Indignation; break;
        case CID::Inner_Peace: c = Inner_Peace; break;
        case CID::Like_Water: c = Like_Water; break;
        case CID::Meditate: c = Meditate; break;
        case CID::Mental_Fortress: c = Mental_Fortress; break;
        case CID::Nirvana: c = Nirvana; break;
        case CID::Perseverance: c = Perseverance; break;
        case CID::Pray: c = Pray; break;
        case CID::Reach_Heaven: c = Reach_Heaven; break;
        case CID::Rushdown: c = Rushdown; break;
        case CID::Sanctity: c = Sanctity; break;
        case CID::Sands_of_Time: c = Sands_of_Time; break;
        case CID::Signature_Move: c = Signature_Move; break;
        case CID::Simmering_Fury: c = Simmering_Fury; break;
        case CID::Study: c = Study; break;
        case CID::Swivel: c = Swivel; break;
        case CID::Talk_to_the_Hand: c = Talk_to_the_Hand; break;
        case CID::Tantrum: c = Tantrum; break;
        case CID::Wallop: c = Wallop; break;
        case CID::Wave_of_the_Hand: c = Wave_of_the_Hand; break;
        case CID::Weave: c = Weave; break;
        case CID::Wheel_Kick: c = Wheel_Kick; break;
        case CID::Windmill_Strike: c = Windmill_Strike; break;
        case CID::Worship: c = Worship; break;
        case CID::Wreath_of_Flame: c = Wreath_of_Flame; break;
        
        //RARE//
        case CID::Alpha: c = Alpha; break;
        case CID::Blasphemy: c = Blasphemy; break;
        case CID::Brilliance: c = Brilliance; break;
        case CID::Conjure_Blade: c = Conjure_Blade; break;
        case CID::Deus_Ex_Machina: c = Deus_Ex_Machina; break;
        case CID::Deva_Form: c = Deva_Form; break;
        case CID::Devotion: c = Devotion; break;
        case CID::Establishment: c = Establishment; break;
        case CID::Judgment: c = Judgment; break;
        case CID::Lesson_Learned: c = Lesson_Learned; break;
        case CID::Master_Reality: c = Master_Reality; break;
        case CID::Omniscience: c = Omniscience; break;
        case CID::Ragnarok: c = Ragnarok; break;
        case CID::Scrawl: c = Scrawl; break;
        case CID::Spirit_Shield: c = Spirit_Shield; break;
        case CID::Vault: c = Vault; break;
        case CID::Wish: c = Wish; break;

        //COLORLESS

        //UNCOMMON//
        case CID::Bandage_Up: c = Bandage_Up; break;
        case CID::Blind: c = Blind; break;
        case CID::Dark_Shackles: c = Dark_Shackles; break;
        case CID::Deep_Breath: c = Deep_Breath; break;
        case CID::Discovery: c = Discovery; break;
        case CID::Dramatic_Entrance: c = Dramatic_Entrance; break;
        case CID::Enlightenment: c = Enlightenment; break;
        case CID::Finesse: c = Finesse; break;
        case CID::Flash_of_Steel: c = Flash_of_Steel; break;
        case CID::Forethought: c = Forethought; break;
        case CID::Good_Instincts: c = Good_Instincts; break;
        case CID::Impatience: c = Impatience; break;
        case CID::Jack_of_All_Trades: c = Jack_of_All_Trades; break;
        case CID::Madness: c = Madness; break;
        case CID::Mind_Blast: c = Mind_Blast; break;
        case CID::Panacea: c = Panacea; break;
        case CID::Panic_Button: c = Panic_Button; break;
        case CID::Purity: c = Purity; break;
        case CID::Swift_Strike: c = Swift_Strike; break;
        case CID::Trip: c = Trip; break;

        //RARE//
        case CID::Apotheosis: c = Apotheosis; break;
        case CID::Chrysalis: c = Chrysalis; break;
        case CID::Hand_of_Greed: c = Hand_of_Greed; break;
        case CID::Magnetism: c = Magnetism; break;
        case CID::Master_of_Strategy: c = Master_of_Strategy; break;
        case CID::Mayhem: c = Mayhem; break;
        case CID::Metamorphosis: c = Metamorphosis; break;
        case CID::Panache: c = Panache; break;
        case CID::Sadistic_Nature: c = Sadistic_Nature; break;
        case CID::Secret_Technique: c = Secret_Technique; break;
        case CID::Secret_Weapon: c = Secret_Weapon; break;
        case CID::The_Bomb: c = The_Bomb; break;
        case CID::Thinking_Ahead: c = Thinking_Ahead; break;
        case CID::Transmutation: c = Transmutation; break;
        case CID::Violence: c = Violence; break;


        //SPECIAL
        case CID::Apparition: c = Apparition; break;
        case CID::Beta: c = Beta; break;
        case CID::Bite: c = Bite; break;
        case CID::Expunger: c = Expunger; break;
        case CID::Insight: c = Insight; break;
        case CID::JAX: c = JAX; break;
        case CID::Omega: c = Omega; break;
        case CID::Ritual_Dagger: c = Ritual_Dagger; break;
        case CID::Safety: c = Safety; break;
        case CID::Shiv: c = Shiv; break;
        case CID::Smite: c = Smite; break;
        case CID::Through_Violence: c = Through_Violence; break;


        //STATUS
        case CID::Burn: c = Burn; break;
        case CID::Dazed: c = Dazed; break;
        case CID::Slimed: c = Slimed; break;
        case CID::Void: c = Void; break;
        case CID::Wound: c = Wound; break;

        //CURSE
        case CID::Ascenders_Bane: c = Ascenders_Bane; break;
        case CID::Clumsy: c = Clumsy; break;
        case CID::Curse_of_the_Bell: c = Curse_of_the_Bell; break;
        case CID::Decay: c = Decay; break;
        case CID::Doubt: c = Doubt; break;
        case CID::Injury: c = Injury; break;
        case CID::Necronomicurse: c = Necronomicurse; break;
        case CID::Normality: c = Normality; break;
        case CID::Pain: c = Pain; break;
        case CID::Parasite: c = Parasite; break;
        case CID::Pride: c = Pride; break;
        case CID::Regret: c = Regret; break;
        case CID::Shame: c = Shame; break;
        case CID::Writhe: c = Writhe; break;


        default: break;

    }
    return c;


}

