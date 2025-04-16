#pragma once
#include "cctype"
#include <string>
#include <vector>

using namespace std;

class Queue;

class Event {
public:
    //Event() : wireName(""), time(-1), state('\0'), count(0);
    Event(string name, int t, char val, int cnt) : wireName(name), time(t), state(val), count(cnt);
    //TODO: Don't use name, use wire's index instead
    //TODO: We need getters 
    friend bool operator<(const Event& e1, const Event& e2); //TODO: implement this in Event.cpp https://csweb.cedarville.edu/shomperk/CS1220/cs1220_web/examples/pqueuetest.cpp

    //TODO: Declare this in main program: priority_queue<Event> q

private:
    string wireName;  //TODO: Change to wireIndex
    int time;
    char state;
    int count;
};