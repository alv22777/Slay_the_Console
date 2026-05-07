#include "ui/colors.h"

std::string color(Color c, std::string input){
    return  
    
    "\033[38;5;"+
    std::to_string(static_cast<int>(c))+
    'm'+input+"\033[0m"
    ;
}

//"\033[;33m The Ironclad \033[m";