//Brandon Aikman and Abby Wurster
//April 16, 2025

#include "Wire.h"
#include "Gate.h"
#include "Event.h"
#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

int main(int argc, char* argv[]) {
	priority_queue<Event, vector<Event>, Comparator> q;
	string cd, ic, keyword, circuitName, wireName, vectorName, dummy;
	map<int, Wire*> wires; // use map::count to check existence
	vector<Gate*> gates;
	Wire* myWire;
	Gate* myGate;
	int delay, wireIndex, input1, input2, output, wTime;
	ifstream in;
	char state;

	Wire* testWire1, *testWire2;  //testing
	
	if (argc != 3) {
		cout << " bad input count" << endl;
		return 1;
	}
	

	cd = argv[1];
	ic = argv[2];

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
			myWire = new Wire('X', wireIndex, wireName, {'\0'}, {nullptr});    // What do we do with these last two??
			wires.insert({wireIndex, myWire});
		} else if (keyword == "OUTPUT") {
			in >> wireName >> wireIndex;
			myWire = new Wire('X', wireIndex, wireName, {'\0'}, {nullptr});
			wires.insert({wireIndex, myWire});
		} else if (keyword == "NOT") {
			in >> delay >> dummy >> input1 >> output;
			// Check if output wire exists
			if (wires.count(output) == 0) {
				myWire = new Wire('X', output, "", { '\0' }, { nullptr });
				wires.insert({wireIndex, myWire});
			}
			myGate = new Gate(keyword, delay, wires[input1], nullptr, wires[output]);
			gates.push_back(myGate);
			// temp done. TODO?: set input1's drives to the new gate
			testWire1 = wires[input1];
			testWire1->AddDrive(myGate);
		} else if (keyword == "AND" || keyword == "OR" || keyword == "XOR" || 
				   keyword == "NAND" || keyword == "NOR" || keyword == "XNOR") {
			in >> delay >> dummy >> input1 >> input2 >> output;
			// Check if output wire exists
			if (wires.count(output) == 0) {
				myWire = new Wire('X', output, "", { '\0' }, { nullptr });
				wires.insert({ wireIndex, myWire });
			}
			myGate = new Gate(keyword, delay, wires[input1], wires[input2], wires[output]);
			gates.push_back(myGate);
			// temp done. TODO?: set input1 and input2's drives to the new gate
			testWire1 = wires[input1];
			testWire2 = wires[input2];
			testWire1->AddDrive(myGate);
			testWire2->AddDrive(myGate);
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

			q.emplace(Event(wireName, wTime, state, q.size() + 1));

		}
		in >> keyword;
	}

	// Close IC file
	in.close();

	cout << "Testing parsing: first wires:" << endl;
	for (auto const& x : wires) {
		cout << x.first << " " << x.second->GetValue() << endl;
	}

	cout << "gates: " << endl;

	for (auto const& x : gates) {
		x->PrintInfo();
		cout << endl;
	}


	// Printing Events
	cout << "Event Queue" << endl;
	cout << "N T S C" << endl;


	while (!q.empty()) {
		// (q.top()).PrintInfo();
		cout << (q.top()).GetName() << " " << (q.top()).GetTime() << " " << (q.top()).GetState() << " " << (q.top()).GetCount() << endl;
		q.pop();
	}

	//Create new events from gates
	int currTime = 0;
	for (int i = 0; i < gates.size(); i++) {
		if (currTime > 60) {
			break;
		}

		Wire* currWire = gates.at(i)->GetOutput();
		char tempChar = '\0';
		currTime += gates.at(i)->GetDelay();

		// Need to update currWire->GetName use GetDrives instead GetName() not needed

		//auto currVec = currWire->GetDrives();

		//currVec.at(0)->GetName();
		//we wouldn't need GetName() if we implemented each gate when it gets made...

		tempChar = (gates.at(i))->evaluate(currWire->GetName(), gates.at(i)->GetInput(1), gates.at(i)->GetInput(2), gates.at(i)->GetOutput());

		if (currWire->GetValue() != tempChar) {
			q.emplace(Event(currWire->GetName(), currTime, tempChar, q.size() + 1));
		}

		currWire->SetValue(tempChar);

	}

	// Checking when new events are created
	while (!q.empty()) {
		auto currEvent = q.top();
		string eventName = currEvent.GetName();
		string wireNm = "";
		Wire* currentWire = NULL;

		if ((currEvent->GetTime()) > 60) {
			break;
		}

		for (int i = 0; i < wires.size(); i++) {
			wireNm = ((wires.at(i)).second)->GetName();
			
			if (eventName == wireNm) {
				currentWire = (wires.at(i)).second;
				break;
			}
		}

		auto myVec = currentWire->GetDrives();

		// Looks at all the gates a wire drives and decides whether a new event is needed based on what event just took place
		for (int i = 0; i < myVec.size(); i++) {
			myVec.at(i)->GetOutput();
			char tempChar = '\0';
			tempChar = (myVec.at(i))->evaluate(currWire->GetName(), myVec.at(i)->GetInput(1), myVec.at(i)->GetInput(2), myVec.at(i)->GetOutput());

			if (currWire->GetValue() != tempChar) {
				q.emplace(Event(currWire->GetName(), currEvent.GetTime() + (myVec.at(i))->GetDelay(), tempChar, q.size() + 1));
			}

			currWire->SetValue(tempChar);

		}

		auto currHistVec = currentWire->GetHistory();
		int newIndex = currentEvent->GetTime();
		
		//Updates history
		if (currHistVec.size() == 0) {
			char cs = currEvent->GetState();
			if (cs == '0') { cs = '_'; }
			else if (cs == '1') { cs = '-';}
			currHistVec.push_back(cs);
		} else {
			int updateVal = (newIndex - 1) - currHistVec.size();
			char currCharacter = currHistVec.back();
			if (currCharacter == '0') { currCharacter = '_'; }
			else if (currCharacter == '1') { currCharacter = '-'; }
			
			currHistVec.push_back(currCharacter);

			for (int i = 0; i < updateVal; i++) {
				
				currHistVec.push_back(currCharacter);
			}

			auto tempChar = currEvent->GetState();
			if (tempChar == '0') { tempChar = '_'; }
			else if (tempChar == '1') { tempChar = '-'; }
			
			currHistVec.push_back(tempChar);

		}

		currentWire.SetHistory(currHistVec);

		q.pop();

	}

	//Print Function
	for (int i = 0; i < wires.size(); i++) {
		((wires.at(i)).second)->PrintHistory();
	}
	cout << "_____________________________" << endl;  //Not sure what the bar is supposed to be
	cout << " 	";
	for (int i = 0; i <= currTime; i++) {
		cout << i << " ";
	}

	return 0;
}