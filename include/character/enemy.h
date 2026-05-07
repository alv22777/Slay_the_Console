#ifndef ENEMY_H
#define ENEMY_H

#include "character/character.h"
#include "ui/colors.h"

class Enemy: public Character{

    //std::deque<Intent> Intents;

    public:
    Enemy(std::string n, int mHP, Color c);

    void displayStatus();
    ~Enemy() noexcept override = default;
};

#endif