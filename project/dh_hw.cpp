#include "systemc.h"
#include "digit.h"
#include "dh_hw.h"

#define WAIT_STATE 0
#define EXECUTE_STATE 1
#define FINISH_STATE 2


void dh_hw::process_hw()
{

  NN_DIGIT t[2];
  NN_HALF_DIGIT aHigh, cLow, cHigh;

  sc_uint <2> state;
  
  for (;;) {  
  
      //initial state is wait
      state = WAIT_STATE; 
      hw_done.write(false); 
 
      switch(state)
      {
        case WAIT_STATE:
          hw_done.write(false); 
          while(hw_enable.read() == false){
            wait(); 
          }
          state = EXECUTE_STATE;
        
        case EXECUTE_STATE:

        // Load Input Registers
        ld_t1_in.write(1); 
        ld_t0_in.write(1);
        ld_c_in.write(1); 
        ld_aHigh_in.write(1); 

        wait();
        wait(); 

        ld_t1_in.write(0);
        ld_t0_in.write(0);
        ld_c_in.write(0); 
        ld_aHigh_in.write(0); 

        //Load output Registers
        ld_cLow_out.write(1); 
        ld_cHigh_out.write(1); 
        ld_t0_out.write(1);
        ld_t1_out.write(1); 
        ld_aHigh_out.write(1); 

        wait(); 
        wait(); 
  
        // Get values from output registers (for bonus)
        cLow = cLow_out.read(); 
        cHigh = cHigh_out.read(); 
        t[0] = t0_out.read();
        t[1] = t1_out.read(); 
        aHigh = aHigh_out.read();

        //Disable loads Output Registers
        ld_cLow_out.write(0); 
        ld_cHigh_out.write(0); 
        ld_t0_out.write(0);
        ld_t1_out.write(0); 
        ld_aHigh_out.write(0); 

        wait(); 
        wait(); 

          //START OF BONUS--------------------------------
          while ((t[1] > cHigh) || ((t[1] == cHigh) && (t[0] >= TO_HIGH_HALF (cLow)))) {
            if ((t[0] -= TO_HIGH_HALF (cLow)) > MAX_NN_DIGIT - TO_HIGH_HALF (cLow)) t[1]--;
              t[1] -= cHigh;
            aHigh++;
      }
      // END OF BONUS-----------------------------------------------------------

          //Write Outputs
          to_sw0.write(t[0]);
          to_sw1.write(t[1]);
	        to_sw2.write(aHigh);

          // Keep hw_done = false  
          hw_done.write(false);

          state = FINISH_STATE; 

        case FINISH_STATE:
          hw_done.write(true); 
          while(hw_enable.read() == true){
            wait(); 
          } 
          state = WAIT_STATE;
      }
 
  }
	  	  
}
