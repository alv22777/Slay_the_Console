#ifndef RNG_H
#define RNG_H
#include<random>
#include<algorithm>
#include<deque>

class RNG{

    std::mt19937 engine;
    uint32_t seed;
    public:
    RNG(uint32_t s);

    //Returns a random integer between min and max, inclusive.
    int nextInt(int min, int max);
    //Returns a random float between min and max.
    float nextFloat(float min, float max);
    
    bool chance(float probability);

    
    //Shuffles a deque (any type) using the rng's seed. Useful for things like randomizing card rewards, relic pools, next events, etc.
    template <typename T>
    void shuffle(std::deque<T>& vec){std::shuffle(vec.begin(), vec.end(), engine);}  
    
    uint32_t getSeed();
};

#endif
