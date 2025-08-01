#include "Event.h"
#include <iostream>

using namespace std;

string Event::GetName() const {
	return name;
}

int Event::GetTime() const {
    return time;
}

char Event::GetState() const {
    return state;
}

int Event::GetCount() const {
    return count;
}

int Event::GetIndex() const {
    return wireIndex;
}

void Event::PrintInfo()  {
	cout << name << " " << time << " " << state << " " << count << endl;
}