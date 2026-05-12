#ifndef ENEMY_H
#define ENEMY_H

#include "character/character.h"
#include "ui/colors.h"
#include "character/intent.h"
#include <deque>

class Game;
class Enemy: public Character{

    std::deque<Intent> possible_intents;
    Intent next_intent;


    public:
    Enemy(std::string n, int mHP, Color c, std::deque<Intent> p_i);
    void act(Game& game);
    void displayStatus();
    void chooseIntent(Game& game);
    

    ~Enemy() noexcept override = default;


};

#endif