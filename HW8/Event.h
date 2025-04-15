#pragma once
#include "cctype"
#include <string>
#include <vector>

using namespace std;

class Queue;

class Event {
public:
    Event() : wireName(""), time(-1), state('\0'), count(0);
    Event(string name, int t, char val, int cnt) : wireName(name), time(t), state(val), count(cnt);

private:
    string wireName;
    int time;
    char state;
    int count;
};