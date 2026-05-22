#ifndef POWER_H
#define POWER_H


#include "stdint.h"

class Power{

    uint32_t intensity;
    bool stackable;
    bool decremented;
    public:
    void trigger();
    void add(uint32_t delta);
    void remove(uint32_t delta);
    void eliminate();
};



#endif