#ifndef EFFECT_H
#define EFFECT_H

#include<deque>
#include<iostream>
#include<optional>

#include "stdint.h"
class Game; class Character; enum class PID; class Power; enum class CID; enum class PileID;

/*
exhume: n cards go from exhaust to hand.
hologram: n cards go from discard to hand.
seek: n cards go from draw to hand.
headbutt: n cards go from discard to draw top.
forethought: n cards go from hand to draw bot.
expertise: target player draws cards until hand size is n.
*/
enum class EID{
    damage, block, energy, hp, max_hp,
    draw, discard, exhaust, exhaust_self, random_card_transfer, cards_bottom, cards_top, expertise,
    gain, lose,
    add_card_bot, add_card_top, shuffleCard,
    
    none
};

enum class TID{player, enemy, enemy_all, random_enemy, self, none};
enum class Condition{target_has_power, cards_discarded, fatal, cards_played, target_intents_to_attack, none};
enum class Position;

struct EffectReport{
    int32_t damage_dealt=0;
    int32_t block_gained=0;
    int32_t hp_delta=0;

    int32_t energy_gained = 0;
    int32_t cards_drawn = 0;
    int32_t cards_transferred = 0;

    CID card_added;
    int32_t cards_added = 0;
    
    PID power_gained;
    bool target_died = false;
    bool fatal = false;
};

class Effect{
    protected:
    EID type;
    int magnitude;
    TID target_type;
    
//  std::optional<Condition> condition;

    public:
    Effect(EID t, int m, TID tar);

    virtual EffectReport apply(std::deque<Character*> target, Character* source, Game& game); //Applies this effect to the target character. 
    EID getType();
    TID getTarget();
    bool isSingleTarget();
    int getMagnitude();

    void setMagnitude(int n);

    std::string log(std::deque<Character*> target, Character* source, EffectReport report);

	virtual ~Effect() noexcept = default;
};

class CombatAction: public Effect{
    private:
    
    public:
    CombatAction(EID t, int m, TID tar);
    EffectReport apply(std::deque<Character*> target, Character* source, Game& game) override;
    ~CombatAction() noexcept override = default;
};

class RunAction: public Effect{
    private:
    public:
    RunAction(EID t, int m);
    EffectReport apply(std::deque<Character*> target, Character* source, Game& game) override;
     ~RunAction() noexcept override = default;
};

class CreateCard: public Effect{
    CID card;
    PileID target_pile;
    Position position;
    
    public:
    //add m cards with CID c to target Pile
    CreateCard(int m, CID c, PileID tar_p, Position pos); 
    
    CID getCID();
    PileID getTargetPile();

    EffectReport apply(std::deque<Character*> target, Character* source, Game& game) override;

    ~CreateCard() noexcept override = default;
};

class CardTransfer: public Effect{
    PileID source_pile;
    PileID target_pile;
    public:
    //move m cards from source pile to target pile
    CardTransfer(EID t, int m, PileID src_p, PileID tar_p);
    PileID getSourcePile();
    PileID getTargetPile();

    EffectReport apply(std::deque<Character*> target, Character* source, Game& game) override;

    ~CardTransfer() noexcept override = default;
};

class PowerManip: public Effect{
    PID power;

    public:
    PowerManip(EID t, int m, TID tar, PID p);
    PID getPID();

    EffectReport apply(std::deque<Character*> target, Character* source, Game& game) override;

    ~PowerManip() noexcept override = default;
};

#endif