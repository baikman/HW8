#pragma once
#include "cctype"
#include <string>
#include <vector>

using namespace std;

class Queue;

class Event {
public:
    //We don't need a default constructor
    Event(int index, int t, char val, int cnt) : wireIndex(index), time(t), state(val), count(cnt) {};
    
    int GetIndex() const;
    int GetTime() const;
    char GetState() const;
    int GetCount() const;

    friend bool operator<(const Event& e1, const Event& e2);

    //TODO: Declare this in main program: priority_queue<Event> q

private:
    int wireIndex, time, count;  
    char state;
};