#include "systemc.h"
#include "fifo.h"
#include "producer.h"
#include "consumer.h"

int sc_main(int argc, char* argv[])
{
  

  sc_clock ClkProducer("ClkProducer", 10, SC_NS, 0.5, 1, SC_NS); //Producer Clock
  sc_clock ClkConsumer("ClkConsumer", 20, SC_NS, 0.5, 1, SC_NS); //Consumer Clock

  fifo<sc_int<8>> Fifo1("F1", 4); //size 4


  producer<sc_int<8>> P1("P1");
  P1.out(Fifo1);
  P1.Clock(ClkProducer);


  consumer<sc_int<8>> C1("C1");
  C1.in(Fifo1);
  C1.Clock(ClkConsumer);

  // run for 1001 seconds
  sc_start(201, SC_NS);

  return 0;
}