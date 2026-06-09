#include "character/character.h"
#include "data/constants.h"
#include "game_logic/game.h"
#include "ui/formatting.h"
#include "game_logic/power.h"

#include <iostream>


Character::Character(std::string N, int MHP, Color c)
    :name(N), max_HP(MHP), HP(MHP),block(0), col(c){}

std::string Character::getName() {return name;}

int Character::getAttribute(Attribute a){
    switch(a){
        case Attribute::hp: return HP;
        case Attribute::max_hp: return max_HP;
        case Attribute::block: return block;
        default: return 0;
    }
}

Color Character::getColor(){return col;}

const std::deque<std::unique_ptr<Power>>& Character::getPowers(){return powers;}

void Character::setName(std::string n){name = n;}

void Character::setAttribute(Attribute att, int value){
    switch(att){
        case Attribute::hp: HP = value; break;
        case Attribute::max_hp: max_HP = value; break;
        case Attribute::block: block = value; break;
    }
}

void Character::displayStatus(){
    //STATUS BAR
    std::cout<<color(col, padRight(getName(),15));
    std::cout<<color(Color::hp, " ♥" +
        padLeft(std::to_string(HP),3) +"/"+
        padRight(std::to_string(max_HP),3)
    );
    std::cout<<color(Color::block, " 🛡️ "+std::to_string(block)+" ");
}

void Character::displayPowers(){
    std::cout<<"{ ";
    for(std::unique_ptr<Power>& p: powers){
        p->display(); std::cout<< " ";
    }
    std::cout<<"}";
}

//Changes chosen attribute by an amount delta.
int32_t Character::changeAttribute(Attribute a, int Delta){
    int d = Delta;

    switch(a){
        case Attribute::hp: 

            if(HP+Delta>max_HP){d = max_HP-HP;}

            HP += Delta; 
            if(HP>max_HP){HP = max_HP;}
            break;

        case Attribute::max_hp: 

            max_HP += Delta;


            if(Delta>0){HP += Delta;}
            else{ if(HP>max_HP){HP = max_HP;}}
            
            if(max_HP<1){max_HP=1; HP = 1; d = max_HP-1;}

            break;

        case Attribute::block: 
            if(block+Delta>MAX_BLOCK){d = MAX_BLOCK-block;}

            block += Delta; 
            if(block>MAX_BLOCK){block = MAX_BLOCK;}
            break;
    }
    return d;
}

bool Character::isAlive(){return (HP>0);}

int32_t Character::takeDamage(int magnitude){
    uint32_t unblocked = 0;
    if(magnitude>block){//Unblocked damage was dealt. 
        unblocked = magnitude - block;
        HP -= unblocked; 
        block = 0;
    }
    else{
        block -= magnitude; 
    }
    return unblocked;               
}



int32_t Character::gainBlock(int magnitude){
    uint32_t gained = 0;

    if(block+magnitude>MAX_BLOCK){
        gained = MAX_BLOCK-block;
        block = MAX_BLOCK;               
    }
    else{
        gained = magnitude;
        block += magnitude; 
    }
    
    return gained;
}

void Character::hpChange(int magnitude){
    HP+=magnitude;
    if(HP>max_HP){HP = max_HP;} //Don't go over max HP!
}

void Character::addPower(PID p, int m){
    std::unique_ptr<Power> P = Power::createPower(p, m, this);
    auto it = std::find_if(powers.begin(), powers.end(), [&](const std::unique_ptr<Power>& a){
        return a->getID() == p;
    }); 
    if(it != powers.end()){ //Power already in list
        (*it)->changeMagnitude(m);
    }
    else{powers.push_back(std::move(P));}
}

void Character::removePower(int pos){
    powers.erase(powers.begin()+pos);
}   
void Character::removeAllPowers(){
    powers.clear();
}

void Character::removeInvalidPowers(){
    powers.erase(std::remove_if(powers.begin(), powers.end(), [](const std::unique_ptr<Power>& p){
        return p->isExpired(); 
    }), powers.end());
}

void Character::onHit(Character* source, Game& game){
    for(auto&p: powers){p->onHit(source, game);}
}

int32_t Character::modOutDamage(int32_t base){ 
    for(auto& p: powers){ base = p->modOutDamageAdd(base); } 
    for(auto& p: powers){ base = p->modOutDamageMult(base); } 
    return base;
}   

int32_t Character::modIncDamage(int32_t base){ for(auto& p: powers){ base = p->modIncDamage(base); } return base;}

int32_t Character::modBlockGain(int32_t base){ 
    for(auto& p: powers){ base = p->modBlockGainAdd(base); }
    for(auto& p: powers){ base = p->modBlockGainMult(base); }
    return base;
}