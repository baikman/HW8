#include "Gate.h"
#include "Wire.h"
#include <iostream>
#include <map>

using namespace std;

int Gate::GetDelay() const {
	return delayTime;
}

Wire* Gate::GetInput(int input) const {
	return ((input == 1) ? input1 : input2);
}

Wire* Gate::GetOutput() const {
	return outputWire;
}

char NOT(char inp1) {
	if (inp1 == '1') {
		return '0';
	} else if (inp1 == '0') {
		return '1';
	} else {
		return 'X';
	}
}

char AND(char inp1, char inp2) {
	if (inp1 == '1' && inp2 == '1') {
		return '1';
	} else if (inp1 == 'X' || inp2 == 'X') {
		if ((inp1 == '1' || inp2 == '1') || (inp1 == 'X' && inp2 == 'X')) {
			return 'X';
		}
		else {
			return '0';
		}
	} else {
		return '0';
	}
}

char OR(char inp1, char inp2) {
	if (inp1 == '1' || inp2 == '1') {
		return '1';
	} else {
		if (inp1 == 'X' || inp2 == 'X') {
			return 'X';
		} else {
			return '0';
		}
	}
}

char XOR(char inp1, char inp2) {
	if ((inp1 == '1' && inp2 == '0') || (inp1 == '0' && inp2 == '1')) {
		return '1';
	} else if (inp1 == 'X' || inp2 == 'X') {
		return 'X';
	} else {
		return '0';
	}
}

char NAND(char inp1, char inp2) {
	return NOT(AND(inp1, inp2));
}

char NOR(char inp1, char inp2) {
	return NOT(OR(inp1, inp2));
}

char XNOR(char inp1, char inp2) {
	return NOT(XOR(inp1, inp2));
}

char Gate::evaluate(Wire* input1, Wire* input2, Wire* output) {
	char inp1 = input1->GetValue();
	char inp2 = 'z';
	if (gateTypes[gateType] != 1) {
		char inp2 = input2->GetValue();
	}
	switch (gateTypes[gateType]) {
	case 1:
		return NOT(inp1);
	case 2:
		return AND(inp1, inp2);
	case 3:
		return OR(inp1, inp2);
	case 4:
		return XOR(inp1, inp2);
	case 5:
		return NAND(inp1, inp2);
	case 6:
		return NOR(inp1, inp2);
	case 7:
		return XNOR(inp1, inp2);
	default: 
		cerr << "Unexpected gate type";
		return '\0';
	}
}

void Gate::PrintInfo()  {
	cout << evaluate(/*gateType, */input1, input2, outputWire) << endl;
}