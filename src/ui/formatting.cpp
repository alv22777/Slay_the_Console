#include "ui/formatting.h"

std::string padRight(std::string s, size_t width){
    if(s.size() >= width){
        return s;
    }
    std::string padding(width-s.size(), ' ');
    return s+padding;
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
    if(0<=n && n <= sizeof(pips)){
        return pips[n];
    }
    else{return "["+std::to_string(n)+"]";}
}
