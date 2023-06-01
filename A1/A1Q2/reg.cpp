#include "systemc.h"
#include "modules.h"

void reg::reg_process() {
    
    while (1) {
        if (reset.read() == true){
        out.write(0);
        } else {
         out.write(in.read());
        }
        
	wait();
    }
}