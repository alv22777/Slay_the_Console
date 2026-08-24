
#include "character/enemy.h"
#include "character/intent.h"
#include "ui/colors.h"
#include "game_logic/effect.h"
#include "game_logic/game.h"
#include "data/constants.h"

#include <iostream>

Enemy::Enemy(EnemyBlueprint bp): 
    Character(bp.name,bp.max_hp,bp.color), possible_intents(bp.intents), next_intent(bp.intents[0]){}

void Enemy::displayStatus(Game& game){
    Character::displayStatus();
    displayIntent(game);
    std::cout<<'\n'<<"   ";
    Character::displayPowers();
    std::cout<<'\n';
}

void Enemy::act(Game& game){
    std::vector<std::shared_ptr<Effect>> actions = next_intent.getActions();    
    for(std::shared_ptr<Effect> e: actions){
        std::deque<Character*> targets = game.selectTargets(e->getTarget(),this);
        Event ev = {e, this, targets};
        game.enqueueEvent(ev);
    }
}

void Enemy::displayIntent(Game& game){
    
    
    std::vector<std::shared_ptr<Effect>> actions = next_intent.getActions(); 
    
    int n = 0;
    for(std::shared_ptr<Effect> e:actions){ if(e->getType()==EID::damage){n++;} } //get number of hits
    
    bool displayedAttack = false;
    for(std::shared_ptr<Effect> e: actions){

        switch(e->getType()){

            case EID::block: std::cout<<"("<<color(Color::block," 🛡️ ")<<")"; break;
            
            case EID::damage:{
                
                int32_t damage = game.calculateIntentDamage(e->getMagnitude(), this);
                if(!displayedAttack){
                    std::cout<<"("<<color(Color::attack,  "🗡️ "+std::to_string(damage) );

                    if(n>1){ std::cout<<color(Color::attack, "x"+std::to_string(n)); }

                    std::cout<<")";

                    displayedAttack = true;
                }

                break;
            }

            case EID::gain: {
                if(e->getTarget()==TID::player){ std::cout<<"( "<<color(Color::debuff, "🠋")<<" )"; }
                else{ std::cout<<"( "<<color(Color::buff  , "🠉")<<" )"; }
                break;
            }

            default: std::cout<<"( "<<color(Color::unknown, "???")<<" )"; break;
        }
    }
}

void Enemy::chooseIntent(Game& game){
    //For now, this just chooses a random intent. Rules and AI will be added in the future.
    next_intent = possible_intents[game.rng.nextInt(0,possible_intents.size()-1)];
}

std::unique_ptr<Enemy> Enemy::createEnemy(EnemyID id){
    switch(id){
        case EnemyID::green_louse: return std::make_unique<Enemy>(green_louse_blueprint);
        case EnemyID::red_louse: return std::make_unique<Enemy>(red_louse_blueprint);
        case EnemyID::cultist: return std::make_unique<Enemy>(cultist_blueprint);
        case EnemyID::jaw_worm: return std::make_unique<Enemy>(jaw_worm_blueprint);
        case EnemyID::gremlin_nob: return std::make_unique<Enemy>(gremlin_nob_blueprint);
        default: throw(std::invalid_argument("Invalid EnemyID passed to Enemy::createEnemy()")); break;
    }
} 