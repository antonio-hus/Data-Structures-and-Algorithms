/// INCLUDES SECTION
// User Defined Modules
#include "Queue.h"
#include "ExtendedTest.h"
#include "ShortTest.h"

// Libraries
#include <iostream>

//Namespaces
using namespace std;

/// MAIN FUNCTION
int main() {

	testAll();
	testAllExtended();
	cout << "All tests passed successfully!" << endl;
}