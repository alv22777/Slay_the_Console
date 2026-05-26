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
    vulnerable, lock_on, surrounded, 

    //Modify block (from self)
    frail, barricade, blur, dexterity,
    
    //Modify energy
    deva, berserk, energized, 
    
    //Modify other powers
    ritual, demon, wraith, biased, devotion, phantasmal_killer,

    //Card draw mod
    draw_next, machine_learning, 
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
    virtual void onPlayerTurnStart();
    virtual void onPlayerTurnEnd();
    virtual void onEnemyTurnStart();
    virtual void onEnemyTurnEnd();
    virtual uint32_t modOutDamage(uint32_t base);
    virtual uint32_t modIncDamage(uint32_t base);

    protected:
    PID ID;
    int32_t magnitude; //Can be negative
    bool stacks_intensity; bool stacks_duration; //Determine if stacking this Power increases intensity or duration.
    Character* owner;
};

class Weak: public Power{    
    public:
    uint32_t modOutDamage(uint32_t base) override;
    Weak(uint32_t i, Character* own);
};

class Vulnerable: public Power{
    public:
    uint32_t modIncDamage(uint32_t base) override;
    Vulnerable(uint32_t i, Character* own);
};

class Ritual: public Power{
    public:
    Ritual(uint32_t i, Character* own);
};


#endif

