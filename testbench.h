#ifndef TESTBENCH_H
#define TESTBENCH_H


#include "systemc.h"
#include "memory.h"


SC_MODULE(mem_testbench) {


    sc_out<bool> new_comm;
    sc_in<bool> complete; 
    sc_in<bool> reset; //
    sc_inout <sc_lv<8>> data; //

    sc_out <sc_uint<2>> comm; 

    sc_out <sc_uint<8>> addr; 

    sc_in_clk clk; //

    //sc_lv <8> buffer[4];

    //sc_rv <sc_lv <8>> buffer[4]; //= {0000000, 00001111, 11110000, 11111111};

    // buffer[0] = "00000000";
    // buffer[1] = "00001111";
    // buffer[2] = "11110000";
    // buffer[3] = "11111111";

    void mem_test()
    {


        sc_lv <8> data_s;
        sc_lv <8> buffer[4];
        buffer[0] = "00000000";
        buffer[1] = "00001111";
        buffer[2] = "11110000";
        buffer[3] = "11111111";

        new_comm.write(false); //set default value to false
//------------------------------------------------------------------------------
        addr.write(255);
        comm.write(WTBYT);
        new_comm.write(true);
        data.write("00001111");
        wait();

        while(complete.read() == true){
            if(reset.read()==true) break;
            new_comm.write(false);
            wait();
        }

        addr.write(255);
        comm.write(RDBYT);
        new_comm.write(true);
        wait();
        wait();
        wait();
        data_s = data.read(); 
        wait(); 

        while(complete.read() == true){
            if(reset.read()==true) break;
            new_comm.write(false);
            wait();
        }



//------------------------------------------------------------------------------

        addr.write(64);
        comm.write(WTBLK);
        new_comm.write(true);
        data.write(buffer[0]);
        wait();
        data.write(buffer[1]);
        wait();
        data.write(buffer[2]);
        wait();
        data.write(buffer[3]);
        wait();


        while(complete.read() == true){
            if(reset.read()==true) break;
            new_comm.write(false);
            wait();
        }

        addr.write(64);
        comm.write(RDBLK);
        new_comm.write(true);
        wait();
        wait();
        wait();

        buffer[0] = data.read();
        wait();
        buffer[1] = data.read();
        wait();
        buffer[2] = data.read();
        wait();
        buffer[3] = data.read();
        wait();

        while(complete.read() == true){
            if(reset.read()==true) break;
            new_comm.write(false);
            wait();
        }
    }
    /*

    new_comm is what I am handling here
    
    new_comm = true && complete = false
    do all the memory writing shit
    complete = true
    new_comm = false
    complete = false
    
    */

    SC_CTOR(mem_testbench){
        SC_CTHREAD(mem_test, clk.pos());
    }

};

#endif