#include "systemc.h"

SC_MODULE(filterA1)
{
    sc_in_clk clock;
    sc_in <bool> reset;

    sc_in <float> x;
    sc_out <float> y;

    float a0, a1, a2, a3, a4; //filter coefficients 

    sc_signal <float> R0out, R1out, R2out, R3out, R4out; //internal signals (think I need more here)

    //Use this to copy y into so we dont have to read an output

/* There will be no RXin signals they are mapped to the following:
        R0in = x, 
        R0out = R1in, 
        R1out = R2in, 
        R3in = y, 
        R3out = R4in
*/


    void seq_proc(){
        while(1){
            if(reset.read() == true){
                R0out.write(0);
                R1out.write(0);
                R2out.write(0);
                R3out.write(0);
                R4out.write(0);
            }
            else {
                R0out.write(x.read());
                R3out.write(y.read()); //Do I need to change y to R3in.read() and set R3 in as a copy of y?
                //R3out.write(R3in.read());

            }
            wait();
        }
    }

    void comb_proc(){
        float xs = x.read();
        float R0s = R0out.read(); 
        float R1s = R1out.read();
        float R2s = R2out.read();
        float R3s = R3out.read();
        float R4s = R4out.read();

        y.write((xs*a0 + R0s*a1 + R1s*a2  + R2s*a3) + R3s*R4s*a4);

        // float var = (xs*a0 + R0s*a1 + R1s*a2  + R2s*a3) + R3s*R4s*a4;
        // y.write(var);
        // R3in.write(var);
    }


    SC_CTOR(filterA1)
    {
        SC_METHOD(comb_proc); 
        sensitive << x << R0out << R1out << R2out << R3out << R4out;

        SC_CTHREAD(seq_proc, clock.pos());

        a0 = 0.1667;
        a1 = -0.5;
        a2 = 0.5;
        a3 = -0.1667;
        a4 = -0.3333;
    }
};

