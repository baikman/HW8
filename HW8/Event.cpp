#include "Event.h"
#include <iostream>

using namespace std;

int Event::GetIndex() const {
	return wireIndex;
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

bool operator<(const Event& e1, const Event& e2) {
	if (e1.time == e2.time) {
		return e1.count > e2.count;
	}

	return e1.time > e2.time; //Is this the right thing to return?
}



