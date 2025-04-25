//Brandon Aikman and Abby Wurster
//April 16, 2025

#include "Wire.h"
#include "Gate.h"
#include "Event.h"
#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

int main() {
	priority_queue<Event, vector<Event>, Comparator> q;
	string cd, ic, keyword, circuitName, wireName, vectorName, dummy;
	map<int, Wire*> wires; // use map::count to check existence
	vector<Gate*> gates;
	vector<string> displayedWires;
	Wire* myWire;
	Gate* myGate;
	int delay, wireIndex, input1, input2, output, wTime;
	ifstream in;
	char state;
	cout << "Enter circuit name: ";
	cin >> cd;
	ic = cd + "_v.txt";
	cd = cd + ".txt";


	in.open(cd);

	// If circuit description file cannot open
	if (!in.is_open()) {
		cout << "Could not open " << cd << endl;
		return 1;
	}

	in >> keyword;
	while (!in.eof()) {
		if (keyword == "CIRCUIT") {
			in >> circuitName;
		} else if (keyword == "INPUT") {
			in >> wireName >> wireIndex;
			myWire = new Wire('X', wireIndex, wireName, {}, {});
			wires.insert({wireIndex, myWire});
		} else if (keyword == "OUTPUT") {
			in >> wireName >> wireIndex;
			myWire = new Wire('X', wireIndex, wireName, {}, {});
			wires.insert({wireIndex, myWire});
		} else if (keyword == "NOT") {
			in >> delay >> dummy >> input1 >> output;
			// Check if output wire exists
			if (wires.count(output) == 0) {
				myWire = new Wire('X', output, "", {}, {});
				wires.insert({output, myWire});
			}
			myGate = new Gate(keyword, delay, wires[input1], nullptr, wires[output]);
			gates.push_back(myGate);
			// temp done. TODO?: set input1's drives to the new gate
			wires[input1]->AddDrive(myGate);
		} else if (keyword == "AND" || keyword == "OR" || keyword == "XOR" || 
				   keyword == "NAND" || keyword == "NOR" || keyword == "XNOR") {
			in >> delay >> dummy >> input1 >> input2 >> output;
			// Check if output wire exists
			if (wires.count(output) == 0) {
				myWire = new Wire('X', output, "", {}, {});
				wires.insert({ output, myWire });
			}
			myGate = new Gate(keyword, delay, wires[input1], wires[input2], wires[output]);
			gates.push_back(myGate);
			// temp done. TODO?: set input1 and input2's drives to the new gate
			wires[input1]->AddDrive(myGate);
			wires[input2]->AddDrive(myGate);
		} 

		in >> keyword;
	}

	// Close circuit description file
	in.close();
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
			in >> wireName >> wTime >> state;

			q.emplace(Event(wireName, wTime, state, q.size() + 1, -1));

		}
		in >> keyword;
	}

	// Close IC file
	in.close();

	for (auto const& x : gates) {
		vector<char> tempHistory(0);
		for (int i = 0; i < x->GetDelay(); i++) {
			tempHistory.push_back('X');
			(x->GetOutput())->SetHistory(tempHistory);
		}
	}

	// Printing Events
	cout << "Event Queue" << endl;
	cout << "N T S C" << endl;

	

	// ABOVE IS FINE

	int lastTime = -1;

	// Checking when new events are created
	Event currEvent = q.top();
	string eventName, wireNm;
	int wireIndx;
	Wire* wireDriver;
	int qSize = q.size();
	while (!q.empty()) {
		currEvent = q.top();
		wireDriver = NULL;

		cout << (q.top()).GetName() << " " << (q.top()).GetTime() << " " << (q.top()).GetState() << " " << (q.top()).GetCount() << endl;


		if (currEvent.GetName() == "") {
			wireIndx = currEvent.GetIndex();
			if ((currEvent.GetTime()) > 60) {
				break;
			}

			char tmpChr = currEvent.GetState();

			for (const auto& pair : wires) {
				if (pair.second->GetIndex() == wireIndx) {
					pair.second->SetValue(tmpChr);
					wireDriver = pair.second;
					break;
				}
			}

			Wire* currWire = NULL;

			if (!(wireDriver->GetDrives()).empty()) {
				vector<Gate*> drivenGates = wireDriver->GetDrives();

				for (int i = 0; i < drivenGates.size(); i++) {
					currWire = (drivenGates.at(i))->GetOutput();
					char currVal = currWire->GetValue();

					char evalState = (drivenGates.at(i))->evaluate((drivenGates.at(i))->GetInput(1), (drivenGates.at(i))->GetInput(2), currWire);

					if (currVal != evalState) {
						qSize++;
						q.emplace(Event(currWire->GetName(), currEvent.GetTime() + (drivenGates.at(i))->GetDelay(), evalState, qSize, currWire->GetIndex()));
						currWire->SetValue(evalState);

					}
				}
			}
		}
		else {
			eventName = currEvent.GetName();
			if ((currEvent.GetTime()) > 60) {
				break;
			}

			char tmpChr = currEvent.GetState();

			for (const auto& pair : wires) {
				if (pair.second->GetName() == eventName) {
					pair.second->SetValue(tmpChr);
					wireDriver = pair.second;
					break;
				}
			}

			Wire* currWire = NULL;

			if (!(wireDriver->GetDrives()).empty()) {
				vector<Gate*> drivenGates = wireDriver->GetDrives();

				for (int i = 0; i < drivenGates.size(); i++) {
					currWire = (drivenGates.at(i))->GetOutput();
					char currVal = currWire->GetValue();

					char evalState = (drivenGates.at(i))->evaluate((drivenGates.at(i))->GetInput(1), (drivenGates.at(i))->GetInput(2), currWire);

					if (currVal != evalState) {
						qSize++;
						q.emplace(Event(currWire->GetName(), currEvent.GetTime() + (drivenGates.at(i))->GetDelay(), evalState, qSize, currWire->GetIndex()));
						currWire->SetValue(evalState);
					}
				}
			}
		}
		
		vector<char> currHistVec = wireDriver->GetHistory();
		int newIndex = currEvent.GetTime();
		
		//Updates history
		if (currHistVec.size() == 0) {
			char cs = currEvent.GetState();
			if (cs == '0') { cs = '_'; }
			else if (cs == '1') { cs = '-'	;}
			currHistVec.push_back(cs);
		} else {
			int updateVal = (newIndex) - (currHistVec.size() - 1);
			char currCharacter = currHistVec.back();
			if (currCharacter == '0') { currCharacter = '_'; }
			else if (currCharacter == '1') { currCharacter = '-'; }
			
			for (int i = 1; i < updateVal; i++) {
				
				currHistVec.push_back(currCharacter);
			}

			auto postState = currEvent.GetState();
			if (postState == '0') { postState = '_'; }
			else if (postState == '1') { postState = '-'; }
			
			currHistVec.push_back(postState);

		}

		wireDriver->SetHistory(currHistVec);

		lastTime = currEvent.GetTime();

		q.pop();

	}

	//Updating all history vectors to be the same length
	for (const auto& pair : wires) {
		vector<char> tempHistVec = pair.second->GetHistory();
		int newVal = lastTime - tempHistVec.size();
		char lastChar = tempHistVec.back();
		
		for (int j = 0; j <= newVal; j++) {
			tempHistVec.push_back(lastChar);
		}

		pair.second->SetHistory(tempHistVec);
	}

	//Print Simulation
	for (const auto& pair : wires) {
		if (pair.second->GetName() != "") {
			pair.second->PrintHistory();
		}
	}
	cout << "\n       ";
	for (int i = 0; i <= lastTime; i++) {
		cout << "_";
	}
	cout << "\n 	";
	for (int i = 0; i <= lastTime; i += 5) {
		cout << i / 10 << "----";
	}
	cout << "\n 	";
	for (int i = 0; i <= lastTime; i += 5) {
		if (i % 2 == 0) {
			cout << 0 << "    ";
		}
		else {
			cout << 5 << "    ";
		}
	}

	return 0;
}