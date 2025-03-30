#include "Gate.h"
#include "Wire.h"

void Wire::SetValue(char val) {
	value = val;
}

void Wire::SetHistory(string hist) {
	history = hist;
}

void Wire::SetDrives(vector<Gate*> drvs) {
	drives = drvs;
}

char Wire::GetValue() const {
	return value;
}

int Wire::GetIndex() const {
	return index;
}

string Wire::GetName() const {
	return name;
}

string Wire::GetHistory() const {
	return history;
}

vector<Gate*> Wire::GetDrives() const {
	return drives;
}