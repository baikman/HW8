#include "Wire.h"
#include "Gate.h"
#include <iostream>

using namespace std;

int main() {
	string keyword, input1, input2, output;
	map<string, Wire*> wires;
	Wire* myWire;
	Gate* myGate;
	int delay;

	in >> keyword;

	while (!in.eof()) {
		if (keyword == "CIRCUIT") {
			in >> circuitName;
		} else if (keyword == "INPUT") {
			in >> wireName >> wireIndex;
			myWire = new Wire('X', wireIndex, wireName, "", NULL);
			wires.insert({ wireName, myWire });
		} else if (keyword == "NOT") {
			in >> delay >> input1 >> output;
			myGate = new Gate(keyword, delay, wires[input], nullptr, wires[output]);
		} else if (keyword == "AND") {
			in >> delay >> input1 >> input2 >> output;
			myGate = new Gate(keyword, delay, wires[input1], wires[input2], wires[output]);
		}
	}
	return 0;
}