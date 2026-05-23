
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
    Character::displayStatus();
    next_intent.display();
    std::cout<<'\n';
}

void Enemy::act(Game& game){

    std::vector<Effect> &actions = next_intent.getActions();    
    if(actions.empty()){return;}
    game.resolveEffects(*this, actions);

}

void Enemy::chooseIntent(Game& game){
    //For now, this just chooses a random intent. Rules and AI will be added in the future.
    next_intent = possible_intents[game.rng.nextInt(0,possible_intents.size()-1)];
}