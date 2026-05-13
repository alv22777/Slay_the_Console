#include "ui/eventlog.h"
#include <iostream>
EventLog::EventLog(int s): size(s), log({}){}

void EventLog::receive(std::string s){
    if(!s.empty()){log.push_back(s);}
    else{return;}

    if(log.size() > size){prune();}
}
void EventLog::prune(){
    log.erase(log.begin());
}
void EventLog::clear(){log.clear();}

void EventLog::broadcast(){
    std::cout<<"Recent Events:\n";
    for(int i = 0; i<size;i++){

        //output log entry if there is one, otherwise just output empty line
        if(i<log.size()){
            std::cout<<log[i];
        }
        std::cout<<'\n';
    }
}
