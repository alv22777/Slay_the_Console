#ifndef POWER_H
#define POWER_H


#include "stdint.h"
#include <iostream>
#include <memory>
class Character; class Game;


enum class PID{
    //outgoing damage additive
    accuracy, strength,
    //Outgoing damage multiplicative
    weak, wrath, phantasmal, pen_nib, 

    //Modify incoming damage
    vulnerable, lock_on, surrounded, buffer, intangible,

    //Modify block (from self)
    frail, barricade, blur, dexterity,
    
    //Modify energy
    deva, berserk, energized, fasting,
    
    //Modify other powers
    ritual, demon, wraith, biased, devotion, phantasmal_killer,

    //Card draw mod
    draw_next, machine_learning, 

    //Trigger on hit
    thorns, curl_up,
    //Character specific powers
    //The Ironclad
    //The Silent
    poison,
    //The Defect
    focus,

    //On Turn End
    omega,
};

class Power{
    
    public:
    Power(PID id, int32_t i, bool in, bool d, Character* own);
    
    
    
    int32_t getMagnitude() const;
    PID getID() const;
    Character* getOwner();
    bool isExpired();
    static std::unique_ptr<Power> createPower(PID id, int32_t magnitude, Character* owner);
    
    static std::string IDtoString(PID id, bool plain_text);
    void display();
    void changeMagnitude(int32_t delta);
    void eliminate();
    virtual ~Power() noexcept = default;


    //Hooks
    virtual void onTurnStart(Game& game);
    virtual void onTurnEnd(Game& game);
    
    virtual int32_t modOutDamageAdd(int32_t base);
    virtual int32_t modOutDamageMult(int32_t base);
    virtual int32_t modIncDamage(int32_t base);
    virtual int32_t modBlockGainAdd(int32_t base);
    virtual int32_t modBlockGainMult(int32_t base);
    
    virtual void onHit(Character* source, Game& game);

    protected:
    PID ID;
    int32_t magnitude; //Can be negative
    bool stacks_intensity; bool stacks_duration; //Determine if stacking this Power increases intensity or duration.
    Character* owner;
};

class WeakPower: public Power{    
    public:
    int32_t modOutDamageMult(int32_t base) override;
    WeakPower(int32_t i, Character* own);
};

class StrengthPower: public Power{
    public:
    int32_t modOutDamageAdd(int32_t base) override;
    StrengthPower(int32_t i, Character* own);
};

class VulnerablePower: public Power{
    public:
    int32_t modIncDamage(int32_t base) override;
    VulnerablePower(int32_t i, Character* own);
};

class RitualPower: public Power{
    public:
    RitualPower(int32_t i, Character* own);
    void onTurnEnd(Game& game) override;
};

class FrailPower: public Power{
    public:
    FrailPower(int32_t i, Character* own);
    int32_t modBlockGainMult(int32_t base) override;
};

class PoisonPower: public Power{
    public:
    PoisonPower(int32_t i, Character* own);
    void onTurnStart(Game& game) override;
    void onTurnEnd(Game& game) override;
};

class ThornsPower: public Power{
    public:
    ThornsPower(int32_t i, Character* own);
    void onHit(Character* source, Game& game) override;
};

class AccuracyPower: public Power{
    public:
    AccuracyPower(int32_t i, Character* own);
    int32_t modOutDamageAdd(int32_t base) override;
};

class DexterityPower: public Power{
    public:
    DexterityPower(int32_t i, Character* own);
    int32_t modBlockGainAdd(int32_t base);
};

class OmegaPower: public Power{
    public:
    OmegaPower(int32_t i, Character* own);
    void onTurnEnd(Game& game);
};

class FastingPower: public Power{
    public:
    FastingPower(int32_t i, Character* own);
    void onTurnStart(Game& game);
};

class CurlUpPower: public Power{
    public:
    CurlUpPower(int32_t i, Character* own);
    void onHit(Character* source, Game& game);
};

#endif


