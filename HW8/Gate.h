#pragma once
#include <string>
#include <map>

using namespace std;


class Wire;

class Gate {
public:
	
	Gate(string type, int delay, Wire* in1, Wire* in2, Wire* output) : gateType(type), delayTime(delay),
		input1(in1), input2(in2), outputWire(output) {};
	
	int getDelay() const;
	Wire* getInput(int input) const;
	Wire* getOutput() const;

	char evaluate(string type, Wire* input1, Wire* input2, Wire* output);

private:
	Wire* input1, * input2;
	Wire* outputWire;
	string gateType;
	int delayTime;
	map<string, int> gateTypes = {
		{"NOT", 1},
		{"AND", 2},
		{"OR", 3},
		{"XOR", 4},
		{"NAND", 5},
		{"NOR", 6},
		{"XNOR", 7}
	};
};