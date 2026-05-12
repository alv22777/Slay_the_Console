#ifndef EVENTLOG_H
#define EVENTLOG_H

#include<iostream>
#include<deque>

class EventLog{
    private:
        std::deque<std::string> log;
        int size;

    public:
    EventLog(int s);
    void receive(std::string s);
    void prune();
    void broadcast();
    void clear();
};


#endif