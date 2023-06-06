#include "systemc.h"
#include "modules.h"

void multiply::multiply_process(){
    out.write(input1.read() * input2.read());
}