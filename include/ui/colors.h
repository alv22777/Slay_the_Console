#ifndef COLORS_H
#define COLORS_H

#include<iostream>

enum class Color{
    red = 1, green = 82, blue = 44, purple = 5, colorless = 244,

    common = 8, uncommon = 14, rare = 226, curse = 61, status = 8,


    hp = 168, block = 6, 
    poison = 28, vulnerable = 124, weak = 240, 
    strength = 1, dexterity = 82, focus = 44,

    lightning = 226, frost = 50, dark = 13, 

    wrath = 124, neutral = 244, calm = 123, divinity = 164,
    
    buff = 123, debuff = 64, attack = 202, unknown = 136,

    regular = 250, keyword = 231 , exhaust = 246,

};

std::string color(Color c, std::string input);
#endif

