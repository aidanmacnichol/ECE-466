#include "systemc.h"
#include <iomanip>

SC_MODULE(stim)
{
  //Keep track of reset and x (different types)
  sc_out<float> x;
  sc_out<bool> reset;

  sc_in_clk Clk;

  void stimgen()
  {
    x.write(false);
    reset.write(true);
    wait(10, SC_NS);
    reset.write(false);
    x.write(true);
    wait(10, SC_NS);
    x.write(false);
  }

    // sc_stop();
  SC_CTOR(stim)
  {
    SC_CTHREAD(stimgen, Clk.pos());
  }
};