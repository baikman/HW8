#pragma once
#include "cctype"
#include <string>
#include <vector>

using namespace std;

class Event {
public:
    Event(string nm, int t, char val, int cnt, int indx) : name(nm), time(t), state(val), count(cnt), wireIndex(indx) {};
    
    string GetName() const;
    int GetTime() const;
    char GetState() const;
    int GetCount() const;
    int GetIndex() const;

    void PrintInfo();

private:
    string name;
    int time, count, wireIndex;  
    char state;
};

class Comparator {
public:
    bool operator()(const Event& e1, const Event& e2) {
        if (e1.GetTime() == e2.GetTime()) {
            return e1.GetCount() > e2.GetCount();
        }

        return e1.GetTime() > e2.GetTime();
    }
};