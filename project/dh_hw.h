#ifndef _DH_HW_H_
#define _DH_HW_H_ 1

#include "systemc.h"
#include "digit.h"
#include "modules.h"

SC_MODULE (dh_hw)
{

  sc_in_clk clk {"clk"}; 

  sc_in <NN_DIGIT> from_sw0, from_sw1, from_sw2;
  sc_in <NN_HALF_DIGIT> from_sw3;

  sc_out <NN_DIGIT> to_sw0 {"to_sw0"}, to_sw1{"to_sw1"};
  sc_out <NN_HALF_DIGIT> to_sw2{"to_sw2"};
  
  sc_in <bool> hw_enable; 
  sc_out <bool> hw_done;


  // Interconnections:

  //Constants
  sc_signal<NN_DIGIT> const_MAXNNDIGIT, const_1;

  //t[1] Path
  sc_signal<NN_DIGIT> t1, Bsub_multp, multp_Csub, Dhtf_Csub, Csub_Dsub, Bmult_Dsub, Dsub_t1regout, t1_out;
  sc_signal<bool> comp_multp;

  //t[0] Path
  sc_signal<NN_DIGIT> t0, Asub_comp, t0_out, toHH_out, Esub_comp; 

  //c path
  sc_signal<NN_DIGIT> c_med, a_half_to_full_out, b_half_to_full_out, Amult_hwtoHH;
  sc_signal<NN_HALF_DIGIT> AhwHH_out, cHigh_out, hwLH_out, cLow_out; 

  //aHigh path 
  sc_signal<NN_DIGIT> Chalf_to_full_out; 
  sc_signal<NN_HALF_DIGIT> aHigh_med, aHigh_out;

  //Register Loads
  sc_signal<bool> ld_c_in, ld_t0_in, ld_t1_in, ld_aHigh_in, ld_cHigh_in, ld_cLow_in; 
  sc_signal<bool> ld_c_out, ld_t0_out, ld_t1_out, ld_aHigh_out, ld_cHigh_out, ld_cLow_out; 

  //Bonus Part
  sc_signal<NN_DIGIT> t0new, t1new; 
  sc_signal<NN_HALF_DIGIT> AHnew; 
  sc_signal<bool> bonus_ready; 


  
  void process_hw();

  //Full Digit Registers
  reg creg_in, t1reg_in, t0reg_in,  t0reg_out, t1reg_out;
  //Half Digit Registers
  half_digit_reg aHighreg_in, aHighreg_out; 
  //Multipliers
  multiply Amultiplier, Bmultiplier; 
  //Subtractors
  subtractor Asubtractor, Bsubtractor, Csubtractor, Dsubtractor, Esubtractor; 
  //Multiplexor
  multiplex multiplexor; 
  //Comperator
  comperator Acomperator; 
  //hw_high_half (half digit out)
  hw_high_half Ahw_high_half;
  //hw_high_half (full digit out)
  hw_Bhigh_half Bhw_high_half;
  //hw_to_high_half
  hw_to_high_half Ahw_to_high_half; 
  //hw_low_half
  hw_low_half Ahw_low_half; 
  //Half to Full digit 
  half_to_full Ahalf_to_full, Bhalf_to_full, Chalf_to_full; 
  //Bonus Module
  bonus BONUS; 

  SC_CTOR(dh_hw):
  //Full Digit Registers
  creg_in("creg_in"), t1reg_in("t1reg_in"), t0reg_in("t0reg_in"), t0reg_out("t0reg_out"), t1reg_out("t1reg_out"),
  //Half Digit Registers
  aHighreg_in("aHighreg_in"), aHighreg_out("aHighreg_out"),
  //Multipliers
  Amultiplier("Amultiplier"), Bmultiplier("Bmultiplier"),
  //Subtractors
  Asubtractor("Asubtractor"), Bsubtractor("Bsuctractor"), Csubtractor("Csubtractor"), Dsubtractor("Dsubtractor"), 
  Esubtractor("Esubtractor"),
  //Multiplexor & Comperator
  multiplexor("multiplexor"), Acomperator("Acomperator"),
  //HW_HIGH_HALF
  Ahw_high_half("Ahw_high_half"), Bhw_high_half("Bhw_high_half"),
  //HW_TO_HIGH_HALF
  Ahw_to_high_half("Ahw_to_high_half"),
  //HW_LOW_HALF
  Ahw_low_half("Ahw_low_half"),
  //HALF_DIGIT to FULL_DIGIT  
  Ahalf_to_full("Ahalf_to_full"), Bhalf_to_full("Bhalf_to_full"), Chalf_to_full("Chalf_to_full"), 
  //Bonus Module
  BONUS("BONUS")

  {

    //Write Constants
    const_MAXNNDIGIT.write(0xffffffff);
    const_1.write(0x1); 



  //-------------------------------------t[1] datapath--------------------------------------------
  t1reg_in.clk(clk); t1reg_in.input(from_sw1); t1reg_in.load(ld_t1_in); t1reg_in.out(t1);
  Bsubtractor.input1(t1); Bsubtractor.input2(const_1); Bsubtractor.out(Bsub_multp);
  multiplexor.input1(t1); multiplexor.input2(Bsub_multp); multiplexor.control(comp_multp); multiplexor.out(multp_Csub);
  Csubtractor.input1(multp_Csub); Csubtractor.input2(Dhtf_Csub); Csubtractor.out(Csub_Dsub);
  Dsubtractor.input1(Csub_Dsub); Dsubtractor.input2(Bmult_Dsub); Dsubtractor.out(Dsub_t1regout);

  //-------------------------------------t[0] datapath--------------------------------------------
  t0reg_in.clk(clk); t0reg_in.input(from_sw0); t0reg_in.load(ld_t0_in); t0reg_in.out(t0);
  Asubtractor.input1(t0); Asubtractor.input2(toHH_out); Asubtractor.out(Asub_comp); 
  Acomperator.input1(Asub_comp); Acomperator.input2(Esub_comp); Acomperator.ls_Out(comp_multp); 

  //-------------------------------------c datapath---------------------------------------------------
  creg_in.clk(clk); creg_in.input(from_sw2); creg_in.load(ld_c_in); creg_in.out(c_med);  
  Ahw_high_half.input(c_med); Ahw_high_half.out(AhwHH_out);
  Ahw_low_half.input(c_med); Ahw_low_half.out(hwLH_out); 
  Ahalf_to_full.input(AhwHH_out); Ahalf_to_full.out(a_half_to_full_out); 
  Bhalf_to_full.input(hwLH_out); Bhalf_to_full.out(b_half_to_full_out);
  //cLow and cHigh output here
  // cLowreg_out.clk(clk); cLowreg_out.input(hwLH_out); cLowreg_out.load(ld_cLow_out); cLowreg_out.out(cLow_out); 
  // cHighreg_out.clk(clk); cHighreg_out.input(AhwHH_out); cHighreg_out.load(ld_cHigh_out); cHighreg_out.out(cHigh_out);

  Amultiplier.input1(b_half_to_full_out); Amultiplier.input2(Chalf_to_full_out); Amultiplier.out(Amult_hwtoHH); 
  Bmultiplier.input1(a_half_to_full_out); Bmultiplier.input2(Chalf_to_full_out); Bmultiplier.out(Bmult_Dsub); 
  Ahw_to_high_half.input(Amult_hwtoHH); Ahw_to_high_half.out(toHH_out);
  Esubtractor.input1(const_MAXNNDIGIT); Esubtractor.input2(toHH_out); Esubtractor.out(Esub_comp);
  Bhw_high_half.input(Amult_hwtoHH); Bhw_high_half.out(Dhtf_Csub);

  //-----------------------------------aHigh datapath-------------------------------------------------
  aHighreg_in.clk(clk); aHighreg_in.input(from_sw3); aHighreg_in.load(ld_aHigh_in); aHighreg_in.out(aHigh_med); 
  Chalf_to_full.input(aHigh_med); Chalf_to_full.out(Chalf_to_full_out); 

  //-----------------------------------BONUS MODULE---------------------------------------------------

  BONUS.T0(Asub_comp); BONUS.T1(Dsub_t1regout); BONUS.C(c_med); BONUS.AH(aHigh_med);
  BONUS.T0new(t0new); BONUS.T1new(t1new); BONUS.AHnew(AHnew); 
  BONUS.clock(clk); BONUS.ready(bonus_ready);

  t1reg_out.clk(clk); t1reg_out.input(t1new); t1reg_out.load(ld_t1_out); t1reg_out.out(t1_out);
  t0reg_out.clk(clk); t0reg_out.input(t0new); t0reg_out.load(ld_t0_out); t0reg_out.out(t0_out);
  aHighreg_out.clk(clk); aHighreg_out.input(AHnew); aHighreg_out.load(ld_aHigh_out); aHighreg_out.out(aHigh_out);


  SC_CTHREAD(process_hw, clk.pos()); 
  }
};

#endif /* end _DH_HW_H_ */