#include "systemc.h"
#include "modules.h"

void multiply::multiply_process(){
    out.write(input1.read()*input2.read()); 
}

void add::add_process(){
    out.write(input1.read() + input2.read()); 
}

void subtractor::subtractor_process(){
    out.write(input1.read() - input2.read()); 
}

void multiplex::multiplex_process(){
    if (control.read() == 0){
        out.write(input1.read());
    } else {
        out.write(input2.read()); 
    }
}

void hw_high_half::hw_high_half_process(){
    out.write(HIGH_HALF(input.read())); 
}

void hw_to_high_half::hw_to_high_half_process(){
    out.write(TO_HIGH_HALF(input.read())); 
}

void hw_low_half::hw_low_half_process(){
    out.write(LOW_HALF(input.read())); 
}

void comperator::comperator_process(){
    if(input1.read() > input2.read()){
        ls_Out.write(1);
    } else {
        ls_Out.write(0); 
    }
}

void reg::reg_process(){
    while(true){
        if(load.read() == 1){
            out.write(input.read());
        }
        wait(); 
    }
}

void splitter2::splitter2_process(){
    out1.write(input);
    out2.write(input); 
}

void splitter3::splitter3_process(){
    out1.write(input);
    out2.write(input); 
    out3.write(input); 
}