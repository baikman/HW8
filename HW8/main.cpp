#include "Wire.h"
#include "Gate.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(/*int argc, char* argv[]*/) {
	string cd, ic, keyword, input1, input2, output, circuitName, wireName, vectorName;
	map<string, Wire*> wires;
	vector<Gate*> gates;
	Wire* myWire;
	Gate* myGate;
	int delay, wireIndex;
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

	while (!in.eof()) {
		if (keyword == "CIRCUIT") {
			in >> circuitName;
		} else if (keyword == "INPUT") {
			in >> wireName >> wireIndex;
			myWire = new Wire('X', wireIndex, wireName, {'\0'}, {nullptr});
			wires.insert({ wireName, myWire });
		} else if (keyword == "OUTPUT") {
			in >> wireName >> wireIndex;
			myWire = new Wire('X', wireIndex, wireName, {'\0'}, {nullptr});
			wires.insert({ wireName, myWire });
		} else if (keyword == "NOT") {
			in >> delay >> input1 >> output;
			myGate = new Gate(keyword, delay, wires[input1], nullptr, wires[output]);
			gates.push_back(myGate);
		} else if (keyword == "AND") {
			in >> delay >> input1 >> input2 >> output;
			myGate = new Gate(keyword, delay, wires[input1], wires[input2], wires[output]);
			gates.push_back(myGate);
		} else if (keyword == "OR") {
			in >> delay >> input1 >> input2 >> output;
			myGate = new Gate(keyword, delay, wires[input1], wires[input2], wires[output]);
			gates.push_back(myGate);
		} else if (keyword == "XOR") {
			in >> delay >> input1 >> input2 >> output;
			myGate = new Gate(keyword, delay, wires[input1], wires[input2], wires[output]);
			gates.push_back(myGate);
		} else if (keyword == "NAND") {
			in >> delay >> input1 >> input2 >> output;
			myGate = new Gate(keyword, delay, wires[input1], wires[input2], wires[output]);
			gates.push_back(myGate);
		} else if (keyword == "NOR") {
			in >> delay >> input1 >> input2 >> output;
			myGate = new Gate(keyword, delay, wires[input1], wires[input2], wires[output]);
			gates.push_back(myGate);
		} else if (keyword == "XNOR") {
			in >> delay >> input1 >> input2 >> output;
			myGate = new Gate(keyword, delay, wires[input1], wires[input2], wires[output]);
			gates.push_back(myGate);
		}
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

	while (!in.eof()) {

		if (keyword == "VECTOR") {
			in >> vectorName;
		}

		else if (keyword == "INPUT") {
			in >> wireName >> wireIndex;
			myWire = new Wire('X', wireIndex, wireName, {'\0'}, {nullptr});
			wires.insert({ wireName, myWire });
		}
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