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
        case Attribute::hp: HP = value; std::cout<<"HP set to "<<value<<".\n"; break;
        case Attribute::max_hp: max_HP = value; std::cout<<"Max HP set to "<<value<<".\n"; break;
        case Attribute::block: block = value; break;
    }
}

//Changes chosen attribute by an amount delta.
void Character::changeAttribute(Attribute a, int Delta){
    switch(a){
        case Attribute::hp: 
            HP += Delta;
            std::cout<<name<<" has "<<((Delta>0)? "Gained ":"Lost ")<<abs(Delta)<<" HP!\n"; break; 
            if(HP>max_HP){
                std::cout<<"Can't have more HP than max HP!\n";
                setAttribute(Attribute::hp,max_HP);
            }
            break;
        case Attribute::max_hp: 
            max_HP += Delta; 
            std::cout<<name<<" has "<<((Delta>0)? "Gained ":"Lost ")<<abs(Delta)<<" max HP!\n"; break; 
        case Attribute::block: 
            block += Delta; 
            std::cout<<name<<" has "<<((Delta>0)? "Gained ":"Lost ")<<abs(Delta)<<" block!\n";
            if(block>MAX_BLOCK){
                std::cout<<"Reached maximum block!\n";
                setAttribute(Attribute::block,MAX_BLOCK);
            }
            break;
    }
}

bool Character::isAlive(){return (HP>0);}


