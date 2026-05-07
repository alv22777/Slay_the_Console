
#include "character/enemy.h"
#include <iostream>

Enemy::Enemy(std::string n, int mHP): Character(n,mHP){}


void Enemy::displayStatus(){
    std::cout<<getName()<<" HP "<<HP<<"/"<<max_HP<<" Block "<<block<<"\n";
}