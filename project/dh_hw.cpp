#include "systemc.h"
#include "digit.h"
#include "dh_hw.h"

#define WAIT_STATE 0
#define INPUT_STATE 1
#define EXECUTE_REQUIRED_STATE 2
#define EXECUTE_BONUS_STATE 3
#define OUTPUT_STATE 4
#define FINISH_STATE 5


void dh_hw::process_hw()
{

  //initially in the wait state
  sc_uint <5> state = WAIT_STATE;

  //initially false
  hw_done.write(false);
  
  for (;;) {  
  
      //reset register load flags
      ld_t1_in.write(0); 
      ld_t0_in.write(0);
      ld_c_in.write(0); 
      ld_aHigh_in.write(0);
      ld_t1_out.write(0);
      ld_t0_out.write(0);
      ld_aHigh_out.write(0);  
      bonus_ready.write(0); 

 
      switch(state)
      {
        case WAIT_STATE:
          hw_done.write(false); 
          if(hw_enable.read() == true){
            state = INPUT_STATE; 
          }
          break; 
        

        case INPUT_STATE:
          //Load Input Registers
          ld_t1_in.write(1); 
          ld_t0_in.write(1);
          ld_c_in.write(1); 
          ld_aHigh_in.write(1);
           
          state = EXECUTE_REQUIRED_STATE; 
          break; 
        
        
        case EXECUTE_REQUIRED_STATE:
          //Required done, set bonus ready
          bonus_ready.write(1);

          state = EXECUTE_BONUS_STATE; 
          break; 

        case EXECUTE_BONUS_STATE:
          //Bonus done, load output registers
          ld_t0_out.write(1);
          ld_t1_out.write(1);
          ld_aHigh_out.write(1);

          state = OUTPUT_STATE; 
          break; 

        case OUTPUT_STATE:
          //write output values
          to_sw0.write(t0_out.read());
          to_sw1.write(t1_out.read());
          to_sw2.write(aHigh_out.read()); 

          state = FINISH_STATE; 
          break;

        case FINISH_STATE:
          hw_done.write(true); 
          if(hw_enable.read() == false){
            state = WAIT_STATE; 
          } 
          break; 
      }

      // Required for timing
      wait(); 
      wait(); 
  }  
}

