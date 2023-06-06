#include "systemc.h"

#include "memory.h"
#include "testbench.h"


int sc_main(int argc, char* argv[])
{
    mem_ctrl Memory("Memory");
    mem_testbench Testbench("Testbench");

    sc_clock clk("TestClock", 10, SC_NS, 0.5, 5, SC_NS);

    sc_signal <bool> reset, new_comm, complete;
    sc_signal < sc_uint<2> > comm;
    sc_signal < sc_uint<8> > addr;
    sc_signal_rv <8> data;
    // NOTE: _rv needed because of multiple drivers
  
    // Interconnections

    Memory.clk(clk);
    Memory.reset(reset);
    Memory.data(data);
    Memory.addr(addr);
    Memory.comm(comm);
    Memory.new_comm(new_comm);
    Memory.complete(complete);

    Testbench.clk(clk);
    Testbench.reset(reset);
    Testbench.data(data);
    Testbench.addr(addr);
    Testbench.comm(comm);
    Testbench.new_comm(new_comm);
    Testbench.complete(complete);

    sc_trace_file* Tf = sc_create_vcd_trace_file("traces");
    Tf->set_time_unit(1, SC_NS); //1ns time unit
    sc_trace(Tf, complete  , "complete" );
    sc_trace(Tf, new_comm  , "new_comm" );
    sc_trace(Tf, comm  , "comm" );
    sc_trace(Tf, addr  , "addr" );
    sc_trace(Tf, data  , "data" );
    sc_trace(Tf, clk, "Clock"); 
    sc_trace(Tf, reset  , "reset" );

    
    sc_start(500, SC_NS);  // run for 260 ns (12 clock cycles)
    sc_close_vcd_trace_file(Tf); 

    
    






    // Clock, module instances, interconnections, etc...
    

    return 0;
}