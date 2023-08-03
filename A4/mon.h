#define SC_INCLUDE_FX
#include "systemc.h"
#include <iomanip>
using namespace std;
using namespace sc_dt; 

SC_MODULE(mon)
{
  sc_in<sc_fixed <16, 3, SC_TRN, SC_WRAP>> x, y;
  sc_in_clk clock;

  void monitor() {
    cout << setw(8) << "Time";
    cout << setw(16) << "x" << setw(16) << "y" << endl;
	
    while (true) {
	cout << setw(8) << sc_time_stamp();
	cout << setw(16) << x.read() << setw(16) << y.read() << endl;
	wait();		
    }
  }

  SC_CTOR(mon) {
    SC_CTHREAD(monitor, clock.pos());
  }

};