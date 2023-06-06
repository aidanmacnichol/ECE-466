#include "systemc.h"
#include "fifo.h"

class producer : public sc_module 
{
public:
  sc_port <fifo_out_if> out;
  sc_in_clk Clock;
  
  void do_writes()
  {
    int i = 0;
    while (true) 
    {
      wait();           // wait for clock edge
      out->write(i); 
      cout << "W " << i << " at " << sc_time_stamp() << endl;
      i = (i+1) % 10;	// Reset to 0 after 9 is reached **should this be 9 or 10?
    }
  } 
    
  SC_CTOR(producer)
  {
    SC_THREAD(do_writes);
    sensitive << Clock.pos();
  }
};



class consumer : public sc_module 
{
public:
  sc_port <fifo_in_if> in;
  sc_in_clk Clock;
  
  void do_reads()
  {
    int i = 0;
    char c;
    while (true) 
    {
      wait();           // wait for clock edge
      in->read(c); 
      cout << "R " << c << " at " << sc_time_stamp() << endl;
      i = (i+1) % 13;	// length of "Hello, world!"
    }
  } 
    
  SC_CTOR(consumer)
  {
    SC_THREAD(do_reads);
    sensitive << Clock.pos();
  }
};




int sc_main(int argc, char* argv[])
{
  sc_clock ClkProducer("ClkProducer", 10, SC_NS); //Producer Clock
  sc_clock ClkConsumer("ClkConsumer", 20, SC_NS); //Consumer Clock

  fifo Fifo1 ("F1", 4);

  producer P1("P1");
  P1.out(Fifo1);
  P1.Clock(ClkProducer);

  consumer C1("C1");
  C1.in(Fifo1);
  C1.Clock(ClkConsumer);

  sc_start(1001, SC_NS);

  return 0;
}