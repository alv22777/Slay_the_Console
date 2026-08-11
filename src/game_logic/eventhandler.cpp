#include "game_logic/eventhandler.h"
#include "game_logic/effect.h"
#include "game_logic/game.h"

EventHandler::EventHandler():
    pending({}){}


void EventHandler::enqueue(Event e){
    pending.push_back(e);
}
void EventHandler::resolveNext(Game& game){
    Event ev = pending.front(); pending.pop_front();
    game.resolveEffect(*(ev.source), ev.event_effect, ev.targets);
}
bool EventHandler::empty(){
    return pending.empty();
}