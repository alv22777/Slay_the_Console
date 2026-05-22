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

Color Character::getColor(){return col;}

void Character::setName(std::string n){name = n;}

void Character::setAttribute(Attribute att, int value){
    switch(att){
        case Attribute::hp: HP = value; break;
        case Attribute::max_hp: max_HP = value; break;
        case Attribute::block: block = value; break;
    }
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