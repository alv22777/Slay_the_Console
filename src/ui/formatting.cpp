#include "ui/formatting.h"

std::string padRight(std::string s, size_t width){
    if(s.size() >= width){
        return s;
    }
    std::string padding(width-s.size(), ' ');
    return s+padding;
}
