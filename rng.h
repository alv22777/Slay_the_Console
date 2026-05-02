#ifndef RNG_H
#define RNG_H
#include<random>
#include<algorithm>
#include<deque>

class RNG{

    std::mt19937 seed;

    public:
    RNG(std::mt19937& s);

    //Returns a random integer between min and max, inclusive. Very useful for things like random enemy targets.
    int nextInt(int min, int max);
    //Returns a random float between min and max. Useful for things like random chances and percentages.
    float nextFloat(float min, float max);
    //Chance function, mostly for convenience. 
    bool chance(float probability);

    
    //Shuffles a deque (any type) using the rng's seed. Useful for things like randomizing card rewards, relic pools, next events, etc.
    template <typename T>
    void shuffle(std::deque<T>& vec){std::shuffle(vec.begin(), vec.end(), seed);}  
     
};

#endif
