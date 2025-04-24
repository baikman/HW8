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
	
	/*
	if (argc != 3) {
		cout << " bad input count" << endl;
		return 1;
	}
	

	cd = argv[1];
	ic = argv[2];

	*/

	cout << "Enter circuit name: ";
	cin >> cd;
	ic = cd + "_v.txt";
	cd = cd + ".txt";
	//cout << "Enter circuit discription: ";
	//cin >> ic;
	/*
	cd = "circuit0.txt";
	ic = "circuit0_v.txt";
	*/

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
			myWire = new Wire('X', wireIndex, wireName, {'\0'}, {});    // What do we do with these last two??
			wires.insert({wireIndex, myWire});
		} else if (keyword == "OUTPUT") {
			in >> wireName >> wireIndex;
			myWire = new Wire('X', wireIndex, wireName, {'\0'}, {});
			wires.insert({wireIndex, myWire});
		} else if (keyword == "NOT") {
			in >> delay >> dummy >> input1 >> output;
			// Check if output wire exists
			if (wires.count(output) == 0) {
				myWire = new Wire('X', output, "", { '\0' }, {});
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
				myWire = new Wire('X', output, "", { '\0' }, {});
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

	/*
	while (!q.empty()) {
		// (q.top()).PrintInfo();
		cout << (q.top()).GetName() << " " << (q.top()).GetTime() << " " << (q.top()).GetState() << " " << (q.top()).GetCount() << endl;
		q.pop();
	}*/

	//Create new events from gates
	int currTime = 0;
	for (int i = 0; i < gates.size(); i++) {
		if (currTime > 60) {
			break;
		}

		Wire* currWire = gates.at(i)->GetOutput();
		char tempChar = '\0';
		currTime += (gates.at(i))->GetDelay();

		// Need to update currWire->GetName use GetDrives instead GetName() not needed

		//auto currVec = currWire->GetDrives();

		//currVec.at(0)->GetName();
		//we wouldn't need GetName() if we implemented each gate when it gets made...

		tempChar = (gates.at(i))->evaluate(/*(gates.at(i))->GetName(), */ (gates.at(i))->GetInput(1), (gates.at(i))->GetInput(2), (gates.at(i))->GetOutput());
		//auto tc = currWire->GetValue();
		if (currWire->GetValue() != tempChar) {
			//cout << currWire->GetName() << endl;
			q.emplace(Event(currWire->GetName(), currTime, tempChar, q.size() + 1));
		}

		currWire->SetValue(tempChar);

	}

	int lastTime = -1;

	// Checking when new events are created
	while (!q.empty()) {
		auto currEvent = q.top();
		string eventName = currEvent.GetName();
		string wireNm = "";
		Wire* currentOutWire = NULL;
		Wire* wireDriver = NULL;

		cout << (q.top()).GetName() << " " << (q.top()).GetTime() << " " << (q.top()).GetState() << " " << (q.top()).GetCount() << endl;

		if ((currEvent.GetTime()) > 60) {
			break;
		}


		char tmpChr = currEvent.GetState();

		for (int i = 1; i < wires.size(); i++) {
			auto tempName = (wires.at(i))->GetName();
			if (tempName == eventName) {
				(wires.at(i))->SetValue(tmpChr);
				wireDriver = wires.at(i);
				break;
			}
		}

		
		auto vecDrives = wireDriver->GetDrives();
		
		Wire* currWire = NULL;

		if (vecDrives.size() != 0) {

			for (int i = 0; i < vecDrives.size(); i++) {
				currWire = (vecDrives.at(i))->GetOutput();
				auto currVal = currWire->GetValue();

				char tempChar = '\0';
				tempChar = (vecDrives.at(i))->evaluate((vecDrives.at(i))->GetInput(1), (vecDrives.at(i))->GetInput(2), currWire);

				cout << wireDriver->GetValue() << endl;
				cout << "tempChar: " << tempChar << endl;
				cout << "currVal: " << currVal << endl;

				if (currVal != tempChar) {
					q.emplace(Event(currWire->GetName(), currEvent.GetTime() + (vecDrives.at(i))->GetDelay(), tempChar, q.size() + 1));
					cout << "New Event Created" << endl;
				}

			}

		}

		/*
		for (int i = 1; i <= wires.size(); i++) {
			wireNm = wires.at(i)->GetName();
			
			//cout << wires.at(i) << endl;

			if (eventName == wireNm) {
				currentOutWire = wires.at(i);
				break;
			}
		}

		//need to update so it isn't GetName it is GetDrives
		vector<Gate*> myVec = currentOutWire->GetDrives();

		// Looks at all the gates a wire drives and decides whether a new event is needed based on what event just took place
		for (int i = 0; i < myVec.size(); i++) {
			myVec.at(i)->GetOutput();
			char tempChar = '\0';
			tempChar = (myVec.at(i))->evaluate(/*myVec.at(i))->GetName(), (myVec.at(i))->GetInput(1), (myVec.at(i))->GetInput(2), (myVec.at(i))->GetOutput());

			if (currentOutWire->GetValue() != tempChar) {
				q.emplace(Event(currentOutWire->GetName(), currEvent.GetTime() + (myVec.at(i))->GetDelay(), tempChar, q.size() + 1));
			}

			currentOutWire->SetValue(tempChar);

		}
	*/

		auto currHistVec = currWire->GetHistory();
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
			
			currHistVec.push_back(currCharacter);

			for (int i = 0; i < updateVal; i++) {
				
				currHistVec.push_back(currCharacter);
			}

			auto tempChar = currEvent.GetState();
			if (tempChar == '0') { tempChar = '_'; }
			else if (tempChar == '1') { tempChar = '-'; }
			
			currHistVec.push_back(tempChar);

		}

		currWire->SetHistory(currHistVec);

		lastTime = currEvent.GetTime();

		q.pop();


	}
	/*
	int biggestHistoryLength = 0;
	for (int i = 1; i <= wires.size(); i++) {
		auto tempVec = (wires.at(i)->GetHistory());
		biggestHistoryLength = tempVec.size();
	}*/

	//Updating all history vectors to be the same length
	for (int i = 1; i <= wires.size(); i++) {
		auto tempHistVec = wires[i]->GetHistory();
		int newVal = lastTime - tempHistVec.size();
		char tempChar = tempHistVec.back();
		
		for (int j = 0; j < newVal; j++) {
			tempHistVec.push_back(tempChar);
		}

		wires[i]->SetHistory(tempHistVec);
	}

	//Print Function
	for (int i = 1; i <= wires.size(); i++) {
		wires[i]->PrintHistory();
	}
	cout << "_____________________________" << endl;  //Not sure what the bar is supposed to be
	cout << " 	";
	for (int i = 0; i <= lastTime; i++) {
		cout << i;
	}

	return 0;
}