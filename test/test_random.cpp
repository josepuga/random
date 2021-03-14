#include <iostream>
#include <type_traits>
#include <algorithm>
#include "random.hpp"
using namespace std;

int main() {
    Random<int> rInt;   //Non Implicit Range: default = std::numeric_limits::min() and std::numeric_limits::max()
    Random<float> rFloat;
    Random<unsigned long long> rUll;
    Random<int16_t> rI16;
    Random<unsigned int> rUint(99, 101);  //Implicit Range

	auto DebugRandom = [](auto&&... rnd) {
        (rnd.DEBUG(), ...); //This class method was created for test purposes. Remove it if you dont need it.
	};

    cout << "(Seed) - Min Val., Max Val.  - Get()" << endl;
    cout << " ----    --------  --------    -----" << endl; 
	DebugRandom(rInt, rFloat, rUll);
    cout << "* rInt SetRandomSeed()\n";
    rInt.SetRandomSeed();

	DebugRandom(rInt, rFloat, rUll, rI16, rUint);

    cout << "\nrFloat.Get(50,100)              = " << rFloat.Get(50, 100) << endl;
    cout << "rFloat.Get() (not range set jet)  = " << rFloat.Get() << endl;
    cout << "* rFloat.SetRange(-1,1)..." << endl;
    rFloat.SetRange(-1, 1);
    cout << "rFloat.Get()                      = " << rFloat.Get() << endl;
	
	
	//Shuffle Vector
	vector<int> myVector = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	std::shuffle(myVector.begin(), myVector.end(), rInt.GetEngine());

    for (auto number : myVector) {
        cout << number << ", ";
    }
    cout << endl;
    
}
