#include "ui/formatting.h"

std::string padRight(std::string s, size_t width){
    if(s.size() >= width){ return s; }
    std::string padding(width-s.size(), ' ');
    return s+padding;
}

std::string padLeft(std::string s, size_t width){
    if(s.size() >= width){ return s; }
    std::string padding(width-s.size(), ' ');
    return padding + s;
}

std::string center(std::string s, size_t width){
    std::string l; std::string r;
    
    if(s.size() >= width){ return s; }

    size_t padding = (width - s.size())/2 ;
    
    r = (padding%2==0)? std::string(padding, ' '):std::string( padding +1, ' ');
    l = std::string(padding, ' ');
    
    return l + s + r;
}

std::string to_energy(int n){

    std::string pips[51] = {
        "⓪", "①", "②", "③", "④", "⑤", "⑥", "⑦", "⑧", "⑨",
        "⑩", "⑪", "⑫", "⑬", "⑭", "⑮", "⑯", "⑰", "⑱", "⑲", 
        "⑳", "㉑", "㉒", "㉓", "㉔", "㉕", "㉖", "㉗", "㉘","㉙",
        "㉚", "㉛", "㉜", "㉝", "㉞", "㉟", "㊱", "㊲", "㊳", "㊴",
        "㊵", "㊶", "㊷", "㊸", "㊹", "㊺", "㊻", "㊼", "㊽", "㊾", "㊿",
    };
    if(n == -2){return "Ⓧ";}
    if(n == -1){return "⦸";}
    if(0<=n && n <= sizeof(pips)){ return pips[n]; }
    else{return "["+std::to_string(n)+"]";}
}


void clearScreen() {
    // \033[2J clears the screen, \033[H moves cursor to (1,1)
    std::cout << "\033[2J\033[H" << std::flush;
}