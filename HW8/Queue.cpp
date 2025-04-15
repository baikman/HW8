#include "Gate.h"
#include "Wire.h"
#include "Defns.h"
#include <iostream>

/*int* ptr1 = new Event(wireName, time, value);
    eventPtr.push_back(ptr1);*/




ifstream inFS;
string fileName;

cin >> fileName;

inFS.open(fileName);

//If file cannot open
if (!inFS.is_open()) {
	cout << "Could not open " << fileName << endl;
	return 1;
}

in >> keyword;

while (!inFS.eof()) {
	
	if (keyword == "VECTOR") {
		in >> vectorName;
	}

	else if (keyword == "INPUT") {
		in >> wireName >> wireIndex;
		myWire = new Wire('X', wireIndex, wireName, "", NULL);
		wires.insert({ wireName, myWire });
	}
}

//close file
inFS.close();