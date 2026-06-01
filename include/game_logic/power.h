#ifndef POWER_H
#define POWER_H


#include "stdint.h"
#include <iostream>
#include <memory>
class Character;


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
    deva, berserk, energized, 
    
    //Modify other powers
    ritual, demon, wraith, biased, devotion, phantasmal_killer,

    //Card draw mod
    draw_next, machine_learning, 

    //Character specific powers
    //The Ironclad
    //The Silent
    poison,
    //The Defect
    focus,
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
    virtual void onTurnStart();
    virtual void onTurnEnd();
    virtual int32_t modOutDamageAdd(int32_t base);
    virtual int32_t modOutDamageMult(int32_t base);
    virtual int32_t modIncDamage(int32_t base);
    virtual int32_t modBlockGain(int32_t base);
    
    protected:
    PID ID;
    int32_t magnitude; //Can be negative
    bool stacks_intensity; bool stacks_duration; //Determine if stacking this Power increases intensity or duration.
    Character* owner;
};

class Weak: public Power{    
    public:
    int32_t modOutDamageMult(int32_t base) override;
    Weak(int32_t i, Character* own);
};

class Strength: public Power{
    public:
    int32_t modOutDamageAdd(int32_t base) override;
    Strength(int32_t i, Character* own);
};

class Vulnerable: public Power{
    public:
    int32_t modIncDamage(int32_t base) override;
    Vulnerable(int32_t i, Character* own);
};

class Ritual: public Power{
    public:
    Ritual(int32_t i, Character* own);
    void onTurnEnd() override;
};

class Frail: public Power{
    public:
    Frail(int32_t i, Character* own);
    int32_t modBlockGain(int32_t base);
};


#endif

