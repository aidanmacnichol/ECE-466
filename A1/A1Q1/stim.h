<<<<<<< HEAD
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
    wait();
    reset.write(false);
    x.write(true);
    wait();
    x.write(false);
    wait();
  }

    // sc_stop();
  SC_CTOR(stim)
  {
    SC_CTHREAD(stimgen, Clk.pos());
  }
=======
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
    wait();
    reset.write(false);
    x.write(true);
    wait();
    x.write(false);
    wait();
  }

    // sc_stop();
  SC_CTOR(stim)
  {
    SC_CTHREAD(stimgen, Clk.pos());
  }
>>>>>>> e969b52edf14eaac20788d0ec172f64c8cbc5486
};