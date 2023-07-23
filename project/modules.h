#include "systemc.h"
#include "digit.h"

/*
HW Multiplier
out = input1 * input2
*/
SC_MODULE(multiply){
    sc_in <NN_DIGIT> input1;
    sc_in <NN_DIGIT> input2; 
    sc_out <NN_DIGIT> out; 

    void multiply_process(); 

    SC_CTOR(multiply){
        SC_METHOD(multiply_process);
        sensitive << input1 << input2; 
    }
}; 

/*
HW Adder
out = input1 + input2
*/
SC_MODULE(add){
    sc_in <NN_DIGIT> input1;
    sc_in <NN_DIGIT> input2;
    sc_out <NN_DIGIT> out; 

    void add_process();

    SC_CTOR(add){
        SC_METHOD(add_process); 
        sensitive << input1 << input2; 
    }
};

/*
HW subtractor
out = input1 - input2
*/
SC_MODULE(subtractor){
    sc_in <NN_DIGIT> input1;
    sc_in <NN_DIGIT> input2;
    sc_out <NN_DIGIT> out;

    void subtractor_process(); 

    SC_CTOR(subtractor){
        SC_METHOD(subtractor_process);
        sensitive << input1 << input2; 
    } 
}; 

/*
HW Multiplexor
if control == 0, out = input1
if control == 1, out = input2
*/
SC_MODULE(multiplex){
    sc_in <NN_DIGIT> input1; 
    sc_in <NN_DIGIT> input2; 
    sc_in <bool> control; 
    sc_out <NN_DIGIT> out; 

    void multiplex_process();

    SC_CTOR(multiplex){
        SC_METHOD(multiplex_process);
        sensitive << input1 << input2 << control; 
    }
};

/*
HW HIGH_HALF inplementation 
*/
SC_MODULE(hw_high_half){
    sc_in <NN_DIGIT> input; 
    sc_out <NN_DIGIT> out; 

    void hw_high_half_process(); 

    SC_CTOR(hw_high_half){
        SC_METHOD(hw_high_half_process);
        sensitive << input; 
    } 
};

/*
HW TO_HIGH_HALF implementation 
*/
SC_MODULE(hw_to_high_half){
    sc_in <NN_DIGIT> input; 
    sc_out <NN_DIGIT> out;

    void hw_to_high_half_process();

    SC_CTOR(hw_to_high_half){
        SC_METHOD(hw_to_high_half_process);
        sensitive << input; 
    } 
};


/*
HW LOW HALF Implementation 
*/
SC_MODULE(hw_low_half){
    sc_in <NN_DIGIT> input;
    sc_out <NN_DIGIT> out; 

    void hw_low_half_process();

    SC_CTOR(hw_low_half){
        SC_METHOD(hw_low_half_process);
        sensitive << input; 
    }
};

/*
HW comperator implimentation 
input1 > input2, return 1
else return 0 <- equal or less returns 0 
Here we are checking greater than tho so this is fine
*/
SC_MODULE(comperator){
    sc_in <NN_DIGIT> input1;
    sc_in <NN_DIGIT> input2;
    sc_out <bool> ls_Out; 

    void comperator_process(); 

    SC_CTOR(comperator){
        SC_METHOD(comperator_process);
        sensitive << input1 << input2; 
    }
}; 

/*
Simple HW register
***************FINISH DO I DO RESET OR LOAD????******************
*/
SC_MODULE(reg){
    sc_in_clk clk; 
    sc_in <NN_DIGIT> input;
    sc_in <bool> load; 
    sc_out <NN_DIGIT> out; 

    void reg_process();

    SC_CTOR(reg){
        SC_CTHREAD(reg_process, clk.pos());
        out.initialize(0); 
    }
};

/*
HW two-way Splitter
out1 = input
out2 = input
*/
SC_MODULE(splitter2){
    sc_in <NN_DIGIT> input;
    sc_out <NN_DIGIT> out1; 
    sc_out <NN_DIGIT> out2;

    void splitter2_process();

    SC_CTOR(splitter2){
        SC_METHOD(splitter2_process);
        sensitive << input; 
    }
};

/*
HW three-way Splitter
out1 = input
out2 = input
out3 = input 
*/
SC_MODULE(splitter3){
    sc_in <NN_DIGIT> input;
    sc_out <NN_DIGIT> out1; 
    sc_out <NN_DIGIT> out2;
    sc_out <NN_DIGIT> out3; 

    void splitter3_process();

    SC_CTOR(splitter3){
        SC_METHOD(splitter3_process);
        sensitive << input; 
    }
};
