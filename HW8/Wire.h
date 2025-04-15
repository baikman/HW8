#pragma once
#include "cctype"
#include <string>
#include <vector>

using namespace std;

class Gate;

class Wire {
public:
	Wire() : value('\0'), index(0), name(""), history({'\0'}), drives({NULL}) {};
	Wire(char val, int ind, string nm, vector<char> hist, vector<Gate*> drvs) : value(val), index(ind), name(nm), history(hist), drives(drvs) {};

	void SetValue(char val);
	void SetHistory(vector<char> hist);
	void SetDrives(vector<Gate*> drvs);
	
	char GetValue() const;
	int GetIndex() const;
	string GetName() const;
	vector<char> GetHistory() const;
	vector<Gate*> GetDrives() const;

	void PrintHistory() const;
	void PrintInfo() const;
private:
	char value;
	int index;
	string name;
	vector<char> history;
	vector<Gate*> drives;
};
