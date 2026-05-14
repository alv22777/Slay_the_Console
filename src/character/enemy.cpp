
#include "character/enemy.h"
#include "character/intent.h"
#include "ui/colors.h"
#include "game_logic/effect.h"
#include "game_logic/game.h"
#include "ui/formatting.h"

#include <iostream>
#include <iomanip>
Enemy::Enemy(std::string n, int mHP, Color c, std::deque<Intent> p_i): 
    Character(n,mHP,c), possible_intents(p_i), next_intent(p_i[0]){}

void Enemy::displayStatus(){
    std::cout<<std::left<<color(col,padRight(getName(),15));
    std::cout<<std::left<<color(Color::hp, padRight((" HP "+std::to_string(HP)+'/'+std::to_string(max_HP)),10));
    std::cout<<std::left<<color(Color::block, padRight((" Block "+std::to_string(block)),10));
    next_intent.display();
    std::cout<<'\n';
}


void Enemy::act(Game& game){

    std::vector<Effect> actions = next_intent.getActions();

    if(actions.empty()){return;}

    //Initial conditions
    std::deque<Character*> targets = game.selectTargets(actions[0].getTarget(), this);
    TargetType prev_target = actions[0].getTarget();
    bool originalTargetDied = false;
    if(!targets.empty()){        
        for(Effect e : actions){
            // Retarget if needed
            if(
                prev_target != e.getTarget() ||
                e.getTarget() == TargetType::ally_all ||
                e.getTarget() == TargetType::enemy_all ||
                e.getTarget() == TargetType::random_enemy
            )
            {targets = game.selectTargets(e.getTarget(), this); }
            else{if(originalTargetDied){continue;}}
    
            prev_target = e.getTarget();
    
            // Apply only if valid targets exist
            if(!targets.empty()){
                e.apply(targets, *this, game); 
                game.event_log.receive(e.log(targets,*this));
            }
    
            // Check whether reused single target died
            if((e.getTarget() == TargetType::ally || e.getTarget() == TargetType::enemy) && !targets[0]->isAlive() ){ originalTargetDied = true; }
    
            game.removeDeadCharacters();
            if(game.isCombatOver()){break;}
        }
    }
}

void Enemy::chooseIntent(Game& game){
    //For now, this just chooses a random intent. Rules and AI will be added in the future.
    next_intent = possible_intents[game.rng.nextInt(0,possible_intents.size()-1)];
}