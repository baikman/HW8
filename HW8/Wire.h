#pragma once
#include "cctype"
#include <string>
#include <vector>

using namespace std;

class Gate;

class Wire {
public:
	Wire() : value(''), index(0), name(""), history({''}), drives({NULL}) {};
	Wire(char val, int ind, string nm, history hist, drives drvs) : value(val), index(ind), name(nm), history(hist), drives(drvs) {};

	void SetValue(char val);
	void SetHistory(string hist);
	void SetDrives(vector<Gate*> drvs);
	
	char GetValue() const;
	int GetIndex() const;
	string GetName() const;
	vector<char> GetHistory() const;
	vector<Gate*> GetDrives() const;

	void PrintHistory() const;
private:
	char value;
	int index;
	string name;
	vector<char> history;
	vector<Gate*> drives;
};
