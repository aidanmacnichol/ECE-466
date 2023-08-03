#define SC_INCLUDE_FX
#include "systemc.h"
using namespace sc_dt; 

SC_MODULE(filter)
{
  sc_in <sc_fixed <16, 3, SC_TRN, SC_WRAP>> x;
  sc_out <sc_fixed <16, 3, SC_TRN, SC_WRAP>> y;

  sc_in_clk clock;
  sc_in<bool> reset;

  sc_fixed <16, 3, SC_TRN, SC_WRAP> c0, c1, c2, c3, c4;
  sc_signal <sc_fixed <16, 3, SC_TRN, SC_WRAP>> R0out, R1out, R2out, R3out, R4out;

  void seq_proc() {  
    while (1) {
      if (reset.read() == true) {
	      R0out.write(0);
	      R1out.write(0);
	      R2out.write(0);
        R3out.write(0);
        R4out.write(0);
	    }
      else {
 	      R0out.write( x.read() );
 	      R1out.write( R0out.read() );
 	      R2out.write( R1out.read() );
        R3out.write( y.read() );
        R4out.write( R3out.read() );
	    }
	    wait();
    }
  }

 
  void comb_proc() {
    sc_fixed <16, 3, SC_TRN, SC_WRAP> A, B;
    
    A = c0*x.read() + c1*R0out.read() + c2*R1out.read() + c3*R2out.read();
    B = c4*R4out.read();

    y.write( A+B );
  }

  
  SC_CTOR(filter) { 
    SC_CTHREAD(seq_proc, clock.pos());
    SC_METHOD(comb_proc);  sensitive << x << R0out << R1out << R2out << R4out;

    c0 = 0.1667;   c1 = -0.5;  c2 = 0.5;  c3 = -0.1667;  c4 = -0.3333;
  }

};