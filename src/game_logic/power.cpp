#include "game_logic/power.h"
#include "character/character.h"
#include "character/player.h"
#include "ui/colors.h"
#include "game_logic/effect.h"
#include "game_logic/game.h"
#include "data/constants.h"
#include "game_logic/eventhandler.h"

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
void Power::onUnblockedAttack(Character* target, Game& game){};

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
            case PID::dexterity_down: return "Dexterity Down";
            case PID::draw_card: return "Draw next turn";
            case PID::energized: return "Energized";
            case PID::envenom: return "Envenom";
            case PID::frail: return "Frail";
            case PID::fasting: return "Fasting";
            case PID::lock_on: return "Lock-on";
            case PID::infinite_blades: return "Infinite Blades";
            case PID::machine_learning: return "Machine learning";
            case PID::metallicize: return "Metallicize";
            case PID::omega: return "Omega";
            case PID::pen_nib: return "Pen Nib";
            case PID::phantasmal: return "Phantasmal";
            case PID::phantasmal_killer: return "Double Damage";
            case PID::poison: return color(Color::green, "Poison");
            case PID::ritual: return "Ritual";
            case PID::shackled: return "Shackled";
            case PID::strength: return color(Color::red, "Strength");
            case PID::strength_down: return "Strength Down";
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
            case PID::dexterity_down: return color(Color::green, "⛊🡇 ");
            case PID::draw_card: return "🂡➡ ";
            case PID::energized: return "🔋";
            case PID::envenom: return color(Color::green, "🗡 🌢 "); //Drop of poison and a blade. this indicates blade has been poisoned.
            case PID::frail: return "🛡️⛓‍💥";
            case PID::fasting: return "🍽️";
            case PID::lock_on: return "⌖";
            case PID::infinite_blades: return "⚔";
            case PID::machine_learning: return "🂡🠝";
            case PID::metallicize: return color(Color::keyword, "◈");
            case PID::omega: return "Ω";
            case PID::pen_nib: return "✒";
            case PID::phantasmal: return "👻";
            case PID::phantasmal_killer: return "DMGx2";
            case PID::poison: return color(Color::green,"🕱");
            case PID::ritual: return "🪶";
            case PID::shackled: return "🔗";
            case PID::strength: return "💪";
            case PID::strength_down: return "💪🡇 ";
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

BerserkPower::BerserkPower(int32_t i, Character* own): Power(PID::berserk, i, true, false, own){}
void BerserkPower::onTurnStart(Game& game){
    std::shared_ptr<Effect> a = std::make_shared<CombatAction>(CombatAction(EID::energy, magnitude, TID::self));
    Event ev (a, owner, {owner}, owner);
    game.enqueueEvent(ev);
}

CurlUpPower::CurlUpPower(int32_t i, Character* own): Power(PID::curl_up, i, true, false, own){}
void CurlUpPower::onHit(Character* source, Game& game){
    std::shared_ptr<Effect> a = std::make_shared<CombatAction>(CombatAction(EID::block, magnitude, TID::self));
    std::deque<Character*> target = {owner};
    Event ev (a, owner, target, owner);
    game.enqueueEvent(ev);
    eliminate();
}

DexterityPower::DexterityPower(int32_t i, Character* own): Power(PID::dexterity, i, true, false, own){}
int32_t DexterityPower::modBlockGainAdd(int32_t base){
    return base + magnitude;
}

DexterityDownPower::DexterityDownPower(int32_t i, Character* own): Power(PID::dexterity_down, i , true, false, own){}
void DexterityDownPower::onTurnEnd(Game& game){
    std::shared_ptr<Effect> a = std::make_shared<PowerManip>(PowerManip(EID::gain, -magnitude, TID::self, PID::dexterity));
    Event ev (a, owner, {owner}, owner);
    game.enqueueEvent(ev);
    eliminate();
}

DrawCardPower::DrawCardPower(int32_t i, Character* own): Power(PID::draw_card, i, true, false, own){}
void DrawCardPower::onTurnStart(Game& game){
    std::shared_ptr<Effect> a = std::make_shared<CombatAction>(CombatAction(EID::draw, magnitude, TID::player));
    Event ev(a, owner, {owner}, owner);
    game.enqueueEvent(ev);
    eliminate();
}

FastingPower::FastingPower(int32_t i, Character* own): Power(PID::fasting, i, true, false, own){}
void FastingPower::onTurnStart(Game& game){
    std::shared_ptr<Effect> a = std::make_shared<CombatAction>(CombatAction(EID::energy, -magnitude, TID::self));
    Event ev (a, owner, {owner}, owner);
    game.enqueueEvent(ev);
}

FrailPower::FrailPower(int32_t i, Character* own): Power(PID::frail, i, false, true, own) {}
int32_t FrailPower::modBlockGainMult(int32_t base){
    return base * (100 - FRAIL_PCENT)/100; 
}

EnvenomPower::EnvenomPower(int32_t i, Character* own): Power(PID::envenom, i, true, false, own){}
void EnvenomPower::onUnblockedAttack(Character* target, Game& game){
    std::shared_ptr<Effect> a = std::make_shared<PowerManip>(PowerManip(EID::gain, magnitude, TID::enemy, PID::poison));
    std::deque<Character*> targets = {target};
    Event ev (a, owner, targets, owner);
    game.stackEvent(ev);
}

EnergizedPower::EnergizedPower(int32_t i, Character* own): Power(PID::energized, i, true, false, own){}
void EnergizedPower::onTurnStart(Game& game){
    std::shared_ptr<Effect> a = std::make_shared<CombatAction>(CombatAction(EID::energy, magnitude, TID::player));
    Event ev(a, owner, {owner}, owner);
    game.enqueueEvent(ev);
    eliminate();
}
InfiniteBladesPower::InfiniteBladesPower(int32_t i, Character* own): Power(PID::infinite_blades, i, true, false, own){}
void InfiniteBladesPower::onTurnStart(Game& game){
    std::shared_ptr<Effect> a = std::make_shared<CreateCard>(CreateCard(magnitude, CID::Shiv, PileID::hand, Position::top));
    Event ev(a,owner,{owner},owner);
    game.enqueueEvent(ev);
}

MachineLearningPower::MachineLearningPower(int32_t i, Character* own): Power(PID::machine_learning, i, true, false, own){}
void MachineLearningPower::onTurnStart(Game& game){
    std::shared_ptr<Effect> a = std::make_shared<CombatAction>(CombatAction(EID::draw, magnitude, TID::self));
    Event ev (a, owner, {owner}, owner);
    game.enqueueEvent(ev);
}

MetallicizePower::MetallicizePower(int32_t i, Character* own): Power(PID::metallicize, i, true, false, own){}
void MetallicizePower::onTurnEnd(Game& game){
    std::shared_ptr<Effect> a = std::make_shared<CombatAction>(CombatAction(EID::block, magnitude, TID::self));
    Event ev (a, owner, {owner}, owner);   
    game.enqueueEvent(ev);
}

OmegaPower::OmegaPower(int32_t i, Character* own): Power(PID::omega, i, true, false, own){}
void OmegaPower::onTurnEnd(Game& game){
    std::deque<Character*> targets = game.selectTargets(TID::enemy_all, owner);
    std::shared_ptr<Effect> a = std::make_shared<CombatAction>(CombatAction(EID::damage, magnitude, TID::enemy_all));
    Event ev (a, owner, targets, owner);
    game.enqueueEvent(ev);
}

PoisonPower::PoisonPower(int32_t i, Character* own): Power(PID::poison, i, true, true, own){}
void PoisonPower::onTurnEnd(Game& game){} //does nothing on turn end
void PoisonPower::onTurnStart(Game& game){
    std::shared_ptr<Effect> a = std::make_shared<CombatAction>(CombatAction(EID::hp, -magnitude, TID::self));
    Event ev (a, owner, {owner}, owner);
    game.enqueueEvent(ev);
    changeMagnitude(-1);
}

RitualPower::RitualPower(int32_t i, Character* own): Power(PID::ritual, i, true, false, own){}
void RitualPower::onTurnEnd(Game& game){
    std::shared_ptr<Effect> a = std::make_shared<PowerManip>(PowerManip(EID::gain, magnitude, TID::self, PID::strength));
    Event ev (a, owner, {owner}, owner);
    game.enqueueEvent(ev);
}

ShackledPower::ShackledPower(int32_t i, Character* own): Power(PID::shackled, i, true, false, own){}
void ShackledPower::onTurnEnd(Game& game){
    std::shared_ptr<Effect> a = std::make_shared<PowerManip>(PowerManip(EID::gain, magnitude, TID::self, PID::strength));
    Event ev (a, owner, {owner}, owner);
    game.enqueueEvent(ev);
    eliminate();
}

StrengthPower::StrengthPower(int32_t i, Character* own): Power(PID::strength, i , true, false, own){ }
int32_t StrengthPower::modOutDamageAdd(int32_t base){
    return base +  magnitude;
}

StrengthDownPower::StrengthDownPower(int32_t i, Character* own): Power(PID::strength_down, i , true, false, own){}
void StrengthDownPower::onTurnEnd(Game& game){
    std::shared_ptr<Effect> a = std::make_shared<PowerManip>(PowerManip(EID::gain, -magnitude, TID::self, PID::strength));
    Event ev (a, owner, {owner}, owner);
    game.enqueueEvent(ev);
    eliminate();
}

ThornsPower::ThornsPower(int32_t i, Character* own): Power(PID::thorns, i, true, false, own){}
void ThornsPower::onHit(Character* source, Game& game){
    std::shared_ptr<Effect> a = std::make_shared<CombatAction>(CombatAction(EID::damage, magnitude, TID::enemy));
    Event ev (a, owner, {source}, owner);
    game.stackEvent(ev);
}

VulnerablePower::VulnerablePower(int32_t i, Character* own):Power(PID::vulnerable, i, false, true, own){}
int32_t VulnerablePower::modIncDamage(int32_t base){
    return base * (100 + VULNERABLE_PCENT)/100;
}

WeakPower::WeakPower(int32_t i, Character* own): Power(PID::weak, i, false, true, own){}
int32_t WeakPower::modOutDamageMult(int32_t base){
    return base * (100 - WEAK_PCENT)/100;
}


std::unique_ptr<Power> Power::createPower(PID id, int32_t magnitude, Character* owner){
    switch(id){
        case PID::accuracy: return std::make_unique<AccuracyPower>(magnitude,owner);
        case PID::berserk: return std::make_unique<BerserkPower>(magnitude, owner);
        case PID::curl_up: return std::make_unique<CurlUpPower>(magnitude, owner);
        case PID::dexterity: return std::make_unique<DexterityPower>(magnitude,owner);
        case PID::dexterity_down: return std::make_unique<DexterityDownPower>(magnitude,owner);
        case PID::draw_card: return std::make_unique<DrawCardPower>(magnitude, owner);
        case PID::frail: return std::make_unique<FrailPower>(magnitude,owner);
        case PID::fasting: return std::make_unique<FastingPower>(magnitude,owner);
        case PID::energized: return std::make_unique<EnergizedPower>(magnitude,owner);
        case PID::envenom: return std::make_unique<EnvenomPower>(magnitude, owner);
        case PID::infinite_blades: return std::make_unique<InfiniteBladesPower>(magnitude,owner);
        case PID::machine_learning: return std::make_unique<MachineLearningPower>(magnitude, owner);
        case PID::metallicize: return std::make_unique<MetallicizePower>(magnitude, owner);
        case PID::omega: return std::make_unique<OmegaPower>(magnitude, owner);
        case PID::poison: return std::make_unique<PoisonPower>(magnitude, owner);
        case PID::ritual: return std::make_unique<RitualPower>(magnitude, owner);
        case PID::shackled: return std::make_unique<ShackledPower>(magnitude,owner);
        case PID::strength: return std::make_unique<StrengthPower>(magnitude, owner);
        case PID::strength_down: return std::make_unique<StrengthDownPower>(magnitude, owner);
        case PID::thorns: return std::make_unique<ThornsPower>(magnitude, owner);
        case PID::vulnerable: return std::make_unique<VulnerablePower>(magnitude,owner);
        case PID::weak: return std::make_unique<WeakPower>(magnitude, owner);
        default:
            throw std::runtime_error("Invalid PID");
    }
}

