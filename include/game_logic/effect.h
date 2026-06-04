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
    damage, block, energy, hp, 
    draw, discard, exhaust, cards_bottom, cards_top, expertise,
    gain, addCard,
    none
};

enum class TID{player, enemy, enemy_all, random_enemy, self, none};

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
    EID type;
    TID target_type;
    int magnitude;
    std::optional<PID> power;
    std::optional<CID> card;
    std::optional<PileID> source_pile;
    std::optional<PileID> target_pile;


    public:
    Effect(EID t, int m, TID tar); //Normal effect
    Effect(EID t, int m, TID tar, PID p);//Gain Power effect
    Effect(EID t, int m, CID c, PileID tar_p);//add m cards with CID c to target Pile
    Effect(EID t, int m, PileID src_p, PileID tar_p);//move m cards from source pile to target pile


    EffectReport apply(std::deque<Character*> target, Character* source, Game& game); //Applies this effect to the target character. 
    EID getType();
    TID getTarget();
    bool isSingleTarget();
    int getMagnitude();
    std::string log(std::deque<Character*> target, Character* source, EffectReport report);
};

#endif