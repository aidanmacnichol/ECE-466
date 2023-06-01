#include "systemc.h"
#include "modules.h"

void add::add_process(){

    out.write(input1.read() + input2.read());
}