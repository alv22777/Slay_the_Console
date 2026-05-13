#include "ui/input.h"
#include<cctype>


int inputInt(int min, int max){
    int choice; bool valid=false;
    
    while(!valid){

        std::cin>>choice;

        if(std::cin.fail()){
            std::cout<<"Invalid input!\n";
            std::cin.clear(); std::cin.ignore(1000,'\n');
            continue;       
        }
        if(!(min <= choice && choice <= max)){
            std::cout<<"Invalid input!\n"; std::cin.ignore(1000,'\n');
            continue;
        }
        
        
        std::cin.ignore(1000,'\n');
        valid = true;
    }
    return choice;
}

char inputChar(){
    char choice;
    std::cin>>choice;
    return tolower(choice);
}