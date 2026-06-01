#include "game_logic/power.h"
#include "character/character.h"


#include "data/constants.h"

Power::Power(PID id, int32_t i, bool in, bool d, Character* own):
    ID(id), magnitude(i), stacks_intensity(in), stacks_duration(d), owner(std::move(own)){}

void Power::onTurnStart(){}
void Power::onTurnEnd(){if(stacks_duration){changeMagnitude(-1);}}


void Power::changeMagnitude(int32_t delta){
    if(stacks_duration || stacks_intensity){magnitude += delta;}
    if(stacks_duration && magnitude <0){magnitude = 0;}
}

void Power::eliminate(){
    magnitude = 0;
}

bool Power::isExpired(){
    if(stacks_duration){return magnitude <= 0;}
    else{return magnitude == 0;}
}

int32_t Power::modOutDamageAdd(int32_t base){return base;}
int32_t Power::modOutDamageMult(int32_t base){return base;}
int32_t Power::modIncDamage(int32_t base){return base;}
int32_t Power::modBlockGain(int32_t base){return base;}
int32_t Power::getMagnitude()const{return magnitude;}

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
            case PID::demon: return "Demon Form";
            case PID::deva: return "Deva";
            case PID::devotion: return "Devotion";
            case PID::dexterity: return "Dexterity";
            case PID::draw_next: return "Draw next turn";
            case PID::energized: return "Energized";
            case PID::frail: return "Frail";
            case PID::lock_on: return "Lock-on";
            case PID::machine_learning: return "Machine learning";
            case PID::pen_nib: return "Pen Nib";
            case PID::phantasmal: return "Phantasmal";
            case PID::phantasmal_killer: return "Double Damage";
            case PID::ritual: return "Ritual";
            case PID::strength: return "Strength";
            case PID::surrounded: return "Surrounded";
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
            case PID::berserk: return "///";
            case PID::biased: return "🔵🡇";
            case PID::blur: return "🌫";
            case PID::demon: return "👹";
            case PID::deva: return "🕉";
            case PID::devotion: return "🙏";
            case PID::dexterity: return "⛨";
            case PID::draw_next: return "🂡➡";
            case PID::energized: return "🔋";
            case PID::frail: return "🛡️⛓‍💥";
            case PID::lock_on: return "⌖";
            case PID::machine_learning: return "🂡🠝";
            case PID::pen_nib: return "✒";
            case PID::phantasmal: return "👻";
            case PID::phantasmal_killer: return "DMGx2";
            case PID::ritual: return "🪶";
            case PID::strength: return "💪";
            case PID::surrounded: return "⇥⇤";
            case PID::vulnerable: return "💔";
            case PID::weak: return "🗡️⛓️‍💥";
            case PID::wraith: return "⛨🡇";
            case PID::wrath: return "💢";
    
            default: return "none";
        }
    }
}

void Power::display(){
    std::cout<<IDtoString(this->ID, false)<<magnitude;
}


Weak::Weak(int32_t i, Character* own): Power(PID::weak, i, false, true, std::move(own)){}
int32_t Weak::modOutDamageMult(int32_t base){
    return base * (100 - WEAK_PCENT)/100;
}

Strength::Strength(int32_t i, Character* own): Power(PID::strength, i , true, false, std::move(own)){ }
int32_t Strength::modOutDamageAdd(int32_t base){
    return base +  magnitude;
}


Vulnerable::Vulnerable(int32_t i, Character* own):Power(PID::vulnerable, i, false, true, std::move(own)){}
int32_t Vulnerable::modIncDamage(int32_t base){
    return base * (100 + VULNERABLE_PCENT)/100;
}

Ritual::Ritual(int32_t i, Character* own): Power(PID::ritual, i, true, false, std::move(own)){}
void Ritual::onTurnEnd(){
    owner->addPower(createPower(PID::strength, magnitude, owner));
}

Frail::Frail(int32_t i, Character* own): Power(PID::frail, i, false, true, std::move(own)) {}
int32_t Frail::modBlockGain(int32_t base){
    return base * (100 - FRAIL_PCENT)/100; 
}

std::unique_ptr<Power> Power::createPower(PID id, int32_t magnitude, Character* owner){
    switch(id){
        case PID::weak: return std::make_unique<Weak>(magnitude, owner);
        case PID::vulnerable: return std::make_unique<Vulnerable>(magnitude,owner);
        case PID::ritual: return std::make_unique<Ritual>(magnitude, owner);
        case PID::frail: return std::make_unique<Frail>(magnitude,owner);
        case PID::strength: return std::make_unique<Strength>(magnitude, owner);
        default:
            throw std::runtime_error("Invalid PID");
    }
}

