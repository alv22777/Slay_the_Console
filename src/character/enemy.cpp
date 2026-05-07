
#include "character/enemy.h"
#include "ui/colors.h"
#include "ui/formatting.h"
#include <iostream>
#include <iomanip>
Enemy::Enemy(std::string n, int mHP, Color c): Character(n,mHP,c){}


void Enemy::displayStatus(){
    
    std::cout<<std::left<<color(col,padRight(getName(),15));
    std::cout<<std::left<<color(Color::hp, padRight((" HP "+std::to_string(HP)+'/'+std::to_string(max_HP)),10));
    std::cout<<std::left<<color(Color::block, padRight((" Block "+std::to_string(block)),10))<<'\n';

}