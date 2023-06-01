#ifndef FILTER_H
#define FILTER_H
#include "systemc.h"
#include "modules.h"

SC_MODULE(filter){

    sc_in_clk clock;
    sc_in <bool> reset;
    sc_in <float> x;
    sc_out <float> y;

    sc_signal <float> a0, a1, a2, a3, a4;
    sc_signal <float> R0out, R1out, R2out, R3out, R4out; 
    sc_signal <float> M0out, M1out, M2out, M3out, M4out; 
    sc_signal <float> A0out, A1out, A2out; 

 
    add ADD0, ADD1, ADD2, ADD3; // adder instances
    multiply MULT0, MULT1, MULT2, MULT3, MULT4; // multiplier instances
    reg REG0, REG1, REG2, REG3, REG4; // register instances


        SC_CTOR(filter):
            ADD0("ADD0"), ADD1("ADD1"), ADD2("ADD2"), ADD3("ADD3"),

            MULT0("MULT0"), MULT1("MULT1"), MULT2("MULT2"),
            MULT3("MULT3"), MULT4("MULT4"),

            REG0("REG0"), REG1("REG1"), REG2("REG2"), 
            REG3("REG3"), REG4("REG4"){

                a0.write(0.1667); a1.write(-0.5); a2.write(0.5);
                a3.write(-0.1667); a4.write(-0.3333);

                //Left side multiplication
                MULT0.input1(x); MULT0.input2(a0); MULT0.out(M0out);
                MULT1.input1(R0out); MULT1.input2(a1); MULT1.out(M1out);
                MULT2.input1(R1out); MULT2.input2(a2); MULT2.out(M2out);
                MULT3.input1(R2out); MULT3.input2(a3); MULT3.out(M3out);

                //Right side addition
                ADD0.input1(M0out); ADD0.input2(M1out); ADD0.out(A0out);
                ADD1.input1(A0out); ADD1.input2(M2out); ADD1.out(A1out);
                ADD2.input1(A1out); ADD2.input2(M3out); ADD2.out(A2out);

                //Right side addition
                ADD3.input1(A2out); ADD3.input2(M4out); ADD3.out(y);

                //Right side multiplication
                MULT4.input1(R4out); MULT4.input2(a4); MULT4.out(M4out); 

                //Z register connections
                REG0.reset(reset); REG0.clock(clock); REG0.in(x); REG0.out(R0out);
                REG1.reset(reset); REG1.clock(clock); REG1.in(R0out); REG1.out(R1out);
                REG2.reset(reset); REG2.clock(clock); REG2.in(R1out); REG2.out(R2out);
                REG3.reset(reset); REG3.clock(clock); REG3.in(y); REG3.out(R3out);
                REG4.reset(reset); REG4.clock(clock); REG4.in(R3out); REG4.out(R4out);



        }
    };

#endif