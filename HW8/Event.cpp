#include "Gate.h"
#include "Wire.h"
#include "Defns.h"
#include <iostream>



//include at the top
#include <iostream>
#include <fstream>


//include in main

ifstream inFS;
string fileName;

cin >> fileName;

inFS.open(fileName);

//If file cannot open
if (!inFS.is_open()) {
    cout << "Could not open " << fileName << endl;
    return 1;
}



//close file
inFS.close();



