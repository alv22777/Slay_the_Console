#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include<deque>
#include<vector>
class Character; class Game;

#include "game_logic/effect.h"

struct Event{
    Effect event_effect;
    Character* source;
    std::deque<Character*> targets;
};

class EventHandler{
    private:
    std::deque<Event> pending;

    public:
    EventHandler();
    void enqueue(Event e);
    void resolveNext(Game& game); //resolves next effect in the queue.
    bool empty();
    /*
    this allows for the queue to be fully resolved every time an effect is enqueued.
    i was thinking of enqueue including this but that may lead to some call stack risky behavior.
    so for now, every effect will enqueu something, then game will resolve the queue until it is empty.
    Effects can also enqueue more effects, so this allows for "chains" of effects to be resolved in a single game loop.
    example: 
     speedster: card -> deal damage -> draw card -> (draw card triggers speedster) -> speedster enqueues dmg to all enemies. -> all enemies take damage.

    while(!queue.empty()){
        queue.resolveNext(Game& game);
    }
    */

};


#endif
