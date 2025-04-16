//Brandon Aikman and Abby Wurster
//April 16, 2025


#include "Wire.h"
#include "Gate.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(/*int argc, char* argv[]*/) {
	string cd, ic, keyword, circuitName, wireName, vectorName, dummy;
	map<int, Wire*> wires;  // TODO: recommend using wireIndex versus wireName in the map
		// use map::count to check existence
	vector<Gate*> gates;
	Wire* myWire;
	Gate* myGate;
	int delay, wireIndex, input1, input2, output;
	ifstream in;

	/*
	if (argc != 3) {
		cout << " bad input count" << endl;
		return 1;
	}
	

	cd = argv[1];
	ic = argv[2];
	*/

	cd = "circuit0.txt";
	ic = "circuit0_v.txt";

	in.open(cd);

	// If circuit description file cannot open
	if (!in.is_open()) {
		cout << "Could not open " << cd << endl;
		return 1;
	}

	//cout << "Got here 0.5" << endl;
	in >> keyword;
	while (!in.eof()) {
		if (keyword == "CIRCUIT") {
			in >> circuitName;
		} else if (keyword == "INPUT") {
			in >> wireName >> wireIndex;
			myWire = new Wire('X', wireIndex, wireName, {'\0'}, {nullptr});
			wires.insert({ wireIndex, myWire });
		} else if (keyword == "OUTPUT") {
			in >> wireName >> wireIndex;
			myWire = new Wire('X', wireIndex, wireName, {'\0'}, {nullptr});
			wires.insert({ wireIndex, myWire });
		} else if (keyword == "NOT") {
			in >> delay >> >> dummy >> input1 >> output;
			// TODO: check tp make sure the wirew exist, and if not create them
			myGate = new Gate(keyword, delay, wires[input1], nullptr, wires[output]);
			gates.push_back(myGate);
		} else if (keyword == "AND" || keyword == "OR" || keyword == "XOR" || keyword == "NAND" || keyword == "NOR" || keyword == "XNOR") {
			in >> delay >> dummy >> input1 >> input2 >> output;
			myGate = new Gate(keyword, delay, wires[input1], wires[input2], wires[output]);
			gates.push_back(myGate);
		} 

		in >> keyword;
	}

	// Close circuit description file
	in.close();
	cout << "Got here" << endl;
	in.open(ic);

	// If circuit description file cannot open
	if (!in.is_open()) {
		cout << "Could not open " << ic << endl;
		return 1;
	}

	in >> keyword;

	while (!in.eof()) {

		if (keyword == "VECTOR") {
			in >> vectorName;
		}

		else if (keyword == "INPUT") {
			in >> wireName >> wireIndex;
			myWire = new Wire('X', wireIndex, wireName, {'\0'}, {nullptr});
			wires.insert({ wireIndex, myWire });
		}
		in >> keyword;
	}

	// Close IC file
	in.close();
	cout << "Got here2" << endl;
	cout << "Testing parsing: first wires:" << endl;
	for (auto const& x : wires) {
		cout << x.first << " " << x.second << endl;
	}

	cout << "gates: " << endl;

	for (auto const& x : gates) {
		x->PrintInfo();
		cout << endl;
	}

	return 0;
}