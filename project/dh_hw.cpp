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

  NN_DIGIT t[2];
  NN_HALF_DIGIT aHigh, cLow, cHigh;

  sc_uint <5> state = WAIT_STATE;

  //initially false
  hw_done.write(false);
  
  for (;;) {  
  
      //initial state is wait
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
          ld_t1_in.write(1); 
          ld_t0_in.write(1);
          ld_c_in.write(1); 
          ld_aHigh_in.write(1); 
          wait(); 
          wait(); 
          state = EXECUTE_REQUIRED_STATE; 
          break; 
        
        
        case EXECUTE_REQUIRED_STATE:
          wait(); 
          state = EXECUTE_BONUS_STATE; 
          break; 

        case EXECUTE_BONUS_STATE:
          bonus_ready.write(1); 
          wait(); 
          state = OUTPUT_STATE; 
          break; 

        case OUTPUT_STATE:
          //throw std::invalid_argument("in output state");
          bonus_ready.write(0); 
          ld_t0_out.write(1);
          ld_t1_out.write(1);
          ld_aHigh_out.write(1);
          wait();
          wait();   

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

      wait(); 
      wait(); 
  }  
}


        // wait();
        // wait(); 

        // ld_t1_in.write(0);
        // ld_t0_in.write(0);
        // ld_c_in.write(0); 
        // ld_aHigh_in.write(0); 

        // //Load output Registers
        // ld_cLow_out.write(1); 
        // ld_cHigh_out.write(1); 
        // ld_t0_out.write(1);
        // ld_t1_out.write(1); 
        // ld_aHigh_out.write(1); 

        // wait(); 
        // wait(); 
  
        // // Get values from output registers (for bonus)
        // cLow = cLow_out.read(); 
        // cHigh = cHigh_out.read(); 
        // t[0] = t0_out.read();
        // t[1] = t1_out.read(); 
        // aHigh = aHigh_out.read();

        // //Disable loads Output Registers
        // ld_t0_out.write(0);
        // ld_t1_out.write(0); 
        // ld_aHigh_out.write(0); 

        // wait(); 
        // wait(); 
