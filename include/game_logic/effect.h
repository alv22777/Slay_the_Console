#ifndef EFFECT_H
#define EFFECT_H

class Game; class Character;

enum class EffectType{damage, block, draw, discard, exhaust, energy, strength, dexterity, hp};

class Effect{
    EffectType type;
    int magnitude; //For block, it's the amount of block. For draw and discard, it's the number of cards to draw/discard. For exhaust, it's the number of cards to exhaust. For energy, it's the amount of energy to gain/lose (negative means lose).   
    public:
    Effect(EffectType t, int m); //Effect constructor, initializes type and magnitude.
    void apply(Character* target, Character& source, Game& game); //Applies this effect to the target character. 

};

#endif