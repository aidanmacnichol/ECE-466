#ifndef MEMORY_H
#define MEMORY_H

#include "systemc.h"

#define RDBLK 0
#define RDBYT 1
#define WTBYT 2
#define WTBLK 3

static const sc_lv<8> Z = "ZZZZZZZZ";


SC_MODULE(mem_ctrl) {

  sc_in < sc_uint<2> > comm;
  sc_in < sc_uint<8> > addr;
  sc_inout <sc_lv<8> > data;

  sc_in_clk clk;
  sc_in <bool> reset;
  sc_in <bool> new_comm;
  sc_out <bool> complete;

  sc_lv <8> memory[256] = {};	// memory space

  void mem_process() {	
  	sc_uint <2> comm_s;		// local variable: command sample
  	sc_uint <8> addr_s;		// local variable: address sample
  	sc_lv <8> data_s;		// local variable: data sample
	while (true) {
	  if (reset.read() == true) complete.write(false);
	  else {
	    if (new_comm.read() == true) { 
		comm_s = comm.read();
		switch (comm_s) {

        case RDBLK:
            addr_s = addr.read();
            data_s = memory[addr_s];
			cout << "@" << sc_time_stamp() 
	  		     << ": RDBLK-0, address = " << addr_s 
			     << ", data = " << data_s << endl;
            wait();
            data.write(data_s);
            addr_s++;
            data_s = memory[addr_s];
			cout << "@" << sc_time_stamp() 
	  		     << ": RDBLK-1, address = " << addr_s 
			     << ", data = " << data_s << endl;    
            wait();
            data.write(data_s);      
            addr_s++;
            data_s = memory[addr_s];
			cout << "@" << sc_time_stamp() 
	  		     << ": RDBLK-2, address = " << addr_s 
			     << ", data = " << data_s << endl;    
            wait();
            data.write(data_s);
            addr_s++;
            data_s = memory[addr_s];
			cout << "@" << sc_time_stamp() 
	  		     << ": RDBLK-3, address = " << addr_s 
			     << ", data = " << data_s << endl;    
            wait();
            data.write(data_s);
            break; 
        

		  case RDBYT:
		    addr_s = addr.read();
			data_s = memory[addr_s];		  	
			cout << "@" << sc_time_stamp() 
	  		     << ": RDBYT, address = " << addr_s 
			     << ", data = " << data_s << endl;
		  	wait();
			data.write(data_s);
		  	break;

		  case WTBYT:
		  	addr_s = addr.read();
			data_s = data.read();
			cout << "@" << sc_time_stamp() 
	  		     << ": WTBYT, address = " << addr_s 
			     << ", data = " << data_s << endl;
		  	wait(); 
		  	memory[addr_s] = data_s;
			break;

		  case WTBLK:
		  	addr_s = addr.read();
			data_s = data.read();
			cout << "@" << sc_time_stamp() 
	  		     << ": WTBLK-0, address = " << addr_s 
			     << ", data = " << data_s << endl;
		  	wait();
			memory[addr_s] = data_s;
			addr_s++;
			data_s = data.read();
			cout << "@" << sc_time_stamp() 
	  		     << ": WTBLK-1, address = " << addr_s 
			     << ", data = " << data_s << endl;
		  	wait();
			memory[addr_s] = data_s;
			addr_s++;
			data_s = data.read();
			cout << "@" << sc_time_stamp() 
	  		     << ": WTBLK-2, address = " << addr_s 
			     << ", data = " << data_s << endl;
		  	wait();
			memory[addr_s] = data_s;
			addr_s++;
			data_s = data.read();
			cout << "@" << sc_time_stamp() 
	  		     << ": WTBLK-3, address = " << addr_s 
			     << ", data = " << data_s << endl;
		  	wait();
			memory[addr_s] = data_s;			     
		  	break;

		default: 
		  	cout << "Illegal command : " << comm_s << endl;
		  	break;
		}
		complete.write(true);
		while (new_comm.read() == true) {
			if (reset.read() == true) break; 
			wait();
		}					//need to add RDBLK here
		if(comm_s == RDBYT || comm_s == RDBLK) data.write(Z);
		complete.write(false);

	    }
	  }
	  wait();
	}
  }

  SC_CTOR(mem_ctrl) { 
	SC_CTHREAD(mem_process, clk.pos()); 
  }

};

#endif