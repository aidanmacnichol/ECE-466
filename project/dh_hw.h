#ifndef _DH_HW_H_
#define _DH_HW_H_ 1

#include "systemc.h"
#include "digit.h"
#include "modules.h"

SC_MODULE (dh_hw)
{

  sc_in_clk clk; 

  sc_in <NN_DIGIT> from_sw0, from_sw1, from_sw2;
  sc_in <NN_HALF_DIGIT> from_sw3;

  sc_out <NN_DIGIT> to_sw0, to_sw1;
  sc_out <NN_HALF_DIGIT> to_sw2;
  
  sc_in <bool> hw_enable; 
  sc_out <bool> hw_done;


  // Interconnections:

  sc_signal <NN_DIGIT> t1_input, t1, t1_Bsub, t1_multp, Bsub_multp, multp_Csub, hwHH_Csub, Csub_Dsub, Bmult_Dsub, Dsub_t1regout, t1_out;
  sc_signal <NN_DIGIT> t0_input, t0, Csplit2_t0regout, Csplit2_Asub, Bsplit3_Asub, Esub_comp, t0_out, Asub_comp;
  sc_signal <NN_DIGIT> c_input, c, Asplit2_AhwHH, Asplit2_hwLH, AhwHH_Amult, hwLH_Bmult, Asplit3_Amult, Asplit3_Bmult, hwtoHH_Bsplit3, Bsplit3_BhwHH, Bsplit3_Esub, Amult_hwtoHH;
  sc_signal <NN_DIGIT> aHigh_input, aHigh, Asplit3_aHighregout, aHigh_out; 
  sc_signal <bool> ld_t1_in, ld_t0_in, ld_t1_out, ld_c_in, ld_t0_out, ld_aHigh_out, ld_aHigh_in, comp_multp;
  sc_signal <NN_DIGIT> const_1, const_MAXNNDIGIT; 

  sc_signal <NN_HALF_DIGIT> aHigh_input, aHigh, Asplit3_aHighregout
          //<UINT4>?
  void process_hw();
  
  // Initialize Modules

  //registers
  reg t0reg_in, t1reg_in, creg_in, aHighreg_in, t0reg_out, aHighreg_out, t1reg_out;
  //2-way splitters
  splitter2 Asplitter2, Bsplitter2, Csplitter2; 
  //3-way splitters
  splitter3 Asplitter3, Bsplitter3;
  //Multipliers
  multiply Amultiplier, Bmultiplier; 
  //Subtractors
  subtractor Asubtractor, Bsubtractor, Csubtractor, Dsubtractor, Esubtractor; 
  //Multiplexor
  multiplex multiplexor; 
  //Comperator
  comperator Acomperator; 
  //hw_high_half
  hw_high_half Ahw_high_half, Bhw_high_half;
  //hw_to_high_half
  hw_to_high_half Ahw_to_high_half; 
  //hw_low_half
  hw_low_half Ahw_low_half; 



  SC_CTOR(dh_hw):
  t0reg_in("t0reg_in"), t1reg_in("t1reg_in"), creg_in("creg_in"), aHighreg_in("aHighreg_in"), t0reg_out("t0reg_out"), 
  aHighreg_out("aHighreg_out"), t1reg_out("t1reg_out"),

  Asplitter2("Asplitter2"), Bsplitter2("Bsplitter2"), Csplitter2("Csplitter2"), 

  Asplitter3("Asplitter3"), Bsplitter3("Bsplitter3"),

  Amultiplier("Amultiplier"), Bmultiplier("Bmultiplier"),

  Asubtractor("Asubtractor"), Bsubtractor("Bsuctractor"), Csubtractor("Csubtractor"), Dsubtractor("Dsubtractor"), Esubtractor("Esubtractor"),

  multiplexor("multiplexror"), Acomperator("Acomperator"),

  Ahw_high_half("Ahw_high_half"), Bhw_high_half("Bhw_high_half"),

  Ahw_to_high_half("Ahw_to_high_half"), Ahw_low_half("Ahw_low_half")

  {
    const_MAXNNDIGIT.write(0xffffffff);
    const_1.write(0x1); 

// list of interconnection signals so far:
/*
t1_input, ld_t1_in, t1, t1_Bsub, t1_multp, Bsub_multp, comp_multp, multp_Csub, hwHH_Csub, Csub_Dsub, Bmult_Dsub, Dsub_t1regout
ld_t1_out, t1_out

t0_input, ld_t0_in, t0, Csplit2_t0regout, Csplit2_Asub, Bsplit3_Asub, Bsub_comp
t0_out, ld_t0_out,

c_input, ld_c_in, c, Asplit_AhwHH, Asplit_hwLH, AhwHH_Amult, hwLH_Bmult, Asplit3_Amult, Asplit3_Bmult,
hwtoHH_Bsplit3, Bsplit3_BhwHH, Bsplit3_Bsub

aHigh_input, ld_aHigh_in, aHigh, Asplit3_aHighregout, ld_aHigh_out, aHigh_out

const_1, const_MAXNNDIGIT
*/

  //-------------------------------------t[1] datapath--------------------------------------------
  t1reg_in.clk(clk); t1reg_in.input(t1_input); t1reg_in.load(ld_t1_in); t1reg_in.out(t1); 
  Bsplitter2.input(t1); Bsplitter2.out1(t1_Bsub); Bsplitter2.out2(t1_multp); 
  Bsubtractor.input1(t1_Bsub); Bsubtractor.input2(const_1); Bsubtractor.out(Bsub_multp);
  multiplexor.input1(t1_multp); multiplexor.input2(Bsub_multp); multiplexor.control(comp_multp); multiplexor.out(multp_Csub);
  Csubtractor.input1(multp_Csub); Csubtractor.input2(hwHH_Csub); Csubtractor.out(Csub_Dsub);
  Dsubtractor.input1(Csub_Dsub); Dsubtractor.input2(Bmult_Dsub); Dsubtractor.out(Dsub_t1regout);
  t1reg_out.clk(clk); t1reg_out.input(Dsub_t1regout); t1reg_out.load(ld_t1_out); t1reg_out.out(t1_out);

  //-------------------------------------t[0] datapath--------------------------------------------
  t0reg_in.clk(clk); t0reg_in.input(t0_input); t0reg_in.load(ld_t0_in); t0reg_in.out(t0);
  Csplitter2.input(t0); Csplitter2.out1(Csplit2_t0regout); Csplitter2.out2(Csplit2_Asub); 
  t0reg_out.clk(clk); t0reg_out.input(Csplit2_t0regout); t0reg_out.load(ld_t0_out); t0reg_out.out(t0_out);
  Asubtractor.input1(Csplit2_Asub); Asubtractor.input2(Bsplit3_Asub); Asubtractor.out(Asub_comp); 
  Acomperator.input1(Asub_comp); Acomperator.input2(Esub_comp); Acomperator.ls_Out(comp_multp); 

  //-------------------------------------c datapath---------------------------------------------------
  creg_in.clk(clk); creg_in.input(c_input); creg_in.load(ld_c_in); creg_in.out(c); 
  Asplitter2.input(c); Asplitter2.out1(Asplit2_AhwHH); Asplitter2.out2(Asplit2_hwLH);
  Ahw_high_half.input(Asplit2_AhwHH); Ahw_high_half.out(AhwHH_Amult);
  Ahw_low_half.input(Asplit2_hwLH); Ahw_low_half.out(hwLH_Bmult); 
  Amultiplier.input1(AhwHH_Amult); Amultiplier.input2(Asplit3_Amult); Amultiplier.out(Amult_hwtoHH); 
  Bmultiplier.input1(hwLH_Bmult); Bmultiplier.input2(Asplit3_Bmult); Bmultiplier.out(Bmult_Dsub); 

  Ahw_to_high_half.input(Amult_hwtoHH); Ahw_to_high_half.out(hwtoHH_Bsplit3); 
  Bsplitter3.input(hwtoHH_Bsplit3); Bsplitter3.out1(Bsplit3_BhwHH); Bsplitter3.out2(Bsplit3_Asub); Bsplitter3.out3(Bsplit3_Esub);
  Esubtractor.input1(Bsplit3_Esub); Esubtractor.input2(const_MAXNNDIGIT); Esubtractor.out(Esub_comp);
  Bhw_high_half.input(Bsplit3_BhwHH); Bhw_high_half.out(hwHH_Csub);

  //-----------------------------------aHigh datapath-------------------------------------------------
  aHighreg_in.clk(clk); aHighreg_in.input(aHigh_input); aHighreg_in.load(ld_aHigh_in); aHighreg_in.out(aHigh); 
  Asplitter3.input(aHigh); Asplitter3.out1(Asplit3_aHighregout); Asplitter3.out2(Asplit3_Amult); Asplitter3.out3(Asplit3_Bmult); 
  aHighreg_out.clk(clk); aHighreg_out.input(Asplit3_aHighregout); aHighreg_out.load(ld_aHigh_out); aHighreg_out.out(aHigh_out); 

  // SC_CTOR (dh_hw)
  // {
  //   SC_THREAD (process_hw); // DONT I NEED TO ADD clock.pos() here????
  //   sensitive << clock.pos(); 
  // }

  SC_CTHREAD(process_hw, clk.pos()); 
  }
};

#endif /* end _DH_HW_H_ */