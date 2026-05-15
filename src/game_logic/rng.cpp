#include "game_logic/rng.h"
RNG::RNG(uint64_t s): engine(s), seed(s){}

//Returns a random integer between min and max, inclusive. Very useful for things like random enemy targets.
int RNG::nextInt(int min, int max){
    std::uniform_int_distribution<uint64_t> dist(min, max);
    return dist(engine);
}
//Returns a random float between min and max. Useful for things like random chances and percentages.
float RNG::nextFloat(float min, float max){
    std::uniform_real_distribution<float> dist(min, max);
    return dist(engine);
}
//Chance function, mostly for convenience. 
bool RNG::chance(float probability){
    return nextFloat(0.0f, 1.0f) < probability;
}

uint64_t RNG::getSeed(){return seed;}

void RNG::setSeed(uint64_t s){
    seed = s;
    engine = std::mt19937_64(s);
}

std::string RNG::base36(){
    uint64_t n = seed; uint64_t remainder;
    std::string result; char pushed;
    int i=1;
    while(n>=36){

        remainder = n%36;
        n /= 36;
        
        (remainder<10)? pushed = '0' + remainder : pushed = 'A' - 10 + remainder ;
        result.push_back(pushed);
    }
    
    remainder = n%36;
    n /= 36;
    (remainder<10)? pushed = '0' + remainder : pushed = 'A' - 10 + remainder ;
    result.push_back(pushed);
    std::reverse(result.begin(),result.end());

    return result;
}