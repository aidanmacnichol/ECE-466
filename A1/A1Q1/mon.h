#include "systemc.h"
#include <iomanip>
using namespace std;

SC_MODULE(mon)
{
  sc_in<bool> Clk;
  sc_in<float> x, y; 

  void monitor()
  {
	// Headers for table
	cout << setw(10) << "Time";
	cout << setw(2) << "x";
	cout << setw(2) << "y" << endl;
	
	while (true) {
		// Printing out x and y with time stamp
		cout << setw(10) << sc_time_stamp();
		cout << setw(2) << x.read();
		cout << setw(2) << y.read() << endl;
		wait();		
	}
  }
  SC_CTOR(mon)
  {
    SC_CTHREAD(monitor, Clk.pos());
  }
};