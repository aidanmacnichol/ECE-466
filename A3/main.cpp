#include "systemc.h"
#include "adder.h"
#include "fork.h"
#include "generator.h"
#include "printer.h"
#include "hw_fifo.h"
#include "read_adapter.h"

int sc_main (int argc, char* argv[]) {
    DF_Const <int> constant ("constant", 1); // constant = 1
    DF_Fork <int> fork("fork"); 
    DF_Printer <int> printer ("printer", 10); // 10 interations
    sc_fifo <int> const_out ("const_out", 1); // FIFO of size 1

    hw_fifo <int> adder_out ("adder_out", 1); // Replaced with HW module

    FIFO_READ_HS <int> adapter ("adapter");
    HW_Adder <int> adder ("adder");




    sc_fifo <int> printer_in ("printer_in", 1); // FIFO of size 1
    sc_fifo <int> feedback ("feedback", 1); // FIFO of size 1

    feedback.write (40); // do not forget about initialization!

    sc_clock clk ("clk", 10, SC_NS, 0.5, 1, SC_NS); 

    //required fifo signals
    sc_signal <bool> adder_valid ("adder_valid");
    sc_signal <bool> fork_valid ("fork_valid");
    sc_signal <bool> adder_ready ("adder_ready");
    sc_signal <bool> fork_ready ("fork_ready");

    sc_signal <int> adder_data ("adder_data");
    sc_signal <int> fork_data ("fork_data");

    //Attach read adapter to fork input
    fork.input(adapter);

    // Required adapter signals:
    // clock, valid, ready, data
    adapter.clock(clk); 
    adapter.valid(fork_valid); 
    adapter.ready(fork_ready); 
    adapter.data(fork_data); 

    // Adder signals:
    // clock, data, valid, ready 
    adder.clock(clk); 
    adder.data(adder_data); 
    adder.valid(adder_valid); 
    adder.ready(adder_ready); 

    // Connect fork to adder
    adder_out.clk(clk); 
    adder_out.data_in (adder_data); adder_out.data_out (fork_data); 
    adder_out.valid_in (adder_valid); adder_out.valid_out (fork_valid); 
    adder_out.ready_out (adder_ready); adder_out.ready_in (fork_ready); 
    

    // Remaining hookups 
    constant.output (const_out); printer.input (printer_in); 
    adder.input1 (const_out); adder.input2(feedback); 
    fork.output1 (feedback); fork.output2(printer_in); 

    // Start simulation without time limit
    // The printer module is responsible for stopping the simulation
    sc_start ();
    return 0;
}
