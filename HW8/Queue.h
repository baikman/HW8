#pragma once
#include "cctype"
#include <string>
#include <vector>
#include <deque>

using namespace std;

class Event;

class Queue {
public:
    Queue() : wireName(""), time(-1), state(""), count(0);   //Default Constructor
    Queue(string name, int t, char val, int cnt) : wireName(name), time(t), state(val), count(cnt);

private:
    deque<Event*> eventPtr;
    string wireName;
    int time;
    char state;
    int count;
};