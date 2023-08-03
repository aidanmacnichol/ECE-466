#define SC_INCLUDE_FX
#include "systemc.h"
using namespace sc_dt; 

SC_MODULE(stim)
{
  sc_out <sc_fixed <16, 3, SC_TRN, SC_WRAP>> x;
  sc_out<bool> reset;
  sc_in_clk clock;

  void stimgen() {
    reset.write(true);
    x.write(0);
    wait();
    reset.write(false);
    x.write(1);
    wait();
    x.write(0);
    wait();
  }

  SC_CTOR(stim) {
    SC_CTHREAD(stimgen, clock.pos());
  }

};