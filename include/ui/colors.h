#ifndef COLORS_H
#define COLORS_H

#include<iostream>

enum class Color{
    red = 1, green = 82, blue = 44, purple = 5, 

    common = 8, uncommon = 12, rare = 226, curse = 240, status = 8,

    hp = 160, block = 6, 
    poison = 28, vulnerable = 124, weak = 240, 
    strength = 1, dexterity = 82, focus = 44,

    lightning = 226, frost = 14, dark = 13, 

    wrath = 124, neutral = 244, calm = 123, divinity = 164,
    
    regular = 250, keyword = 231 

};

std::string color(Color c, std::string input);
#endif

