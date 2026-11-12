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
    target, //done for cards that need to select a target to do checks on that target but don't actually do anything to the target.
    none
};

enum class TID{player, enemy, enemy_all, random_enemy, self, none};
enum class Predicate{target_has_power, target_has_block, cards_discarded, fatal, cards_played, target_intents_to_attack, none};
struct Condition{
    Predicate predicate;
    int32_t threshold;
    TID checked_target;

    PID power;
    Condition(Predicate p, int32_t t, TID c): predicate(p), threshold(t), checked_target(c){}
    Condition(Predicate p, PID pw, TID c): predicate(p), threshold(1), power(pw), checked_target(c){}
    Condition(Predicate p, TID c): predicate(p), threshold(0), checked_target(c){}
    Condition(): predicate(Predicate::none), threshold(0), checked_target(TID::none){}
    
    bool check(Game* game, Character* target);
};
enum class Position;

// struct EventRegistry {
//     EffectReport result;
//     int32_t ID;
// }
// EventHistory{
//     deque<EventRegistry> history;
//     public: EffectReport seek(int32_t id);
// }

struct EffectReport{
    int32_t damage_dealt=0;
    int32_t block_gained=0;
    int32_t hp_delta=0;

    int32_t energy_gained = 0;
    int32_t cards_drawn = 0;
    int32_t cards_transferred = 0;

    CID card_added;
    int32_t cards_added = 0;
    

    Character* single_target = nullptr;

    PID power_gained;
    bool target_died = false;
    bool fatal = false;
};

class Effect{
    protected:
    EID type;
    int magnitude;
    TID target_type;
    Condition condition;

    public:
    Effect(EID t, int m, TID tar);

    virtual EffectReport apply(std::deque<Character*> target, Character* source, Game& game, Character* check); //Applies this effect to the target character. 
    EID getType();
    TID getTarget();
    bool isSingleTarget();
    int getMagnitude();
    Condition getCondition();
    void setMagnitude(int n);

    std::string log(std::deque<Character*> target, Character* source, EffectReport report);

	virtual ~Effect() noexcept = default;
};

class CombatAction: public Effect{
    public:
    CombatAction(EID t, int m, TID tar);
    CombatAction(EID t, int m, TID tar, Condition cond);
    EffectReport apply(std::deque<Character*> target, Character* source, Game& game, Character* check) override;
    ~CombatAction() noexcept override = default;
};

class RunAction: public Effect{
    private:
    public:
    RunAction(EID t, int m);
    RunAction(EID t, int m, Condition cond);

    EffectReport apply(std::deque<Character*> target, Character* source, Game& game, Character* check) override;
     ~RunAction() noexcept override = default;
};

class CreateCard: public Effect{
    CID card;
    PileID target_pile;
    Position position;
    
    public:
    //add m cards with CID c to target Pile
    CreateCard(int m, CID c, PileID tar_p, Position pos); 
    CreateCard(int m, CID c, PileID tar_p, Position pos, Condition cond); 
    
    CID getCID();
    PileID getTargetPile();

    EffectReport apply(std::deque<Character*> target, Character* source, Game& game, Character* check) override;

    ~CreateCard() noexcept override = default;
};

class CardTransfer: public Effect{
    PileID source_pile;
    PileID target_pile;
    public:
    //move m cards from source pile to target pile
    CardTransfer(EID t, int m, PileID src_p, PileID tar_p);
    CardTransfer(EID t, int m, PileID src_p, PileID tar_p, Condition cond);
    PileID getSourcePile();
    PileID getTargetPile();

    EffectReport apply(std::deque<Character*> target, Character* source, Game& game, Character* check) override;

    ~CardTransfer() noexcept override = default;
};

class PowerManip: public Effect{
    PID power;

    public:
    PowerManip(EID t, int m, TID tar, PID p);
    PowerManip(EID t, int m, TID tar, PID p, Condition cond);
    PID getPID();

    EffectReport apply(std::deque<Character*> target, Character* source, Game& game, Character* check) override;

    ~PowerManip() noexcept override = default;
};

#endif