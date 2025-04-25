#pragma once
#include "cctype"
#include <string>
#include <vector>

using namespace std;

class Event {
public:
    // We don't need a default constructor
    Event(string nm, int t, char val, int cnt, int indx) : name(nm), time(t), state(val), count(cnt), wireIndex(indx) {};
    
    string GetName() const;
    int GetTime() const;
    char GetState() const;
    int GetCount() const;
    int GetIndex() const;

    void PrintInfo();

    // TODO: Declare this in main program: priority_queue<Event> q
    /*
    struct Comparator {
        bool operator()(const Event& e1, const Event& e2) {
            if (e1.time == e2.time) {
                return e1.count > e2.count;
            }

            return e1.time > e2.time;
        }
    };
    */
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