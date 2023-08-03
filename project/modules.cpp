#include "systemc.h"
#include "modules.h"


void reg::reg_process(){
    while(true){
        if(load.read() == true){
            out.write(input.read()); 
        } 
        wait(); 
    }
}

void half_digit_reg::half_digit_reg_process(){
        while(true){
        if(load.read() == true){
            out.write(input.read());
        } 
        wait(); 
    }
}

void multiply::multiply_process(){
    out.write(input1.read()*input2.read()); 
}

void subtractor::subtractor_process(){
    out.write(input1.read() - input2.read()); 
}

void multiplex::multiplex_process(){
    if (control.read() == false){
        out.write(input1.read());
    } else {
        out.write(input2.read()); 
    }
}

void comperator::comperator_process(){
    if(input1.read() > input2.read()){
        ls_Out.write(true);
    } else {
        ls_Out.write(false); 
    }
}

void hw_high_half::hw_high_half_process(){
    out.write((NN_HALF_DIGIT)HIGH_HALF(input.read())); 
}

void hw_Bhigh_half::hw_Bhigh_half_process(){
    out.write(HIGH_HALF(input.read())); 
}

void hw_to_high_half::hw_to_high_half_process(){
    out.write(TO_HIGH_HALF(input.read())); 
}

void hw_low_half::hw_low_half_process(){
    out.write((NN_HALF_DIGIT)LOW_HALF(input.read())); 
}

void half_to_full::half_to_full_process(){
    out.write((NN_DIGIT)input); 
}

