#include "game_logic/eventhandler.h"
#include "game_logic/effect.h"


EventHandler::EventHandler():
    pending({}){}


void EventHandler::enqueue(Effect e){
    pending.push_back(e);
}
void EventHandler::resolveNext(Game& game){
    pending.pop_front();
}
bool EventHandler::empty(){
    return pending.empty();
}