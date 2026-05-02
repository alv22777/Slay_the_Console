#include "rng.h"

RNG::RNG(std::mt19937& s): seed(s){}

//Returns a random integer between min and max, inclusive. Very useful for things like random enemy targets.
int RNG::nextInt(int min, int max){
    std::uniform_int_distribution<int> dist(min, max);
    return dist(seed);
}
//Returns a random float between min and max. Useful for things like random chances and percentages.
float RNG::nextFloat(float min, float max){
    std::uniform_real_distribution<float> dist(min, max);
    return dist(seed);
}
//Chance function, mostly for convenience. 
bool RNG::chance(float probability){
    return nextFloat(0.0f, 1.0f) < probability;
}


//Shuffles a deque (any type) using the rng's seed. Useful for things like randomizing card rewards, relic pools, next events, etc.
