#include "systemc.h"
#include "fifo_if.h"

template <class T> class producer : public sc_module 
{
public:
  sc_port < fifo_out_if<T> > out;
  sc_in_clk Clock; 

  void do_writes()
  {
    T data = 0;
    int i = 0; 
    while (true) 
    { 
      //cout << "In Producer" << endl;
      if (out->write(data)){ 
        cout << "W " << data << " at " << sc_time_stamp() << endl;
      }
      data = (data+1) % 10; // 0-9, size 10
      wait(); 
    }
  }

  SC_CTOR(producer)
  {
  SC_THREAD(do_writes);
  sensitive << Clock.pos(); dont_initialize();
  }
};

