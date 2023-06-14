<<<<<<< HEAD
#ifndef MODULES_H
#define MODULES_H
#include "systemc.h"

////////////////////////
// add - adds number A to number B
////////////////////////
SC_MODULE(add) {
    //
    // Ports
    //
    sc_in <float> input1; 
    sc_in <float> input2;	
    sc_out <float> out;

    void add_process();
    
    SC_CTOR(add) {
        SC_METHOD(add_process);
        sensitive << input1 << input2;
    }
};

////////////////////////
// multiply - multiplies number A with number B
////////////////////////
SC_MODULE(multiply) {
    //
    // Ports
    //
    sc_in <float> input1; 
    sc_in <float> input2;	
    sc_out <float> out;

    void multiply_process();
    
    SC_CTOR(multiply) {
        SC_METHOD(multiply_process);
        sensitive << input1 << input2;
    }
};

////////////////////////
// reg - word register with reset and load
////////////////////////
SC_MODULE(reg) {
    //
    // Ports
    //
    sc_in <bool> reset;
    sc_in_clk clock;
    sc_in <float> in; 
    sc_out <float> out;	

    void reg_process();
    
    SC_CTOR(reg) {
        SC_CTHREAD(reg_process, clock.pos());
    }
};


=======
#ifndef MODULES_H
#define MODULES_H
#include "systemc.h"

////////////////////////
// add - adds number A to number B
////////////////////////
SC_MODULE(add) {
    //
    // Ports
    //
    sc_in <float> input1; 
    sc_in <float> input2;	
    sc_out <float> out;

    void add_process();
    
    SC_CTOR(add) {
        SC_METHOD(add_process);
        sensitive << input1 << input2;
    }
};

////////////////////////
// multiply - multiplies number A with number B
////////////////////////
SC_MODULE(multiply) {
    //
    // Ports
    //
    sc_in <float> input1; 
    sc_in <float> input2;	
    sc_out <float> out;

    void multiply_process();
    
    SC_CTOR(multiply) {
        SC_METHOD(multiply_process);
        sensitive << input1 << input2;
    }
};

////////////////////////
// reg - word register with reset and load
////////////////////////
SC_MODULE(reg) {
    //
    // Ports
    //
    sc_in <bool> reset;
    sc_in_clk clock;
    sc_in <float> in; 
    sc_out <float> out;	

    void reg_process();
    
    SC_CTOR(reg) {
        SC_CTHREAD(reg_process, clock.pos());
    }
};


>>>>>>> e969b52edf14eaac20788d0ec172f64c8cbc5486
#endif