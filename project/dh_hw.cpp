#include "systemc.h"
#include "digit.h"
#include "dh_hw.h"

#define WAIT_STATE 0
#define EXECUTE_STATE 1
#define FINISH_STATE 2


void dh_hw::process_hw()
{

  NN_DIGIT t[2], c, u, v;
  NN_HALF_DIGIT aHigh, cLow, cHigh;

  sc_uint <2> state;
  
  for (;;) {  
  
	    // Read inputs (blocking FIFO access)
	    // t[0] = from_sw0.read();
	    // t[1] = from_sw1.read();
      // c = from_sw2.read();
      // aHigh = from_sw3.read();

		
	    // Original code from NN_DigitDivHH():	

//--------------------------MESSING AROUND--------------------------------------------

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
        // // ORIGINAL NN_DigitDivHH() code

        //   //READ INPUTS
        // 	t[0] = from_sw0.read();
	      //   t[1] = from_sw1.read();
        //   c = from_sw2.read();
        //   aHigh = from_sw3.read();

        //   cHigh = (NN_HALF_DIGIT)HIGH_HALF (c);
        //   cLow = (NN_HALF_DIGIT)LOW_HALF (c);

        //   u = (NN_DIGIT)aHigh * (NN_DIGIT)cLow;
        //   v = (NN_DIGIT)aHigh * (NN_DIGIT)cHigh;

        //   //t[0] = t[0] - TO_HIGH_HALF(u) > 
        //   if ((t[0] -= TO_HIGH_HALF (u)) > (MAX_NN_DIGIT - TO_HIGH_HALF (u))) t[1]--;

        //   t[1] -= HIGH_HALF (u); //t[1] = t[1] - HIGH_HALF(u); 
        //   t[1] -= v; //t[1] = t[1] - v

        ld_t1_in.write(1);
        t1_input.write(from_sw0.read());

        ld_t0_in.write(1);
        t0_input.write(from_sw1.read());

        ld_c_in.write(1); 
        c_input.write(from_sw2.read());

        ld_aHigh_in.write(1);
        aHigh_input.write(from_sw3.read()); 

          //START OF BONUS--------------------------------
          while ((t[1] > cHigh) || ((t[1] == cHigh) && (t[0] >= TO_HIGH_HALF (cLow)))) {
            if ((t[0] -= TO_HIGH_HALF (cLow)) > MAX_NN_DIGIT - TO_HIGH_HALF (cLow)) t[1]--;
              t[1] -= cHigh;
            aHigh++;
      }
      // END OF BONUS-----------------------------------------------------------


          // Write outputs (OG CODE)
          to_sw0.write(t0_out.read());
          to_sw1.write(t1_out.read());
	        to_sw2.write(aHigh_out.read());

          // Keep hw_done = false  
          hw_done.write(false); //This should probs be default before switch

          state = FINISH_STATE; 

        case FINISH_STATE:
          hw_done.write(true); 
          while(hw_enable.read() == true){
            wait(); 
          } 
          state = WAIT_STATE;
      }



//--------------------------END MESSING AROUND---------------------------------

      /*** Begin: Required part (to do: Datapath + Control) ***/
      // cHigh = (NN_HALF_DIGIT)HIGH_HALF (c);
      // cLow = (NN_HALF_DIGIT)LOW_HALF (c);
  
      // u = (NN_DIGIT)aHigh * (NN_DIGIT)cLow;
      // v = (NN_DIGIT)aHigh * (NN_DIGIT)cHigh;
      
      // if ((t[0] -= TO_HIGH_HALF (u)) > (MAX_NN_DIGIT - TO_HIGH_HALF (u))) t[1]--;
      
      // t[1] -= HIGH_HALF (u);
      // t[1] -= v;
      /*** End: Required part ***/

      /*** Begin: Bonus part (optional: Extra Datapath + Extra Control) ***/
      // while ((t[1] > cHigh) || ((t[1] == cHigh) && (t[0] >= TO_HIGH_HALF (cLow)))) {
      //     if ((t[0] -= TO_HIGH_HALF (cLow)) > MAX_NN_DIGIT - TO_HIGH_HALF (cLow)) t[1]--;
      //     t[1] -= cHigh;
      //     aHigh++;
      // }
      /*** End: Bonus part ***/
		
      // Write outputs (blocking FIFO access)
      // to_sw0.write(t[0]);
      // to_sw1.write(t[1]);
	    // to_sw2.write(aHigh);

    // wait(); 
    // wait(); 
  }
	  	  
}
