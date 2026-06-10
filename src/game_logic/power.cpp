#include "game_logic/power.h"
#include "character/character.h"
#include "character/player.h"
#include "ui/colors.h"
#include "game_logic/effect.h"
#include "game_logic/game.h"
#include "data/constants.h"

Power::Power(PID id, int32_t i, bool in, bool d, Character* own):
    ID(id), magnitude(i), stacks_intensity(in), stacks_duration(d), owner(std::move(own)){}


void Power::changeMagnitude(int32_t delta){
    if(stacks_duration || stacks_intensity){magnitude += delta;}
    if(stacks_duration && magnitude <0){magnitude = 0;}
}

void Power::eliminate(){magnitude = 0;}

bool Power::isExpired(){
    if(stacks_duration){return magnitude <= 0;}
    else{return magnitude == 0;}
}

void Power::onTurnStart(Game& game){}
void Power::onTurnEnd(Game& game){if(stacks_duration){changeMagnitude(-1);}}


int32_t Power::modOutDamageAdd(int32_t base){return base;}
int32_t Power::modOutDamageMult(int32_t base){return base;}
int32_t Power::modIncDamage(int32_t base){return base;}
int32_t Power::modBlockGainAdd(int32_t base){return base;}
int32_t Power::modBlockGainMult(int32_t base){return base;}
int32_t Power::getMagnitude()const{return magnitude;}

void Power::onHit(Character* source, Game& game){};

PID Power::getID()const{return ID;}
Character* Power::getOwner(){return owner;}

std::string Power::IDtoString(PID id, bool plain_text){
    if(plain_text){
        switch(id){
            case PID::accuracy: return "Accuracy";
            case PID::barricade: return "Barricade";
            case PID::berserk: return "Berserk";
            case PID::biased: return "Biased";
            case PID::blur: return "Blur";
            case PID::curl_up: return "Curl Up";
            case PID::demon: return "Demon Form";
            case PID::deva: return "Deva";
            case PID::devotion: return "Devotion";
            case PID::dexterity: return "Dexterity";
            case PID::draw_next: return "Draw next turn";
            case PID::energized: return "Energized";
            case PID::frail: return "Frail";
            case PID::fasting: return "Fasting";
            case PID::lock_on: return "Lock-on";
            case PID::machine_learning: return "Machine learning";
            case PID::metallicize: return "Metallicize";
            case PID::omega: return "Omega";
            case PID::pen_nib: return "Pen Nib";
            case PID::phantasmal: return "Phantasmal";
            case PID::phantasmal_killer: return "Double Damage";
            case PID::poison: return color(Color::green, "Poison");
            case PID::ritual: return "Ritual";
            case PID::strength: return "Strength";
            case PID::surrounded: return "Surrounded";
            case PID::thorns: return "Thorns";
            case PID::vulnerable: return "Vulnerable";
            case PID::weak: return "Weak";
            case PID::wraith: return "Wraith";
            case PID::wrath: return "Wrath";
    
            default: return "none";
        }
    }else{
        switch(id){
            case PID::accuracy: return "🎯";
            case PID::barricade: return "🚧";
            case PID::berserk: return "𒉭";
            case PID::biased: return "🔵🡇";
            case PID::blur: return "🌫";
            case PID::curl_up: return "⟳ ";
            case PID::demon: return "👹";
            case PID::deva: return "🕉";
            case PID::devotion: return "🙏";
            case PID::dexterity: return color(Color::green, "⛊ ");
            case PID::draw_next: return "🂡➡";
            case PID::energized: return "🔋";
            case PID::frail: return "🛡️⛓‍💥";
            case PID::fasting: return "🍽️";
            case PID::lock_on: return "⌖";
            case PID::machine_learning: return "🂡🠝";
            case PID::metallicize: return color(Color::keyword, "◈");
            case PID::omega: return "Ω";
            case PID::pen_nib: return "✒";
            case PID::phantasmal: return "👻";
            case PID::phantasmal_killer: return "DMGx2";
            case PID::poison: return color(Color::green,"🕱");
            case PID::ritual: return "🪶";
            case PID::strength: return "💪";
            case PID::surrounded: return "⇥⇤";
            case PID::thorns: return "✷ ";
            case PID::vulnerable: return "💔";
            case PID::weak: return "🗡️⛓️‍💥";
            case PID::wraith: return "🛡🡇";
            case PID::wrath: return "💢";
            default: return "none";
        }
    }
}

void Power::display(){
    std::cout<<IDtoString(ID, false)<<magnitude;
}

BerserkPower::BerserkPower(int32_t i, Character* own): Power(PID::berserk, i, true, false, own){}
void BerserkPower::onTurnStart(Game& game){
    std::vector<Effect> e = {Effect(EID::energy, magnitude, TID::self)};
    game.resolveEffects(*owner, e);
}

MetallicizePower::MetallicizePower(int32_t i, Character* own): Power(PID::metallicize, i, true, false, own){}
void MetallicizePower::onTurnEnd(Game& game){
    std::vector<Effect> e = {Effect(EID::block, magnitude, TID::self)};
    game.resolveEffects(*owner, e);
}


WeakPower::WeakPower(int32_t i, Character* own): Power(PID::weak, i, false, true, own){}
int32_t WeakPower::modOutDamageMult(int32_t base){
    return base * (100 - WEAK_PCENT)/100;
}

StrengthPower::StrengthPower(int32_t i, Character* own): Power(PID::strength, i , true, false, own){ }
int32_t StrengthPower::modOutDamageAdd(int32_t base){
    return base +  magnitude;
}


VulnerablePower::VulnerablePower(int32_t i, Character* own):Power(PID::vulnerable, i, false, true, own){}
int32_t VulnerablePower::modIncDamage(int32_t base){
    return base * (100 + VULNERABLE_PCENT)/100;
}

RitualPower::RitualPower(int32_t i, Character* own): Power(PID::ritual, i, true, false, own){}
void RitualPower::onTurnEnd(Game& game){
    std::vector<Effect> e = { Effect(EID::gain, magnitude, TID::self, PID::strength) };
    game.resolveEffects(*owner, e);
}

FrailPower::FrailPower(int32_t i, Character* own): Power(PID::frail, i, false, true, own) {}
int32_t FrailPower::modBlockGainMult(int32_t base){
    return base * (100 - FRAIL_PCENT)/100; 
}

PoisonPower::PoisonPower(int32_t i, Character* own): Power(PID::poison, i, true, true, own){}
void PoisonPower::onTurnEnd(Game& game){} //does nothing on turn end
void PoisonPower::onTurnStart(Game& game){
    std::vector<Effect> e  = {Effect(EID::hp, -magnitude, TID::self)};
    game.resolveEffects(*owner, e);
    changeMagnitude(-1);
}

ThornsPower::ThornsPower(int32_t i, Character* own): Power(PID::thorns, i, true, false, own){}
void ThornsPower::onHit(Character* source, Game& game){ source->takeDamage(magnitude); }

AccuracyPower::AccuracyPower(int32_t i, Character* own): Power(PID::accuracy, i, true, false, own){}
int32_t AccuracyPower::modOutDamageAdd(int32_t base){
    Player* p = dynamic_cast<Player*>(owner);
    if(p){
        if(p->getPlayed().getID() == CID::Shiv){
                return base + magnitude; 
        }
    }
    return base;
}

DexterityPower::DexterityPower(int32_t i, Character* own): Power(PID::dexterity, i, true, false, own){}
int32_t DexterityPower::modBlockGainAdd(int32_t base){
    return base + magnitude;
}

OmegaPower::OmegaPower(int32_t i, Character* own): Power(PID::omega, i, true, false, own){}
void OmegaPower::onTurnEnd(Game& game){
    std::vector<Effect> e = {Effect(EID::damage, magnitude, TID::enemy_all)};
    game.resolveEffects(*owner, e);
}

FastingPower::FastingPower(int32_t i, Character* own): Power(PID::fasting, i, true, false, own){}
void FastingPower::onTurnStart(Game& game){
    std::vector<Effect> e = {Effect(EID::energy, -magnitude, TID::self)};
    game.resolveEffects(*owner, e);
}

CurlUpPower::CurlUpPower(int32_t i, Character* own): Power(PID::curl_up, i, true, false, own){}
void CurlUpPower::onHit(Character* source, Game& game){
    std::vector<Effect> e = {Effect(EID::block, magnitude, TID::self)};
    game.resolveEffects(*owner, e);
    eliminate();
}

std::unique_ptr<Power> Power::createPower(PID id, int32_t magnitude, Character* owner){
    switch(id){
        case PID::accuracy: return std::make_unique<AccuracyPower>(magnitude,owner);
        case PID::berserk: return std::make_unique<BerserkPower>(magnitude, owner);
        case PID::curl_up: return std::make_unique<CurlUpPower>(magnitude, owner);
        case PID::dexterity: return std::make_unique<DexterityPower>(magnitude,owner);
        case PID::frail: return std::make_unique<FrailPower>(magnitude,owner);
        case PID::fasting: return std::make_unique<FastingPower>(magnitude,owner);
        case PID::metallicize: return std::make_unique<MetallicizePower>(magnitude, owner);
        case PID::omega: return std::make_unique<OmegaPower>(magnitude, owner);
        case PID::poison: return std::make_unique<PoisonPower>(magnitude, owner);
        case PID::ritual: return std::make_unique<RitualPower>(magnitude, owner);
        case PID::strength: return std::make_unique<StrengthPower>(magnitude, owner);
        case PID::thorns: return std::make_unique<ThornsPower>(magnitude, owner);
        case PID::vulnerable: return std::make_unique<VulnerablePower>(magnitude,owner);
        case PID::weak: return std::make_unique<WeakPower>(magnitude, owner);
        default:
            throw std::runtime_error("Invalid PID");
    }
}

