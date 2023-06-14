<<<<<<< HEAD
#include "systemc.h"
#include "modules.h"

void multiply::multiply_process(){
    out.write(input1.read() * input2.read());
=======
#include "systemc.h"
#include "modules.h"

void multiply::multiply_process(){
    out.write(input1.read() * input2.read());
>>>>>>> e969b52edf14eaac20788d0ec172f64c8cbc5486
}