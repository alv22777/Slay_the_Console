
#include "character/enemy.h"
#include "character/intent.h"
#include "ui/colors.h"
#include "game_logic/effect.h"
#include "game_logic/game.h"

#include <iostream>

Enemy::Enemy(std::string n, int mHP, Color c, std::deque<Intent> p_i): 
    Character(n,mHP,c), possible_intents(p_i), next_intent(p_i[0]){}

void Enemy::displayStatus(Game& game){
    Character::displayStatus();
    displayIntent(game);
    std::cout<<'\n'<<"   ";
    Character::displayPowers();
    std::cout<<'\n';
}

void Enemy::act(Game& game){

    std::vector<Effect> &actions = next_intent.getActions();    
    if(actions.empty()){return;}
    game.resolveEffects(*this, actions);
    
}

void Enemy::displayIntent(Game& game){
    
    
    std::vector<Effect> &actions = next_intent.getActions(); 
    
    int n = 0;
    for(Effect e:actions){ if(e.getType()==EID::damage){n++;} } //get number of hits
    
    bool displayedAttack = false;
    for(Effect e: actions){

        switch(e.getType()){

            case EID::block: std::cout<<"("<<color(Color::block," 🛡️ ")<<")"; break;
            
            case EID::damage:{
                
                int32_t damage = game.calculateIntentDamage(e.getMagnitude(), this);
                if(!displayedAttack){
                    std::cout<<"("<<color(Color::attack,  "🗡️ "+std::to_string(damage) );

                    if(n>1){ std::cout<<color(Color::attack, "x"+std::to_string(n)); }

                    std::cout<<")";

                    displayedAttack = true;
                }

                break;
            }

            case EID::gain: {
                if(e.getTarget()==TID::player){ std::cout<<"( "<<color(Color::debuff, "🠋")<<" )"; }
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