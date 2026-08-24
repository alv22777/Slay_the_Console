#ifndef ENEMY_H
#define ENEMY_H

#include "character/character.h"
#include "ui/colors.h"
#include "character/intent.h"
#include <deque>
enum class EnemyID{
    green_louse, red_louse, cultist, jaw_worm, gremlin_nob
};
struct EnemyBlueprint{
    std::string name;
    int max_hp;
    Color color;
    std::deque<Intent> intents;
};

class Game;
class Enemy: public Character{

    std::deque<Intent> possible_intents;
    Intent next_intent;
    
    public:

    Enemy(EnemyBlueprint bp);
    void act(Game& game);
    void displayStatus(Game& game);
    void displayIntent(Game& game);
    void chooseIntent(Game& game);

    static std::unique_ptr<Enemy> createEnemy(EnemyID id);

    Enemy(const Enemy&) = delete;
    Enemy& operator=(const Enemy&) = delete;

    Enemy(Enemy&&) noexcept = default;
    Enemy& operator=(Enemy&&) noexcept = default;

    ~Enemy() noexcept override = default;
};

#endif