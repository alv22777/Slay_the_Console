#ifndef EFFECT_H
#define EFFECT_H

#include<deque>
#include<iostream>
#include<optional>

#include "stdint.h"
class Game; class Character; enum class PID; class Power; enum class CID;

/*
exhume: n cards go from exhaust to hand.
hologram: n cards go from discard to hand.
seek: n cards go from draw to hand.
headbutt: n cards go from discard to draw top.
forethought: n cards go from hand to draw bot.
expertise: target player draws cards until hand size is n.
*/
enum class EffectType{
    damage, block, energy, hp, 
    draw, discard, exhaust, exhume, hologram, seek, headbutt, forethought, expertise,
    gain, addCard,
    none
};

enum class TargetType{player, enemy, enemy_all, random_enemy, self, none};

struct EffectReport{
    int32_t damage_dealt=0;
    int32_t block_gained=0;
    int32_t hp_delta=0;

    int32_t energy_gained = 0;
    int32_t cards_drawn = 0;
    int32_t cards_exhausted = 0;
    int32_t cards_discarded = 0;

    CID card_added;
    int32_t cards_added = 0;
    
    PID power_gained;
    bool target_died = false;
    bool fatal = false;
};

class Effect{
    EffectType type;
    TargetType target_type;
    int magnitude;
    std::optional<PID> power;
    std::optional<CID> card;

    public:
    Effect(EffectType t, int m, TargetType tar); //Normal effect
    Effect(EffectType t, int m, TargetType tar, PID p);//Gain Power effect
    Effect(EffectType t, int m, TargetType tar, CID c);//add card effect

    EffectReport apply(std::deque<Character*> target, Character* source, Game& game); //Applies this effect to the target character. 
    EffectType getType();
    TargetType getTarget();
    bool isSingleTarget();
    int getMagnitude();
    std::string log(std::deque<Character*> target, Character* source, EffectReport report);
};

#endif