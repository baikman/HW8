#include "Gate.h"
#include "Wire.h"

using namespace std;

int Gate::getDelay() const {
	return delayTime;
}

Wire* Gate::getInput(int input) const {
	return ((input == 1) ? input1 : input2);
}

Wire* Gate::getOutput() const {
	return outputWire;
}

char Gate::evaluate(string type, Wire* input1, Wire* input2, Wire* output) {
	char inp1 = input1->GetValue();
	char inp2 = input2->GetValue();
	switch (gateTypes[type]) {
	case 1 :
		if (inp1 == '1') {
			return '0';
		} else if (inp1 == '0') {
			return '1';
		} else {
			return 'X';
		}
	case 2:
		if (inp1 == '1' && inp2 == '1') {
			return '1';
		} else if (inp1 == 'X' || inp2 == 'X') {
			if (inp1 == '1' || inp2 == '1') {
				return 'X';
			} else {
				return '0';
			}
		} else {
			return '0';
		}
	case 3: 
		if (inp1 == '1' || inp2 == '1') {
			return '1';
		}
		else {
			if (inp1 == 'X' || inp2 == 'X') {
				return 'X';
			} else {
				return '0';
			}
		}
	}
}
	
	/*delayTime

	int i = 0;
	int numNums = 0;
	int finalVal = 0;

	while (isdigit(delayTime.at(i)) {
		numNums += 1;
		i++;
	}

	/* logic is wrong
	for (int j = (numNums - 1); j >= 0; j++) {
		finalVal += (delay.at(j) * pow(10, j));
	} */


