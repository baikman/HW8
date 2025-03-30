#pragma once
#include "Gate.h"
#include "cctype"
#include <string>
#include <vector>

using namespace std;

class Gate;

class Wire {
public:
	Wire() : value('X'), index(0), name("wire"), history(""), drives(NULL) {};
	void SetValue(char val);
	void SetHistory(string hist);
	void SetDrives(vector<Gate*> drvs);
	char GetValue() const;
	int GetIndex() const;
	string GetName() const;
	string GetHistory() const;
	vector<Gate*> GetDrives() const;
private:
	char value;
	int index;
	string name;
	string history;
	vector<Gate*> drives;
};