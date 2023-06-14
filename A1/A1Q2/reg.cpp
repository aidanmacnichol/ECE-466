<<<<<<< HEAD
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
=======
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
>>>>>>> e969b52edf14eaac20788d0ec172f64c8cbc5486
}