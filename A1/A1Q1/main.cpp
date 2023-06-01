#include "systemc.h"
#include "stim.h"
#include "filterA1.h"
#include "mon.h"

int sc_main(int argc, char* argv[])
{
  sc_signal<bool> reset;
  sc_signal<float> xSig, ySig;
  //20 Second clock time * 0.5 = 10ns clock period
  //Initial value will be false (default)
  sc_clock TestClk("TestClock", 20, SC_NS, 0.5, 1, SC_NS); 

  //Future note I used a different var for clock each .h file this is confusing dont do that
  filterA1 Filter1("Filter");
  Filter1.clock(TestClk);
  Filter1.reset(reset);
  Filter1.x(xSig);
  Filter1.y(ySig);
  
  stim Stim1("Stimulus");
  Stim1.x(xSig);
  Stim1.reset(reset);
  Stim1.Clk(TestClk);
    

  mon Monitor1("Monitor");
  Monitor1.x(xSig);
  Monitor1.y(ySig);
  Monitor1.Clk(TestClk); 
  
  sc_trace_file* Tf = sc_create_vcd_trace_file("traces");
  Tf->set_time_unit(1, SC_NS); //1ns time unit
  sc_trace(Tf, xSig  , "x" );
  sc_trace(Tf, ySig  , "y" );
  sc_trace(Tf, reset  , "reset" );
  sc_trace(Tf, TestClk, "Clock");

  sc_start(300, SC_NS);  // run for 260 ns (12 clock cycles)
  sc_close_vcd_trace_file(Tf);
  
  return 0;
}