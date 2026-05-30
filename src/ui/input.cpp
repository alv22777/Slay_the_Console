#include "ui/input.h"
#include "ui/colors.h"
#include<cctype>
#include<conio.h>

int inputInt(int min, int max, bool mandatory){
    int choice; bool valid=false;
    
    while(!valid){

        std::cin>>choice;

        if(std::cin.fail()){
            std::cout<<"Invalid input!\n";
            std::cin.clear(); std::cin.ignore(1000,'\n');
            if(!mandatory){return INT_MAX;}
            continue;       
        }
        if(!(min <= choice && choice <= max)){
            std::cout<<"Invalid input!\n"; std::cin.ignore(1000,'\n');
            if(!mandatory){return INT_MAX;}
            continue;
        }
        
        std::cin.ignore(1000,'\n');
        valid = true;
    }
    return choice;
}

char inputChar(){
    return tolower(_getch());
}

int characterSelect(){
    std::cout << "Please select your character:\n";
    std::cout<<color(Color::red, "1. The Ironclad\n")<<color(Color::green, "2. The Silent\n")<<
    color(Color::blue, "3. The Defect\n")<<color(Color::purple, "4. The Watcher\n");
    return inputInt(1,4, true);
}