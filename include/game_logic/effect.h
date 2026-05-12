#ifndef EFFECT_H
#define EFFECT_H

#include<deque>
#include<iostream>
class Game; class Character;

enum class EffectType{damage, block, draw, discard, exhaust, energy, strength, dexterity, hp};
enum class TargetType{ally, ally_all, enemy, enemy_all, random_enemy, self, none};


class Effect{
    EffectType type;
    TargetType target_type;
    int magnitude;
     
    public:
    Effect(EffectType t, int m, TargetType tar); //Effect constructor, initializes type and magnitude.
    void apply(std::deque<Character*> target, Character& source, Game& game); //Applies this effect to the target character. 
    EffectType getType();
    TargetType getTarget();
    int getMagnitude();
    std::string log(std::deque<Character*> target, Character& source);
};

#endif