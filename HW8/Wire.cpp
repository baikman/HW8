#include "Gate.h"
#include "Wire.h"
#include <iostream>

void Wire::SetValue(char val) {
	value = val;
}

void Wire::SetHistory(vector<char> hist) {
	history = hist;
}

void Wire::SetDrives(vector<Gate*> drvs) {
	drives = drvs;
}

void Wire::AddDrive(Gate* drv) {
	drives.push_back(drv);
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

vector<char> Wire::GetHistory() const {
	return history;
}

vector<Gate*> Wire::GetDrives() const {
	return drives;
}

void Wire::PrintHistory() const {
	cout << " " << name << " | ";
	for (char c : history) {
		cout << c;
	}
	cout << "\n   |\n";
}


void Wire::PrintInfo() const {
	cout << value << " " << index << " " << name << " ";
	PrintHistory();
	for (Gate* g : drives) {
		if (g != NULL) {
			g->PrintInfo();
			cout << " ";
		}
	}
}
