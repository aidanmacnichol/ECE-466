#include "systemc.h"
#include "digit.h"
#include "dh_sw.h"
#include "dh_hw.h"

int sc_main(int argc , char *argv[]) {

	sc_signal <bool> enable{"enable"}, done;

	// Important: All FIFOs are of size 1.

	// sc_signal<NN_DIGIT> ch0(1), ch1(1), ch2(1), ch4(1), ch5(1);
	// sc_signal <NN_HALF_DIGIT> ch3(1), ch6(1);

	sc_signal<NN_DIGIT> ch0, ch1, ch2, ch4, ch5;
	sc_signal <NN_HALF_DIGIT> ch3, ch6{"ch6"};


  	sc_clock clk("clk", 10, SC_NS, 0.5, 1, SC_NS);

	
	

	enable.write(false);
	done.write(false);
	
	dh_sw DH_SW("DH_Software_Module");
	DH_SW.to_hw0(ch0);                 // output0 to hardware
	DH_SW.to_hw1(ch1);                 // output1 to hardware
	DH_SW.to_hw2(ch2);                 // output2 to hardware
	DH_SW.to_hw3(ch3);                 // output3 to hardware
 	DH_SW.from_hw0(ch4);               // input from hardware
 	DH_SW.from_hw1(ch5);               // input from hardware
 	DH_SW.from_hw2(ch6);               // input from hardware
	DH_SW.hw_enable(enable);           // hardware-enable output
	DH_SW.hw_done(done);               // hardware-done input
		
	dh_hw DH_HW("DH_Hardware_Module");
	DH_HW.clk(clk); 
	DH_HW.from_sw0(ch0);               // input0 from software
	DH_HW.from_sw1(ch1);               // input1 from software
	DH_HW.from_sw2(ch2);               // input2 from software
	DH_HW.from_sw3(ch3);               // input3 from software
 	DH_HW.to_sw0(ch4);                 // output to software
 	DH_HW.to_sw1(ch5);                 // output to software
 	DH_HW.to_sw2(ch6);                 // output to software
	DH_HW.hw_enable(enable);           // hardware-enable input
	DH_HW.hw_done(done);               // hardware-done output

	
	//For handshaking waveforms
	sc_trace_file* Tf = sc_create_vcd_trace_file("traces");
  	Tf->set_time_unit(1, SC_NS); //1ns time unit
  	sc_trace(Tf, enable  , "Enable" );
  	sc_trace(Tf, done  , "Done" );

  	sc_start(); 

  	sc_close_vcd_trace_file(Tf);

	return(0);
 
}