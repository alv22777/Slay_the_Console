#include "game_logic/eventhandler.h"
#include "game_logic/effect.h"
#include "game_logic/game.h"

EventHandler::EventHandler():
    pending({}){}


void EventHandler::enqueue(Event e){
    pending.push_back(e);
}
void EventHandler::stack(Event e){
    pending.push_front(e);
}

void EventHandler::resolveNext(Game& game){
    Event ev = pending.front(); 
    pending.pop_front();
    game.resolveEffect(*(ev.source), ev.event_effect, ev.targets, ev.check_condition);
    //add this event's results to the Game object's EventHistory with ID
}
bool EventHandler::empty(){
    return pending.empty();
}