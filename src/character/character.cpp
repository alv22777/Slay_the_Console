#include "character/character.h"
#include "data/constants.h"
#include "game_logic/game.h"
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


void Character::setName(std::string n){name = n;}

void Character::setAttribute(Attribute att, int value){
    switch(att){
        case Attribute::hp: HP = value; break;
        case Attribute::max_hp: max_HP = value; break;
        case Attribute::block: block = value; break;
    }
}

//Changes chosen attribute by an amount delta.
void Character::changeAttribute(Attribute a, int Delta){
    switch(a){
        case Attribute::hp: 
            HP += Delta; 
            if(HP>max_HP){setAttribute(Attribute::hp,max_HP);}
            break;
        case Attribute::max_hp: 

            max_HP += Delta;

            if(Delta>0){HP += Delta;}
            else{ if(HP>max_HP){setAttribute(Attribute::hp, max_HP);} }

            if(max_HP<1){setAttribute(Attribute::max_hp, 1); setAttribute(Attribute::hp,1);}

        break;

        case Attribute::block: 
            block += Delta; 
            if(block>MAX_BLOCK){setAttribute(Attribute::block,MAX_BLOCK);}
            break;
    }
}

bool Character::isAlive(){return (HP>0);}

void Character::takeDamage(int magnitude){
    if(magnitude>getAttribute(Attribute::block)){//If the damage > target's block, apply excess damage logic.
        changeAttribute(Attribute::hp,-magnitude+getAttribute(Attribute::block)); 
        setAttribute(Attribute::block,0);   
    }
    else{changeAttribute(Attribute::block,-magnitude);}
}

void Character::gainBlock(int magnitude){
    if(getAttribute(Attribute::block)+magnitude>MAX_BLOCK){
        setAttribute(Attribute::block,MAX_BLOCK);                
    }
    else{changeAttribute(Attribute::block, magnitude);}
}

void Character::hpChange(int magnitude){
    HP+=magnitude;
    if(HP>max_HP){setAttribute(Attribute::hp, max_HP);} //Don't go over max HP!
}