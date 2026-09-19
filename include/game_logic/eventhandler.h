#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include<deque>
#include<vector>
#include<memory>

class Character; class Game;

#include "game_logic/effect.h"

struct Event{
    std::shared_ptr<Effect> event_effect;
    Character* source;
    std::deque<Character*> targets;
    Character* check_condition;
    Event(std::shared_ptr<Effect> e, Character* s, std::deque<Character*> t, Character* con):
        event_effect(e), source(s), targets(t), check_condition(con){}
        
};

class EventHandler{
    private:
    std::deque<Event> pending;

    public:
    EventHandler();
    void enqueue(Event e);
    void stack(Event e);
    void resolveNext(Game& game); //resolves next effect in the queue.
    bool empty();

};


#endif
